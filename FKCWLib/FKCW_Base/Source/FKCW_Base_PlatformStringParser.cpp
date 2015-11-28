//--------------------------------------------------------------------
#include "../Include/FKCW_Base_PlatformStringParser.h"
//--------------------------------------------------------------------
FKCW_Base_PlatformStringParser::FKCW_Base_PlatformStringParser()
{

}
//--------------------------------------------------------------------
FKCW_Base_PlatformStringParser::~FKCW_Base_PlatformStringParser()
{

}
//--------------------------------------------------------------------
FKCW_Base_PlatformStringParser* FKCW_Base_PlatformStringParser::Create()
{
	FKCW_Base_PlatformStringParser* p = new FKCW_Base_PlatformStringParser();
	return ( FKCW_Base_PlatformStringParser* )p->autorelease();
}
//--------------------------------------------------------------------
// ����ƽ̨�� xml ���������ַ����ֵ���
// ������p_strPath xml�ļ���·������·����ƽ̨�޹صģ�������ӳ�䵽��Ӧ��ƽ̨��ʽ
// ���磺Android�ϵ�"/sdcard/strings.xml" ����ӳ�䵽iOSϵͳ�ϵ�"~/Documents/sdcard/strings.xml" ��
void FKCW_Base_PlatformStringParser::Parse( const string& p_strPath, const CCDictionary& p_Dict )
{
	// ��ȡxml���ݡ���Ϊtinyxml���ܴ�apk�ж�ȡ�ļ�
	unsigned long size;
	unsigned char* data = CCFileUtils::sharedFileUtils()->getFileData(p_strPath.c_str(), "rb", &size);

	// �����ļ�����ȡ
	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
	if(doc->Parse((const char*)data, size) == XML_NO_ERROR) {
		m_pDict = (CCDictionary*)&p_Dict;
		doc->Accept(this);
	}

	free(data);
	delete doc;
}
//--------------------------------------------------------------------
// ����XMLVisitor����
bool FKCW_Base_PlatformStringParser::VisitEnter(const XMLElement& element, const XMLAttribute* firstAttribute)
{
	if(!strcmp(element.Name(), "string")) {
		CCString* s = CCString::create(element.GetText() ? element.GetText() : "");
		const char* key = element.Attribute("name");
		if(key) 
		{
			m_pDict->setObject(s, key);
		}
	}
	return true;
}
//--------------------------------------------------------------------