//*************************************************************************
//	��������:	2014-12-23
//	�ļ�����:	FKCW_Action_Curl.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_Action_Macros.h"
//--------------------------------------------------------------------
class FKCW_Action_Curl : public CCActionInterval
{
private:
	CCPoint m_center;			// ���ĵ�
	float m_fromRadius;			// From�뾶
	float m_toRadius;			// To�뾶
	float m_angularVelocity;	// ���ٶ�
	float m_initAngle;			// ��ʼ�Ƕ�

public:
	FKCW_Action_Curl();
	virtual ~FKCW_Action_Curl();

	static FKCW_Action_Curl* Create(float duration, CCPoint center, float toRadius, float angularVelocity);
	bool initWithDuration(float d, CCPoint center, float toRadius, float angularVelocity);

	virtual void update(float time);
	virtual void startWithTarget(CCNode *pTarget);
	virtual CCObject* copyWithZone(CCZone* pZone);
	virtual CCActionInterval* reverse();
};