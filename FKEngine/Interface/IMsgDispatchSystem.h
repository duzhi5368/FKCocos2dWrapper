//*************************************************************************
//	��������:	2015-1-12
//	�ļ�����:	IMsgDispatchSystem.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
/*
	ע�⣺����ӿڽ��ṩ��������Ϣ�ַ�������Ҫ�߼��ڲ���Ϣ�ַ�����ʹ��EventSystem
*/
//-------------------------------------------------------------------------
// ��Ϣ���ͼ�����
typedef unsigned short MSG_MAIN_TYPE;		// ����Ϣ������
typedef unsigned short MSG_SUB_TYPE;		// ����Ϣ������
//-------------------------------------------------------------------------
// ��Ϣ���ջص�������
class IMessageHandler
{
public:
	// ���յ���Ϣ[ע�⣬�յ�����Ϣ�ڣ���������Ϣ�룬������������Ϣ��]
	// ������szMsgData �յ�������ָ��
	// ������nLen �յ������ݳ���
	virtual void		OnNetMessage( const char* szMsgData, int nLen ) = 0;
};
//-------------------------------------------------------------------------
// ��Ϣ�ַ���ϵͳ
class IMsgDispatchSystem
{
public:
	// �ͷ�
	virtual void		Release() = 0;
	// �ַ���Ϣ
	// ������szMsgData ��Ҫ�ַ�������ָ��
	// ������nLen ��Ҫ�ַ������ݳ���
	virtual void		DispatchMsg( const char* szMsgData, int nLen ) = 0;
	// ע����Ϣ��������
	// ������pHandler ��Ϣ��������
	// ������usMainType ����Ϣ��
	// ������usSubType ����Ϣ��
	virtual bool		RegisteMsgHandler( IMessageHandler* pHandler, 
		MSG_MAIN_TYPE usMainType, MSG_SUB_TYPE usSubType ) = 0;
	// ע����Ϣ��������
	virtual bool		UnregisterMsgHandler( IMessageHandler* pHandler,
		MSG_MAIN_TYPE usMainType, MSG_SUB_TYPE usSubType ) = 0;
};
//-------------------------------------------------------------------------
// ��ȡ��Ϣ�ַ����ӿ�
extern IMsgDispatchSystem* GetMsgDispatchSystem();
//-------------------------------------------------------------------------