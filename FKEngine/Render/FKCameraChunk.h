//*************************************************************************
//	��������:	2015-1-26
//	�ļ�����:	FKCameraChunk.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKMapChunk.h"
//-------------------------------------------------------------------------
// �������
class FKCameraChunk : public FKMapChunk
{
public:
	FKCameraChunk( RENDER_MAP_CHUNK_ID id );
	~FKCameraChunk();
public:
	virtual void			draw();
protected:
	// ����Ӹ�
	virtual bool			_SubAddGrid( IMapGridInfo* pGridInfo );
	// �Ƴ��Ӹ�
	virtual void			_SubDelGrid( CCPoint& tagPos );
private:
	typedef map< unsigned short, SCameraGridInfo* >	CameraGridsMap;
	CameraGridsMap		m_mapCameraGrids;		// ������ϰ�����
};