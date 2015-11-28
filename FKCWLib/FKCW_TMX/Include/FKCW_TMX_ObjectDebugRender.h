//*************************************************************************
//	��������:	2014-12-29
//	�ļ�����:	FKCW_TMX_ObjectDebugRender.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_TMX_Macros.h"
//-------------------------------------------------------------------------
class FKCW_TMX_Map;
//-------------------------------------------------------------------------
class FKCW_TMX_ObjectDebugRender : public CCNode
{
protected:
	FKCW_TMX_ObjectDebugRender();

public:
	virtual ~FKCW_TMX_ObjectDebugRender();
	static FKCW_TMX_ObjectDebugRender* create(FKCW_TMX_Map* m);

	virtual bool initWithMap(FKCW_TMX_Map* map);
	virtual void draw();

	CC_SYNTHESIZE(FKCW_TMX_Map*, m_map, Map);					// tmx��Map
	CC_SYNTHESIZE(FKCW_Base_PointList, m_vertices, Vertices);	// ����Buffer�б�
};