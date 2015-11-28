//*************************************************************************
//	��������:	2015-1-22
//	�ļ�����:	FKAnimateEx.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../FKEngineCommonHead.h"
#include "FKAnimateExRes.h"
//-------------------------------------------------------------------------
// ��������״̬
enum ENUM_AnimState
{
	eAnimState_Normal	= 0,	// ��������״̬
	eAnimState_Pause	= 1,	// ��ͣ״̬
	eAnimState_Stop		= 2,	// ֹͣ״̬
};
//-------------------------------------------------------------------------
class FKAnimateExRes;
class FKAnimateEx : public IAnimation
{
public:
	FKAnimateEx();
	~FKAnimateEx();
public:
	// ����
	virtual void	Reset();
	// ���ö�����Դ
	virtual void	SetAnimateExRes( FKAnimateExRes* pAniRes );
	// ����Ŀ�����
	virtual void	SetTargetNode( CCNode* pTaeget );
	// ֡����
	virtual void	Update( float dt );
public:
	// ���ö������Żص�����
	virtual void	SetAniCallback( IAnimationCallback* p_pAniCallBack, void* p_pContext );

	// ���Ŷ��������ö�������ֹͣ״̬�����������
	virtual void	Play( const std::string& p_szAniName, float p_fSpeed = 1.0f,
		int p_nLoops = -1, bool p_bForceUpdate = false );

	// ֹͣ����
	virtual void	Stop();

	// ��ͣ����
	virtual void	Pause();

	// �Ƿ񶯻��ڲ���
	virtual bool	IsPlaying();

	// �Ƿ񶯻�����ͣ״̬
	virtual bool	IsPause();

	// �Ƿ����ָ�����ƵĶ���
	virtual bool	IsAniExit( const string& p_szAniName );

	// ��ȡ�����б�
	virtual void	GetAnimationList( FK_OUT list<string>& p_listAnimations );

	// ����/��ȡ�����ٶ�
	virtual void	SetSpeed( float p_fSpeed );
	virtual float	GetSpeed();
protected:
	// �����ص�
	void			_OnAniCallback( float fLastTime, float fCurTime, float fDuration );
private:
	bool			m_bIsResValid;		// �Ƿ���Դ��Ч
	float			m_fTime;			// ��������ʱ��
	float			m_fSpeed;			// ���������ٶ�
	int				m_nLoopTime;		// �������Ŵ���
	int				m_nNextFrame;		// ��һ֡����
	bool			m_bIsNewLoop;		// �Ƿ����µĲ���ѭ��
	string			m_szCurAniName;		// ��ǰ������
	FKAnimateExRes*	m_pAniRes;			// ����������Դ
	ENUM_AnimState	m_eState;			// ��������״̬
	CCAnimation*	m_pCurAnimation;	// ��ǰ����
	CCNode*			m_pTarget;			// Ŀ�����
	vector<float>	m_vecFrameTimes;	// ֡ʱ��

	IAnimationCallback*			m_pAniCallback;			// �������Żص�
	void*						m_pAniCallbackContext;	// �����ص�����
	vector<SAnimationCallback>	m_vecAniCallbacks;		// �����ص�����
};