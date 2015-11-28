/********************************************************************
	created:	2014/10/31
	file base:	FKCW_Network_Packet
	author:		FreeKnight
	
	purpose:	
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include "FKCW_Network_Macros.h"
//--------------------------------------------------------------------
class FKCW_Network_Packet : public CCObject
{
public:
	typedef struct SHeader
	{
		char magic[4];
		int protocolVersion;
		int serverVersion;
		int command;
		int encryptAlgorithm;
		int length;					// ͷ��֮������ݳ���
	}PACKET_HEADER;

	CC_SYNTHESIZE_PASS_BY_REF_NC(SHeader, m_Header, Header);
	CC_SYNTHESIZE(char*, m_pBuffer, Buffer);
	CC_SYNTHESIZE_READONLY(size_t, m_unPacketLength, PacketLength);
	CC_SYNTHESIZE_READONLY(bool, m_bIsRaw, Raw);
protected:
	FKCW_Network_Packet();

	virtual bool	InitWithStandardBuf( const char* p_szBuf, size_t p_unLen );
	virtual bool	InitWithRawBuf( const char* p_szBuf, size_t p_unLen, int p_nAlgorithm );
	virtual bool	InitWithJson( const string& p_strMagic, int p_nCommand, FKCW_Json_Object* p_pJson,
		int p_nProtocolVersion, int p_nServerVersion, int p_nAlgorithm );

	// ����һ���ڴ�
	void			Allocate( size_t p_unLen );
	// д��Ϣͷ
	void			WriteHeader();
public:
	virtual			~FKCW_Network_Packet();
	// ͨ��һ����׼���洴��һ��ͷ
	static FKCW_Network_Packet* CreateStandardPacket( const char* p_szBuf, size_t p_unLen );
	// ����һ��������ͷ��ԭʼ���ݰ������������ڴ�socket���յ���ԭʼ���ݡ�
	// ע����������Ҫ���ܣ������� p_nAlgorithm ������Ĭ��-1��ʾ������ԭʼ����
	static FKCW_Network_Packet* CreateRawPacket( const char* p_szBuf, size_t p_unLen, int p_nAlgorithm = -1 );
	// ����һ����׼��Ϣ�����������Դ��һ�� json ����
	static FKCW_Network_Packet* CreateStandardPacket( const string& p_strMagic, int p_nCommand, 
		FKCW_Json_Object* p_pJson, int p_nAlgorithm = -1 );
	static FKCW_Network_Packet* CreateStandardPacket( const string& p_strMagic, int p_nCommand, 
		FKCW_Json_Object* p_pJson, int p_nProtocolVersion, int p_nServerVersion, int p_nAlgorithm = -1 );

	// ��ȡ��Ϣ����Ĵ�С
	int				GetBodyLength();
	// ��ȡ��Ϣ����ָ��
	const char*		GetBody();
};