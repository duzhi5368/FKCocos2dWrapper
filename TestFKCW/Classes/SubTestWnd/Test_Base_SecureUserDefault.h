//*************************************************************************
//	��������:	2014-12-23
//	�ļ�����:	Test_Base_SecureUserDefault.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../resource.h"
#include "../TestScene.h"
#include "../../../FKCWLib/FKCocos2dxWrapper.h"
//-------------------------------------------------------------------------
const char* decrypt(const char* p_szEnc, int p_nEncLen, int* p_pPlainLen )
{
	char* dec = (char*)malloc(p_nEncLen+1 * sizeof(char));
	for(int i = 0; i < p_nEncLen; i++) {
		dec[i] = ~p_szEnc[i];
	}
	// ����β����\0������
	dec[p_nEncLen] = '\0';
	if(p_pPlainLen)
		*p_pPlainLen = p_nEncLen+1;

	return dec;
}
const char* encrypt(const char* p_pPlain, int p_nPlainLen, int* p_pEncLen )
{
	char* enc = (char*)malloc(p_nPlainLen * sizeof(char));
	for(int i = 0; i < p_nPlainLen; i++) {
		enc[i] = ~p_pPlain[i];
	}
	if(p_pEncLen)
		*p_pEncLen = p_nPlainLen;
	return enc;
}
//-------------------------------------------------------------------------
class CTest_Base_SecureUserDefaultLayer : public CCLayer
{
public:
	virtual bool init()
	{
		FKCW_Base_SecureUserDefault::Init(encrypt, decrypt);
		FKCW_Base_SecureUserDefault::GetInstance()->setStringForKey("testkey", "testvalue�������");

		string v = CCUserDefault::sharedUserDefault()->getStringForKey("testkey");
		char buf[1024];
		sprintf(buf, "CCUserDefault���صõ�:  %s", v.c_str());
		CCLabelTTF* label = CCLabelTTF::create( A2U(buf).c_str(), "Helvetica", 30);
		label->setPosition(SCREEN_CENTER_POS+ccp(0, 100));
		addChild(label);

		v = FKCW_Base_SecureUserDefault::GetInstance()->getStringForKey("testkey");
		memset( buf, 0, 1024 );
		sprintf(buf, "CCSecureUserDefault���صõ�:  %s", v.c_str());
		label = CCLabelTTF::create( A2U(buf).c_str(), "Helvetica", 30);
		label->setPosition(SCREEN_CENTER_POS+ccp(0,-100));
		addChild(label);

		return true;
	}
public:
	CREATE_FUNC( CTest_Base_SecureUserDefaultLayer );
};
//-------------------------------------------------------------------------
CREATE_TEST_SCENE_CLASS(Base, SecureUserDefault, �����ܵĻ��������ļ�)
//-------------------------------------------------------------------------