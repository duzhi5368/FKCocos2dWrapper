//*************************************************************************
//	��������:	2015-1-28
//	�ļ�����:	ICamera.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../../FKCWLib/FKCocos2dxWrapper.h"
//-------------------------------------------------------------------------
class ICameraSystem
{
public:
	// ��ȡ��ǰ�ӿ���������
	virtual void		GetViewport( CCPoint& pt ) = 0;
	// ���õ�ǰ�ӿ���������
	virtual void		SetViewport( CCPoint& pt ) = 0;
	// ��ȡ��ǰ�ӿڿ��ӷ�Χ
	virtual void		GetViewSize( CCSize& size ) = 0;
	// ���õ�ǰ�ӿڿ��ӷ�Χ
	virtual void		SetViewSize( CCSize& size ) = 0;
	// ��ȡ��ǰ�������������
	virtual void		GetViewRect( CCRect& rect ) = 0;

	// ���ӿ�
	// ������fMinRange ����С��Χ
	// ������fMaxRange �����Χ
	// ������fTime �����¼�
	virtual void		ShakeCamera( float fMinRange, float fMaxRange, float fTime ) = 0;
	// �����ӿڸ���
	// ������pFollower �������
	virtual void		TrackCamera( CCNode* pFollower ) = 0;
	// �����ӿ�·���������������ָ��·���ƶ�
	// ������strPointListFile �㼯�ļ����ļ��ڰ������б��ʱ�䣩
	virtual void		TrackCamera( const string& strPointListFile ) = 0;
	// �����ӿ���������Զ
	// ������fScaleDis �����������Ⱦ��ľ���
	virtual void		StrechCamera( float fScaleDis ) = 0;
};
//-------------------------------------------------------------------------
// ��ȡ�����ϵͳ
extern ICameraSystem*	GetCameraSystem();
//-------------------------------------------------------------------------