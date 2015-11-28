//*************************************************************************
//	��������:	2015-1-10
//	�ļ�����:	FKNetworkMacros.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
// �ͻ������socket������
static const int		gs_MAX_CLIENT_SOCKET_NUM		= 16;
// �ͻ������ӳ�ʱʱ��
static const float		gs_MAX_TIMEOUT_TIME				= 3.0f;
//-------------------------------------------------------------------------
// �ͻ���������Ϣ����ö��
enum ENUM_ClientNetMsgType
{
	eCNMT_ConnectSuccess		= 0,		// ���ӳɹ���Ϣ
	eCNMT_RecvMsg,							// ���յ�������Ϣ
	eCNMT_Close,							// ���ӹر�
	eCNMT_Error,							// �쳣����
};
//-------------------------------------------------------------------------
// �ͻ������Ӵ�������ö��
enum ENUM_ClientNetErrorType
{
	eCNET_Unknown				= 0,		// δ��ȷ���쳣
	eCNET_IoError,							// IO��д����
	eCNET_ConnectTimeout,					// ���ӳ�ʱ
	eCNET_NotEnoughMemory,					// �ڴ治��

	// todo...

	eCNET_Max,
};
static const string gs_ClientNetErrorInfo[eCNET_Max] = 
{
	"δ��ȷ���쳣",
	"��д����",
	"���ӳ�ʱ",
	"�ڴ治��",
};
//-------------------------------------------------------------------------
