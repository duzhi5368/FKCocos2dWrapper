//-------------------------------------------------------------------------
#include "FKFramework.h"
#include "SimpleAudioEngine.h"
//-------------------------------------------------------------------------
FKFramework::FKFramework()
{

}
//-------------------------------------------------------------------------
FKFramework::~FKFramework()
{

}
//-------------------------------------------------------------------------
// �յ�������Ϣ�Ļص�������
bool FKFramework::OnInputMessage( unsigned int unMsgType, int nTouchID, 
							   float fPosX, float fPosY, void* pParam )
{
	return true;
}
//-------------------------------------------------------------------------
// ��ʼ��
bool FKFramework::Init( float fWidth, float fHeight )
{
	CCEGLView* pEglView = CCEGLView::sharedOpenGLView();
	pEglView->setViewName("FKEngine");
	pEglView->setFrameSize( fWidth, fHeight );
	return true;
}
//-------------------------------------------------------------------------
// ��ʼ������
bool FKFramework::InitSystem()
{
	GetSceneSystem();
	GetAudioSystem();
	GetNetworkSystem();
	GetTimerSystem();
	GetMsgDispatchSystem();
	GetEventSystem();
	GetUISystem();
	GetInputSystem();
	GetDebugSystem();
	
	GetInputSystem()->Init();
	GetInputSystem()->SetInputMsgCallback( this );
	GetInputSystem()->SetInputEnabled( true );

	return SubInit();
}
//-------------------------------------------------------------------------
// ֡����
void FKFramework::UpdateFrame( float dt )
{
	GetNetworkSystem()->UpdateEvent();
	GetTimerSystem()->UpdateTimer();
	SubUpdate( dt );
}
//-------------------------------------------------------------------------
// �ͷŹ���
void FKFramework::Release()
{
	SubRelease();

	cocos2d::extension::CCArmatureDataManager::purge();
	cocos2d::extension::DictionaryHelper::purgeDictionaryHelper();
	GetInputSystem()->SetInputEnabled( false );

	GetDebugSystem()->Release();
	GetInputSystem()->Release();
	GetUISystem()->Release();
	GetEventSystem()->Release();
	GetMsgDispatchSystem()->Release();
	GetTimerSystem()->Release();
	GetNetworkSystem()->Release();
	GetAudioSystem()->Release();
	GetSceneSystem()->end();
}
//-------------------------------------------------------------------------
// ִ��ѭ��
int FKFramework::Run()
{
	return CCApplication::sharedApplication()->run();
}
//-------------------------------------------------------------------------
// ����Ӧ�ó���
bool FKFramework::applicationDidFinishLaunching()
{
	CCDirector *pDirector = CCDirector::sharedDirector();
	if( pDirector == NULL )
		return false;
	pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
	pDirector->setDisplayStats( true );
	pDirector->setAnimationInterval(1.0 / 60);

	// �Լ��ĳ�ʼ��
	if( ! InitSystem() )
		return false;

	return true;
}
//-------------------------------------------------------------------------
// Ӧ�ó�������̨
void FKFramework::applicationDidEnterBackground()
{
	CCDirector::sharedDirector()->stopAnimation();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}
//-------------------------------------------------------------------------
// Ӧ�ó������ǰ̨
void FKFramework::applicationWillEnterForeground()
{
	CCDirector::sharedDirector()->startAnimation();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}
//-------------------------------------------------------------------------