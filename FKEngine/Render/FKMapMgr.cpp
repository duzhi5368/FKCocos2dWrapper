//-------------------------------------------------------------------------
#include "FKMapMgr.h"
#include "FKMapObj.h"
//-------------------------------------------------------------------------
FKBannerReelMapMgr::FKBannerReelMapMgr()
	: m_pCurMapObj( NULL )
	, m_pMapRootNode( NULL )
	, m_unMapID( 0 )
{
}
//-------------------------------------------------------------------------
FKBannerReelMapMgr::~FKBannerReelMapMgr()
{

}
//-------------------------------------------------------------------------
// ���ø���Ⱦ�ڵ㣬���г���ȫ���ҽ��ڱ��ڵ���
void FKBannerReelMapMgr::SetRoot( CCNode* pMapRootNode )
{
	m_pMapRootNode = pMapRootNode;
}
//-------------------------------------------------------------------------
// ��ȡ��ǰ�����еĵ�ͼ����
IMapObj* FKBannerReelMapMgr::GetCurrentMap()
{
	return m_pCurMapObj;
}
//-------------------------------------------------------------------------
// ���½����³���
// ������szFKMFileName ��ͼ�����ļ�
RENDER_MAP_ID FKBannerReelMapMgr::EnterMap( const char* szFKMFileName )
{
	if( m_pMapRootNode == NULL )
		return 0;
	CCDirector *pDirector = CCDirector::sharedDirector();
	if( pDirector == NULL )
		return 0;
	if( szFKMFileName == NULL )
		return 0;

	FKMapObj* pNewMap = NULL;
	// ������ID
	if( ++m_unMapID == 0 )
		++m_unMapID;

	pNewMap = new FKMapObj( m_unMapID );
	if( pNewMap == NULL )
		return 0 ;

	if( !pNewMap->InitFromFile(szFKMFileName) )
	{
		CC_SAFE_DELETE( pNewMap );
		return 0;
	}

	// �Ƴ���ǰ����
	if( m_pCurMapObj != NULL )
	{
		m_pMapRootNode->removeChild( (FKMapObj*)m_pCurMapObj, true );
		m_pCurMapObj = NULL;
	}

	pNewMap->autorelease();
	m_pMapRootNode->addChild( pNewMap );
	m_pCurMapObj = pNewMap;
	
	return m_pCurMapObj->GetID();
}
//-------------------------------------------------------------------------
// �Ƿ�����Update
void FKBannerReelMapMgr::SetEnableUpdate( bool bIsEnable )
{
	if( m_pCurMapObj )
	{
		m_pCurMapObj->SetEnableUpdate( bIsEnable );
	}
}
//-------------------------------------------------------------------------