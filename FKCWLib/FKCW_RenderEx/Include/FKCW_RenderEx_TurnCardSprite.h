//*************************************************************************
//	��������:	2014-11-22
//	�ļ�����:	FKCW_RenderEx_TurnCardSprite.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_RenderEx_Macros.h"
//-------------------------------------------------------------------------
class FKCW_RenderEx_TurnCardSprite : public CCSprite
{
public:
	FKCW_RenderEx_TurnCardSprite();
	~FKCW_RenderEx_TurnCardSprite();
	static FKCW_RenderEx_TurnCardSprite* create(const char* inCardImageName, const char* outCardImageName, float duration);
	virtual bool init(const char* inCardImageName, const char* outCardImageName, float duration);

private:
	bool				m_bIsOpened;
	CCActionInterval*	m_pOpenAnimIn;
	CCActionInterval*	m_pOpenAnimOut;

	void __InitData(const char* inCardImageName, const char* outCardImageName, float duration);
public:
	void OpenCard();
};