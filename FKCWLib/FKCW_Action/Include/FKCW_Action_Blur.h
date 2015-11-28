/********************************************************************
	created:	2014/11/03
	file base:	FKCW_Action_Blur
	author:		FreeKnight
	
	purpose:	ģ������
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include "FKCW_Action_Macros.h"
//--------------------------------------------------------------------
class FKCW_Action_Blur : public CCActionInterval
{
private:
	 CCGLProgram*				m_pOldProgram;
	 CCSize						m_tagStartBlurSize;		// ��ʼģ���Ĵ�С
	 CCSize						m_tagEndBlurSize;		// ����ģ���Ĵ�С
	 CCSize						m_tagDeltaBlurSize;		// ����ģ����С
protected:
	FKCW_Action_Blur();
public:
	virtual ~FKCW_Action_Blur();

	static	FKCW_Action_Blur* Create(float duration, CCSize startBlurSize, CCSize endBlurSize);

	bool	InitWithBlurSize(float d, CCSize startBlurSize, CCSize endBlurSize);

	virtual void update(float time);
	virtual void startWithTarget(CCNode *pTarget);
	virtual void stop();
	virtual CCObject* copyWithZone(CCZone* pZone);
	virtual CCActionInterval* reverse();
};
//--------------------------------------------------------------------