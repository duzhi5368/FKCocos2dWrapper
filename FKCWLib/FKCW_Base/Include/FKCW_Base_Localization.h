/********************************************************************
	created:	2014/10/27
	file base:	FKCW_Base_Localization
	author:		FreeKnight
	
	purpose:	
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include "FKCW_Base_Macro.h"
//--------------------------------------------------------------------
class FKCW_Base_Localization : public CCObject
{
private:
	static FKCW_Base_Localization* s_Instance;
private:
	// Key �����Ե�ISO��ţ�Value���ַ���CCDictionary
	CCDictionary		m_LanguageDicMap;		// ���Ա�
private:
	// �� ascii ���滻 \n \t \r
	string				__UnEscape( const string& s );
protected:
	FKCW_Base_Localization();
public:
	virtual ~FKCW_Base_Localization();
	static FKCW_Base_Localization* GetInstance();
public:
	// ��ȡһ��ƽ̨��strings.xml�ļ�
	// ע���ļ�������ƽ̨xml��ʽ�ļ�
	// ������p_strLanguage ISO639-1˫��ĸ���� 
	// ������p_strPath xml�ļ���·������·����ƽ̨�޹صģ�������ӳ�䵽��Ӧ��ƽ̨��ʽ
	// ���磺Android�ϵ�"/sdcard/strings.xml" ����ӳ�䵽iOSϵͳ�ϵ�"~/Documents/sdcard/strings.xml" ��
	// ������p_bMerge��True��ʾ�����ǰ�ַ����Ѿ����ڣ����ַ�������ϲ���ȥ��
	//		false��ʾ����ǰ�ַ����Ѿ����ڣ������ַ�����ֱ�����ԭ�ַ�����
	void	AddPlatformString( const string& p_strLanguage, const string& p_strPath, bool p_bMerge = false );

	// ͨ��ָ�����������࣬����key��Ӧ��value������������Ҳ��������ָ�ΪĬ�ϵ� English ���Խ��в��ҡ�
	// ע��Ĭ��ʹ������
	string	GetString( const string& p_strKey, const string& p_strLanguage = "zh" );
};
//--------------------------------------------------------------------
#define FKCW_LocStr(k)		(FKCW_Base_Localization::GetInstance()->GetString((k)))
#define FKCW_LocCharPtr(k)	(FKCW_LocStr(k).c_str())