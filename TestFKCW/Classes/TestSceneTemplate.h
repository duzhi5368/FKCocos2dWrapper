//*************************************************************************
//	��������:	2014-12-13
//	�ļ�����:	TestSceneTemplate.h
//  �� �� ��:   WilhanTian
//	��Ȩ����:	MIT
//	˵    ��:	��������Scene��ģ��
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
// ����һ������SCENE
#define CREATE_TEST_SCENE_CLASS(_TEST_ITEM_TYPE_, _TEST_ITEM_NAME_, _DESCRIPTION_TEXT_)\
class CTest_##_TEST_ITEM_TYPE_##_##_TEST_ITEM_NAME_##Scene : public CTestScene\
{\
public:\
	CREATE_SCENE_FUNC(CTest_##_TEST_ITEM_TYPE_##_##_TEST_ITEM_NAME_##Scene);\
public:\
	CTest_##_TEST_ITEM_TYPE_##_##_TEST_ITEM_NAME_##Scene()\
	{\
		SetInfo( #_DESCRIPTION_TEXT_ );\
	}\
	virtual void Run()\
	{\
		CCLayerColor *layer = CCLayerColor::create( ccc4BFromccc4F(ccc4FFromccc3B( ccc3(18,53,85) )));\
		addChild(layer);\
\
		CTest_##_TEST_ITEM_TYPE_##_##_TEST_ITEM_NAME_##Layer* pLayer = (CTest_##_TEST_ITEM_TYPE_##_##_TEST_ITEM_NAME_##Layer*)CTest_##_TEST_ITEM_TYPE_##_##_TEST_ITEM_NAME_##Layer::create();\
		if( pLayer )\
		{\
			this->addChild( pLayer );\
		}\
	}\
};

//-------------------------------------------------------------------------