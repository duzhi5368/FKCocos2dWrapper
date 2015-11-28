//*************************************************************************
//	��������:	2015-1-3
//	�ļ�����:	FKCW_Story_MessageLayer.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_Story_Macros.h"
//-------------------------------------------------------------------------
class FKCW_Story_Command;
class FKCW_Story_Player;
class FKCW_Story_TimerLabelTTF;
//-------------------------------------------------------------------------
class FKCW_Story_MessageLayer : public CCLayer 
{
private:
	CCLabelTTF* m_msgLabel;					// ��Ϣ��ǩ
	CCLabelTTF* m_nameLabel;				// ���ֱ�ǩ
	bool m_looping;							// �Ƿ�ѭ����ʾ���
	FKCW_Story_Player* m_player;			// Player
	float m_wait;							// �ȴ�ʱ��

protected:
	FKCW_Story_MessageLayer();

	// �ص�����
	void onDialogEndLooping();
	void onDialogDisplayedSomeWhile(float delta);

	// �û������Ϣ
	void handleUserClick();

public:
	virtual ~FKCW_Story_MessageLayer();
	static FKCW_Story_MessageLayer* create(FKCW_Story_Player* player);

	virtual bool initWithPlayer(FKCW_Story_Player* player);
	virtual void onExit();
	virtual void onEnter();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void keyBackClicked();

	// ��ʼ��ʾһ�ζԻ�
	void showMessage(FKCW_Story_Command* cmd);
	// ����Ӧ��������
	/*	horizontalSpacing�� ˮƽ��� 
		verticalSpacing��   ��ֱ��� 
		lineWidth��         һ�е������ 
	*/  
	CCLabelTTF* AutoNewLineText(std::string _string, const char *fontName, 
	float fontSize, float horizontalSpacing, float verticalSpacing, float lineWidth, ccColor3B p_fontColor );
	// �ַ��¼��ص�
	void TTFItemDelayOver(CCNode* pSender);
};
