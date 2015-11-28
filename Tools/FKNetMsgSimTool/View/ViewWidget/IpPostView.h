#ifndef _IP_POST_VIEW_H_
#define _IP_POST_VIEW_H_

#include "FKCWLib/FKCocos2dxWrapper.h"
#include "cocos-ext.h"
using namespace cocos2d::extension;

class IpPostView;

class IpPostViewDelegate
{
public:
	//���ð�ť��Ϣί��
	virtual void onIpPostButtonClickMessage(IpPostView* pSender, string ip, short post) = 0;
};

/**
 * IpPostView
 * IP�Ͷ˿��������
 */
class IpPostView : public FKCW_UIWidget_Layout
{
public:
	CREATE_FUNC(IpPostView);
public:
	//���ð�ť����
	void setButtonText(const char* text);
	void setDeleagte(IpPostViewDelegate* pDelegate);
protected:
	IpPostView();
	virtual ~IpPostView();
	virtual bool init();

	void onButtonClick(CCObject* pSender);
private:
	CCEditBox* m_pEditBoxIP;
	CCEditBox* m_pEditBoxPost;
	FKCW_UIWidget_Button* m_pButton;
	IpPostViewDelegate* m_pDelegate;
};

#endif