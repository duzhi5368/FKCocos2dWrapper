//*************************************************************************
//	��������:	2014-8-18   18:20
//	�ļ�����:	IAnimation.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../Include/BaseMacro.h"
#include <string>
#include <list>
using std::string;
using std::list;
//-------------------------------------------------------------------------
struct SAnimationCallbackInfo
{
	char	m_szActName[32];	// ��������
	char	m_szName[32];		// �ص�����
	float	m_fFrameTime;		// ֡�ص�ʱ��

	SAnimationCallbackInfo()
	{
		memset( this, 0, sizeof(*this) );
	}
};

// �������Žӿ�
class IAnimationCallback
{
public:
	virtual void	OnAnimaitonCallback( const SAnimationCallbackInfo& p_tagInfo, void* p_pContext ) = 0;
};

class IAnimation
{
public:
	// ���ö������Żص�����
	virtual void	SetAniCallback( IAnimationCallback* p_pAniCallBack, void* p_pContext ) = 0;

	// ���Ŷ��������ö�������ֹͣ״̬�����������
	virtual void	Play( const std::string& p_szAniName, float p_fSpeed = 1.0f, int p_nLoops = -1, bool p_bForceUpdate = false ) = 0;

	// ֹͣ����
	virtual void	Stop() = 0;

	// ��ͣ����
	virtual void	Pause() = 0;

	// �Ƿ񶯻��ڲ���
	virtual bool	IsPlaying() = 0;

	// �Ƿ񶯻�����ͣ״̬
	virtual bool	IsPause() = 0;

	// �Ƿ����ָ�����ƵĶ���
	virtual bool	IsAniExit( const string& p_szAniName ) = 0;

	// ��ȡ�����б�
	virtual void	GetAnimationList( FK_OUT list<string>& p_listAnimations ) = 0;

	// ����/��ȡ�����ٶ�
	virtual void	SetSpeed( float p_fSpeed ) = 0;
	virtual float	GetSpeed() = 0;
};

//-------------------------------------------------------------------------

//-------------------------------------------------------------------------