//--------------------------------------------------------------------
#include "../Include/FKCW_Base_ByteBuffer.h"
//--------------------------------------------------------------------
#define DEFAULT_SIZE 0x1000
//--------------------------------------------------------------------
FKCW_Base_ByteBuffer::FKCW_Base_ByteBuffer()
	: m_pBuffer( NULL )
	, m_unReadPos( 0 )
	, m_unWritePos( 0 )
	, m_bExternal( false )
{
	_Reserve( DEFAULT_SIZE );
}
//--------------------------------------------------------------------
FKCW_Base_ByteBuffer::FKCW_Base_ByteBuffer( size_t p_unRes )
	: m_pBuffer( NULL )
	, m_unReadPos( 0 )
	, m_unWritePos( 0 )
	, m_bExternal( false )
{
	_Reserve( p_unRes );
}
//--------------------------------------------------------------------
FKCW_Base_ByteBuffer::FKCW_Base_ByteBuffer( const FKCW_Base_ByteBuffer& p_Other )
	: m_pBuffer( NULL )
	, m_unReadPos( 0 )
	, m_unWritePos( 0 )
	, m_bExternal( false )
{
	_Reserve( p_Other.m_unBufferSize );
	memcpy( p_Other.m_pBuffer, m_pBuffer, p_Other.m_unWritePos );
	m_unReadPos		= p_Other.m_unReadPos;
	m_unWritePos	= p_Other.m_unWritePos;
}
//--------------------------------------------------------------------
// ��������һ���ⲿ���ݣ��������Լ��ڷ��ڴ�
// ������p_szBuffer ������ p_unBufSize ��������С p_unDataLen �ڻ������еĿ�������
FKCW_Base_ByteBuffer::FKCW_Base_ByteBuffer( const char* p_szBuffer, size_t p_unBufSize, size_t p_unDataLen )
	: m_pBuffer( (uint8*)p_szBuffer )
	, m_unReadPos( 0 )
	, m_unWritePos( p_unDataLen )
	, m_bExternal( true )
	, m_unBufferSize( p_unBufSize )
{

}
//--------------------------------------------------------------------
FKCW_Base_ByteBuffer::~FKCW_Base_ByteBuffer()
{
	if( !m_bExternal )
	{
		CC_SAFE_FREE( m_pBuffer );
	}
}
//--------------------------------------------------------------------
// ����һ��Ĭ�ϴ�С�� FKCW_Base_ByteBuffer
FKCW_Base_ByteBuffer* FKCW_Base_ByteBuffer::Create()
{
	FKCW_Base_ByteBuffer* p = new FKCW_Base_ByteBuffer();
	return (FKCW_Base_ByteBuffer*)p->autorelease();
}
//--------------------------------------------------------------------
// ����һ��ָ����С�� FKCW_Base_ByteBuffer��
FKCW_Base_ByteBuffer* FKCW_Base_ByteBuffer::Create( size_t p_unRes )
{
	FKCW_Base_ByteBuffer* p = new FKCW_Base_ByteBuffer(p_unRes);
	return (FKCW_Base_ByteBuffer*)p->autorelease();
}
//--------------------------------------------------------------------
// ����һ���ƶ���С���ڴ�
void FKCW_Base_ByteBuffer::_Reserve( size_t p_unRes )
{
	if( m_bExternal )
		return;

	if( m_pBuffer )
		m_pBuffer = (uint8*)realloc( m_pBuffer, p_unRes );
	else
		m_pBuffer = (uint8*)malloc( p_unRes );

	m_unBufferSize = p_unRes;
}
//--------------------------------------------------------------------
// ȷ���������㹻���ܹ�дָ���ֽڴ�С������
void FKCW_Base_ByteBuffer::_EnsureCanWrite( size_t p_unSize )
{
	size_t new_size = m_unWritePos + p_unSize;
	if(new_size > m_unBufferSize) {
		new_size = (new_size / DEFAULT_INCREASE_SIZE + 1) * DEFAULT_INCREASE_SIZE;
		_Reserve(new_size);
	}
}
//--------------------------------------------------------------------
// ���ö�дָ��λ��
void FKCW_Base_ByteBuffer::Clear()
{
	m_unReadPos = m_unWritePos = 0;
}
//--------------------------------------------------------------------
// ���ػ�����ָ��
const uint8* FKCW_Base_ByteBuffer::GetBuffer()
{
	return m_pBuffer;
}
//--------------------------------------------------------------------
// ��ȡ�ɶ������С
size_t FKCW_Base_ByteBuffer::GetAvailable()
{
	return m_unWritePos - m_unReadPos;
}
//--------------------------------------------------------------------
// ��ǰ�ƶ���ָ��
void FKCW_Base_ByteBuffer::Skip( size_t p_unLen )
{
	if(m_unReadPos + p_unLen > m_unWritePos)
		p_unLen = (m_unWritePos - m_unReadPos);
	m_unReadPos += p_unLen;
}
//--------------------------------------------------------------------
// ����ƶ���ָ��
void FKCW_Base_ByteBuffer::Revoke( size_t p_unLen )
{
	m_unReadPos -= p_unLen;
	m_unReadPos = MAX(0, m_unReadPos);
}
//--------------------------------------------------------------------
// �ƶ���ǰ���ݵ��������ײ�
void FKCW_Base_ByteBuffer::Compact()
{
	if( m_unReadPos >  0 )
	{
		memmove( m_pBuffer, m_pBuffer + m_unReadPos, GetAvailable() );
		m_unWritePos -= m_unReadPos;
		m_unReadPos = 0;
	}
}
//--------------------------------------------------------------------
// �ӻ�������ȡָ����С�����ݣ�����ȡLen�����˻�������С������������������ֽ�
// ����ֵ������ʵ�ʶ�ȡ���ֽ���
size_t FKCW_Base_ByteBuffer::Read( uint8* p_pBuffer, size_t p_unLen )
{
	if( m_unReadPos + p_unLen > m_unWritePos )
		p_unLen = ( m_unWritePos - m_unReadPos );

	memcpy( p_pBuffer, &m_pBuffer[m_unReadPos], p_unLen );
	m_unReadPos += p_unLen;
	return p_unLen;
}
//--------------------------------------------------------------------
// ��ȡһ��string
void FKCW_Base_ByteBuffer::Read( string& p_strDest )
{
	ReadCString( p_strDest );
}
//--------------------------------------------------------------------
// ��ȡһ��C string
void FKCW_Base_ByteBuffer::ReadCString( string& p_strDest )
{
	p_strDest.clear();
	char c;
	while( true )
	{
		c = Read<char>();
		if( c == 0 )
			break;
		p_strDest += c;
	}
}
//--------------------------------------------------------------------
// ��ȡһ��pascal �ַ�������ǰ�����ֽڱ������ַ�������
void FKCW_Base_ByteBuffer::ReadPascalString( string& p_strDest )
{
	p_strDest.clear();
	uint16 len = Read<uint16>();
	while(len-- > 0) 
	{
		p_strDest += Read<char>();
	}
}
//--------------------------------------------------------------------
// ��ȡһ���ַ��������ǵ������л��ߵ��˽�β�Ż�ֹͣ
void FKCW_Base_ByteBuffer::ReadLine( string& p_strDest )
{
	p_strDest.clear();
	char c;
	while(m_unReadPos < m_unBufferSize)	
	{
		c = Read<char>();
		if(c == '\r')
			continue;
		else if(c == 0 || c == '\n')
			break;
		p_strDest += c;
	}
}
//--------------------------------------------------------------------
// д��ָ��������
void FKCW_Base_ByteBuffer::Write( const uint8* p_pData, size_t p_unSize )
{
	size_t new_size = m_unWritePos + p_unSize;
	if(new_size > m_unBufferSize) 
	{
		if(m_bExternal) 
		{
			CCLOGWARN("external mode: buffer size is not enough to write");
			return;
		}
		new_size = (new_size / DEFAULT_INCREASE_SIZE + 1) * DEFAULT_INCREASE_SIZE;
		_Reserve(new_size);
	}

	memcpy(&m_pBuffer[m_unWritePos], p_pData, p_unSize);
	m_unWritePos += p_unSize;
}
//--------------------------------------------------------------------
// д��һ��string
void FKCW_Base_ByteBuffer::Write( const string& p_strData )
{
	WriteCString( p_strData );
}
//--------------------------------------------------------------------
// д��һ��C string
void FKCW_Base_ByteBuffer::WriteCString( const string& p_strData )
{
	if(m_unWritePos + p_strData.length() + 1 > m_unBufferSize) 
	{
		if(m_bExternal) 
		{
			CCLOGWARN("external mode: buffer size is not enough to write");
			return;
		}
		_EnsureCanWrite(p_strData.length() + 1);
	}

	memcpy(&m_pBuffer[m_unWritePos], p_strData.c_str(), p_strData.length() + 1);
	m_unWritePos += (p_strData.length() + 1);
}
//--------------------------------------------------------------------
// д��һ��pascal �ַ�������ǰ�����ֽڱ������ַ������ȣ���ע�⣬�ַ�������β����0
void FKCW_Base_ByteBuffer::WritePascalString( const string& p_strData )
{
	if(m_unWritePos + p_strData.length() + sizeof(uint16) > m_unBufferSize) 
	{
		if(m_bExternal) 
		{
			CCLOGWARN("external mode: buffer size is not enough to write");
			return;
		}
		_EnsureCanWrite(p_strData.length() + sizeof(uint16));
	}

	Write<uint16>(p_strData.length());
	memcpy(&m_pBuffer[m_unWritePos], p_strData.c_str(), p_strData.length());
	m_unWritePos += p_strData.length();
}
//--------------------------------------------------------------------
// д��һ��string������
void FKCW_Base_ByteBuffer::WriteLine( const string& p_strData )
{
	if(m_unWritePos + p_strData.length() + 2 * sizeof(char) > m_unBufferSize) 
	{
		if(m_bExternal) 
		{
			CCLOGWARN("external mode: buffer size is not enough to write");
			return;
		}
		_EnsureCanWrite(p_strData.length() + 2 * sizeof(char));
	}

	memcpy(&m_pBuffer[m_unWritePos], p_strData.c_str(), p_strData.length());
	m_unWritePos += p_strData.length();
	Write<char>('\r');
	Write<char>('\n');
}
//--------------------------------------------------------------------
// ��ȡ��ָ��λ��
size_t FKCW_Base_ByteBuffer::GetReadPos()
{
	return m_unReadPos;
}
//--------------------------------------------------------------------
// ���ö�ָ��
void FKCW_Base_ByteBuffer::SetReadPos( size_t p_unPos )
{
	if(p_unPos <= m_unWritePos) 
		m_unReadPos = p_unPos;
}
//--------------------------------------------------------------------
// ����дָ��
void FKCW_Base_ByteBuffer::SetWritePos( size_t p_unPos )
{
	if(p_unPos <= m_unBufferSize)
		m_unWritePos = p_unPos;
}
//--------------------------------------------------------------------