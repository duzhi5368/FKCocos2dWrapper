//*************************************************************************
//	��������:	2015-2-9
//	�ļ�����:	FKCamera.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../FKEngineCommonHead.h"
//-------------------------------------------------------------------------
class FKCameraSystem :public ICameraSystem
{
public:
	FKCameraSystem();
	~FKCameraSystem();
public:
	// ��ȡ��ǰ�ӿ���������
	virtual void		GetViewport( CCPoint& pt );
	// ���õ�ǰ�ӿ���������
	virtual void		SetViewport( CCPoint& pt );
	// ��ȡ��ǰ�ӿڿ��ӷ�Χ
	virtual void		GetViewSize( CCSize& size );
	// ���õ�ǰ�ӿڿ��ӷ�Χ
	virtual void		SetViewSize( CCSize& size );
	// ��ȡ��ǰ�������������
	virtual void		GetViewRect( CCRect& rect );

	// ���ӿ�
	// ������fMinRange ����С��Χ
	// ������fMaxRange �����Χ
	// ������fTime �����¼�
	virtual void		ShakeCamera( float fMinRange, float fMaxRange, float fTime );
	// �����ӿڸ���
	// ������pFollower �������
	virtual void		TrackCamera( CCNode* pFollower );
	// �����ӿ�·���������������ָ��·���ƶ�
	// ������strPointListFile �㼯�ļ����ļ��ڰ������б��ʱ�䣩
	virtual void		TrackCamera( const string& strPointListFile );
	// �����ӿ���������Զ
	// ������fScaleDis �����������Ⱦ��ľ���
	virtual void		StrechCamera( float fScaleDis );
};
//-------------------------------------------------------------------------
extern FKCameraSystem gs_FKCameraSystem;
//-------------------------------------------------------------------------