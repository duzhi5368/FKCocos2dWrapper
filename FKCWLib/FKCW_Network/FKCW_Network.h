/********************************************************************
	created:	2014/11/01
	file base:	FKCW_Network
	author:		FreeKnight
	
	purpose:	
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
/* 
====================================
ģ��˵����	
====================================
	����֧�ֿ�
====================================
�ڲ��ļ�����˵����
====================================
	FKCW_Network_NetworkCommon
		����֧��ģ��ʹ�õĲ��ֻ���������Ͷ���
	FKCW_Network_Packet
		������Ϣ���Ͱ�ͷ��ʽ����ͳ��ú�����

	FKCW_Network_TCPSocket
		TCP�����׽��ַ�װ
	FKCW_Network_TCPSocketHub
		TCP���ӹ�����

	FKCW_Network_UDPSocket
		UDP�����׽��ַ�װ
	FKCW_Network_UDPSocketHub
		UDP���ӹ�����

	FKCW_Network_HttpRequest
		Http������
	FKCW_Network_HttpResponse
		HttpӦ����
	FKCW_Network_HttpClient
		����CCHttpClient��������һ������ļ�ǿ��

	FKCW_Network_FileDownLoader
		һ��ʹ��HttpЭ����ļ���������������һ����Ҫ�����ļ��б����Զ�һ����һ��������ȫ���ļ�������ָ���ռ䡣
====================================
������Ŀ/�⣺
====================================
	FKCW_Base
====================================
todo:
====================================

*/
//--------------------------------------------------------------------
#include "Include/FKCW_Network_NetworkCommon.h"
#include "Include/FKCW_Network_Packet.h"

#include "Include/FKCW_Network_TCPSocket.h"
#include "Include/FKCW_Network_TCPSocketHub.h"

#include "Include/FKCW_Network_UDPSocket.h"
#include "Include/FKCW_Network_UDPSocketHub.h"

#include "Include/FKCW_Network_HttpRequest.h"
#include "Include/FKCW_Network_HttpResponse.h"
#include "Include/FKCW_Network_HttpClient.h"
#include "Include/FKCW_Network_FileDownLoader.h"