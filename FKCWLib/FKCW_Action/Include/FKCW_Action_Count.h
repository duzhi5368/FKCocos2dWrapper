/********************************************************************
	created:	2014/11/03
	file base:	FKCW_Action_Count
	author:		FreeKnight
	
	purpose:	���ַ�ת����
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include "FKCW_Action_Macros.h"
//--------------------------------------------------------------------
// ���ӻ����һ�����ֱ�ǩ����תΪ��һ��
// ע�������������ʵ��CCLabelProtocol����cocostudio��Labels.
//  ���磺UILabelBMFont �� UILabel
class FKCW_Action_Count : public CCActionInterval
{
private:
	enum ENUM_LabelType
	{
		eLabelType_Protocol,
		eLabelType_Label,
		eLabelType_BitmapLabel,
	};
private:
	int				m_nFrom;		// ԭֵ
	int				m_nTo;			// Ŀ��ֵ
	string			m_strPattern;	// ��ʽģ��
	char*			m_szBuf;		// ������
	ENUM_LabelType	m_eType;		// ��ǩ����
public:
	FKCW_Action_Count();
	virtual ~FKCW_Action_Count();

	// ����һ����ת���ֶ���ʵ��
	// ������pattern Label���ָ�ʽ���������һ�� %d ��ʽ
	static FKCW_Action_Count* Create(float duration, int from, int to, const string& pattern = "%d");
	bool InitWithDuration(float d, int from, int to, const string& pattern);

	virtual void update(float time);
	virtual void startWithTarget(CCNode *pTarget);
	virtual CCObject* copyWithZone(CCZone* pZone);
	virtual CCActionInterval* reverse();
};