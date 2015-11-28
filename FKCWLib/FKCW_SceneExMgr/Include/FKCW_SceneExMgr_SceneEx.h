//*************************************************************************
//	��������:	2014-11-12
//	�ļ�����:	FKCW_SceneExMgr_SceneEx.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_SceneExMgr_MsgManager.h"
#include "FKCW_SceneExMgr.h"
//-------------------------------------------------------------------------
class FKCW_SceneExMgr_SceneExMgr;

class FKCW_SceneExMgr_SceneEx 
#if USING_FKCW_WIDGET
	: public cocos2d::cocoswidget::FKCW_UI_WidgetWindow
#else
	: public CCNode
#endif
	, public FKCW_SceneExMgr_MsgDelegate
{
public:
	FKCW_SceneExMgr_SceneEx();
	virtual ~FKCW_SceneExMgr_SceneEx();

	// ���ȣ���һ�����ã�����ȫ����Դ.�ú������ᱻ����һ�Ρ�
	virtual void onLoadResources(){};
	// �ڶ������ã�������ɡ��ú������ᱻ����һ�Ρ�
	virtual void onLoadResourcesCompleted(){};
	// ���������ã����ص�ǰ�������ú������ᱻ����һ�Ρ�
	virtual void onLoadScene(){};

	// ��������ʾʱ����
	virtual void onEnterScene(){};
	// ����������ʱ����
	virtual void onExitScene(){};

	// ͬ������ͼƬ�������������߳�loopһ��ʱ��
	void addImage(const char* pFile);
	// �첽����ͼƬ���������������߳�loopʱ��
	void addImageAsync(const char* pFile);

	// �Ƿ񵱳���������ʱ�Զ�ɾ��ͼƬ
	bool isAutoRemoveUnusedTexture() const;
	// ���ã��Ƿ񵱳���������ʱ�Զ�ɾ��ͼƬ
	void setAutoRemoveUnusedTexture(bool bAuto);

	// �Ƿ���һ���ɻ���ĳ���
	bool isCachable() const;
	// ���ã��Ƿ���һ���ɻ���ĳ���
	void setCachable(bool bCachable);

	// ��ȡһЩ��������
	CCObject* getExtraObject() const;
	// ����һЩ��������
	void setExtraObject(CCObject* pExtraObject);

	// ��ȡ��������
	const char* getClassName();
	// �Ƿ�ǰ�����Ѿ��������
	bool isLoaded() const;

public:

	// ���غ���
	virtual void onEnter();
	virtual void onExit();

private:
	friend class FKCW_SceneExMgr_SceneExMgr;

	// �Ƿ��� onLoadResources() �����ص�֮���첽����
	bool isLoadingResourcesAsync();
	// ͬ��������Դ
	void loadResourcesSync();
	// �첽������Դ
	void loadResourcesAsync();
	// �첽������Դ�ص�����
	void loadingResourcesCallBack(CCObject* pTextureObj);
	// ���ó�������
	void setClassName(const char* pClassName);
	// ���ã���������Դ�Ƿ��Ѿ��������
	void setLoaded(bool bLoaded);

private:
	std::vector<std::string>	m_vLoadImageFilesSync;		// ��Ҫͬ�����ص�ͼƬ��Դ�ļ�
	std::vector<std::string>	m_vLoadImageFilesAsync;		// ��Ҫ�첽���ص�ͼƬ��Դ�ļ�
	std::string					m_strClassName;				// ��������
	CCObject*					m_pExtraObject;				// ����������Ϣ
	bool						m_bLoaded;					// �����Ƿ��Ѿ��������
	bool						m_bCachable;				// �����Ƿ���Ի���
	bool						m_bAutoRemoveUnusedTexture;	// �Ƿ��Զ��Ƴ�����ʹ�õ���Դ
	int							m_nLoadResourcesAsyncCount;	// �첽���ص���Դ����
	int							m_nLoadResourcesAsyncIdx;	// ��ǰ�첽���ص���Դ���
};
//-------------------------------------------------------------------------