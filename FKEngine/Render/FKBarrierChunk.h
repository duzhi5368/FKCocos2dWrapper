//*************************************************************************
//	��������:	2015-1-21
//	�ļ�����:	FKBarrierChunk.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKMapChunk.h"
//-------------------------------------------------------------------------
// �ϰ�����
class FKBarrierChunk : public FKMapChunk
{
public:
	FKBarrierChunk( RENDER_MAP_CHUNK_ID id );
	~FKBarrierChunk();
public:
	virtual void			draw();
protected:
	// ����Ӹ�
	virtual bool			_SubAddGrid( IMapGridInfo* pGridInfo );
	// �Ƴ��Ӹ�
	virtual void			_SubDelGrid( CCPoint& tagPos );
private:
	typedef map< unsigned short, SBarrierGridInfo* >	BarrierGridsMap;
	BarrierGridsMap		m_mapBarrierGrids;		// �ϰ�����
};