//*************************************************************************
//	��������:	2014-11-18
//	�ļ�����:	FKCW_EffectNode_Shatter.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_EffectNode_Mesh.h"
#include "FKCW_EffectNode_IndexVBO.h"
#include "FKCW_EffectNode_GLProgramWithUnifos.h"
//-------------------------------------------------------------------------
class FKCW_EffectNode_ShatterFragSprite:public CCSprite
{
public:
	int m_randomNumber;
	FKCW_EffectNode_ShatterFragSprite()
	{
		m_randomNumber=-1;
	}
};
//-------------------------------------------------------------------------
class FKCW_Action_ShatterAction;
class FKCW_EffectNode_ShatterSprite:public CCSprite
{
public:
	friend class FKCW_Action_ShatterAction;
public:
	FKCW_EffectNode_ShatterSprite();
	virtual~FKCW_EffectNode_ShatterSprite();

	bool		init(const string&texFileName);

protected:
	void		_CreateShatter();
	void		_ResetShatter();
	void		_UpdateShatterAction(float time,float dt,float growSpeedOfTargetR);
protected:
	float m_gridSideLen;				// ���ӱ߳���Ҳ������Ƭ�߳���С
	float m_initalFrageScale;			// ������Ҫ��ʼ��������΢�Ŵ�
	vector<vector<FKCW_EffectNode_ShatterFragSprite*> > m_grid;// ȫ����Ƭ�б�
	CCSpriteBatchNode* m_fragBatchNode;	// ��ȫ����Ƭ��ӵ���batchNode��
};
//-------------------------------------------------------------------------
class FKCW_Action_ShatterAction : public CCActionInterval
{
public:
	FKCW_Action_ShatterAction();
	virtual~FKCW_Action_ShatterAction();

	static FKCW_Action_ShatterAction* create(float fDuration);
	bool			initWithDuration(float fDuration);

	virtual void	stop();
	virtual void	startWithTarget(CCNode *pTarget);
	virtual void	update(float time);
	virtual bool	isDone();
protected:
	void			_InitMembers();
protected:
	float m_timeFoe;
	float m_timeCur;
	float m_growSpeedOfTargetR;
};
//-------------------------------------------------------------------------