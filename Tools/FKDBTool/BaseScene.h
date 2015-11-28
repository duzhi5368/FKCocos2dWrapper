#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
//-------------------------------------------------------------------------
#include "cocos2d.h"
#include "../../FKCWLib/FKCocos2dxWrapper.h"
#include "../../FKCoreLib/FKPicLib/FKPicLib.h"
#include "../../FKCoreLib/FKDBCocos2dxLib/FKDBCocos2dxLib.h"
//-------------------------------------------------------------------------
class BaseLayer : public cocos2d::CCLayer
{
public:
    virtual bool init();  
    static cocos2d::CCScene* scene();
	BaseLayer();
public:
	// WINDOWS ��Ϣ
	static void KeyboardHook( UINT message,WPARAM wParam, LPARAM lParam );
private:
	// ��ʾ���������
	void UpdateBoneNum();
	// ��ʾ���鶯����
	void UpdateFileName();
	// ��ʾ���鶯���б�
	void UpdateActionList();
public:
	// ����UI
	bool CreateUI();
protected:
	// ���²��Ŷ�����ǩ
	void OnSelActionBtn(CCObject* pSender );
	// ѡ����DB�ļ�
	void OnSelDBFile(CCObject* sender);
	// ����������ɫ
	void OnChangeBGColor(CCObject* sender);
public:
    CREATE_FUNC(BaseLayer);
public:
	CCocos2dxDBSprite*		m_pDBSprite;			// DragonBones����
	CCLabelTTF*				m_pBonesArmasNumLabel;	// ����Arma������Ϣ
	CCLabelTTF*				m_pDBFileLabel;			// DB�����ļ���
	CCMenu*					m_pActionListMenu;		// ������ť�б�˵�
	CCLayerColor*			m_pBackgroundLayer;		// ����ɫ��
};
//-------------------------------------------------------------------------
class CTestAnimCallbackHandler : public IAnimationCallback
{
	void OnAnimaitonCallback( const SAnimationCallbackInfo& p_tagInfo, void* p_pContext );
};
//-------------------------------------------------------------------------
#endif // __HELLOWORLD_SCENE_H__
