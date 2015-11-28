//--------------------------------------------------------------------
#include "../Include/FKCW_IO_MemoryOutputStream.h"
//--------------------------------------------------------------------
FKCW_IO_MemoryOutputStream::FKCW_IO_MemoryOutputStream( char* p_szBuffer, size_t p_unCapacity, bool p_bIsSelfRelease )
	: m_szBuffer( p_szBuffer )
	, m_unCapacity( p_unCapacity )
	, m_unLength( 0 )
	, m_unPosition( 0 )
	, m_bIsSelfRelease( p_bIsSelfRelease )
{

}
//--------------------------------------------------------------------
// ȷ�������������㹻дlen���ֽ�
void FKCW_IO_MemoryOutputStream::_EnsureCapacity( size_t p_unLen )
{
	if(m_unPosition + p_unLen > m_unCapacity - 1) 
	{
		m_unCapacity = (m_unPosition + p_unLen) * 2;
		m_szBuffer = (char*)realloc(m_szBuffer, m_unCapacity * sizeof(char));
	}
}
//--------------------------------------------------------------------
FKCW_IO_MemoryOutputStream::FKCW_IO_MemoryOutputStream()
	: m_unCapacity( 16 * 1024 )
	, m_unLength( 0 )
	, m_unPosition( 0 ),
	m_bIsSelfRelease( true )
{
	m_szBuffer = ( char* )malloc( m_unCapacity * sizeof(char) );
}
//--------------------------------------------------------------------
FKCW_IO_MemoryOutputStream::~FKCW_IO_MemoryOutputStream()
{
	if( m_bIsSelfRelease )
	{
		free( (void*)m_szBuffer );
		m_szBuffer = NULL;
	}
}
//--------------------------------------------------------------------
// ����һ��Ĭ���ڴ���������û��汻���ڴ����������
FKCW_IO_MemoryOutputStream* FKCW_IO_MemoryOutputStream::Create()
{
	char* buffer = (char*)malloc(16 * 1024 * sizeof(char));
	FKCW_IO_MemoryOutputStream* s = new FKCW_IO_MemoryOutputStream(buffer, 16 * 1024, true);
	return (FKCW_IO_MemoryOutputStream*)s->autorelease();
}
//--------------------------------------------------------------------
// ����һ��ָ����С���ڴ������
// ע�����ڴ汻���������������δ���ɱ������ɾ����ɾ�����μ����� p_bIsSelfRelease��
FKCW_IO_MemoryOutputStream* FKCW_IO_MemoryOutputStream::Create( size_t p_unCapacity, bool p_bIsSelfRelease )
{
	char* buffer = (char*)malloc(p_unCapacity);
	FKCW_IO_MemoryOutputStream* s = new FKCW_IO_MemoryOutputStream(buffer, p_unCapacity, p_bIsSelfRelease);
	return (FKCW_IO_MemoryOutputStream*)s->autorelease();
}
//--------------------------------------------------------------------
// �رյ�ǰ�����
void FKCW_IO_MemoryOutputStream::Close()
{

}
//--------------------------------------------------------------------
// дһ������
// ����ֵ��-1 ����������ʵ��д��Ĵ�С
ssize_t FKCW_IO_MemoryOutputStream::Write( const char* p_pData, size_t p_nLen )
{
	_EnsureCapacity( p_nLen );
	memcpy( m_szBuffer + m_unPosition, p_pData, p_nLen );
	m_unPosition += p_nLen;
	m_unLength = MAX( m_unPosition, m_unLength );
	return p_nLen;
}
//--------------------------------------------------------------------
ssize_t FKCW_IO_MemoryOutputStream::Write( const int* p_pData, size_t p_nLen )
{
	_EnsureCapacity( p_nLen * sizeof(int));
	memcpy( m_szBuffer + m_unPosition, p_pData, p_nLen * sizeof(int) );
	m_unPosition += p_nLen * sizeof(int);
	m_unLength = MAX( m_unPosition, m_unLength );
	return p_nLen;
}
//--------------------------------------------------------------------
// ��ȡ��ǰ�����ļ�ͷ��ƫ����
size_t FKCW_IO_MemoryOutputStream::GetPosition()
{
	return m_unPosition;
}
//--------------------------------------------------------------------
// ���¶�ȡָ��λ��
// ������p_nOffset ƫ����
// ������p_nMode SEEK_CUR SEEK_END SEEK_SET ֮һ
// ����ֵ��ƫ��֮�󣬺��ļ�ͷ�����ƫ����
size_t FKCW_IO_MemoryOutputStream::Seek( int p_nOffset, int p_nMode )
{
	switch(p_nMode) 
	{
	case SEEK_CUR:
		m_unPosition = (size_t)clampf((float)m_unPosition + (float)p_nOffset, 0, (float)m_unLength);
		break;
	case SEEK_END:
		m_unPosition = (size_t)clampf((float)m_unLength + (float)p_nOffset, 0, (float)m_unLength);
		break;
	case SEEK_SET:
		m_unPosition = (size_t)clampf((float)p_nOffset, 0, (float)m_unLength);
		break;
	}

	return m_unPosition;
}
//--------------------------------------------------------------------
// ��ȡ��ǰ���������д����ڴ泤��
size_t FKCW_IO_MemoryOutputStream::GetLength()
{
	return m_unLength;
}
//--------------------------------------------------------------------
// ��ȡ��ǰ�����дָ��
const char* FKCW_IO_MemoryOutputStream::GetBuffer()
{
	m_szBuffer[m_unPosition] = 0;
	return m_szBuffer;
}
//--------------------------------------------------------------------
// ���������ָ�룬׼����д������
void FKCW_IO_MemoryOutputStream::Reset()
{
	m_unPosition = 0;
	m_unLength = 0;
}
//--------------------------------------------------------------------