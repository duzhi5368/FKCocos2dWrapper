//*************************************************************************
//	��������:	2015-1-17
//	�ļ�����:	IRenderSystem.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../../FKCWLib/FKCocos2dxWrapper.h"
#include "IRenderObj.h"
//-------------------------------------------------------------------------
class IRenderText;
class IMapMgr;
class IMapObj;
class IRenderSystem
{
public:
	// ��ʼ����Ⱦϵͳ
	// ������tagDesignSize ��Ⱦ���ڴ�С
	virtual void		Init( CCSize& tagDesignSize ) = 0;
	// ���ø���Ⱦ�ڵ㣬���г���ȫ���ҽ��ڱ��ڵ���
	virtual void		SetRoot( CCNode* pMapRootNode ) = 0;
	// ��ȡ��ǰ�����еĵ�ͼ����
	virtual IMapObj*	GetCurrentMap() = 0;
	// ���½����³���
	// ������szFKMFileName ��ͼ�����ļ�
	virtual unsigned int	EnterMap( const char* szFKMFileName ) = 0;
	// �Ƿ�����Update
	virtual void			SetEnableUpdate( bool bIsEnable ) = 0;
	// ���ó���������ӵ�
	// ������tagLocPos ������ӵ�λ��
	virtual void		SetViewPoint( const CCPoint& tagLocPos ) = 0;
	// ��ȡ����������ӵ�
	// ������[out]tagLocPos ������ӵ�λ��
	virtual bool		GetViewPoint( const CCPoint& tagLocPos ) = 0;
	// ת����Ļ���굽��������
	// ������[in]tagScreenPos ��Ļ����
	// ������[out]tagScenePos ��������
	virtual bool		ConvertScreenPosToScenePos( const CCPoint& tagScreenPos,
		CCPoint& tagScenePos ) = 0;

	// ��ȡ��ײ����
	// ������ObjList ����ײ�Ķ����б�
	virtual void		HitRenderObj( const CCPoint& tagScreenPos, list<IRenderObj*>& ObjList ) = 0;
	// ������Ⱦ����
	// ������szGameObjName ��Ϸ������
	virtual IRenderObj*	CreateRenderObj( const char* szGameObjName ) = 0;
	// ɾ����Ⱦ����
	// ����: pRenderObj ��Ҫɾ������Ⱦ����
	virtual bool		RemoveRenderObj( IRenderObj* pRenderObj ) = 0;
	// ɾ����Ⱦ����
	// ����: id ��Ҫɾ������Ⱦ����ID
	virtual bool		RemoveRenderObj( RENDER_OBJ_ID id ) = 0;
	// �����Ⱦ���󵽵�ǰ����
	// ������pRenderObj �����Ⱦ���󵽵�ǰ����
	virtual bool		AddRenderObjToScene( IRenderObj* pRenderObj ) = 0;
	// �ӵ�ǰ����ɾ����Ⱦ����
	// ������pRenderObj ��Ҫ�ӵ�ǰ����ɾ������Ⱦ����
	virtual bool		RemoveRenderObjFromScene( IRenderObj* pRenderObj ) = 0;

	// ������Ⱦ����
	// ������szString ����
	// ������szFontName ��������
	// ������nFontSize �����С
	// ������tagDimentions ����ߴ�
	// ������bIsBmpFont �Ƿ���BMP����
	virtual IRenderText* CreateRenderText( const char* szString, const char* szFontName, 
		int nFontSize,  CCSize tagDimentions = CCSizeZero, bool bIsBmpFont = false ) = 0;
	// ɾ����Ⱦ����
	// ������pRenderText ��Ҫɾ������Ⱦ����
	virtual bool		RemoveRenderText( IRenderText* pRenderText ) = 0;
	// ɾ����Ⱦ����
	// ������id ΨһID
	virtual bool		RemoveRenderTextByID( RENDER_OBJ_ID id ) = 0;
};
//-------------------------------------------------------------------------
// ��ȡ��Ⱦϵͳ
extern IRenderSystem* GetRenderSystem();
//-------------------------------------------------------------------------