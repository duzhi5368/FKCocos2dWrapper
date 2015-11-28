//-------------------------------------------------------------------------
#include "TestApp.h"
#include "LoginScene.h"
#include "PlayTestScene.h"
#include "AchieTestScene.h"
#include "ShopTestScene.h"
#include "GameCommon.h"
//-------------------------------------------------------------------------
TestApp gs_App;
TestApp* GetApp()
{
	return &gs_App;
}
//-------------------------------------------------------------------------
bool TestApp::SubInit()
{
	// �Զ���Ļ����
	__AutomaticScreenAdaptation();
	// ����ȫ�ֹ�����Դ
	__LoadGlobleResources();
	// ע���¼�
	m_EventBridge.RegisteFKEvent();
	// ע�᳡��
	REGISTER_SCENE_FUNC(CLoginScene);
	REGISTER_SCENE_FUNC(CPlayTestScene);
	REGISTER_SCENE_FUNC(CShopTestScene);
	REGISTER_SCENE_FUNC(CAchieTestScene);

	IEventSystem* pEvent = GetEventSystem();
	if (pEvent == NULL)
	{
		return false;
	}
	pEvent->FireExec(eEvent_UIEvent,eEvent_Scene_Switch,eSubSceneType_Login,NULL,0);

	return true;
}
//-------------------------------------------------------------------------
void TestApp::SubUpdate( float dt )
{

}
//-------------------------------------------------------------------------
void TestApp::SubRelease()
{
	// �Ƴ�ȫ���¼�
	m_EventBridge.UnRegisteFKEvent();

	// �ͷ�ȫ�ֹ�����Դ
	__RelesaeGlobleResources();
}
//-------------------------------------------------------------------------
// �յ�������Ϣ�Ļص�������
// ������unMsgType �������Ϣ���͡��μ�ENUM_InputMsgType��
// ������nTouchID ������Ϣ��ID����Ϊkey��Ϣ�����ֵ��ЧΪ0
// ������fPosX xλ��
// ������fPosY y��Ϣ
// ��������ϸ����ָ�룬���������Ϣ�ж�������ݣ��Ŵ�����С�������Ķ������ݣ��������򣩵ȣ�����¼�ڴˡ�
// ����ֵ��������true��ʾ���Ժ���ĵ��ã���Ϣ������󴫵ݣ�������false���ʾ��Ϣ���������´���
bool TestApp::OnInputMessage( unsigned int unMsgType, int nTouchID, 
							   float fPosX, float fPosY, void* pParam )
{
	return true;
}
//-------------------------------------------------------------------------
// �Զ���Ļ����
void TestApp::__AutomaticScreenAdaptation()
{
	vector<string> vecResourcePaths;
	vecResourcePaths.push_back( "Resources" );
	vecResourcePaths.push_back( "Resources/Game/" );
	CCSize tagScreenSize = CCEGLView::sharedOpenGLView()->getFrameSize();
	CCSize tagDesignSize = CCSizeMake(720, 1280);
	// todo:��Ļ����
	if( tagScreenSize.width / tagScreenSize.height < 1.4f )
	{
		vecResourcePaths.push_back( "Resources/Game/1280x720/");
	}
	else
	{
		vecResourcePaths.push_back( "Resources/Game/1280x720/");
	}
	CCFileUtils::sharedFileUtils()->setSearchPaths(vecResourcePaths);
}
//-------------------------------------------------------------------------
// ����ȫ����Դ
void TestApp::__LoadGlobleResources()
{
	CCSpriteFrameCache *pCache=CCSpriteFrameCache::sharedSpriteFrameCache();
	if (pCache == NULL)
	{
		return;
	}
	pCache->addSpriteFramesWithFile(s_szUIGPListPath,s_szUIGPngPath);
	pCache->addSpriteFramesWithFile(s_szUIResPlistPath,s_szUIResPngPath);
}
//-------------------------------------------------------------------------
// �ͷ�ȫ����Դ
void TestApp::__RelesaeGlobleResources()
{
	// ɾ������
	CCSpriteFrameCache *pCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	if (pCache == NULL)
	{
		return;
	}
	pCache->removeSpriteFramesFromFile(s_szUIGPListPath);
	pCache->removeSpriteFramesFromFile(s_szUIResPlistPath);
}
//-------------------------------------------------------------------------