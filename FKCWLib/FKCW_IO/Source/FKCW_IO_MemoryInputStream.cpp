//-------------------------------------------------------------------------
#include "../Include/FKCW_IO_MemoryInputStream.h"
//-------------------------------------------------------------------------
FKCW_IO_MemoryInputStream::FKCW_IO_MemoryInputStream(char* buffer, size_t length, bool release) 
	: m_szBuffer(buffer)
	, m_unLength(length)
	, m_bIsSelfRelease(release)
	, m_unPosition(0) 
{
}
//-------------------------------------------------------------------------
FKCW_IO_MemoryInputStream::~FKCW_IO_MemoryInputStream()
{
	if( m_bIsSelfRelease )
	{
		if( m_szBuffer )
		{
			free( m_szBuffer );
			m_szBuffer = NULL;
		}
	}
}
//-------------------------------------------------------------------------
FKCW_IO_MemoryInputStream* FKCW_IO_MemoryInputStream::Create( char* p_szBuffer, size_t p_unLength, bool p_bIsSelfRelease )
{
	FKCW_IO_MemoryInputStream* s = new FKCW_IO_MemoryInputStream(p_szBuffer, p_unLength, p_bIsSelfRelease);
	return (FKCW_IO_MemoryInputStream*)s->autorelease();
}
//-------------------------------------------------------------------------
// ��ȡ���ݻ�����ָ��
char* FKCW_IO_MemoryInputStream::GetBuffer()
{
	return m_szBuffer;
}
//-------------------------------------------------------------------------
// ��ȡ��ǰ�����ļ�ͷ��ƫ����
size_t FKCW_IO_MemoryInputStream::GetPosition()
{
	return m_unPosition;
}
//-------------------------------------------------------------------------
// ��ȡȫ���ݳ���
size_t FKCW_IO_MemoryInputStream::GetLength()
{
	return m_unLength;
}
//-------------------------------------------------------------------------
// ��ȡ��Ч���ݳ���
size_t FKCW_IO_MemoryInputStream::GetAvailableLength()
{
	return m_unLength - m_unPosition;
}
//-------------------------------------------------------------------------
// �ر�һ����Դ
void FKCW_IO_MemoryInputStream::Close()
{

}
//-------------------------------------------------------------------------
// ��ȡһ�����ݵ�������
// ����ֵ��-1 ����0 �����ݣ���ֵ ʵ�ʶ����������
ssize_t FKCW_IO_MemoryInputStream::Read( char* p_szBuffer, size_t p_unLength )
{
	int canRead = MIN(p_unLength, GetAvailableLength());
	memcpy(p_szBuffer, m_szBuffer + m_unPosition, canRead);
	m_unPosition += canRead;
	return canRead;
}
//-------------------------------------------------------------------------
// ���¶�ȡָ��λ��
// ������p_nOffset ƫ����
// ����ֵ��ƫ��֮�󣬺��ļ�ͷ�����ƫ����
size_t FKCW_IO_MemoryInputStream::Seek( int p_nOffset, int p_nMode )
{
	switch( p_nMode ) 
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
//-------------------------------------------------------------------------