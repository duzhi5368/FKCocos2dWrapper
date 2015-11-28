//*************************************************************************
//	��������:	2015-1-21
//	�ļ�����:	FKMapLayer.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../FKEngineCommonHead.h"
//-------------------------------------------------------------------------
struct SMapLayerInfo;
class FKMapLayer : public CCLayer, public IMapLayer
{
public:
	FKMapLayer( RENDER_MAP_LAYER_ID id );
	~FKMapLayer();
public:
	// �ͷ�
	virtual void			Release();
	// ֡����
	virtual void			Update( float dt );

	// ���ò�ID
	virtual void			SetLayerID( unsigned int unLayerID );
	// ��ȡ��ID
	virtual unsigned int	GetLayerID() const;
	// ���ò���
	virtual void			SetLayerDepth( int nLayerDepth );
	// ��ȡ����
	virtual int				GetLayerDepth();
	// ��ȡ��ͼ������( ���� ENUM_MapImageLayerType )
	virtual int				GetLayerType();
	// ��ȡ������Ӳ�
	virtual float			GetLayerHeightParallax();
	// ��ȡ�������Ӳ�
	virtual float			GetLayerWidthParallax();
	// ���ò�����Ӳ�
	virtual void			SetLayerHeightParallax( float fParallax );
	// ���ò������Ӳ�
	virtual void			GetLayerHeightParallax( float fParallax );
	// ����/�ر�DEBUG��Ⱦ
	virtual void			SetDebugRender( bool bIsUseDebugRender );

	// �����Chunk
	virtual RENDER_MAP_CHUNK_ID	AttachChunk( IMapChunk* pChunk );
	// �����յ���Chunk
	virtual RENDER_MAP_CHUNK_ID CreateEmptyChunk( CCPoint& tagPos );
	// �Ƴ���Chunk
	virtual bool			DeleteChunk( RENDER_MAP_CHUNK_ID unChunkID );
	// ��ȡ��Chunk
	virtual IMapChunk*		GetChunkByID( RENDER_MAP_CHUNK_ID unChunkID );
	// ��ȡ��chunk
	virtual IMapChunk*		GetChunkByPos( const CCPoint& tagPos );

	// ���һ��Obj
	virtual bool			AddObj( RENDER_OBJ_MAP_ID id, IRenderObj* pObj );
	// ��̬����Objλ��
	virtual void			SetObjPos( RENDER_OBJ_MAP_ID id, const CCPoint& tagPos );
	// ��ȡ��ȾObj
	virtual IRenderObj*		GetObjByID( RENDER_OBJ_MAP_ID id );
	// �Ƴ���ȾObj
	virtual void			RemoveObjByID( RENDER_OBJ_MAP_ID id );

	// �����������Ұ�ü�
	virtual void			CullVisiableChunks();
protected:
	typedef map<RENDER_MAP_CHUNK_ID, IMapChunk*>		ChunksMap;
	typedef set<RENDER_MAP_CHUNK_ID>					ChunksSet;
	SMapLayerInfo*			m_pMapLayerInfo;		// ��������Ϣ
	ChunksMap				m_mapChunks;			// ����
	bool					m_bIsOpenDebug;			// �Ƿ�����DEBUG��Ⱦ
	bool					m_bIsNeedUpdateChunk;	// �Ƿ�Ҫ��������ɼ���
	unsigned int			m_unCurChunkID;			// ��ǰChunkID
	ChunksSet				m_setVisiableChunks;	// ����������[��ʱ]
	ChunksSet				m_setRenderedChunks;	// ���ڱ���Ⱦ��������
};