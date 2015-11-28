//-------------------------------------------------------------------------
#include "FKMapChunk.h"
#include "FKMapStruct.h"
//-------------------------------------------------------------------------
FKMapChunk::FKMapChunk( RENDER_MAP_CHUNK_ID id )
	: m_pOwnerLayer( NULL )
	, m_bIsUseDebugRender( false )
	, m_bIsVisible( false )
{
	m_pMapChunkInfo = new SMapChunkInfo();
	if( m_pMapChunkInfo )
	{
		m_pMapChunkInfo->unChunkID = id;
	}
}
//-------------------------------------------------------------------------
FKMapChunk::~FKMapChunk()
{
	Release();
	CC_SAFE_DELETE( m_pMapChunkInfo );
}
//-------------------------------------------------------------------------
// �ͷ�ȫ����Ϣ
void FKMapChunk::Release()
{

}
//-------------------------------------------------------------------------
// ֡����
void FKMapChunk::Update( float dt )
{
	if( IsVisiable() )
	{
		_SubUpdate( dt );
	}
}
//-------------------------------------------------------------------------
// ��ȡChunkID
unsigned int FKMapChunk::GetChunkID() const
{
	if( m_pMapChunkInfo )
		return m_pMapChunkInfo->GetChunkID();
	return 0;
}
//-------------------------------------------------------------------------
// ����ChunkID
void FKMapChunk::SetChunkID( unsigned int unChunkID )
{
	if( m_pMapChunkInfo )
		m_pMapChunkInfo->unChunkID = unChunkID;
}
//-------------------------------------------------------------------------
// ��ȡ��ǰ������ڴ��ͼ������λ��
void FKMapChunk::GetGlobalPosition( CCPoint& tagPos )
{
	if( m_pMapChunkInfo )
	{
		tagPos = m_pMapChunkInfo->tagPos;
		return;
	}
	tagPos = getPosition();
}
//-------------------------------------------------------------------------
// ���õ�ǰ��������ڴ��ͼ�е�λ��
void FKMapChunk::SetGlobalPosition( const CCPoint& tagPos )
{
	if( m_pMapChunkInfo )
		m_pMapChunkInfo->tagPos = tagPos;
	setPosition( tagPos );
}
//-------------------------------------------------------------------------
// ��ȡ��ǰ�����С
void FKMapChunk::GetSize( CCSize& tagSize )
{
	tagSize = CCSizeZero;
	if( m_pMapChunkInfo )
	{
		m_pMapChunkInfo->GetSize( tagSize );
	}
}
//-------------------------------------------------------------------------
// ��ȡ��ǰ����Χ
void FKMapChunk::GetRect( CCRect& rect )
{
	rect = CCRectZero;
	if( m_pMapChunkInfo )
	{
		m_pMapChunkInfo->GetRect( rect );
	}
}
//-------------------------------------------------------------------------
// ��ȡ��ͼ������( ���� ENUM_MapChunkType )
int FKMapChunk::GetType()
{
	if( m_pMapChunkInfo )
		return m_pMapChunkInfo->GetType();
	return eMCT_Max;
}
//-------------------------------------------------------------------------
// ����/�ر�DEBUG��Ⱦ
void FKMapChunk::SetDebugRender( bool bIsUseDebugRender )
{
	m_bIsUseDebugRender = bIsUseDebugRender;
}
//-------------------------------------------------------------------------
// ��ȡ�������ڲ�
IMapLayer* FKMapChunk::GetLayer()
{
	return m_pOwnerLayer;
}
//-------------------------------------------------------------------------
// �����������ڲ�
void FKMapChunk::SetLayer( IMapLayer* pLayer )
{
	m_pOwnerLayer = pLayer;
}
//-------------------------------------------------------------------------
// �Ƿ�ɼ�
bool FKMapChunk::IsVisiable()
{
	return m_bIsVisible;
}
//-------------------------------------------------------------------------
// �����Ƿ�ɼ�
void FKMapChunk::SetIsVisiable( bool bIsVisiable )
{
	m_bIsVisible = bIsVisiable;
}
//-------------------------------------------------------------------------
// ���һ�����Ƿ��ڱ�������
bool FKMapChunk::IsPosInChunk( const CCPoint& pos )
{
	if( m_pMapChunkInfo == NULL )
	{
		return false;
	}
	CCRect rect = CCRectZero;
	m_pMapChunkInfo->GetRect( rect );
	return rect.containsPoint( pos );
}
//-------------------------------------------------------------------------
// ����Ӹ�
bool FKMapChunk::AddGrid( IMapGridInfo* pGridInfo )
{
	return _SubAddGrid( pGridInfo );
}
//-------------------------------------------------------------------------
// �Ƴ��Ӹ�
void FKMapChunk::DelGrid( CCPoint& tagPos )
{
	return _SubDelGrid( tagPos );
}
//-------------------------------------------------------------------------
// �����Ⱦ����
bool FKMapChunk::AddRenderObj( RENDER_OBJ_ID id, const string& strTerrainObjName, CCRect& rc,
							  CCPoint& tagOffset, CCPoint& tagScale, ccColor4B& tagColor )
{
	return _SubAddRenderObj( id, strTerrainObjName, rc, tagOffset, tagScale, tagColor );
}
//-------------------------------------------------------------------------
// �����Ⱦ����
bool FKMapChunk::AddRenderObj( RENDER_OBJ_ID id, IRenderObj* pRenderObj )
{
	return _SubAddRenderObj( id, pRenderObj );
}
//-------------------------------------------------------------------------
// ��ȡ��Ⱦ����
IRenderObj* FKMapChunk::GetRenderObj( RENDER_OBJ_ID id )
{
	return _SubGetRenderObj( id );
}
//-------------------------------------------------------------------------
// �Ƴ���Ⱦ����
void FKMapChunk::DelRenderObj( RENDER_OBJ_ID id )
{
	return _SubDelRenderObj( id );
}
//-------------------------------------------------------------------------
// ת���������굽chunk�е�����
void FKMapChunk::ConvertGlobalPos2ChunkPos( CCPoint& GlobalPos, CCPoint& ChunkPos )
{
	CCSize tagChunkSize = CCSizeZero;
	GetSize( tagChunkSize );
	CCPoint tagChunkCenterPos = CCPointZero;
	GetGlobalPosition( tagChunkCenterPos );
	ChunkPos = GlobalPos + ccp( tagChunkSize.width / 2, tagChunkSize.height / 2 ) - tagChunkCenterPos;
}
//-------------------------------------------------------------------------
// ת��chunk�е����굽��������
void FKMapChunk::ConvertChunkPos2GlobalPos( CCPoint& ChunkPos, CCPoint& GlobalPos )
{
	CCSize tagChunkSize = CCSizeZero;
	GetSize( tagChunkSize );
	CCPoint tagChunkCenterPos = CCPointZero;
	GetGlobalPosition( tagChunkCenterPos );
	GlobalPos = ChunkPos + tagChunkCenterPos - ccp( tagChunkSize.width / 2, tagChunkSize.height / 2 );
}
//-------------------------------------------------------------------------