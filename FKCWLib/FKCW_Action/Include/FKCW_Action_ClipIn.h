//*************************************************************************
//	��������:	2014-11-3
//	�ļ�����:	FKCW_Action_ClipIn.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	����ʾһ���ڵ�
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_Action_Macros.h"
//-------------------------------------------------------------------------
// ����ʾһ���ڵ�
// ע���ö������ɱ� CCClippingNode ִ�У��Ҹ� CCClippingNode ������һ��CCDrawNodeģ��
class FKCW_Action_ClipIn : public CCActionInterval
{
private:
	float			m_fCos;			// ����cosֵ
	float			m_fSin;			// ����sinֵ
	float			m_fDistance;	// ��������
	CCPoint			m_tagP1;		// �ױ߹̶���1
	CCPoint			m_tagP2;		// �ױ߹̶���2
	CC_SYNTHESIZE_PASS_BY_REF(CCPoint, m_tagDirection, Direction);
protected:
	FKCW_Action_ClipIn();
public:
	virtual ~FKCW_Action_ClipIn();
	// ����һ�� ClipIn ����ʵ��
	// ������p_fDuration ��������ʱ��
	//		p_tagV �ü������ƶ�����ʸ����Ĭ�����������(1,0)����ʾ��X���ƶ�
	static FKCW_Action_ClipIn* Create( float p_fDuration, CCPoint p_tagV = ccp(1, 0 ));

	bool	InitWithDuration( float p_fDuration, CCPoint p_tagV );

	virtual void update(float time);
	virtual void startWithTarget(CCNode *pTarget);
	virtual CCActionInterval* reverse();
};