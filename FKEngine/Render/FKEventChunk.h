//*************************************************************************
//	��������:	2015-1-26
//	�ļ�����:	FKEventChunk.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKMapChunk.h"
//-------------------------------------------------------------------------
// �¼���
class FKEventChunk : public FKMapChunk
{
public:
	FKEventChunk( RENDER_MAP_CHUNK_ID id );
	~FKEventChunk();
public:
	virtual void			draw();
protected:
	// ����Ӹ�
	virtual bool			_SubAddGrid( IMapGridInfo* pGridInfo );
	// �Ƴ��Ӹ�
	virtual void			_SubDelGrid( CCPoint& tagPos );
private:
	typedef map< unsigned short, SEventGridInfo* >	EventGridsMap;
	EventGridsMap			m_mapEventGrids;		// �¼��ϰ�����
};