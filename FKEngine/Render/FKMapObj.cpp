//-------------------------------------------------------------------------
#include "FKMapObj.h"
#include "FKMapStruct.h"

#include "FKBackgroundLayer.h"
#include "FKFarLayer.h"
#include "FKFrontLayer.h"
#include "FKCameraMaskLayer.h"
#include "FKBarrierLayer.h"
#include "FKCameraLayer.h"
#include "FKMaskLayer.h"
#include "FKEventLayer.h"
#include "FKNormalLayer.h"
#include "FKRenderObj.h"
//-------------------------------------------------------------------------
FKMapObj::FKMapObj( RENDER_MAP_ID id )
	: m_bIsUseDebugRender( false )
	, m_unRenderObjSceneID( 0 )
{
	m_pMapInfo = new SMapInfo();
	if( m_pMapInfo )
	{
		m_pMapInfo->unMapID = id;
	}
	m_AllLayers.clear();
}
//-------------------------------------------------------------------------
FKMapObj::~FKMapObj()
{
	CC_SAFE_DELETE( m_pMapInfo );
}
//-------------------------------------------------------------------------
void FKMapObj::update( float dt )
{
	if( !m_bIsNeedUpdate )
		return;

	map<RENDER_MAP_ID,FKMapLayer*>::iterator Ite = m_AllLayers.begin();
	for( ; Ite != m_AllLayers.end(); ++Ite )
	{
		if( Ite->second )
			Ite->second->Update( dt );
	}
}
//-------------------------------------------------------------------------
void FKMapObj::onEnter()
{
	CCNode::onEnter();

	scheduleUpdate();
}
//-------------------------------------------------------------------------
void FKMapObj::onExit()
{
	CCNode::onExit();

	unscheduleUpdate();
}
//-------------------------------------------------------------------------
// ��һ��FKM��Դ�ļ�����
bool FKMapObj::InitFromFile( const char* szFKMFileName )
{
	// TODO:
	return false;
}
//-------------------------------------------------------------------------
// д�뵽һ����Դ�ļ�
bool FKMapObj::WriteToFile( const char* szFileName )
{
	// TODO:
	return false;
}
//-------------------------------------------------------------------------
// ���һ��Obj
unsigned int FKMapObj::AddObj( RENDER_MAP_LAYER_ID id, IRenderObj* pObj )
{
	FKMapLayer* pLayer = (FKMapLayer*)GetLayerByID( id );
	if( pLayer == nullptr )
		return 0;
	if( ++m_unRenderObjSceneID == 0 )
		++m_unRenderObjSceneID;
	IRenderObj* p = GetObjByID( id );
	while( p != NULL )
	{
		if( ++m_unRenderObjSceneID == 0 )
			++m_unRenderObjSceneID;
		p = GetObjByID( id );
	}

	if( pLayer->AddObj( m_unRenderObjSceneID, pObj ))
	{
		return m_unRenderObjSceneID;
	}
	return 0;
}
//-------------------------------------------------------------------------
// ��̬����Objλ��
void FKMapObj::SetObjPos( RENDER_MAP_CHUNK_ID id, const CCPoint& tagPos )
{
	IRenderObj* p = NULL;
	IMapLayer* pLayer = NULL;
	map<RENDER_MAP_ID,FKMapLayer*>::iterator Ite = m_AllLayers.begin();
	for( ; Ite != m_AllLayers.end(); ++Ite )
	{
		if( Ite->second )
		{
			p = Ite->second->GetObjByID( id );
			if( p != NULL )
			{
				pLayer = Ite->second;
				break;
			}
		}
	}
	if( p != nullptr && pLayer != NULL )
	{
		pLayer->SetObjPos( id, tagPos );
	}	
}
//-------------------------------------------------------------------------
// ��ȡ��ȾObj
IRenderObj*	FKMapObj::GetObjByID( RENDER_MAP_CHUNK_ID id )
{
	IRenderObj* p = NULL;
	map<RENDER_MAP_ID,FKMapLayer*>::iterator Ite = m_AllLayers.begin();
	for( ; Ite != m_AllLayers.end(); ++Ite )
	{
		if( Ite->second )
		{
			p = Ite->second->GetObjByID( id );
			if( p != NULL )
			{
				return p;
			}
		}
	}

	return NULL;
}
//-------------------------------------------------------------------------
// �Ƴ���ȾObj
void FKMapObj::RemoveObjByID( RENDER_MAP_CHUNK_ID id )
{
	IRenderObj* p = NULL;
	IMapLayer* pLayer = NULL;
	map<RENDER_MAP_ID,FKMapLayer*>::iterator Ite = m_AllLayers.begin();
	for( ; Ite != m_AllLayers.end(); ++Ite )
	{
		if( Ite->second )
		{
			p = Ite->second->GetObjByID( id );
			if( p != NULL )
			{
				pLayer = Ite->second;
				break;
			}
		}
	}
	if( p != nullptr && pLayer != NULL )
	{
		pLayer->RemoveObjByID( id );
	}	
}
//-------------------------------------------------------------------------
// ��ȡָ����
IMapLayer* FKMapObj::GetLayerByID( RENDER_MAP_LAYER_ID id )
{
	map<RENDER_MAP_ID,FKMapLayer*>::iterator Ite = m_AllLayers.find( id );
	if( Ite == m_AllLayers.end() )
		return NULL;
	if( Ite->second == NULL )
		return NULL;
	return Ite->second;
}
//-------------------------------------------------------------------------
// ת����Ļ���굽��������
void FKMapObj::ConvertScreenPos2ScenePos( const CCPoint& screenPos,
												  CCPoint& scenePos )
{
	if( GetCameraSystem() == NULL )
		return;
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint ptCenterPos = CCPointZero;
	ptCenterPos.x = visibleSize.width / 2;
	ptCenterPos.y = visibleSize.height / 2;
	CCPoint ptCameraPos = ptCenterPos;
	GetCameraSystem()->GetViewport( ptCameraPos );
	scenePos.x = ( screenPos.x - ptCenterPos.x ) + ptCameraPos.x;
	scenePos.y = ( screenPos.y - ptCenterPos.y ) + ptCameraPos.y;
	return;
}
//-------------------------------------------------------------------------
inline bool		listRenderObjZOrderCmp( const IRenderObj* lhs, const IRenderObj* rhs )
{
	if( lhs == NULL || rhs == NULL )
		return false;
	return ((FKRenderObj*)lhs)->getVertexZ() > ((FKRenderObj*)rhs)->getVertexZ();
}
// ��ײѡȡ���
void FKMapObj::HitTestObj( const CCPoint& pt, list<IRenderObj*>& ObjList )
{
	set<IRenderObj*>	setRenderObjs;
	setRenderObjs.clear();
	list<IRenderObj*>	listObjs;
	listObjs.clear();

	GetRenderObjsSet( setRenderObjs );

	set<IRenderObj*>::iterator Ite = setRenderObjs.begin();
	for( ; Ite != setRenderObjs.end(); ++Ite )
	{
		if( *Ite == NULL )
			continue;
		if( (*Ite)->HitTest(pt) )
		{
			listObjs.push_back( *Ite );
		}
	}

	if( listObjs.empty() )
		return;

	listObjs.sort( listRenderObjZOrderCmp );
	ObjList = listObjs;

	return;
}
//-------------------------------------------------------------------------
// ��ȡ����ID
RENDER_MAP_ID FKMapObj::GetID()
{
	if( m_pMapInfo == NULL )
		return 0;
	return m_pMapInfo->unMapID;
}
//-------------------------------------------------------------------------
// ��ȡ�����ļ���
void FKMapObj::GetSceneFileName( string& strFileName )
{
	if( m_pMapInfo == NULL )
		strFileName.clear();
	strFileName = m_pMapInfo->strMapFileName;
}
//-------------------------------------------------------------------------
// ����/�ر�DEBUG��Ⱦ
void FKMapObj::SetDebugRender( bool bIsUseDebugRender )
{
	m_bIsUseDebugRender = bIsUseDebugRender;

	map<RENDER_MAP_ID,FKMapLayer*>::iterator Ite = m_AllLayers.begin();
	for( ; Ite != m_AllLayers.end(); ++Ite )
	{
		if( Ite->second )
			Ite->second->SetDebugRender( bIsUseDebugRender );
	}
}
//-------------------------------------------------------------------------
// ��ȡ����ͼ��ȫ����Ⱦ�����б�
void FKMapObj::GetRenderObjsSet( set<IRenderObj*>& SetRenderObjs )
{
	// TODO:
}
//-------------------------------------------------------------------------
// �Ƿ�����Update
void FKMapObj::SetEnableUpdate( bool bIsEnable )
{
	if( m_bIsNeedUpdate == bIsEnable )
		return;

	if( bIsEnable )
		scheduleUpdate();
	else
		unscheduleUpdate();

	m_bIsNeedUpdate = bIsEnable;
}
//-------------------------------------------------------------------------