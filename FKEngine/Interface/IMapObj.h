//*************************************************************************
//	��������:	2015-1-21
//	�ļ�����:	IMapObj.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../../FKCWLib/FKCocos2dxWrapper.h"
//-------------------------------------------------------------------------
// ��ͼ��ID
typedef unsigned int	RENDER_MAP_CHUNK_ID;
// ��ͼ��ID
typedef unsigned int	RENDER_MAP_LAYER_ID;
// ��ͼID
typedef unsigned int	RENDER_MAP_ID;
// ��ͼ�е���Ⱦ����ID
typedef unsigned int	RENDER_OBJ_MAP_ID;
//-------------------------------------------------------------------------
class IMapLayer;
struct IMapGridInfo
{
	// ��ȡ����ID����IDӦ���ڱ�Chunk��Ψһ
	virtual unsigned short		GetGridID()	= 0;
	// ��ȡ���Ӵ�С
	virtual void				GetSize( CCSize& tagSize ) = 0;
	// ��ȡ��������
	virtual void				GetRectInChunk( CCRect& tagRect ) = 0;
};
//-------------------------------------------------------------------------
class IMapChunk
{
public:
	// �ͷ�ȫ����Ϣ
	virtual void			Release() = 0;
	// ֡����
	virtual void			Update( float dt ) = 0;

	// ��ȡChunkID
	virtual unsigned int	GetChunkID() const = 0;
	// ����ChunkID
	virtual void			SetChunkID( unsigned int unChunkID ) = 0;
	// ��ȡ��ǰ������ڴ��ͼ������λ��
	virtual void 			GetGlobalPosition( CCPoint& tagPos ) = 0;
	// ���õ�ǰ��������ڴ��ͼ�е�λ��
	virtual void			SetGlobalPosition( const CCPoint& tagPos ) = 0;
	// ��ȡ��ǰ�����С
	virtual void			GetSize( CCSize& tagSize ) = 0;
	// ��ȡ��ǰ����Χ
	virtual void			GetRect( CCRect& rect ) = 0;
	// ��ȡ��ͼ������( ���� ENUM_MapChunkType )
	virtual int				GetType() = 0;
	// ����/�ر�DEBUG��Ⱦ
	virtual void			SetDebugRender( bool bIsUseDebugRender ) = 0;

	// ��ȡ�������ڲ�
	virtual IMapLayer*		GetLayer() = 0;
	// �����������ڲ�
	virtual void			SetLayer( IMapLayer* pLayer ) = 0;
	// �Ƿ�ɼ�
	virtual bool			IsVisiable() = 0;
	// �����Ƿ�ɼ�
	virtual void			SetIsVisiable( bool bIsVisiable ) = 0;
	// ���һ�����Ƿ��ڱ�������
	virtual bool			IsPosInChunk( const CCPoint& pos ) = 0;

	// ����Ӹ�
	virtual bool			AddGrid( IMapGridInfo* pGridInfo ) = 0;
	// �Ƴ��Ӹ�
	virtual void			DelGrid( CCPoint& tagPos ) = 0;
	// �����Ⱦ����
	virtual bool			AddRenderObj( RENDER_OBJ_MAP_ID id, const string& strTerrainObjName, CCRect& rc,
		CCPoint& tagOffset, CCPoint& tagScale, ccColor4B& tagColor ) = 0;
	// �����Ⱦ����
	virtual bool			AddRenderObj( RENDER_OBJ_MAP_ID id, IRenderObj* pRenderObj ) = 0;
	// ��ȡ��Ⱦ����
	virtual IRenderObj*		GetRenderObj( RENDER_OBJ_MAP_ID id ) = 0;
	// �Ƴ���Ⱦ����
	virtual void			DelRenderObj( RENDER_OBJ_MAP_ID id ) = 0;

	// ת���������굽chunk�е�����
	virtual void			ConvertGlobalPos2ChunkPos( CCPoint& GlobalPos, CCPoint& ChunkPos ) = 0;
	// ת��chunk�е����굽��������
	virtual void			ConvertChunkPos2GlobalPos( CCPoint& ChunkPos, CCPoint& GlobalPos ) = 0;
};
//-------------------------------------------------------------------------
class IMapLayer
{
public:
	// �ͷ�
	virtual void			Release() = 0;
	// ֡����
	virtual void			Update( float dt ) = 0;

	// ��ȡ��ID
	virtual unsigned int	GetLayerID() const = 0;
	// ���ò�ID
	virtual void			SetLayerID( unsigned int unLayerID ) = 0;
	// ���ò���
	virtual void			SetLayerDepth( int nLayerDepth ) = 0;
	// ��ȡ����
	virtual int				GetLayerDepth() = 0;
	// ��ȡ������Ӳ�
	virtual float			GetLayerHeightParallax() = 0;
	// ��ȡ�������Ӳ�
	virtual float			GetLayerWidthParallax() = 0;
	// ���ò�����Ӳ�
	virtual void			SetLayerHeightParallax( float fParallax ) = 0;
	// ���ò������Ӳ�
	virtual void			GetLayerHeightParallax( float fParallax ) = 0;
	// ��ȡ��ͼ������( ���� ENUM_MapImageLayerType )
	virtual int				GetLayerType() = 0;
	// ����/�ر�DEBUG��Ⱦ
	virtual void			SetDebugRender( bool bIsUseDebugRender ) = 0;

	// �����Chunk
	virtual RENDER_MAP_CHUNK_ID	AttachChunk( IMapChunk* pChunk ) = 0;
	// �����յ���Chunk
	virtual RENDER_MAP_CHUNK_ID CreateEmptyChunk( CCPoint& tagPos ) = 0;
	// �Ƴ���Chunk
	virtual bool			DeleteChunk( RENDER_MAP_CHUNK_ID unChunkID ) = 0;
	// ��ȡ��Chunk
	virtual IMapChunk*		GetChunkByID( RENDER_MAP_CHUNK_ID unChunkID ) = 0;
	// ��ȡ��chunk
	virtual IMapChunk*		GetChunkByPos( const CCPoint& tagPos ) = 0;

	// ���һ��Obj
	virtual bool			AddObj( RENDER_OBJ_MAP_ID id, IRenderObj* pObj ) = 0;
	// ��̬����Objλ��
	virtual void			SetObjPos( RENDER_OBJ_MAP_ID id, const CCPoint& tagPos ) = 0;
	// ��ȡ��ȾObj
	virtual IRenderObj*		GetObjByID( RENDER_OBJ_MAP_ID id ) = 0;
	// �Ƴ���ȾObj
	virtual void			RemoveObjByID( RENDER_OBJ_MAP_ID id ) = 0;

	// �����������Ұ�ü�
	virtual void			CullVisiableChunks() = 0;
};
//-------------------------------------------------------------------------
class IMapObj
{
public:
	// �Ƿ�����Update
	virtual void			SetEnableUpdate( bool bIsEnable ) = 0;
	// ��һ����Դ�ļ�����
	virtual bool			InitFromFile( const char* szFileName ) = 0;
	// д�뵽һ����Դ�ļ�
	virtual bool			WriteToFile( const char* szFileName ) = 0;

	// ���һ��Obj
	virtual unsigned int	AddObj( RENDER_MAP_LAYER_ID id, IRenderObj* pObj ) = 0;
	// ��̬����Objλ��
	virtual void			SetObjPos( RENDER_MAP_CHUNK_ID id, const CCPoint& tagPos ) = 0;
	// ��ȡ��ȾObj
	virtual IRenderObj*		GetObjByID( RENDER_MAP_CHUNK_ID id ) = 0;
	// �Ƴ���ȾObj
	virtual void			RemoveObjByID( RENDER_MAP_CHUNK_ID id ) = 0;

	// ��ȡָ����
	virtual IMapLayer*		GetLayerByID( RENDER_MAP_LAYER_ID id ) = 0;

	// ת����Ļ���굽��������
	virtual void			ConvertScreenPos2ScenePos( const CCPoint& screenPos, 
		CCPoint& scenePos ) = 0;

	// ��ײѡȡ���
	virtual void			HitTestObj( const CCPoint& pt, list<IRenderObj*>& ObjList ) = 0;

	// ��ȡ����ID
	virtual RENDER_MAP_ID	GetID() = 0;
	// ��ȡ�����ļ���
	virtual void			GetSceneFileName( string& strFileName ) = 0;
	// ����/�ر�DEBUG��Ⱦ
	virtual void			SetDebugRender( bool bIsUseDebugRender ) = 0;
};
//-------------------------------------------------------------------------