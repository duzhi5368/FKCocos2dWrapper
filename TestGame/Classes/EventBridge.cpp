//-------------------------------------------------------------------------
#include "EventBridge.h"
#include "GameCommon.h"
//-------------------------------------------------------------------------


EventBridge::EventBridge(void)
{
}


EventBridge::~EventBridge(void)
{
}
//-------------------------------------------------------------------------
// �յ�ִ����Ϣ����ص�
// ������usID �¼�ID
// ������usSrcType ������Դ���ͣ��μ����ö�٣�
// ������unSrcID ������Ψһ��ʾ�������ǽ�ɫUID����ƷUID��
//		�Լ�ĳ����ָ��ȣ�����Ϣ�����߼�����Ա�Լ��涨��
// ������szEvent ��Ϣ��������ָ��
// ������nEventLen ��Ϣ���ݵĳ���
void EventBridge::OnExec( EVENT_TYPE usID, unsigned short usSrcType,
					 unsigned int unSrcID, const char* szEvent, int nEventLen )
{
	if (usID <= eEvent_Min || eEventE_Max <= usID)
	{
		return;
	}
	if (usSrcType <= eEvent_Src_Min || eEvent_Src_Max <= usSrcType)
	{
		return;
	}

	int nTag = unSrcID;
	switch (usSrcType)
	{
	case eEvent_Scene_Switch:
		__SwitchScene(nTag);
		break;

	case eEvent_Play_ButtonClick:
		__ClickPlayButton(nTag);
		break;

	default:
		break;
	}


}
//-------------------------------------------------------------------------
// �л�Scene
void EventBridge::__SwitchScene(int nTag)
{
	FKCW_SceneExMgr_SceneExMgr* pSceneSystem = GetSceneSystem();
	if (pSceneSystem == NULL)
	{
		return;
	}

	switch (nTag)
	{
	case eSubSceneType_Login:
		pSceneSystem->pushScene(LoadScene("CLoginScene") );
		break;
	case eSubSceneType_Play:
		pSceneSystem->pushScene(LoadScene("CPlayTestScene") );
		break;
	case eSubSceneType_Shop:
		pSceneSystem->pushScene(LoadScene("CShopTestScene") );
		break;
	case eSubSceneType_Achie:
		pSceneSystem->pushScene(LoadScene("CAchieTestScene") );
		break;
	default:
		break;
	}
}
//-------------------------------------------------------------------------
// ��ť�ص���Ϣ����
void EventBridge::__ClickPlayButton(int nTag)
{
	switch (nTag)
	{
	case eTestPlayButton_AddMoney:
		break;
	case eTestPlayButton_All:
		break;
	case eTestPlayButton_SortStar:
		break;
	case eTestPlayButton_HandMagic:
		break;
	default:
		break;
	}

	// ģ��������� �ͻ��� ������Ϣ
	S_GAME_INTVALUE_S2C sGameIntValue;
	sGameIntValue.mainType = eNetMsg_Main_Game;
	sGameIntValue.subType = eNetMsg_Sub_PlayStar;
	S_GAME_INTVALUE_SUB_S2C sGameIntVlaueSub;
	sGameIntVlaueSub.nValue = nTag;
	sGameIntVlaueSub.nFlag = 1;
	sGameIntValue.sSubS2C = sGameIntVlaueSub;

	IMsgDispatchSystem* pMsgDispath = GetMsgDispatchSystem();
	if (pMsgDispath)
	{
		pMsgDispath->DispatchMsg((const char*)&sGameIntValue,sizeof(S_GAME_INTVALUE_S2C));
	}
}
//-------------------------------------------------------------------------
// ע��ȫ���¼�
void EventBridge::RegisteFKEvent()
{
	IEventSystem* pEvenSystem = GetEventSystem();
	if (pEvenSystem == NULL)
	{
		return;
	}
	pEvenSystem->SubscibeExec(this,eEvent_UIEvent,eEvent_Scene_Switch);
	pEvenSystem->SubscibeExec(this,eEvent_UIEvent,eEvent_Play_ButtonClick);
}
//-------------------------------------------------------------------------
// �Ƴ�ȫ���¼�
void EventBridge::UnRegisteFKEvent()
{
	IEventSystem* pEvenSystem = GetEventSystem();
	if (pEvenSystem == NULL)
	{
		return;
	}
	pEvenSystem->UnSubscibeExec(this,eEvent_UIEvent,eEvent_Scene_Switch);
	pEvenSystem->UnSubscibeExec(this,eEvent_UIEvent,eEvent_Play_ButtonClick);
}
//-------------------------------------------------------------------------
