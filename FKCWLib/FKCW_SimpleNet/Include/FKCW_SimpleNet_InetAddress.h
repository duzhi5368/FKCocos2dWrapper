//*************************************************************************
//	��������:	2014-11-15
//	�ļ�����:	FKCW_SimpleNet_InetAddress.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	��ַ
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_SimpleNet_Macro.h"
//-------------------------------------------------------------------------
class FKCW_SimpleNet_InetAddress : public sockaddr_in
{
public:
	FKCW_SimpleNet_InetAddress();
	FKCW_SimpleNet_InetAddress(const char* ip, unsigned short port);
	FKCW_SimpleNet_InetAddress(const struct sockaddr* addr);
	virtual ~FKCW_SimpleNet_InetAddress(void);

public:
	operator struct sockaddr*();
	operator const struct sockaddr*() const;
	const char*		getHostAddress() const;
	const char*		getIp() const;
	unsigned short	getPort() const;
	void			setIp(const char* ip);
	void			setIp(unsigned int ip);
	void			setPort(unsigned short port);
	void			setHost(const char* name);
	int				getLength();
};
//-------------------------------------------------------------------------