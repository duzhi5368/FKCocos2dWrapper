//*************************************************************************
//	��������:	2015-3-19
//	�ļ�����:	sceneMacro.h
//  �� �� ��:   �˹۸� Rect 	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../FKEngine/FKEngineCommonHead.h"
#include "GameResource.h"
#include "EventCommon.h"
//-------------------------------------------------------------------------
enum ENMU_TEST_KFENGINE_TYPE
{
	eTestFKEngine_Default = 0,
	eTestFKEngine_Login,
	eTestFKEngine_Play,
	eTestFKEngine_Shop,
	eTestFKEngine_Achie,
};

enum ENMU_AWARD_TYPE
{
	eAwardType_Min = 0,
	eAwardType_LoginGift,  // ��¼����
	eAwardType_NewGuyGift, // ���˽���
	eAwardType_PetGift,    // ���ｱ��
	eAwardType_Max,
};

enum ENMU_EFFECT_TYPE
{
	eEffect_Default = 0,
	eEffect_Button,
};
