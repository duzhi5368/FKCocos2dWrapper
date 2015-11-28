//*************************************************************************
//	��������:	2014-12-29
//	�ļ�����:	FKCW_TMX_Object.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_TMX_Macros.h"
//-------------------------------------------------------------------------
class FKCW_TMX_Object : public CCObject 
{
public:
	// ��������
	enum ENUM_Shape 
	{
		eShape_NORMAL,		// ��ͨ���󣬸�ʽΪ Key = value ��
		eShape_POLYGON,		// ����ζ��󣬿��Ի�ȡ������б�
		eShape_POLYLINE		// ���߶�����β�ڵ㲻����
	};
	
protected:
	FKCW_TMX_Object();
	
public:
	virtual ~FKCW_TMX_Object();
	static FKCW_TMX_Object* create();
	
	// ����Key��ȡһ������ֵ
	string getProperty(const string& key);
	// ���һ������
	void addProperty(const string& key, const string& value);
public:
	CC_SYNTHESIZE_PASS_BY_REF_NC(CCDictionary, m_properties, Properties);	// ���Դʵ�
	CC_SYNTHESIZE_PASS_BY_REF_NC(FKCW_Base_PointList, m_points, Points);	// ���б�������POLYGON��POLYLINE����
	CC_SYNTHESIZE(ENUM_Shape, m_shape, Shape);								// ��������
	CC_SYNTHESIZE_PASS_BY_REF_NC(string, m_name, Name);						// ����
	CC_SYNTHESIZE_PASS_BY_REF_NC(string, m_type, Type);						// ����
	CC_SYNTHESIZE_PASS_BY_REF_NC(CCPoint, m_pos, Position);					// λ��
	CC_SYNTHESIZE_PASS_BY_REF_NC(CCSize, m_size, Size);						// ��С
};
