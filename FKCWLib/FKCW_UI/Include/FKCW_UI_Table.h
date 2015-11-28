//*************************************************************************
//	��������:	2014-11-14
//	�ļ�����:	FKCW_UI_Table.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_UI_Macros.h"
//-------------------------------------------------------------------------
class FKCW_UI_Table : public CCObject
{
public:
	FKCW_UI_Table();
	static FKCW_UI_Table* create(const CCRect& tWindowRect, int nWindowColumnCount, int nWindowRowCount, bool bFillDirectionHorizontal, bool bLayerDirectionHorizontal);
	bool init(const CCRect& tWindowRect, int nWindowColumnCount, int nWindowRowCount, bool bFillDirectionHorizontal, bool bLayerDirectionHorizontal);

	void registerNode(CCNode* pNode);
	void clearNodes();
	void arrangeItems();
	CCNode* createCellNode();
public:
	CC_SYNTHESIZE_READONLY_PASS_BY_REF(CCSize, m_tCellSize, CellSize);
	CC_SYNTHESIZE_READONLY_PASS_BY_REF(CCSize, m_tLayerSize, LayerSize);
private:
	CCRect		m_tWindowRect;
	int			m_nWindowColumnCount;
	int			m_nWindowRowCount;
	bool		m_bFillDirectionHorizontal;
	bool		m_bLayerDirectionHorizontal;
	CCArray		m_tNodes;
};
