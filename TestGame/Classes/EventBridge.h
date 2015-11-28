//*************************************************************************
//	��������:	2015-3-24
//	�ļ�����:	EventBridge.h
//  �� �� ��:   �˹۸� Rect 	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../../FKEngine/FKEngineCommonHead.h"
//-------------------------------------------------------------------------
class EventBridge : public IExecEventHandler
{
public:
	EventBridge(void);
	~EventBridge(void);

public:
	// �յ�ִ����Ϣ����ص�
	// ������usID �¼�ID
	// ������usSrcType ������Դ���ͣ��μ����ö�٣�
	// ������unSrcID ������Ψһ��ʾ�������ǽ�ɫUID����ƷUID��
	//		�Լ�ĳ����ָ��ȣ�����Ϣ�����߼�����Ա�Լ��涨��
	// ������szEvent ��Ϣ��������ָ��
	// ������nEventLen ��Ϣ���ݵĳ���
	virtual void	OnExec( EVENT_TYPE usID, unsigned short usSrcType,
		unsigned int unSrcID, const char* szEvent, int nEventLen );

public:
	// ע��ȫ���¼�
	void			RegisteFKEvent();
	// �Ƴ�ȫ���¼�
	void			UnRegisteFKEvent();

private:
	// �л�Scene
	void			__SwitchScene(int nTag);
	// ��ť�ص���Ϣ����
	void			__ClickPlayButton(int nTag);
};

