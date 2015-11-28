//*************************************************************************
//	��������:	2015-1-21
//	�ļ�����:	FKImageChunk.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKMapChunk.h"
//-------------------------------------------------------------------------
// �����е����
struct STerrainObj
{
	RENDER_OBJ_ID			m_unID;				// ����ΨһID
	RENDER_MAP_CHUNK_ID		m_unChunkID;		// ����Chunk ID
	RENDER_MAP_LAYER_ID		m_unLayerID;		// ����Layer ID
	CCPoint					m_tagScale;			// ����ֵ
	CCPoint					m_tagOffset;		// ƫ��ֵ
	ccColor4B				m_tagColor;			// ��ɫֵ
	CCRect					m_tagRc;			// ��ʾ��
	IRenderObj*				m_pRenderObj;		// ��Ⱦ����
	string					m_strFileName;		// ����ļ���
	unsigned int			m_unTime;			// �ڳ����д�����ʱ��
	STerrainObj()
		: m_unID( 0 )
		, m_unChunkID( 0 )
		, m_unLayerID( 0 )
		, m_unTime( 0 )
		, m_pRenderObj( NULL )
	{
		m_tagScale = ccp( 1.0f, 1.0f );
		m_tagOffset = CCPointZero;
		m_tagColor = ccc4( 255, 255, 255, 255 );
		m_tagRc = CCRectZero;
		m_strFileName.clear();
	}
};
//-------------------------------------------------------------------------
// ͼƬ��
class FKImageChunk : public FKMapChunk
{
public:
	FKImageChunk( RENDER_MAP_CHUNK_ID id );
	~FKImageChunk();
public:
	virtual void			draw();
protected:
	// ֡����
	virtual void			_SubUpdate( float dt );
	// �����Ⱦ����
	virtual bool			_SubAddRenderObj( RENDER_OBJ_MAP_ID id, const string& strTerrainObjName, CCRect& rc,
		CCPoint& tagOffset, CCPoint& tagScale, ccColor4B& tagColor );
	// �����Ⱦ����
	virtual bool			_SubAddRenderObj( RENDER_OBJ_MAP_ID id, IRenderObj* pRenderObj );
	// �Ƴ���Ⱦ����
	virtual void			_SubDelRenderObj( RENDER_OBJ_MAP_ID id );
	// ��ȡ��Ⱦ����
	virtual IRenderObj*		_SubGetRenderObj( RENDER_OBJ_MAP_ID id );
private:
	// ���¿��Ӷ���
	void					__UpdateVisibleObject();
private:
	typedef map< RENDER_OBJ_MAP_ID, STerrainObj >	TerrainObjsMap;
	typedef map< RENDER_OBJ_ID, RENDER_OBJ_MAP_ID >	RenderObjID2TerrainObjIDMap;
	typedef set< RENDER_OBJ_MAP_ID >				TerrainRenderObjsSet;
	TerrainObjsMap				m_mapTerrainObjs;			// ��Ҫ������Ⱦ�������
	bool						m_bIsNeedUpdateTerrainObj;	// �Ƿ���Ҫ���µ��ζ���
	RenderObjID2TerrainObjIDMap	m_mapRenderObj2TerrainObj;	// ��Ⱦ����ID->��������ID��Ӧ��
	TerrainRenderObjsSet		m_setTerrainRenderObjs;		// ���������ڱ���Ⱦ���������
};