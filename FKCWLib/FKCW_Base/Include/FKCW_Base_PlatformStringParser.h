/********************************************************************
	created:	2014/10/27
	file base:	FKCW_Base_PlatformStringParser
	author:		FreeKnight
	
	purpose:	
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include "FKCW_Base_Macro.h"
#include "support/tinyxml2/tinyxml2.h"
//--------------------------------------------------------------------
using namespace tinyxml2;
//--------------------------------------------------------------------
class FKCW_Base_PlatformStringParser : public CCObject, public XMLVisitor
{
private:
	CCDictionary*		m_pDict;			// �ʵ�
public:
	FKCW_Base_PlatformStringParser();
	virtual ~FKCW_Base_PlatformStringParser();
	static FKCW_Base_PlatformStringParser* Create();
public:
	// ����ƽ̨�� xml ���������ַ����ֵ���
	// ������p_strPath xml�ļ���·������·����ƽ̨�޹صģ�������ӳ�䵽��Ӧ��ƽ̨��ʽ
	// ���磺Android�ϵ�"/sdcard/strings.xml" ����ӳ�䵽iOSϵͳ�ϵ�"~/Documents/sdcard/strings.xml" ��
	void			Parse( const string& p_strPath, const CCDictionary& p_Dict );
	// ����XMLVisitor����
	virtual bool	VisitEnter(const XMLElement& element, const XMLAttribute* firstAttribute);
};
