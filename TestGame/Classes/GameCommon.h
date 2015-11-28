//*************************************************************************
//	��������:	2015-3-19
//	�ļ�����:	sceneMacro.h
//  �� �� ��:   �˹۸� Rect 	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../../FKEngine/FKEngineCommonHead.h"
#include "GameResource.h"
#include "EventCommon.h"
//-------------------------------------------------------------------------
// ��������
enum ENMU_SubSceneType
{
	eSubSceneType_Min = 0,					
	eSubSceneType_Login,						// ��¼������
	eSubSceneType_Play,							// ��������������
	eSubSceneType_Shop,							// �̳ǳ���
	eSubSceneType_Achie,						// �ɾͳ���
	eSubSceneType_Max,
};

// ��Ϸ�����еİ�ťö��
enum ENMU_TEST_PLAYBUTTON_TYPE
{
	eTestPlayButton_Min = eSubSceneType_Max,
	eTestPlayButton_Music,						// ���ְ�ť
	eTestPlayButton_AddMoney,					// ��Ǯ��ť
	eTestPlayButton_All,						// ը��������ָ��С��Χ���鰴ť
	eTestPlayButton_SortStar,					// �������ȫ�����鰴ť��ť
	eTestPlayButton_HandMagic,					// ����ĳһ�����鰴ť
	eTestPlayButton_Max,
};

// ��Ϣ���������� - ����
enum ENMU_MSG_GIFT_TYPE
{
	eAwardType_Min = 0,
	eAwardType_LoginGift,						// ��¼����
	eAwardType_NewGuyGift,						// ���˽���
	eAwardType_PetGift,							// ���ｱ��
	eAwardType_Max,
};

// ��Ϣ���������� - ��ͨ
enum ENMU_MSG_NORMAL_TYPE
{
	eNormalType_Min = 0,
	eNormalType_GameSuccess,					// ͨ��
	eNormalType_GameOver,						// ʧ��
	eNormalType_Max,
};

// ��Ч����
enum ENMU_SOUND_TYPE
{
	eSound_Min = 0,
	eSound_Button,
	eSound_StarOut,
	eSound_StarClick,
	eSound_StarCombo,
	eSound_StarGood,
	eSound_StarAmazing,
	eSound_StarUnbeliveable,
	eSound_Max,
};

// ������Ϣ������
enum ENMU_NET_MSGMAIN_TYPE
{
	eNetMsg_Main_Min = 100,
	eNetMsg_Main_Game,
	eNetMsg_Main_Max,
};

// ������Ϣ������
enum ENMU_NET_MSGSUB_TYPE
{
	eNetMsg_Sub_Min = 10,
	eNetMsg_Sub_PlayStar,
	eNetMsg_Sub_ShopItem,
	eNetMsg_Sub_AchieThings,
	eNetMsg_Sub_Max,
};

// �ϲ�ʹ��,������Ϣģ��ṹ�� server to client 
struct S_GAME_INTVALUE_SUB_S2C
{
	int nValue;
	int nFlag;
	S_GAME_INTVALUE_SUB_S2C()
	{
		memset(this,0,sizeof(S_GAME_INTVALUE_SUB_S2C));
	}
};

// �ײ㴫��ʹ��,������Ϣģ��ṹ��  server to client
struct S_GAME_INTVALUE_S2C
{
	MSG_MAIN_TYPE mainType;
	MSG_SUB_TYPE subType;
	S_GAME_INTVALUE_SUB_S2C  sSubS2C;
	S_GAME_INTVALUE_S2C()
	{
		memset(this,0,sizeof(S_GAME_INTVALUE_S2C));
	}
};