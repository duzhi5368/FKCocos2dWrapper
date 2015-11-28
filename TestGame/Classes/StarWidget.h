//*************************************************************************
//	��������:	2015-3-26
//	�ļ�����:	StarWidget.h
//  �� �� ��:   �˹۸� Rect 	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../../FKEngine/FKEngineCommonHead.h"
//-------------------------------------------------------------------------
class IStarTouchHandle
{
public:
	virtual void OnTouchEnd(CCPoint& pos) = 0;
};

class CStarWidget : public FKCW_UIWidget_ColorView
{
public:
	CStarWidget();
	virtual ~CStarWidget();

public:
	static CStarWidget* create(const ccColor4B& color,IStarTouchHandle* pTouchHandle = NULL);

public:
	virtual void onTouchMoved(CCTouch* pTouch, float fDuration);
	virtual void onTouchEnded(CCTouch* pTouch, float fDuration);
	virtual void onTouchCancelled(CCTouch* pTouch, float fDuration);

public:

	void		SetTouchHandel(IStarTouchHandle* pHandle);
	void		DoEffect(CCPoint&pos,string strEffectName,string strEffectFirstFarmeName);
	void		OnEffectEnd(CCNode* pSender);
	void		DoSpecialEffect(string strFrameName);
private:
	IStarTouchHandle* m_pTouchHandel;
};

