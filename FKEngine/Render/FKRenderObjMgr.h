//*************************************************************************
//	��������:	2015-1-19
//	�ļ�����:	FKRenderObjMgr.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../FKEngineCommonHead.h"
//-------------------------------------------------------------------------
class FKRenderObj;
class FKRenderObjModel;
class FKRenderObjMgr
{
public:
	FKRenderObjMgr();
	~FKRenderObjMgr();
public:
	// ������Ⱦ����
	// ������szGameObjName ��Ϸ������
	FKRenderObj*	CreateRenderObj( const char* szFKOFileName );
	// ɾ����Ⱦ����
	// ����: id ��Ҫɾ������Ⱦ����ID
	bool			RemoveRenderObj( RENDER_OBJ_ID id );
	// ��ȡ��Ⱦ����
	FKRenderObj*	GetRenderObj( RENDER_OBJ_ID id );
	// �ͷ�δʹ�õ�ģ�Ͷ�������
	void			ReleaseUnusedObjModel();
	// �Ƿ�����Update
	void			SetEnableUpdate( bool bIsEnable );
private:
	typedef map< RENDER_OBJ_ID, FKRenderObj* >	RenderObjMap;
	typedef map< string, FKRenderObjModel* >	RenderObjModelMap;
	RenderObjMap		m_mapRenderObjs;		// ��Ⱦ���������
	RenderObjModelMap	m_mapRenderObjModels;	// ��Ⱦ����ģ�������
};