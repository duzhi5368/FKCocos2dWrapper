#ifndef _DIALOG_BASE_H_
#define _DIALOG_BASE_H_

#include "FKCWLib/FKCocos2dxWrapper.h"
/**
 * ��Ҫ�̳�ʵ��
 */
class DialogBase : public CCLayer
{
public:
	//���öԻ��򱳾�ɫ
	virtual void setDialogColor(ccColor4B color);
	//���öԻ������������
	virtual void setTitle(const char* title);
	//��Ի������Node
	virtual void addDialogChild(CCNode* pChild);
	virtual CCSize getContentSize();
protected:
	DialogBase();
	virtual ~DialogBase();
	virtual bool init();

	//ǿ�����öԻ����С
	virtual CCSize GetDialogSize() = 0;
	//�رհ�ť�¼��ص�
	void onCloseButtonClick(CCObject* pSender);
	virtual bool ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent );
private:
	FKCW_UIWidget_Label* m_pLabel;
	FKCW_UIWidget_Layout* m_pLayout;
};

#endif