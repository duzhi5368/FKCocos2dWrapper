//*************************************************************************
//	��������:	2015-1-13
//	�ļ�����:	IConfigFileSystem.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
/*
	ע�⣺��ϵͳ�����������ļ���أ��ļ�����֤��App��ʼ��ʱ�����أ�
		  �ҽ������ڳ����˳�ʱ�ű��ͷŵ�������Դ�ŷ������

	��ǰ����������������ļ���ʽ���ͣ�
	1�����ػ�������������ּ���ָ�������Ĺ̶�xml��ʽ�� string-en.xml string-zn.xml ��
	2�������û����������ļ��������̶�xml��ʽ�� UserDefault.xml
	3���߻����ñ������ļ�������ǹ̶�csv��ʽ�� һϵ�е�csv��ʽ�����ļ�
	4���û������ݼ�¼�ļ��������̶�sqlite3���ݿ��ʽ�� UserDefault.db
	5���������������ļ�������ǹ̶�json��ʽ��һϵ�е�json��ʽ�����ļ������ڶ�㼶��ϵ���ݱ��
	ע�⣬��Ϸ��������صĶ����ļ�����ͼ�ļ�����ɫ�����ļ���UI��Ϣ�ļ��������ڱ�������롣
	
	�Ժ������Ҫ��ӵĻ���֧�ְ�����TODO��
	1�����ָ�ʽ�������Զ���ǹ̶�ini�����ļ�����XML�����ļ�������㼶��ϵ���ݹ���
	2�����ֶ��⹦�ܣ����ܣ�zip����pak���м���
	3�����̼߳���֧��
*/
//-------------------------------------------------------------------------
#include <string>
//-------------------------------------------------------------------------
// Csv�����ļ�ID
typedef int		CSV_ID;
//-------------------------------------------------------------------------
// �����ļ�����
enum ENUM_ConfigFileType
{
	eCFT_Localization			= 0,	// ���ػ������ļ�
	eCFT_UserDefaultXML,				// ϵͳ���û���������xml�ļ�
	eCFT_UserDefaultDB,					// �û���������db�ļ�
	eCFT_CSVConfig,						// �߻�CSV�����ļ�
	eCFT_JsonConfig,					// Json���Ӳ㼶�����ļ�
	eCFT_IniConfig,						// ��׼�����ļ�
};
//-------------------------------------------------------------------------
// �����ļ�ϵͳ
class IConfigFileSystem
{
public:
	// �ͷű�ϵͳ
	virtual void		Release() = 0;
	// ����һ�������ļ�
	// ������szConfigFile �����ļ�·�����ļ���
	// ������eType �����ļ�����
	// ������nID �������ļ�ΨһID
	virtual bool		LoadConfig( const char* szConfigFile, ENUM_ConfigFileType eType, CSV_ID nID ) = 0;
	// �����޸�һ�������ļ�
	// ������nID �������ļ�ΨһID
	virtual bool		SaveConfig( CSV_ID nID ) = 0;
	// ��ȡһ�������ļ�ID
	virtual CSV_ID		GetConfigID( const char* szConfigFile, ENUM_ConfigFileType eType ) = 0;
	// ��ȡ����
	// ������nID �����ļ�ΨһID
	// ������szCol �����ñ�Ϊ eCFT_UserDefaultDB �� eCFT_CSVConfig ��ʽʱ������Ϊ�ֶ���
	//			   �����ñ�Ϊ eCFT_Localization ��ʽʱ������ΪISO639-1˫��ĸ���룬��"zh","en"��
	//			   �����ñ�Ϊ eCFT_UserDefaultXML ��ʽʱ���˴���Ч
	//			   �����ñ�Ϊ eCFT_JsonConfig ��ʽʱ���˴�Ϊ�������FKCW_Json_Objectָ�룬���ϲ�����NULL
	// ������szKey ��ֵ
	// ������outValue ��ȡ�������ݣ�����ȡ�����������cDefaultValue ��
	// ������cDefaultValue ����ȡ��������õ�Ĭ��ֵ
	// ����ֵ����ȡȫ�����г����κ������ʧ�ܣ���������false���ɹ��򷵻�true
	virtual bool		GetCharByKey( CSV_ID nID, const char* szCol, const char* szKey,
		char& outValue, char cDefaultValue = 0 ) = 0;
	virtual bool		GetShortByKey( CSV_ID nID, const char* szCol, const char* szKey,
		short& outValue, short sDefaultValue = 0 ) = 0;
	virtual bool		GetIntByKey( CSV_ID nID, const char* szCol, const char* szKey,
		int& outValue, int nDefaultValue = 0 ) = 0;
	virtual bool		GetFloatByKey( CSV_ID nID, const char* szCol, const char* szKey,
		float& outValue, float fDefaultValue = 0.0f ) = 0;
	virtual bool		GetStringByKey( CSV_ID nID, const char* szCol, const char* szKey,
		std::string& outValue, std::string szDefaultValue = "" ) = 0;
	virtual bool		GetBoolByKey( CSV_ID nID, const char* szCol, const char* szKey,
		bool& outValue, bool bDefaultValue = false ) = 0;

	// д������
	// ע�⣺ eCFT_Localization  eCFT_CSVConfig �����ָ�ʽ��ֹд�롣������д�뺯���ؽ�ʧ�ܡ�
	// ע�⣺��д����ļ���ֵ�������ݣ����Զ����и��Ǹ�;��û�У��򴴽���ӡ�
	// ������szCol �����ñ�Ϊ eCFT_UserDefaultDB �� eCFT_CSVConfig ��ʽʱ������Ϊ�ֶ���
	//			   �����ñ�Ϊ eCFT_Localization ��ʽʱ������ΪISO639-1˫��ĸ���룬��"zh","en"��
	//			   �����ñ�Ϊ eCFT_UserDefaultXML ��ʽʱ���˴���Ч
	//			   �����ñ�Ϊ eCFT_JsonConfig ��ʽʱ���˴�Ϊ�������FKCW_Json_Objectָ�룬���ϲ�����NULL
	// ������szKey ��ֵ
	// ������Value д����޸ĵ�����
	// ����ֵ��д��ȫ�����г����κ������ʧ�ܣ���������false���ɹ��򷵻�true
	virtual bool		SetCharByKey( CSV_ID nID, const char* szCol, const char* szKey, char cValue ) = 0;
	virtual bool		SetShortByKey( CSV_ID nID, const char* szCol, const char* szKey, short sValue ) = 0;
	virtual bool		SetIntByKey( CSV_ID nID, const char* szCol, const char* szKey, int nValue ) = 0;
	virtual bool		SetFloatByKey( CSV_ID nID, const char* szCol, const char* szKey, float fValue ) = 0;
	virtual bool		SetStringByKey( CSV_ID nID, const char* szCol, const char* szKey, std::string strValue ) = 0;
	virtual bool		SetBoolByKey( CSV_ID nID, const char* szCol, const char* szKey, bool bValue ) = 0;
};
//-------------------------------------------------------------------------