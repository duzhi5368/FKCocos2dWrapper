//*************************************************************************
//	创建日期:	2015-1-21
//	文件名称:	FKBarrierChunk.h
//  创 建 人:   王宏张 FreeKnight	
//	版权所有:	MIT
//	说    明:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKMapChunk.h"
//-------------------------------------------------------------------------
// 障碍区域
class FKBarrierChunk : public FKMapChunk
{
public:
	FKBarrierChunk( RENDER_MAP_CHUNK_ID id );
	~FKBarrierChunk();
public:
	virtual void			draw();
protected:
	// 添加子格
	virtual bool			_SubAddGrid( IMapGridInfo* pGridInfo );
	// 移除子格
	virtual void			_SubDelGrid( CCPoint& tagPos );
private:
	typedef map< unsigned short, SBarrierGridInfo* >	BarrierGridsMap;
	BarrierGridsMap		m_mapBarrierGrids;		// 障碍格组
};