//*************************************************************************
//	��������:	2015-2-2
//	�ļ�����:	FKRenderSystem.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../FKEngineCommonHead.h"
//-------------------------------------------------------------------------
class FKRenderObjMgr;
class FKBannerReelMapMgr;
class FKRenderTextMgr;
class FKRenderSystem : public IRenderSystem
{
public:
	FKRenderSystem();
	~FKRenderSystem();
public:
	// ��ʼ����Ⱦϵͳ
	// ������tagDesignSize ��Ⱦ���ڴ�С
	virtual void		Init( CCSize& tagDesignSize );
	// ���ø���Ⱦ�ڵ㣬���г���ȫ���ҽ��ڱ��ڵ���
	virtual void		SetRoot( CCNode* pMapRootNode );
	// ��ȡ��ǰ�����еĵ�ͼ����
	virtual IMapObj*	GetCurrentMap();
	// ���½����³���
	// ������szFKMFileName ��ͼ�����ļ�
	virtual RENDER_MAP_ID	EnterMap( const char* szFKMFileName );
	// �Ƿ�����Update
	virtual void			SetEnableUpdate( bool bIsEnable );
	// ���ó���������ӵ�
	// ������tagLocPos ������ӵ�λ��
	virtual void		SetViewPoint( const CCPoint& tagLocPos );
	// ��ȡ����������ӵ�
	// ������[out]tagLocPos ������ӵ�λ��
	virtual bool		GetViewPoint( const CCPoint& tagLocPos );
	// ת����Ļ���굽��������
	// ������[in]tagScreenPos ��Ļ����
	// ������[out]tagScenePos ��������
	virtual bool		ConvertScreenPosToScenePos( const CCPoint& tagScreenPos,
		CCPoint& tagScenePos );

	// ��ȡ��ײ����
	// ������ObjList ����ײ�Ķ����б�
	virtual void		HitRenderObj( const CCPoint& tagScreenPos, list<IRenderObj*>& ObjList );
	// ������Ⱦ����
	// ������szGameObjName ��Ϸ������
	virtual IRenderObj*	CreateRenderObj( const char* szGameObjName );
	// ɾ����Ⱦ����
	// ����: pRenderObj ��Ҫɾ������Ⱦ����
	virtual bool		RemoveRenderObj( IRenderObj* pRenderObj );
	// ɾ����Ⱦ����
	// ����: id ��Ҫɾ������Ⱦ����ID
	virtual bool		RemoveRenderObj( RENDER_OBJ_ID id );
	// ��ȡ��Ⱦ����
	virtual IRenderObj*	GetRenderObj( RENDER_OBJ_ID id );
	// �����Ⱦ���󵽵�ǰ����
	// ������pRenderObj �����Ⱦ���󵽵�ǰ����
	virtual bool		AddRenderObjToScene( IRenderObj* pRenderObj );
	// �ӵ�ǰ����ɾ����Ⱦ����
	// ������pRenderObj ��Ҫ�ӵ�ǰ����ɾ������Ⱦ����
	virtual bool		RemoveRenderObjFromScene( IRenderObj* pRenderObj );

	// ������Ⱦ����
	// ������szString ����
	// ������szFontName ��������
	// ������nFontSize �����С
	// ������tagDimentions ����ߴ�
	// ������bIsBmpFont �Ƿ���BMP����
	virtual IRenderText* CreateRenderText( const char* szString, const char* szFontName, 
		int nFontSize,  CCSize tagDimentions = CCSizeZero, bool bIsBmpFont = false );
	// ɾ����Ⱦ����
	// ������pRenderText ��Ҫɾ������Ⱦ����
	virtual bool		RemoveRenderText( IRenderText* pRenderText );
	// ɾ����Ⱦ����
	// ������id ΨһID
	virtual bool		RemoveRenderTextByID( RENDER_OBJ_ID id );
private:
	FKRenderObjMgr*				m_pRenderObjMgr;
	FKBannerReelMapMgr*			m_pMapMgr;
	FKRenderTextMgr*			m_pRenderTextMgr;
};

//-------------------------------------------------------------------------
extern FKRenderSystem gs_FKRenderSystem;
//-------------------------------------------------------------------------

