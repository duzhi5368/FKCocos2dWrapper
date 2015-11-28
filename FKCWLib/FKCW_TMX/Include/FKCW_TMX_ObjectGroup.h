//*************************************************************************
//	��������:	2014-12-29
//	�ļ�����:	FKCW_TMX_ObjectGroup.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_TMX_Object.h"
//-------------------------------------------------------------------------
class FKCW_TMX_ObjectGroup : public CCObject
{
protected:
	FKCW_TMX_ObjectGroup();
	
public:
	virtual ~FKCW_TMX_ObjectGroup();
	static FKCW_TMX_ObjectGroup* create();
	
	// ���һ������
	void addProperty(const string& key, const string& value);
	// ����Key��ȡһ������ֵ
	string getProperty(const string& name);
	
	// ����һ���µ�TMXObject
	// ע���ö�������ӵ�TMXObjectGroup��
	FKCW_TMX_Object* newObject();
	// �������ֻ�ȡһ��Object
	// ���ö��󲻴��ڣ��򷵻�NULL
	FKCW_TMX_Object* getObject(const string& name);
	// ����λ����������һ��Object
	// ����λ�޶����򷵻�NULL
	FKCW_TMX_Object* getObjectAt(int index);
	// ��ȡ�������еĶ������
	int getObjectCount() { return m_objects.count(); }
	
public:
	CC_SYNTHESIZE(string, m_name, Name);									// ��������
	CC_SYNTHESIZE(float, m_offsetX, OffsetX);								// ������ƫ��X
	CC_SYNTHESIZE(float, m_offsetY, OffsetY);								// ������ƫ��Y
	CC_SYNTHESIZE_PASS_BY_REF(CCArray, m_objects, Objects);					// �����б�ÿ����Ԫ��һ��FKCW_TMX_Object
	CC_SYNTHESIZE_PASS_BY_REF_NC(CCDictionary, m_properties, Properties);	// ���Դʵ�
	CC_SYNTHESIZE(int, m_color, Color);										// ��������ɫ.argb8888��ʽ�ġ�alphaΪ0xff
	CC_SYNTHESIZE_SETTER(float, m_opacity, Opacity);						// ������͸���ȡ�0,1��
};