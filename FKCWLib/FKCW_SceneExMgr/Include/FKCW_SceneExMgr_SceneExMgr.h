//*************************************************************************
//	��������:	2014-11-12
//	�ļ�����:	FKCW_SceneExMgr_SceneExMgr.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_SceneExMgr_SceneEx.h"
#include "FKCW_SceneExMgr.h"
//-------------------------------------------------------------------------
typedef FKCW_SceneExMgr_SceneEx* (*Fn_CreateSceneExtension)();
//-------------------------------------------------------------------------
// ��ݺ�
#ifndef CREATE_SCENE_FUNC
#define CREATE_SCENE_FUNC(_CLASS_) \
	static FKCW_SceneExMgr_SceneEx* createThisScene() { return new _CLASS_; }
#endif

// ע�᳡����������������
#ifndef REGISTER_SCENE_FUNC
#define REGISTER_SCENE_FUNC(_CLASS_) \
	FKCW_SceneExMgr_SceneExMgr::sharedManager()->registerSceneClass(#_CLASS_, &_CLASS_::createThisScene)
#endif

// ����������ڻ��峡�����ڣ�����س���
#ifndef LoadScene
#define LoadScene(_CLASS_) \
	FKCW_SceneExMgr_SceneExMgr::sharedManager()->loadScene(_CLASS_)
#endif

// ����ָ������
#ifndef SeekScene
#define SeekScene(_CLASS_) \
	FKCW_SceneExMgr_SceneExMgr::sharedManager()->seekScene(_CLASS_)
#endif
//-------------------------------------------------------------------------
// �����滻������Ϣ��ʽ
enum ENUM_SceneSwitchType
{
	eSceneSwitchPushScene,
	eSceneSwitchReplaceScene,
	eSceneSwitchPopScene,
	eSceneSwitchPopToSceneStackLevel
};
//-------------------------------------------------------------------------
// UI�����滻������Ϣ��ʽ
enum ENUM_UISceneSwitchType					
{
	eUISceneSwitchRunScene,	
	eUISceneSwitchPopScene
};
//-------------------------------------------------------------------------
// �����滻����
struct SSceneSwitchInfo
{
	FKCW_SceneExMgr_SceneEx* pNextScene;	// ��һ����Ҫ��ʾ�ĳ���
	CCObject* pExtra;						// ��һ�������Ķ�������
	ENUM_SceneSwitchType eType;				// �����滻��ʽ
	int nPopSceneStackLevel;				// ������ջ�ĵ����㼶
	bool bLockedSwitch;						// �Ƿ����������滻����
};
//-------------------------------------------------------------------------
// UI �����滻����
struct SUISceneSwitchInfo
{
	FKCW_SceneExMgr_SceneEx* pScene;		// ��һ����Ҫ��ʾ�ĳ�������ΪNULL�����ʾֱ������
	ENUM_UISceneSwitchType eType;			// �����滻��ʽ
	bool bLockedSwitch;						// �Ƿ����������滻����
};
//-------------------------------------------------------------------------
// ����������
class FKCW_SceneExMgr_SceneExMgr : public CCScene
{
public:
	virtual ~FKCW_SceneExMgr_SceneExMgr();
	static FKCW_SceneExMgr_SceneExMgr* sharedManager();

	// ��ȡ��ǰ�����еĳ������������г����ѵĶѶ���
	FKCW_SceneExMgr_SceneEx* getRunningScene() const;

	// �Ƿ�Ҫ����ǰ���г���
	inline bool isSendCleanupToScene(){ return m_bSendCleanupToScene; }
	// ����Ϸ��ʼʱ����һ��������Ӧ��ֻ������һ��
	void runWithScene(FKCW_SceneExMgr_SceneEx* pScene, CCObject* pExtra = NULL);
	// ��ָ�������Ƶ��Ѷ�
	void pushScene(FKCW_SceneExMgr_SceneEx* pScene, CCObject* pExtra = NULL);
	// �滻���г����������еĳ��������У�
	void replaceScene(FKCW_SceneExMgr_SceneEx* pScene, CCObject* pExtra = NULL);
	// ���������Ѷ������������������ջ���ˣ��������Ϸ��
	void popScene(CCObject* pExtra = NULL);

	// ���������ֻ����������
	void popToRootScene(CCObject* pExtra = NULL);
	// �������ָ���㼶֮�ϵ�ȫ����������nlevelС��1����������Ϸ
	void popToSceneStackLevel(int nLevel, CCObject* pExtra = NULL);
	// ����һ��UI����
	void runUIScene(FKCW_SceneExMgr_SceneEx* pScene, CCObject* pExtra = NULL);
	// �ر�һ��UI����
	void popUIScene(FKCW_SceneExMgr_SceneEx* pScene);
	// �ر�ȫ��UI����
	void popAllUIScene();
	// �Ƿ�һ��UI��������������
	bool isSceneRunning(const char* pSceneName);
	// ������Ϸ
	void end();

	// �ӻ��泡������ɾ��ָ���Ļ���ĳ���
	void removeCachedScene(const char* pSceneName);
	// ɾ�����泡������ȫ�����泡��
	void removeAllCachedScenes();
	// ɾ�����泡�����еĵ�ȫ��δʹ�ó���
	void removeUnusedCachedScenes();

	// ����Ϸ����ʱ�����г������ע�ᣬ�ú���Ӧ��ֻ������һ�Ρ�
	void registerSceneClass(const char* pSceneName, Fn_CreateSceneExtension pFn);

	// ����������ڻ��峡�����ڣ�����س���
	FKCW_SceneExMgr_SceneEx* loadScene(const char* pSceneName);
	// ����ָ������
	FKCW_SceneExMgr_SceneEx* seekScene(const char* pSceneName);
	// ��ȡ�������ȼ����ú���ÿ����һ�Σ���ֵ������һ�Ρ�
	int getTouchPriority();


public:
	// ��ѭ������
	virtual void visit();
	
protected:
	friend class FKCW_SceneExMgr_SceneEx;
	

	// ÿ֡���ã��������������߼���ѭ��
	void mainLoop();
	// ������һ�����еĳ���
	void setNextScene();
	// �������л��¼�
	void handleSceneSwitch(SSceneSwitchInfo& tSceneSwitch);
	// ����һ�������л��¼�
	void unlockSceneSwitch(const char* pClassName);
	// ����UI�����л��¼�
	void handleUISceneSwitch(SUISceneSwitchInfo& tSceneSwitch);
	// ����һ��UI�����л��¼�
	void unlockUISceneSwitch(const char* pClassName);
	// ��������ȫ��UI����
	void visitUIScenes();
	// ����ָ�������������Դ
	bool loadSceneResources(FKCW_SceneExMgr_SceneEx* pScene);
	// ���ó���������Ϣ
	void setExtraToScene(FKCW_SceneExMgr_SceneEx* pScene, CCObject* pExtra);
	// ���������Ҫ���棬��ָ��������ӵ����������
	void addCachableScene(FKCW_SceneExMgr_SceneEx* pScene);
	// ��ȡ����������
	const char* getSceneClassName(FKCW_SceneExMgr_SceneEx* pScene);

protected:
	bool											m_bSendCleanupToScene;		// �Ƿ�Ҫ����ǰ���г���
	FKCW_SceneExMgr_MsgManager*						m_pMsgManager;				// ��Ϸ��Ϣ������
	FKCW_SceneExMgr_SceneEx*						m_pRunningScene;			// ��ǰ�������еĳ���
	FKCW_SceneExMgr_SceneEx*						m_pNextScene;				// ��һ��׼�����еĳ���
	std::vector<FKCW_SceneExMgr_SceneEx*>			m_vRunningSceneStack;		// ���г�������	
	std::list<SSceneSwitchInfo>						m_lSceneSwitchQueue;		// �����л��¼�����
	std::list<SUISceneSwitchInfo>					m_lUISceneSwitchQueue;		// UI�����л��¼�����
	std::vector<FKCW_SceneExMgr_SceneEx*>			m_vRunningUIScenes;			// UI��������
	std::map<std::string, Fn_CreateSceneExtension>	m_mFnSceneCreatePointers;	// ������ָ̬����У�Э�������³���
	std::map<std::string, FKCW_SceneExMgr_SceneEx*> m_mSceneCachePool;			// ���泡����

#if(COCOS2D_DEBUG >= 1)
	void debugSceneSwitchInfo();
#endif

private:
	FKCW_SceneExMgr_SceneExMgr();

};
