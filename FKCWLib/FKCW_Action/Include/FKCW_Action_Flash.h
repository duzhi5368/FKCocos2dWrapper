//*************************************************************************
//	��������:	2014-11-3
//	�ļ�����:	FKCW_Action_Flash.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	����Ч��
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_Action_Macros.h"
//-------------------------------------------------------------------------
// ��һ���ڵ�Ĳ�͸������ִ������Ч��
class FKCW_Action_Flash : public CCActionInterval
{
private:
	CCGLProgram*			m_pOldProgram;		// ��¼��һ�ε�program
	ccColor3B				m_tagColor;			// ��ɫ
	float					m_fR;
	float					m_fG;
	float					m_fB;
protected:
	FKCW_Action_Flash();
public:
	virtual ~FKCW_Action_Flash();

	// ����һ���������
	// ������p_fDuration ���⶯������ʱ�� p_tagColor ����ɫ
	static FKCW_Action_Flash* Create(float p_fDuration, ccColor3B p_tagColor );

	bool InitWithDurationAndColor(float d, ccColor3B c);

	virtual void update(float time);
	virtual void startWithTarget(CCNode *pTarget);
	virtual void stop();
	virtual CCObject* copyWithZone(CCZone* pZone);
	virtual CCActionInterval* reverse();
};