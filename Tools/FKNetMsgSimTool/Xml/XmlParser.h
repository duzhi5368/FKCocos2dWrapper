#ifndef _XML_PARSER_
#define _XML_PARSER_

//-------------------------------------------------------------------------
#include "support/tinyxml2/tinyxml2.h"
#include "FKCWLib/FKCocos2dxWrapper.h"
//-------------------------------------------------------------------------
enum ENUM_MSG_DATA_TYPE
{
	EMDT_SHORT,
	EMDT_INT,
	EMDT_FLOAT,
	EMDT_BOOL,
	EMDT_STRING,
};

//��Ϣ���Զ���
struct MsgAttObject
{
	std::string name;			//��
	ENUM_MSG_DATA_TYPE type;	//��������
	std::string data;			//����
};

struct MsgPack
{
	short mainType;
	short subType;
	std::vector<MsgAttObject> atts;

	short fbm;	//����������
	short fbs;	//����������
};

class XmlParser : public cocos2d::CCObject
{
public:
	//��ȡXmlParser����
	static XmlParser* getInstance()
	{
		if(m_pInstance == NULL)
		{
			m_pInstance = new XmlParser();
		}
		return m_pInstance;
	}
	
	//����xml�ļ�
	bool loadFile(const char* pFilePath);
	void newFile(const char* pFilePath);

	//��ȡ����ʽ�����ڵ�CString��  ��ʽ��:"�������͡�����"
	std::vector<std::string> getMainElementCStrings();
	//��ȡ����ʽ���ӽڵ�Cstring��  ��ʽ��:"�������͡� ���� [����������](����������)"
	std::vector<std::string> getSubElementCstrings(short mainType);
	//��ȡ����ʽ������Cstring��  ��ʽ��:"���������� (��������) Ĭ��ֵ"
	std::vector<std::string> getAttributeCstrings(short mainType, short subType);
	
	//��ȡĳ������Ϣ������
	std::string getSubElementName(short mainType, short subType);
	//��ȡĳ������Ϣ�ķ���������
	short getSubElementFBM(short mainType, short subType);
	//��ȡĳ������Ϣ�ķ���������
	short getSubElementFBS(short mainType, short subType);

	//��ȡ�������Զ��� todo...
	std::vector<MsgAttObject> getAttributeObjects(short mainType, short subType);
	//�µĸ�ʽ��:"���������� (��������) Ĭ��ֵ"
	std::string getAttributeCstring(short mainType, short subType, std::string attName);
	MsgAttObject getAttributeObject(short mainType, short subType, std::string attName);


	//���������
	bool addMainElement(short mainType, std::string name);
	//���������
	bool addSubElement(short mainType, std::string name, short subType, short fbm, short fbs);
	//�������
	bool addAttributeElement(short mainType, short subType, std::string attName, std::string dataType, std::string sValue);

	//�޸�������type
	bool setMainElementType(short mainType, short newMainType);
	//�޸�������type
	bool setSubElementType(short mainType, short subType, short newMainType);
	//�޸�������CS
	bool setSubElementCS(short mainType, short subType, std::string newCS);
	//�޸�������
	bool setAttributeElementName(short mainType, short subType, std::string attName, std::string newName);
	//�޸�����������
	bool setMainElementName(short mainType, std::string newName);
	//�޸�����������
	bool setSubElementName(short mainType, short subType, std::string newName);
	//���÷���������
	bool setSubElementFBM(short mainType, short subType, short fbm);
	//���÷���������
	bool setSubElementFBS(short mainType, short subType, short fbs);
	//�޸���������
	bool setAttributeElementDataType(short mainType, short subType, std::string attName, std::string newType);
	//�޸�����ֵ
	bool setAttributeElementValue(short mainType, short subType, std::string attName, std::string newValue);

	//ɾ��������
	bool removeMainElement(short mainType);
	//ɾ��������
	bool removeSubElement(short mainType, short subType);
	//ɾ������
	bool removeAttributeElement(short mainType, short subType, std::string attName);

	bool isHaveMainElement(short mainType);
	bool isHaveSubElement(short mainType, short subType);

	//��ȡ��Ϣ��
	MsgPack getMsgPack(short mainType, short subType);

public:
	//��������ʽ���ַ��� "���������� (��������) Ĭ��ֵ"
	static ENUM_MSG_DATA_TYPE GetDataType(std::string text);

	ENUM_MSG_DATA_TYPE getDataType(short mainType, short subType, std::string attName);
	static std::string	GetAttName(std::string text);
	static std::string	GetAttData(std::string text);
	static std::string	GetAttType(std::string text);
	//��ȡ�ɲ������������͵��ַ���
	static std::string  GetSubString(std::string text);
	//��������ʽ���ַ���
	static short		GetMainType(std::string text);
	static string		GetMainName(std::string text);
	//��������ʽ���ַ���
	static short		GetSubType(std::string text);
	static std::string  GetNoFBTypeToSubName(std::string text);
	//��������������
	static short		GetSubFBM(std::string text);
	static short		GetSubFBS(std::string text);

	//��std::string ת����int
	static int			StringToInt(std::string text)
	{
		return atoi(text.c_str());
	}
	//��std::string ת����float
	static float		StringToFloat(std::string text)
	{
		return (float)atof(text.c_str());
	}
	//��std::string ת����short
	static short		StringToShort(std::string text)
	{
		return (short)atoi(text.c_str());
	}
	//��std::string ת����long
	static string   	StringToBool(std::string text)
	{
		if(text.compare("false") == 0 || text.compare("0") == 0)
			return "false";
		return "true";
	}

private:
	//�õ������͵�XMLElement
	tinyxml2::XMLElement* _getMainElement(short mainType);
	//�õ������͵�XMLElement
	tinyxml2::XMLElement* _getSubElement(short mainType, short subType);
	//�õ����Ե�XMLElement
	tinyxml2::XMLElement* _getAttributeElement(short mainType, short subType, std::string attName);

	//����ת��
	string _typeConversion(string type, string value);

private:
	static XmlParser* m_pInstance;	//XmlParser����
	std::string m_pFilePath;		//��ǰ�����ļ�·��
	tinyxml2::XMLDocument* m_pDoc;

private:
	XmlParser();
	~XmlParser();

};

#endif