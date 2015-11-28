//*************************************************************************
//	��������:	2015-3-25
//	�ļ�����:	PlayUILayer.h
//  �� �� ��:   �˹۸� Rect 	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "GameCommon.h"
//-------------------------------------------------------------------------

class CUILayerInstance : public CCLayer
{
	CUILayerInstance(void);
	~CUILayerInstance(void);
public:
	static CUILayerInstance& instance()
	{
		static CUILayerInstance _inst;
		return _inst;
	}

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

public:

	void	AddTouchObject(CCNode* pNode);
	void	RemoveTouchObject(CCNode* pNode);
	void	RemoveTouchObjecetAll();

private:

	std::vector<CCNode*>		m_vecTouchNode;
};

