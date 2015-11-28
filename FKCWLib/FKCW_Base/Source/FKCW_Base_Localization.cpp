//--------------------------------------------------------------------
#include "../Include/FKCW_Base_Localization.h"
#include "../Include/FKCW_Base_PlatformStringParser.h"
//--------------------------------------------------------------------
FKCW_Base_Localization* FKCW_Base_Localization::s_Instance = NULL;
//--------------------------------------------------------------------
// �� ascii ���滻 \n \t \r
string FKCW_Base_Localization::__UnEscape( const string& s )
{
	string unescaped;
	char c;
	const char* buf = s.c_str();
	int len = s.length();
	for(int i = 0; i < len; i++) {
		if(buf[i] == '\\') {
			switch (buf[i + 1]) {
			case 'n':
				c = '\n';
				unescaped.append(&c, 1);
				i++;
				break;
			case 'r':
				c = '\r';
				unescaped.append(&c, 1);
				i++;
				break;
			case 't':
				c = '\t';
				unescaped.append(&c, 1);
				i++;
				break;
			default:
				unescaped.append(&buf[i], 1);
				break;
			}
		} else {
			unescaped.append(&buf[i], 1);
		}
	}
	return unescaped;
}
//--------------------------------------------------------------------
FKCW_Base_Localization::FKCW_Base_Localization()
{

}
//--------------------------------------------------------------------
FKCW_Base_Localization::~FKCW_Base_Localization()
{
	if(s_Instance) 
	{
		s_Instance->release();
		s_Instance = NULL;
	}
}
//--------------------------------------------------------------------
FKCW_Base_Localization* FKCW_Base_Localization::GetInstance()
{
	if(!s_Instance) 
	{
		s_Instance = new FKCW_Base_Localization();
	}
	return s_Instance;
}
//--------------------------------------------------------------------
// ע�����һЩ�ַ���
// ע���ļ�������ƽ̨xml��ʽ�ļ�
// ������p_strLanguage ISO639-1˫��ĸ���� 
// ������p_strPath xml�ļ���·������·����ƽ̨�޹صģ�������ӳ�䵽��Ӧ��ƽ̨��ʽ
// ���磺Android�ϵ�"/sdcard/strings.xml" ����ӳ�䵽iOSϵͳ�ϵ�"~/Documents/sdcard/strings.xml" ��
// ������p_bMerge��True��ʾ�����ǰ�ַ����Ѿ����ڣ����ַ�������ϲ���ȥ��
//		false��ʾ����ǰ�ַ����Ѿ����ڣ������ַ�����ֱ�����ԭ�ַ�����
void FKCW_Base_Localization::AddPlatformString( const string& p_strLanguage, const string& p_strPath, bool p_bMerge )
{
	if( p_strPath.empty() ) 
	{
		CCLOGWARN("CCLocalization::addAndroidStrings: string file path is empty");
		return;
	}
	if( p_strLanguage.length() != 2 ) 
	{
		CCLOGWARN("CCLocalization::addAndroidStrings: language code is not in ISO 639-1 format");
		return;
	}

	// ע�����Դʵ�
	CCDictionary* d = (CCDictionary*)m_LanguageDicMap.objectForKey(p_strLanguage);
	if(!d) 
	{
		d = CCDictionary::create();
		m_LanguageDicMap.setObject(d, p_strLanguage);
	}

	// ������ϣ�����ɾ���ڵ�
	if(!p_bMerge) 
	{
		d->removeAllObjects();
	}

	// parse it
	FKCW_Base_PlatformStringParser::Create()->Parse(p_strPath, *d);
}
//--------------------------------------------------------------------
// ͨ��ָ�����������࣬����key��Ӧ��value������������Ҳ��������ָ�ΪĬ�ϵ� English ���Խ��в��ҡ�
string FKCW_Base_Localization::GetString( const string& p_strKey, const string& p_strLanguage )
{
	// ��ָ�������ԣ����Ҳ���������Ӣ��
	bool fallback = false;
	string lan = p_strLanguage;
	CCDictionary* strings = (CCDictionary*)m_LanguageDicMap.objectForKey(lan);
	if(!strings) 
	{
		fallback = true;
		strings = (CCDictionary*)m_LanguageDicMap.objectForKey("en");
	}

	if(strings) 
	{
		CCString* s = (CCString*)strings->objectForKey(p_strKey);
		if(s) 
		{
			string ret = s->getCString();
			ret = __UnEscape(ret);
			return ret;
		} 
		else if(!fallback)
		{
			strings = (CCDictionary*)m_LanguageDicMap.objectForKey("en");
			CCString* s = (CCString*)strings->objectForKey(p_strKey);
			if(s) 
			{
				string ret = s->getCString();
				ret = __UnEscape(ret);
				return ret;
			}
		}
	}

	return "!" + p_strKey + "!";
}
//--------------------------------------------------------------------