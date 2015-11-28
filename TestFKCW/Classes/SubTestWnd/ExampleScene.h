//*************************************************************************
//	��������:	2014-11-27
//	�ļ�����:	ExampleScene.h
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
class CExampleLayer : public CCLayer
{
public:
	virtual bool init()
	{
		do 
		{
			CC_BREAK_IF( !CCLayer::init() );

			// ���������ֳ�ʼ������
			CCSize winSize = CCDirector::sharedDirector()->getWinSize();
			CCLabelTTF* pInfo = CCLabelTTF::create(FKCW_Base_StringConvert::a2u("�������� FreeKnight ��cocos2dx 2.x�汾��Wrapper�� �Ĳ�������").c_str(), "", 26 );
			pInfo->setPosition( ccp( winSize.width / 2, winSize.height / 2 ));
			pInfo->setColor( ccRED );
			this->addChild(pInfo);

			return true;
		} while ( 0 );
		return false;
	}
public:
	CREATE_FUNC( CExampleLayer );
};
//-------------------------------------------------------------------------
// ����ĳ���ע����ListControllerLayer��ע��
// CREATE_TEST_SCENE_CLASS(MainType, SubType, Desc)
//-------------------------------------------------------------------------
class CExampleScene : public CTestScene
{
public:
	CREATE_SCENE_FUNC(CExampleScene);
public:
	CExampleScene()
	{
		SetInfo("����һ�����Գ������Ա�ѧϰ");
	}
public:
	// ���������ֳ�ʼ������,���������main
	virtual void Run()
	{
		CCLayerColor *layer = CCLayerColor::create( ccc4BFromccc4F(ccc4FFromccc3B( ccGRAY )));
		layer->setColor( ccGRAY );
		addChild(layer);

		CExampleLayer* pLayer = (CExampleLayer*)CExampleLayer::create();
		if( pLayer )
		{
			this->addChild( pLayer );
		}
	}
};
//-------------------------------------------------------------------------