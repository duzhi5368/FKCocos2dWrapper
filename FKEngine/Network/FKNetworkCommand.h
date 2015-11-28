//*************************************************************************
//	��������:	2015-1-10
//	�ļ�����:	FKNetworkCommand.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../FKEngineCommonHead.h"
#include "FKNetworkMacros.h"
//-------------------------------------------------------------------------
class FKNetworkCommand
{
public:
	unsigned int			m_unType;		// ��Ϣ����[ENUM_ClientNetMsgType]
	unsigned int			m_unSocketID;	// SocketID
	unsigned int			m_unSocket;		// Socketָ�� ���� ErrorCode
	unsigned int			m_unLen;		// ��Ϣ���� ���� ������ʾ��Ϣ����
	vector<char>			m_szMsg;		// ��Ϣ���� ���� ������ʾ��Ϣ
public:
	FKNetworkCommand();
	FKNetworkCommand( const FKNetworkCommand& other );
	FKNetworkCommand& operator= ( const FKNetworkCommand& other );
};