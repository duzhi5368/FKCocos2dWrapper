//*************************************************************************
//	��������:	2014-12-29
//	�ļ�����:	FKCW_TMX_LayerInfo.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_TMX_Macros.h"
//-------------------------------------------------------------------------
class FKCW_TMX_LayerInfo : public CCObject
{
protected:
	FKCW_TMX_LayerInfo();
	
public:
	virtual ~FKCW_TMX_LayerInfo();
	static FKCW_TMX_LayerInfo* create();
	
	// ����Key��ȡһ������ֵ
	string getProperty(const string& key);
	// ���һ������
	void addProperty(const string& key, const string& value);
	
public:
	CC_SYNTHESIZE(string, m_name, Name);									// ����
	CC_SYNTHESIZE(int, m_layerWidth, LayerWidth);							// ����Tile��Ƭ�Ŀ��
	CC_SYNTHESIZE(int, m_layerHeight, LayerHeight);							// ����Tile��Ƭ�ĸ߶�
	CC_SYNTHESIZE(int*, m_tiles, Tiles);									// Tile������
	CC_SYNTHESIZE_BOOL(m_visible, Visible);									// ���Ƿ�ɼ�
	CC_SYNTHESIZE(int, m_alpha, Alpha);										// ��Alphaֵ
	CC_SYNTHESIZE_PASS_BY_REF_NC(CCDictionary, m_properties, Properties);	// ���Դʵ�
	CC_SYNTHESIZE(float, m_offsetX, OffsetX);								// Xƫ��
	CC_SYNTHESIZE(float, m_offsetY, OffsetY);								// Yƫ��
};