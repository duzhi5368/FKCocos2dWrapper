//*************************************************************************
//	��������:	2014-11-3
//	�ļ�����:	FKCW_Action_Missile.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	����/Ͷ���� ���ٶ���
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_Action_Macros.h"
//-------------------------------------------------------------------------
/*
	��һ��node�ƶ�����һ��node����
	ִ�ж����Ķ���ڵ� �� �ƶ�Ŀ��λ��Ŀ��ڵ㣬��������ͬһ�����ڵ㡣
	��������ʼ�󣬶���ڵ㿪ʼ��Ŀ��ڵ㻡���ƶ������ߵ���������Ŀ��ڵ�λ��ÿ֡���е�����
	ע�⣬�ö�����������Ᵽ��Ŀ��ڵ㣬�����û����뱣֤�����������֮ǰ��Ŀ��ڵ��Ȼ���ڡ�
	����ΪĿ��ڵ�����ƶ������Ե��������ĳ���ʱ���޷��϶���������sequence����Э��������ɻص���
*/
class FKCW_Action_Missile : public CCActionInterval
{
protected:
	float			m_fVelocity;		// �ƶ��ٶ�
	CCNode*			m_pAimedNode;		// Ŀ��ڵ�
	float			m_fPresetDegree;	// Ԥ�Ƕ�( �����ڵ� ����� Ŀ��ڵ��·���Ƕ�)
	float			m_fDstDegree;		// Ŀ��Ƕ�
	CCCallFunc*		m_pDoneCallFunc;	// �����Ϣ�ص�
	bool			m_bIsDone;			// �Ƿ���ɱ�ǩ
public:
	// ����һ���������ٶ�������
	// ������velocity �ƶ��ٶ� aimed Ŀ����� 
	//	targetPresetDegree ����ڵ����Ŀ��ڵ����ת�Ƕȣ���ֵ��ʾ˳ʱ��
	static FKCW_Action_Missile* Create( float velocity, CCNode* aimed, float targetPresetDegree, CCCallFunc* doneCallFunc = NULL );

	FKCW_Action_Missile();
	virtual ~FKCW_Action_Missile();

	bool InitWithVelocity( float velocity, CCNode* aimed, float targetPresetDegree, CCCallFunc* doneCallFunc );

	virtual CCObject* copyWithZone(CCZone* pZone);
	virtual void step(float dt);
	virtual bool isDone() { return m_bIsDone; }
};