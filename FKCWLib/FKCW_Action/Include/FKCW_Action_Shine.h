/********************************************************************
	created:	2014/11/04
	file base:	FKCW_Action_Shine
	author:		FreeKnight
	
	purpose:	��̬����Ч��
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include "FKCW_Action_Macros.h"
//--------------------------------------------------------------------
// ��һ��node����ʾһϵ�й���Ч��
// ��Ч��Ϊ���������ƶ�һ�Σ�����Ϊ�ݶ�״�����ɱ��������������ɫ
class FKCW_Action_Shine : public CCActionInterval
{
private:
	CCGLProgram*				m_pOldProgram;	// �ϵ�Program
	CCSize						m_tagSize;		// Ŀ���С
	CC_SYNTHESIZE_PASS_BY_REF(ccColor4B, m_tagColor1, Color1);
	CC_SYNTHESIZE_PASS_BY_REF(ccColor4B, m_tagColor2, Color2);
	CC_SYNTHESIZE_PASS_BY_REF(ccColor4B, m_tagColor3, Color3);
	CC_SYNTHESIZE_PASS_BY_REF(ccVertex3F, m_tagGradientPositions, GradientPositions);	// �ݶ�λ��
protected:
	FKCW_Action_Shine();
public:
	virtual ~FKCW_Action_Shine();

	static FKCW_Action_Shine* Create(float duration, ccColor4B color1, ccColor4B color2, ccColor4B color3, ccVertex3F gradientPositions);
	bool InitWithColors(float duration, ccColor4B color1, ccColor4B color2, ccColor4B color3, ccVertex3F gradientPositions);

	virtual void update(float time);
	virtual void startWithTarget(CCNode *pTarget);
	virtual void stop();
	virtual CCObject* copyWithZone(CCZone* pZone);
	virtual CCActionInterval* reverse();
};