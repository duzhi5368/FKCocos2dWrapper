//*************************************************************************
//	��������:	2015-1-15
//	�ļ�����:	TestApp.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../../FKEngine/FKEngineCommonHead.h"
#include "EventBridge.h"
//-------------------------------------------------------------------------
class TestApp : public FKFramework
{
public:
	virtual bool	SubInit();
	virtual void	SubUpdate( float dt );
	virtual void	SubRelease();
public:

	// �յ�������Ϣ�Ļص�������
	// ������unMsgType �������Ϣ���͡��μ�ENUM_InputMsgType��
	// ������nTouchID ������Ϣ��ID����Ϊkey��Ϣ�����ֵ��ЧΪ0
	// ������fPosX xλ��
	// ������fPosY y��Ϣ
	// ��������ϸ����ָ�룬���������Ϣ�ж�������ݣ��Ŵ�����С�������Ķ������ݣ��������򣩵ȣ�����¼�ڴˡ�
	// ����ֵ��������true��ʾ���Ժ���ĵ��ã���Ϣ������󴫵ݣ�������false���ʾ��Ϣ���������´���
	virtual bool	OnInputMessage( unsigned int unMsgType, int nTouchID, 
		float fPosX, float fPosY, void* pParam );
	
private:
	// �Զ���Ļ����
	void			__AutomaticScreenAdaptation();
	// ����ȫ����Դ
	void			__LoadGlobleResources();
	// �ͷ�ȫ����Դ
	void			__RelesaeGlobleResources();

private:
	EventBridge m_EventBridge;

};
//-------------------------------------------------------------------------
extern TestApp* GetApp();
//-------------------------------------------------------------------------