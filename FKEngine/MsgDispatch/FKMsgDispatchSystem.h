//*************************************************************************
//	��������:	2015-1-12
//	�ļ�����:	FKMsgDispatchSystem.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../FKEngineCommonHead.h"
//-------------------------------------------------------------------------
class FKMsgDispatchSystem : public IMsgDispatchSystem
{
public:
	FKMsgDispatchSystem();
	~FKMsgDispatchSystem();
public:
	// �ͷ�
	virtual void		Release();
	// �ַ���Ϣ
	// ������szMsgData ��Ҫ�ַ�������ָ��
	// ������nLen ��Ҫ�ַ������ݳ���
	virtual void		DispatchMsg( const char* szMsgData, int nLen );
	// ע����Ϣ��������
	// ������pHandler ��Ϣ��������
	// ������usMainType ����Ϣ��
	// ������usSubType ����Ϣ��
	virtual bool		RegisteMsgHandler( IMessageHandler* pHandler, 
		MSG_MAIN_TYPE usMainType, MSG_SUB_TYPE usSubType );
	// ע����Ϣ��������
	virtual bool		UnregisterMsgHandler( IMessageHandler* pHandler, 
		MSG_MAIN_TYPE usMainType, MSG_SUB_TYPE usSubType );
private:
	typedef list<IMessageHandler*>			MESSAGE_RECEIVER_LIST;
	typedef map<MSG_MAIN_TYPE,MESSAGE_RECEIVER_LIST>	MESSAGE_RECEIVER_ARRAY;

	MESSAGE_RECEIVER_ARRAY		m_MsgReceiverArray;
};
//-------------------------------------------------------------------------
extern FKMsgDispatchSystem gs_FKMsgDispatchSystem;
//-------------------------------------------------------------------------