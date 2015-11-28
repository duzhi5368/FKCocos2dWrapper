/********************************************************************
	created:	2014/11/03
	file base:	FKCW_Action_Shake
	author:		FreeKnight
	
	purpose:	��
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include "FKCW_Action_Macros.h"
//--------------------------------------------------------------------
// �ڵ������һ��Բ���˶�����������
class FKCW_Action_Shake : public CCActionInterval
{
private:
	enum ENUM_ShakeMode{
		eShakeMode_Ring,
		eShakeMode_DynamicRing,
	};
protected:
	float		m_fMinRadius;			// ��Ȧ��С�뾶
	float		m_fMaxRadius;			// ��Ȧ���뾶
	float		m_fEndMaxRadius;		// eShakeMode_DynamicRingģʽ��ʹ�á����ƫ�Ʒ�Χ
	float		m_fEndMinRadius;		// eShakeMode_DynamicRingģʽ��ʹ�á���Сƫ�Ʒ�Χ
	float		m_fOriginalX;			// �ڵ�Ļ�׼��x
	float		m_fOriginalY;			// �ڵ�Ļ�׼��y
	ENUM_ShakeMode	m_eMode;			// �ڵ���ģʽ
protected:
	FKCW_Action_Shake();
public:
	// ����һ����̬Ȧ�𶯶���
	// ������duration ����ʱ��
	static FKCW_Action_Shake* Create( float duration, float maxRadius, float minRadius = 0 );

	// ����һ����̬Ȧ�𶯶���
	static FKCW_Action_Shake* Create( float duration, float startMaxRadius, float endMaxRadius, float startMinRadius, float endMinRadius );

	virtual ~FKCW_Action_Shake();

	bool	InitWithRing( float duration, float maxRadius, float minRadius );
	bool	InitWithDynamicRing( float duration, float startMaxRadius, float endMaxRadius, float startMinRadius, float endMinRadius );

	virtual CCObject* copyWithZone(CCZone* pZone);
	virtual CCActionInterval* reverse();
	virtual void update(float t);
	virtual void startWithTarget(CCNode* pTarget);
};