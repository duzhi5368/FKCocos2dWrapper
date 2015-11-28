//*************************************************************************
//	��������:	2015-1-8
//	�ļ�����:	Test_RenderEx_SwayNode.h
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
class CTest_RenderEx_SwayNodeLayer : public CCLayer
{
public:
	bool init()
	{
		do 
		{
			CC_BREAK_IF( !CCLayer::init() );

			FKCW_RenderEx_SwayNode* pNode = FKCW_RenderEx_SwayNode::create( s_szGrassPath );
			pNode->setPosition( SCREEN_CENTER_POS );
			addChild( pNode );

			return true;
		} while ( 0 );
		return false;
	}
public:
	CREATE_FUNC( CTest_RenderEx_SwayNodeLayer );
};
//-------------------------------------------------------------------------
CREATE_TEST_SCENE_CLASS(RenderEx, SwayNode, ���ϲ�ҡҷ�ľ���ڵ㣬�ʺ����ݻ���)
//-------------------------------------------------------------------------