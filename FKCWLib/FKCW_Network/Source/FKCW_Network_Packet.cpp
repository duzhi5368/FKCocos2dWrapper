//--------------------------------------------------------------------
#include "../Include/FKCW_Network_Packet.h"
#include "../Include/FKCW_Network_NetworkCommon.h"
#include "../Include/FKCW_Network_TCPSocketHub.h"
#include "../../FKCW_Base/Include/FKCW_Base_Macro.h"
//--------------------------------------------------------------------
FKCW_Network_Packet::FKCW_Network_Packet()
	: m_pBuffer( NULL )
	, m_unPacketLength( 0 )
	, m_bIsRaw( false )
{
	memset( &m_Header, 0, sizeof(m_Header) );
}
//--------------------------------------------------------------------
FKCW_Network_Packet::~FKCW_Network_Packet()
{
	CC_SAFE_FREE( m_pBuffer );
}
//--------------------------------------------------------------------
// ͨ��һ����׼���洴��һ��ͷ
FKCW_Network_Packet* FKCW_Network_Packet::CreateStandardPacket( const char* p_szBuf, size_t p_unLen )
{
	if( p_unLen < PacketHeaderLength )
		return NULL;

	FKCW_Network_Packet* p = new FKCW_Network_Packet();
	if( p->InitWithStandardBuf(p_szBuf, p_unLen) )
	{
		return (FKCW_Network_Packet*)p->autorelease();
	}
	CC_SAFE_FREE( p );
	return NULL;
}
//--------------------------------------------------------------------
// ����һ��������ͷ��ԭʼ���ݰ������������ڴ�socket���յ���ԭʼ���ݡ�
// ע����������Ҫ���ܣ������� p_nAlgorithm ������Ĭ��-1��ʾ������ԭʼ����
FKCW_Network_Packet* FKCW_Network_Packet::CreateRawPacket( const char* p_szBuf, size_t p_unLen, int p_nAlgorithm )
{
	FKCW_Network_Packet* p = new FKCW_Network_Packet();
	if( p->InitWithRawBuf(p_szBuf, p_unLen, p_nAlgorithm) )
	{
		return (FKCW_Network_Packet*)p->autorelease();
	}
	CC_SAFE_FREE( p );
	return NULL;
}
//--------------------------------------------------------------------
// ����һ����׼��Ϣ�����������Դ��һ�� json ����
FKCW_Network_Packet* FKCW_Network_Packet::CreateStandardPacket( const string& p_strMagic, int p_nCommand, 
												 FKCW_Json_Object* p_pJson, int p_nAlgorithm )
{
	FKCW_Network_Packet* p = new FKCW_Network_Packet();
	if( p->InitWithJson( p_strMagic, p_nCommand, p_pJson, 0, 0, p_nAlgorithm ) )
	{
		return (FKCW_Network_Packet*)p->autorelease();
	}
	CC_SAFE_FREE( p );
	return NULL;
}
//--------------------------------------------------------------------
FKCW_Network_Packet* FKCW_Network_Packet::CreateStandardPacket( const string& p_strMagic, int p_nCommand, 
	FKCW_Json_Object* p_pJson, int p_nProtocolVersion, int p_nServerVersion, int p_nAlgorithm )
{
	FKCW_Network_Packet* p = new FKCW_Network_Packet();
	if( p->InitWithJson( p_strMagic, p_nCommand, p_pJson, p_nProtocolVersion, p_nServerVersion, p_nAlgorithm ) )
	{
		return (FKCW_Network_Packet*)p->autorelease();
	}
	CC_SAFE_FREE( p );
	return NULL;
}
//--------------------------------------------------------------------
bool FKCW_Network_Packet::InitWithStandardBuf( const char* p_szBuf, size_t p_unLen )
{
	if(p_unLen < PacketHeaderLength)
		return false;
	
	// ��Ϣͷ
	FKCW_Base_ByteBuffer bb(p_szBuf, p_unLen, p_unLen);
	m_Header.magic[0] = bb.Read<char>();
	m_Header.magic[1] = bb.Read<char>();
	m_Header.magic[2] = bb.Read<char>();
	m_Header.magic[3] = bb.Read<char>();
	m_Header.protocolVersion	= betoh32(bb.Read<int>());
	m_Header.serverVersion		= betoh32(bb.Read<int>());
	m_Header.command			= betoh32(bb.Read<int>());
	m_Header.encryptAlgorithm	= betoh32(bb.Read<int>());
	m_Header.length				= betoh32(bb.Read<int>());

	// ��Ϣbody
	if(bb.GetAvailable() >= static_cast<size_t>(m_Header.length)) 
	{
		if(FKCW_Network_TCPSocketHub::GetDecryptFunc()) 
		{
			// ��ȡbody�����Խ���
			char* body = (char*)malloc(m_Header.length * sizeof(char));
			bb.Read((uint8*)body, m_Header.length);
			size_t plainLen;
			char* plain = (char*)(*FKCW_Network_TCPSocketHub::GetDecryptFunc())(body, 
				m_Header.length, &plainLen, m_Header.encryptAlgorithm);
			if(plain != body)
				free(body);

			// ������������
			Allocate(plainLen + PacketHeaderLength + 1);
			memcpy(m_pBuffer + PacketHeaderLength, plain, plainLen);
			m_Header.length = (int)plainLen;
			free(plain);
		} 
		else
		{
			Allocate(m_Header.length + PacketHeaderLength + 1);
			bb.Read((uint8*)m_pBuffer + PacketHeaderLength, m_Header.length);
		}
	}
	else 
	{
		return false;
	}

	// ��ʼ������һЩ��Ϣ
	m_bIsRaw = false;
	m_unPacketLength = m_Header.length + PacketHeaderLength;

	// д��ͷ��
	WriteHeader();

	return true;
}
//--------------------------------------------------------------------
bool FKCW_Network_Packet::InitWithRawBuf( const char* p_szBuf, size_t p_unLen, int p_nAlgorithm )
{
	if(FKCW_Network_TCPSocketHub::GetDecryptFunc() && p_nAlgorithm != -1)
	{
		// ��ȡbody�����Խ���
		size_t plainLen;
		char* plain = (char*)(*FKCW_Network_TCPSocketHub::GetDecryptFunc())
			(p_szBuf, p_unLen, &plainLen, p_nAlgorithm);

		// ��������Ϣ������
		Allocate(plainLen + 1);
		memcpy(m_pBuffer, plain, plainLen);
		m_Header.length = (int)plainLen;
		if(plain != p_szBuf)
			free(plain);
	} 
	else 
	{
		m_Header.length = (int)p_unLen;
		Allocate(p_unLen + 1);
		memcpy(m_pBuffer, p_szBuf, p_unLen);
	}

	// ����
	m_bIsRaw = true;
	m_unPacketLength = m_Header.length;

	return true;
}
//--------------------------------------------------------------------
bool FKCW_Network_Packet::InitWithJson( const string& p_strMagic, int p_nCommand, FKCW_Json_Object* p_pJson,
							 int p_nProtocolVersion, int p_nServerVersion, int p_nAlgorithm )
{
	// ���ħ��
	if( p_strMagic.length() < 4 )
		return false;

	m_Header.magic[0] = p_strMagic.at(0);
	m_Header.magic[1] = p_strMagic.at(1);
	m_Header.magic[2] = p_strMagic.at(2);
	m_Header.magic[3] = p_strMagic.at(3);

	// Э��汾
	m_Header.protocolVersion		= p_nProtocolVersion;
	// �������汾
	m_Header.serverVersion			= p_nServerVersion;
	// ID
	m_Header.command				= p_nCommand;
	// ����
	m_Header.encryptAlgorithm		= p_nAlgorithm;
	
	// ��Ϣ����
	string strBodyStr = p_pJson->ToString();
	char* plain = (char*)strBodyStr.c_str();
	if(FKCW_Network_TCPSocketHub::GetEncryptFunc() && p_nAlgorithm != -1)
	{
		// ��Ҫ���ܣ����ȼ���body
		size_t bodyLen = strBodyStr.length();
		size_t encLen;
		const char* enc = (*FKCW_Network_TCPSocketHub::GetEncryptFunc())(plain, bodyLen, &encLen, p_nAlgorithm);
		Allocate(encLen + PacketHeaderLength + 1);
		memcpy(m_pBuffer + PacketHeaderLength, enc, encLen);
		if(enc != plain) 
		{
			free((void*)enc);
		}

		// ��Ϣ����
		m_Header.length = (int)encLen;
		m_unPacketLength = encLen + PacketHeaderLength;
	} 
	else 
	{
		// ����Ҫ����
		m_Header.length = (int)strBodyStr.length();
		Allocate(strBodyStr.length() + PacketHeaderLength + 1);
		memcpy(m_pBuffer + PacketHeaderLength, plain, strBodyStr.length());
		m_unPacketLength = strBodyStr.length() + PacketHeaderLength;
	}

	// д��ͷ����Ϣ
	WriteHeader();

	// ��ʼ��
	m_bIsRaw = false;

	return true;

}
//--------------------------------------------------------------------
// ����һ���ڴ�
void FKCW_Network_Packet::Allocate( size_t p_unLen )
{
	if( !m_pBuffer )
		m_pBuffer = (char*)calloc( p_unLen, sizeof(char) );
}
//--------------------------------------------------------------------
// д��Ϣͷ
void FKCW_Network_Packet::WriteHeader()
{
	FKCW_Base_ByteBuffer bb(m_pBuffer, m_unPacketLength, 0);

	// ħ��
	bb.Write<char>(m_Header.magic[0]);
	bb.Write<char>(m_Header.magic[1]);
	bb.Write<char>(m_Header.magic[2]);
	bb.Write<char>(m_Header.magic[3]);

	bb.Write<int>(htobe32(m_Header.protocolVersion));
	bb.Write<int>(htobe32(m_Header.serverVersion));
	bb.Write<int>(htobe32(m_Header.command));
	bb.Write<int>(htobe32(m_Header.encryptAlgorithm));
	bb.Write<int>(htobe32(m_Header.length));
}
//--------------------------------------------------------------------
// ��ȡ��Ϣ����Ĵ�С
int FKCW_Network_Packet::GetBodyLength()
{
	return m_Header.length;
}
//--------------------------------------------------------------------
// ��ȡ��Ϣ����ָ��
const char* FKCW_Network_Packet::GetBody()
{
	if( m_bIsRaw )
		return m_pBuffer;
	else
		return m_pBuffer + PacketHeaderLength;
}
//--------------------------------------------------------------------