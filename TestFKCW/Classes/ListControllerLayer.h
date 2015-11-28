//*************************************************************************
//	��������:	2014-11-26
//	�ļ�����:	ListControllerLayer.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "cocos2d.h"
//-------------------------------------------------------------------------
USING_NS_CC;
//-------------------------------------------------------------------------
class CListControllerLayer : public CCLayer
{
public:
	CListControllerLayer();
	~CListControllerLayer();
public:
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);

	virtual void onEnter();

	void menuCallback(CCObject * pSender);
	void closeCallback(CCObject * pSender);
protected:
	ccColor3B	_GetColorByName(std::string p_szName);
private:
	CCPoint m_tBeginPos;
	CCMenu* m_pItemMenu;
};
//-------------------------------------------------------------------------