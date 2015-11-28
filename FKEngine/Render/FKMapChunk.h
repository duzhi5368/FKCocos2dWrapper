//*************************************************************************
//	��������:	2015-1-27
//	�ļ�����:	FKMapChunk.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../FKEngineCommonHead.h"
#include "FKMapSystemMacros.h"
#include "FKMapStruct.h"
//-------------------------------------------------------------------------
struct SMapChunkInfo;
class FKMapChunk : public IMapChunk, public CCNode
{
public:
	FKMapChunk( RENDER_MAP_CHUNK_ID id );
	virtual ~FKMapChunk();
public:
	// �ͷ�ȫ����Ϣ
	virtual void			Release();
	// ֡����
	virtual void			Update( float dt );

	// ��ȡChunkID
	virtual unsigned int	GetChunkID() const;
	// ����ChunkID
	virtual void			SetChunkID( unsigned int unChunkID );
	// ��ȡ��ǰ������ڴ��ͼ������λ��
	virtual void 			GetGlobalPosition( CCPoint& tagPos );
	// ���õ�ǰ��������ڴ��ͼ�е�λ��
	virtual void			SetGlobalPosition( const CCPoint& tagPos );
	// ��ȡ��ǰ�����С
	virtual void			GetSize( CCSize& tagSize );
	// ��ȡ��ǰ����Χ
	virtual void			GetRect( CCRect& rect );
	// ��ȡ��ͼ������( ���� ENUM_MapChunkType )
	virtual int				GetType();
	// ����/�ر�DEBUG��Ⱦ
	virtual void			SetDebugRender( bool bIsUseDebugRender );

	// ��ȡ�������ڲ�
	virtual IMapLayer*		GetLayer();
	// �����������ڲ�
	virtual void			SetLayer( IMapLayer* pLayer );
	// �Ƿ�ɼ�
	virtual bool			IsVisiable();
	// �����Ƿ�ɼ�
	virtual void			SetIsVisiable( bool bIsVisiable );
	// ���һ�����Ƿ��ڱ�������
	virtual bool			IsPosInChunk( const CCPoint& pos );

	// ����Ӹ�
	virtual bool			AddGrid( IMapGridInfo* pGridInfo );
	// �Ƴ��Ӹ�
	virtual void			DelGrid( CCPoint& tagPos );
	// �����Ⱦ����
	virtual bool			AddRenderObj( RENDER_OBJ_MAP_ID id, const string& strTerrainObjName, CCRect& rc,
		CCPoint& tagOffset, CCPoint& tagScale, ccColor4B& tagColor );
	// �����Ⱦ����
	virtual bool			AddRenderObj( RENDER_OBJ_MAP_ID id, IRenderObj* pRenderObj );
	// ��ȡ��Ⱦ����
	virtual IRenderObj*		GetRenderObj( RENDER_OBJ_MAP_ID id );
	// �Ƴ���Ⱦ����
	virtual void			DelRenderObj( RENDER_OBJ_MAP_ID id );

	// ת���������굽chunk�е�����
	virtual void			ConvertGlobalPos2ChunkPos( CCPoint& GlobalPos, CCPoint& ChunkPos );
	// ת��chunk�е����굽��������
	virtual void			ConvertChunkPos2GlobalPos( CCPoint& ChunkPos, CCPoint& GlobalPos );
protected:
	// ֡����
	virtual void			_SubUpdate( float dt ){};
	// ����Ӹ�
	virtual bool			_SubAddGrid( IMapGridInfo* pGridInfo ){ return true; }
	// �Ƴ��Ӹ�
	virtual void			_SubDelGrid( CCPoint& tagPos ){}
	// �����Ⱦ����
	virtual bool			_SubAddRenderObj( RENDER_OBJ_MAP_ID id, const string& strTerrainObjName, CCRect& rc,
		CCPoint& tagOffset, CCPoint& tagScale, ccColor4B& tagColor ){ return true; }
	// �����Ⱦ����
	virtual bool			_SubAddRenderObj( RENDER_OBJ_MAP_ID id, IRenderObj* pRenderObj ){ return true; }
	// �Ƴ���Ⱦ����
	virtual void			_SubDelRenderObj( RENDER_OBJ_MAP_ID id ){}
	// �Ƴ���Ⱦ����
	virtual void			_SubDelRenderObj( IRenderObj* pRenderObj ){}
	// ��ȡ��Ⱦ����
	virtual IRenderObj*		_SubGetRenderObj( RENDER_OBJ_MAP_ID id ){ return NULL; }
protected:
	IMapLayer*				m_pOwnerLayer;					// ������Layer
	bool					m_bIsUseDebugRender;			// �Ƿ���ʹ��Debug��Ⱦ
	SMapChunkInfo*			m_pMapChunkInfo;				// ��������Ϣ
	bool					m_bIsVisible;					// �Ƿ�ɼ�
};