//*************************************************************************
//	��������:	2014-11-22
//	�ļ�����:	FKCW_UI_DynamicNumLabel.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_UI_Macros.h"
//-------------------------------------------------------------------------
class FKCW_UI_DynamicNumLabel : public CCLabelTTF
{
public:
	FKCW_UI_DynamicNumLabel();
	~FKCW_UI_DynamicNumLabel();

	static FKCW_UI_DynamicNumLabel* create(const char *string, const char *fontName, float fontSize);
	static FKCW_UI_DynamicNumLabel* create(const char *string, const char *fontName, float fontSize,
		const CCSize& dimensions, CCTextAlignment hAlignment);
	static FKCW_UI_DynamicNumLabel* create(const char *string, const char *fontName, float fontSize,
		const CCSize& dimensions, CCTextAlignment hAlignment,
		CCVerticalTextAlignment vAlignment);
	static FKCW_UI_DynamicNumLabel* createWithFontDefinition(const char *string, ccFontDefinition &textDefinition);

public:
	void	SetDynamicValue(int value);
	int		GetDynamicValue();

private:
	int		m_nCurValue;
	bool	m_bIsInUpdate;
	void	__InitData( const char* p_szString );
	void	__UpdateDynamicValue(float dt);
};