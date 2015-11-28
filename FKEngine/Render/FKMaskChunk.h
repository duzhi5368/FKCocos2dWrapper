//*************************************************************************
//	��������:	2015-1-27
//	�ļ�����:	FKMaskChunk.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKMapChunk.h"
//-------------------------------------------------------------------------
class FKMaskChunk : public FKMapChunk
{
public:
	FKMaskChunk( RENDER_MAP_CHUNK_ID id );
	~FKMaskChunk();
public:
	virtual void			draw();
protected:
	// ����Ӹ�
	virtual bool			_SubAddGrid( IMapGridInfo* pGridInfo );
	// �Ƴ��Ӹ�
	virtual void			_SubDelGrid( CCPoint& tagPos );
private:
	typedef map< unsigned short, SMaskGridInfo* >	MaskGridsMap;
	MaskGridsMap		m_mapMaskGrids;		// �����ϰ�����
};