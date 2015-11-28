//-------------------------------------------------------------------------
#include "FKMapLayer.h"
#include "FKMapStruct.h"
#include "FKMapChunk.h"
//-------------------------------------------------------------------------
FKMapLayer::FKMapLayer( RENDER_MAP_LAYER_ID id )
	: m_bIsOpenDebug( false )
	, m_unCurChunkID( 0 )
	, m_bIsNeedUpdateChunk( false )
{
	m_pMapLayerInfo = new SMapLayerInfo();
	if( m_pMapLayerInfo )
	{
		m_pMapLayerInfo->unLayerID = id;
	}
	m_mapChunks.clear();
	m_setVisiableChunks.clear();
	m_setRenderedChunks.clear();
}
//-------------------------------------------------------------------------
FKMapLayer::~FKMapLayer()
{
	Release();
	CC_SAFE_DELETE( m_pMapLayerInfo );
}
//-------------------------------------------------------------------------
// �ͷ�
void FKMapLayer::Release()
{
	ChunksMap::iterator Ite = m_mapChunks.begin();
	for( ; Ite != m_mapChunks.end(); ++Ite )
	{
		if( Ite->second )
		{
			removeChild( (FKMapChunk*)Ite->second );

			Ite->second->Release();
			delete Ite->second;
			Ite->second = NULL;
		}
	}
	m_mapChunks.clear();

	m_setVisiableChunks.clear();
}
//-------------------------------------------------------------------------
// ֡����
void FKMapLayer::Update( float dt )
{
	ChunksSet::iterator Ite = m_setRenderedChunks.begin();
	for( ; Ite != m_setRenderedChunks.end(); ++Ite )
	{
		ChunksMap::iterator IteChunk = m_mapChunks.find( *Ite );
		if( IteChunk == m_mapChunks.end() )
			continue;

		if( IteChunk->second == NULL )
			continue;

		((FKMapChunk*)IteChunk->second)->Update( dt );
	}

	if( m_bIsNeedUpdateChunk )
	{
		CullVisiableChunks();
		m_bIsNeedUpdateChunk = false;
	}
}
//-------------------------------------------------------------------------
// ���ò�ID
void FKMapLayer::SetLayerID( unsigned int unLayerID )
{
	if( m_pMapLayerInfo )
		m_pMapLayerInfo->unLayerID = unLayerID;
}
//-------------------------------------------------------------------------
// ��ȡ��ID
unsigned int FKMapLayer::GetLayerID() const
{
	if( m_pMapLayerInfo )
		return m_pMapLayerInfo->unLayerID;
	return 0;
}
//-------------------------------------------------------------------------
// ���ò���
void FKMapLayer::SetLayerDepth( int nLayerDepth )
{
	if( m_pMapLayerInfo )
		m_pMapLayerInfo->nDepth  = nLayerDepth;
	setZOrder( nLayerDepth );
}
//-------------------------------------------------------------------------
// ��ȡ����
int FKMapLayer::GetLayerDepth()
{
	if( m_pMapLayerInfo )
		return m_pMapLayerInfo->nDepth;
	return getZOrder();
}
//-------------------------------------------------------------------------
// ��ȡ������
int FKMapLayer::GetLayerType()
{
	return eMILT_Max;
}
//-------------------------------------------------------------------------
// ��ȡ������Ӳ�
float FKMapLayer::GetLayerHeightParallax()
{
	if( m_pMapLayerInfo )
		return m_pMapLayerInfo->fHeightParallax;
	return 1.0f;
}
//-------------------------------------------------------------------------
// ��ȡ�������Ӳ�
float FKMapLayer::GetLayerWidthParallax()
{
	if( m_pMapLayerInfo )
		return m_pMapLayerInfo->fWidthParallax;
	return 0.0f;
}
//-------------------------------------------------------------------------
// ���ò�����Ӳ�
void FKMapLayer::SetLayerHeightParallax( float fParallax )
{
	if( m_pMapLayerInfo )
		m_pMapLayerInfo->fHeightParallax = fParallax;
}
//-------------------------------------------------------------------------
// ���ò������Ӳ�
void FKMapLayer::GetLayerHeightParallax( float fParallax )
{
	if( m_pMapLayerInfo )
		m_pMapLayerInfo->fWidthParallax = fParallax;
}
//-------------------------------------------------------------------------
// ����/�ر�DEBUG��Ⱦ
void FKMapLayer::SetDebugRender( bool bIsUseDebugRender )
{
	// ֪ͨ�ӿ�
	if( m_bIsOpenDebug != bIsUseDebugRender )
	{
		ChunksMap::iterator Ite = m_mapChunks.begin();
		for( ; Ite != m_mapChunks.end(); ++Ite )
		{
			if( Ite->second )
			{
				Ite->second->SetDebugRender( bIsUseDebugRender );
			}
		}
	}

	m_bIsOpenDebug = bIsUseDebugRender;	
}
//-------------------------------------------------------------------------
// �����Chunk
RENDER_MAP_CHUNK_ID	FKMapLayer::AttachChunk( IMapChunk* pChunk )
{
	if( pChunk == NULL )
		return 0;

	// ���ID
	if( pChunk->GetChunkID() == 0 )
	{
		if( ++m_unCurChunkID == 0 )
			++m_unCurChunkID;
		IMapChunk* p = GetChunkByID( m_unCurChunkID );
		while ( p != NULL )
		{
			if( ++m_unCurChunkID == 0 )
				++m_unCurChunkID;
			p = GetChunkByID( m_unCurChunkID );
		}
		pChunk->SetChunkID( m_unCurChunkID );
	}
	pChunk->SetLayer( this );

	// �������Ⱦ�ڵ�
	addChild( (FKMapChunk*)pChunk );

	m_mapChunks[pChunk->GetChunkID()] = pChunk;

	return pChunk->GetChunkID();
}
//-------------------------------------------------------------------------
// �����յ���Chunk
RENDER_MAP_CHUNK_ID FKMapLayer::CreateEmptyChunk( CCPoint& tagPos )
{
	if( ++m_unCurChunkID == 0 )
		++m_unCurChunkID;
 	IMapChunk* p = GetChunkByID( m_unCurChunkID );
	while ( p != NULL )
	{
		if( ++m_unCurChunkID == 0 )
			++m_unCurChunkID;
		p = GetChunkByID( m_unCurChunkID );
	}

	FKMapChunk* pNew = new FKMapChunk( m_unCurChunkID );
	if( pNew == NULL )
		return 0;
	return AttachChunk( pNew );
}
//-------------------------------------------------------------------------
// �Ƴ���Chunk
bool FKMapLayer::DeleteChunk( RENDER_MAP_CHUNK_ID unChunkID )
{
	ChunksMap::iterator Ite = m_mapChunks.find( unChunkID );
	if( Ite == m_mapChunks.end() )
		return true;
	if( Ite->second )
	{
		removeChild( (FKMapChunk*)Ite->second );

		delete Ite->second;
		Ite->second = NULL;
	}
	m_mapChunks[unChunkID] = NULL;
	m_mapChunks.erase( Ite );

	return true;
}
//-------------------------------------------------------------------------
// ��ȡ��Chunk
IMapChunk* FKMapLayer::GetChunkByID( RENDER_MAP_CHUNK_ID unChunkID )
{
	ChunksMap::iterator Ite = m_mapChunks.find( unChunkID );
	if( Ite == m_mapChunks.end() )
		return NULL;
	if( Ite->second )
		return Ite->second;
	return NULL;
}
//-------------------------------------------------------------------------
// ��ȡ��chunk
IMapChunk* FKMapLayer::GetChunkByPos( const CCPoint& tagPos )
{
	ChunksMap::iterator Ite = m_mapChunks.begin();
	for( ; Ite != m_mapChunks.end(); ++Ite )
	{
		if( Ite->second )
		{
			if( Ite->second->IsPosInChunk( tagPos ) )
			{
				return Ite->second;
			}
		}
	}
	return NULL;
}
//-------------------------------------------------------------------------
// ���һ��Obj
bool FKMapLayer::AddObj( RENDER_OBJ_MAP_ID id, IRenderObj* pObj )
{
	if( pObj == NULL )
		return false;

	CCPoint tagPos = CCPointZero;
	pObj->GetPos( tagPos );
	IMapChunk* p = GetChunkByPos( tagPos );
	// ���������
	if( p )
	{
		return p->AddRenderObj( id, pObj );
	}
	
	// �����µ������
	RENDER_MAP_CHUNK_ID unChunkId = CreateEmptyChunk( tagPos );
	if( unChunkId == 0 )
		return false;
	p = GetChunkByID( unChunkId );
	if( p == NULL )
		return false;
	return p->AddRenderObj( id, pObj );
}
//-------------------------------------------------------------------------
// ��̬����Objλ��
void FKMapLayer::SetObjPos( RENDER_OBJ_MAP_ID id, const CCPoint& tagPos )
{
	IRenderObj* p = GetObjByID( id );
	if( p == NULL )
		return;
	p->SetPos( tagPos );
}
//-------------------------------------------------------------------------
// ��ȡ��ȾObj
IRenderObj* FKMapLayer::GetObjByID( RENDER_OBJ_MAP_ID id )
{
	IRenderObj* p = NULL;
	ChunksMap::iterator Ite = m_mapChunks.begin();
	for( ; Ite != m_mapChunks.end(); ++Ite )
	{
		if( Ite->second )
		{
			p = Ite->second->GetRenderObj( id );
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
void FKMapLayer::RemoveObjByID( RENDER_OBJ_MAP_ID id )
{
	IRenderObj* p = NULL;
	ChunksMap::iterator Ite = m_mapChunks.begin();
	for( ; Ite != m_mapChunks.end(); ++Ite )
	{
		if( Ite->second )
		{
			p = Ite->second->GetRenderObj( id );
			if( p != NULL )
			{
				Ite->second->DelRenderObj( id );
			}
		}
	}
}
//-------------------------------------------------------------------------
// �����������Ұ�ü�
void FKMapLayer::CullVisiableChunks()
{
	ICameraSystem* pCameraSystem = GetCameraSystem();
	if( pCameraSystem == NULL )
		return;

	CCRect tagVisiableRect = CCRectZero;
	pCameraSystem->GetViewRect( tagVisiableRect );

	// ���ҿ�������
	m_setVisiableChunks.clear();

	CCRect tagChunkRect;
	CCPoint tagChunkCenterPos;
	ChunksMap::iterator IteChunk = m_mapChunks.begin();
	for( ; IteChunk != m_mapChunks.end(); ++IteChunk )
	{
		if( IteChunk->second )
		{
			IteChunk->second->GetRect( tagChunkRect );
			IteChunk->second->GetGlobalPosition( tagChunkCenterPos );
			if( tagVisiableRect.intersectsRect( tagChunkRect ) ||
				tagVisiableRect.containsPoint( tagChunkCenterPos) )
			{
				// ���������Ұ������
				m_setVisiableChunks.insert( IteChunk->second->GetChunkID() );
				IteChunk->second->SetIsVisiable( true );
			}
		}
	}

	// ��������Ⱦ�����������Ա�
	vector<RENDER_MAP_CHUNK_ID> vecNeedBeRemovedChunks;
	vecNeedBeRemovedChunks.clear();

	ChunksSet::iterator Ite = m_setRenderedChunks.begin();
	for( ; Ite != m_setRenderedChunks.end(); ++Ite )
	{
		if( m_setVisiableChunks.find(*Ite) == m_setVisiableChunks.end() )
		{
			vecNeedBeRemovedChunks.push_back( *Ite );
		}
	}

	// ɾ�����ɼ�����
	unsigned int nSize = vecNeedBeRemovedChunks.size();
	for( unsigned int i = 0; i < nSize; ++i )
	{
		ChunksMap::iterator Ite = m_mapChunks.find( vecNeedBeRemovedChunks[i] );
		if( Ite != m_mapChunks.end() )
		{
			if( Ite->second )
			{
				FKMapChunk* p = (FKMapChunk*)(Ite->second);
				if( p )
				{
					p->SetIsVisiable( false );
					removeChild( p );

					// ע�⣬����û��ɾ�����������Ƴ�
				}
			}
		}
	}

	// ��¼
	m_setRenderedChunks = m_setVisiableChunks;
}
//-------------------------------------------------------------------------