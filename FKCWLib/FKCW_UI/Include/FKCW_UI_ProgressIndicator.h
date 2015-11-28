//*************************************************************************
//	��������:	2014-11-6
//	�ļ�����:	FKCW_UI_ProgressIndicator.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_UI_Macros.h"
//-------------------------------------------------------------------------
// һ��������ʾ�����ͽ�������ͬ���ǣ��ý�����ʾ�����޷�ȷ�Ͻ��ȳ���ʱ��ģ�
// ע����������ʾ���Դ�һ����Ϣ��ʾLabel
// ������ʾ��������Ը���ͼƬ���Դ�һ������ͼƬЧ������Ҳ����ֱ�ӱ�����
class FKCW_UI_ProgressIndicator : public CCLayerColor
{
protected:
	CCSprite*					m_pIndicator;			// ��ʾ������
	CCLabelTTF*					m_pMsgLabel;			// ��Ϣ��ʾLabel
	CCSize						m_tagPanelSize;			// ����С
	float						m_fTime;				// ���¶�����ʱ��
	CC_SYNTHESIZE_BOOL(m_bIsCancellable, Cancellable);							// �Ƿ�������ȡ����ʾ��ʾ������
	CC_SYNTHESIZE_PASS_BY_REF_SETTER(ccColor4B, m_tagDimColor, DimColor);		// ��ɫ
	CC_SYNTHESIZE_PASS_BY_REF_SETTER(ccColor4B, m_tagPanelColor, PanelColor);	// ��ʾ��ʾ�����ı���ɫ
	CC_SYNTHESIZE_SETTER(CCSprite*, m_pIcon, Icon);								// ��ʾ���������飬����ֵΪNULL�����ʹ��Ĭ�ϵ���ʾ������
	CC_SYNTHESIZE_PASS_BY_REF_SETTER(string, m_strMessage, Message);			// ��ʾ����Ϣ
	CC_SYNTHESIZE_BOOL_SETTER(m_bIsForceSquare, ForceSquare);					// ���Ϊtrue�����ʾ��ʾ��ʾ������Ϊ������
protected:
	FKCW_UI_ProgressIndicator();
	void								_RelayOut();
	static FKCW_UI_ProgressIndicator*	Create( const string& p_strMessage );
public:
	virtual ~FKCW_UI_ProgressIndicator();

	// ���ظ��ຯ��
	virtual bool initWithMessage(const string& message);
	virtual void draw();
	virtual void update(float delta);
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
	virtual void keyBackClicked();

	// ����һ��������ʾ������ԭ��û�У���ᴴ���µġ�
	// ע��������ʾ������ӵ���ǰ���еĳ����У��һ������Zֵ����
	static FKCW_UI_ProgressIndicator* CreateInstance(const string& message);
	static FKCW_UI_ProgressIndicator* CreateInstance(const string& message, CCNode* parent);
	static FKCW_UI_ProgressIndicator* GetInstance();

	// ����ǰ���ڽ�����ʾ�������������أ����򽫲�����
	static void Hide();
};