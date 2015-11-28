//*************************************************************************
//	��������:	2015-1-16
//	�ļ�����:	FKUISystem.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../FKEngineCommonHead.h"
//-------------------------------------------------------------------------
class CRootUIScene;
class FKUISystem : public IUISystem
{
public:
	FKUISystem();
	~FKUISystem();
public:
	// �ͷ�����
	virtual void							Release();
	// ��ȡUIϵͳ���ڵ㴰��
	virtual FKCW_UIWidget_WidgetWindow*		GetRoot() const;
private:
	FKCW_UIWidget_WidgetWindow*				m_pRootWindow;
};
//-------------------------------------------------------------------------
extern FKUISystem gs_FKUISystem;
//-------------------------------------------------------------------------