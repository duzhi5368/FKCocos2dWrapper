//*************************************************************************
//	��������:	2014-8-20   13:49
//	�ļ�����:	Cocos2dxDBAnimation.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "CommonHead.h"
#include "cocos-ext.h"
//-------------------------------------------------------------------------
USING_NS_CC;
//-------------------------------------------------------------------------
class CCocos2dxDBNode;
class CCocos2dxDBAnimation : public CCObject, public IAnimation
{
public:
	CCocos2dxDBAnimation();
	~CCocos2dxDBAnimation();
public:
	// ������Ⱦ�ڵ�
	void			SetDBNode( CCocos2dxDBNode* p_pDBNode );

	// ���ö������Żص�����
	virtual void	SetAniCallback( IAnimationCallback* p_pAniCallBack, void* p_pContext );

	// ���Ŷ��������ö�������ֹͣ״̬�����������
	// Loop -1 ��ʾ��������
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

	// ���ö���ѭ������
	virtual void	SetAniLoop( int nLoop );
private:
	// �����ص�����
	void			OnMovementEventCallFunc( extension::CCArmature* p_pArmature,
		extension::MovementEventType p_eMovementEventType, const char* p_szEventName );

	// ֡�¼��ص�
	void			OnFrameEventCallFunc( extension::CCBone* p_pBone, 
		const char* p_szEventName, int p_nFrameID, int p_nTime );

	// ���������ص�
	void			OnDBEventCallFunc( CCNode* pNode, void* p_pEvent );
private:
	int					m_nState;			// ����״̬ 0���� 1��ͣ 2ֹͣ
	float				m_fSpeed;			// ���������ٶ�
	string				m_szCurActionName;	// ��ǰ��������
	CAnimation*			m_pAnimation;		// ��������
	CArmature*			m_pArmature;		// ��������
	CCocos2dxDBNode*	m_pDBNode;			// ��Ⱦ�ڵ����
	IAnimationCallback*	m_pAniCallback;		// �������Żص�
	void*				m_pCallbackContext;	// �����ص�����
};