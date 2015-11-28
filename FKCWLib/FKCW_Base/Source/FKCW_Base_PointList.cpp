//--------------------------------------------------------------------
#include "../Include/FKCW_Base_PointList.h"
//--------------------------------------------------------------------
FKCW_Base_PointList::FKCW_Base_PointList()
	: m_nCount( 0 )
	, m_nCapacity( 10 )
	, m_pBuffer( NULL )
{
	m_pBuffer = (CCPoint*)malloc( m_nCapacity * sizeof(CCPoint) );
}
//--------------------------------------------------------------------
FKCW_Base_PointList::~FKCW_Base_PointList()
{
	if( m_pBuffer )
	{
		free( m_pBuffer );
		m_pBuffer = NULL;
	}
}
//--------------------------------------------------------------------
FKCW_Base_PointList* FKCW_Base_PointList::Create()
{
	FKCW_Base_PointList* p = new FKCW_Base_PointList();
	if( p )
		p->autorelease();
	return p;
}
//--------------------------------------------------------------------
// ���һ����
void FKCW_Base_PointList::AddPoint( float x, float y )
{
	while( m_nCount >= m_nCapacity )
	{
		m_nCapacity *= 2;
		m_pBuffer = ( CCPoint* )realloc( m_pBuffer, m_nCapacity * sizeof( CCPoint ) );
	}
	m_pBuffer[m_nCount].x = x;
	m_pBuffer[m_nCount].y = y;
	m_nCount++;
}
//--------------------------------------------------------------------
// ���һ������
void FKCW_Base_PointList::AddPoints( FKCW_Base_PointList& p_pList )
{
	while( m_nCount + p_pList.GetCount() >= m_nCapacity )
	{
		m_nCapacity *= 2;
		m_pBuffer = ( CCPoint* )realloc( m_pBuffer, m_nCapacity * sizeof( CCPoint ) );
	}

	memcpy( m_pBuffer + m_nCount, p_pList.GetBuffer(), p_pList.GetCount() * sizeof(CCPoint) );
	m_nCount += p_pList.GetCount();
}
//--------------------------------------------------------------------
// ���ȫ����
void FKCW_Base_PointList::Clear()
{
	// ����û���ͷ�ԭ���ڴ棬���ڴ���ſ��޸����·����ڴ�
	m_nCount = 0;
}
//--------------------------------------------------------------------
// ��������ɾ��һ����
void FKCW_Base_PointList::DeletePointAt( int p_nIndex )
{
	if( p_nIndex < 0 || p_nIndex >= m_nCount )
		return;
	if( p_nIndex == m_nCount - 1 )
	{
		m_nCount--;
	}
	else
	{
		memmove( m_pBuffer + p_nIndex, m_pBuffer + p_nIndex + 1, 
			(m_nCount - p_nIndex - 1 ) * sizeof(CCPoint) );
		m_nCount--;
	}
}
//--------------------------------------------------------------------
//  ��ȡָ������λ��һ����
CCPoint FKCW_Base_PointList::GetPointAt( int p_nIndex )
{
	if( m_nCount > 0 )
	{
		p_nIndex = MAX( 0, min(m_nCount - 1, p_nIndex) );
		return m_pBuffer[p_nIndex];
	}
	else
	{
		return CCPointZero;
	}
}
//--------------------------------------------------------------------