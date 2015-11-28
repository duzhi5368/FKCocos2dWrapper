//*************************************************************************
//	��������:	2014-11-11
//	�ļ�����:	FKCW_Base_Bundle.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	Key-Valueһ�����ķ�װ������������һ������������ָ�ʽ���͵�Value��
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_Base_Macro.h"
//-------------------------------------------------------------------------
class FKCW_Base_Bundle : public CCObject
{
public:
	FKCW_Base_Bundle();
	virtual ~FKCW_Base_Bundle();
	static FKCW_Base_Bundle* create();

public:
	struct SBoundValue
	{
		int   nType;
		void* pValue;
	};

public:
	void				putShort(const char* key, short value);
	void				putUShort(const char* key, unsigned short value);
	void				putInt(const char* key, int value);
	void				putUInt(const char* key, unsigned int value);
	void				putFloat(const char* key, float value);
	void				putDouble(const char* key, double value);
	void				putString(const char* key, const char* value);
	void				putBundle(const char* key, FKCW_Base_Bundle* value);
	void				putObject(const char* key, CCObject* value);
	void				putParam(const char* key, void* value);

public:
	short				getShort(const char* key);
	unsigned short		getUShort(const char* key);
	int					getInt(const char* key);
	unsigned int		getUInt(const char* key);
	float				getFloat(const char* key);
	double				getDouble(const char* key);
	const char*			getString(const char* key);
	FKCW_Base_Bundle*	getBundle(const char* key);
	CCObject*			getObject(const char* key);
	void*				getParam(const char* key);

protected:
	virtual CCObject*	copyWithZone(CCZone* pZone);

private:
	void				removeValueByKey(const char* key);
	void				removeValue(const SBoundValue& tValue);

private:
	map<string, SBoundValue> m_mDatas;
};
