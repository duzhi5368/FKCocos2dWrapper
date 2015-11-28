#include "ReviseMainMessageDialog.h"

#include "../../Resource.h"

ReviseMainMessageDialog* ReviseMainMessageDialog::create(short mainType, string mainName)
{
	ReviseMainMessageDialog* pBuf = new ReviseMainMessageDialog();
	if (pBuf && pBuf->init(mainType, mainName))
	{
		pBuf->autorelease();
		return pBuf;
	}
	delete pBuf;
	pBuf = NULL;
	return NULL;
}

ReviseMainMessageDialog::ReviseMainMessageDialog():
	m_pDelegate(NULL)
{

}

ReviseMainMessageDialog::~ReviseMainMessageDialog()
{

}

bool ReviseMainMessageDialog::init(short mainType, string mainName)
{
	if (!DialogBase::init())
	{
		return false;
	}

	m_mainType = mainType;

	this->setTitle(A2U("�޸�������").c_str());

	/********************************************************************************************/

	//�����ͱ�ǩ
	FKCW_UIWidget_Label* pMainTypeLabel = FKCW_UIWidget_Label::create(A2U("������(short)��").c_str(), "", 14);
	pMainTypeLabel->setAnchorPoint(ccp(0, 0.5));
	pMainTypeLabel->setPosition(ccp(20, getContentSize().height - 50));
	this->addDialogChild(pMainTypeLabel);

	//�����ͱ༭��
	CCScale9Sprite* pEditBoxMainTypeBK = CCScale9Sprite::create(s_szSprite9Btn1Path);
	m_pEditBoxMainType = CCEditBox::create(
		CCSizeMake(170, 30), 
		pEditBoxMainTypeBK );
	m_pEditBoxMainType->setAnchorPoint(ccp(0, 0.5));
	m_pEditBoxMainType->setPosition( ccp(pMainTypeLabel->getPositionX() + pMainTypeLabel->getContentSize().width, pMainTypeLabel->getPositionY()) );
	char cMainType[25];
	_itoa(mainType, cMainType, 10);
	m_pEditBoxMainType->setText( cMainType );
	m_pEditBoxMainType->setTouchPriority( -255 );
	this->addDialogChild( m_pEditBoxMainType );

	/********************************************************************************************/

	//����������
	FKCW_UIWidget_Label* pMainNameLabel = FKCW_UIWidget_Label::create(A2U("������������").c_str(), "", 14);
	pMainNameLabel->setAnchorPoint(ccp(0, 0.5));
	pMainNameLabel->setPosition(ccp(pMainTypeLabel->getPositionX(), m_pEditBoxMainType->getPositionY() - 50));
	this->addDialogChild(pMainNameLabel);

	//�����������༭��
	CCScale9Sprite* pEditBoxMainNameBK = CCScale9Sprite::create(s_szSprite9Btn1Path);
	m_pEditBoxMainName = CCEditBox::create(
		CCSizeMake(230, 30), 
		pEditBoxMainNameBK );
	m_pEditBoxMainName->setAnchorPoint(ccp(0, 0.5));
	m_pEditBoxMainName->setPosition( ccp(pMainNameLabel->getPositionX() + pMainNameLabel->getContentSize().width, pMainNameLabel->getPositionY()) );
	m_pEditBoxMainName->setText( mainName.c_str() );
	m_pEditBoxMainName->setTouchPriority( -255 );
	this->addDialogChild( m_pEditBoxMainName );

	/********************************************************************************************/
	//ȷ����ť
	FKCW_UIWidget_Button* pButton = FKCW_UIWidget_Button::createWith9Sprite(CCSizeMake(150, 32), 
		s_szSprite9Btn1Path, s_szSprite9Btn2Path );
	pButton->setAnchorPoint(ccp(0.5, 0));
	pButton->setOnClickListener(this, fkcw_uiwidget_click_selector(ReviseMainMessageDialog::onButtonClick));
	pButton->setPosition(ccp(this->getContentSize().width/2, 10));
	pButton->getLabel()->setFontSize(18);
	pButton->getLabel()->setString(A2U( "ȷ��" ).c_str());
	this->addDialogChild(pButton);

	return true;
}

void ReviseMainMessageDialog::setDelegate(ReviseMainMessageDialogDelegate* pDelegate)
{
	m_pDelegate = pDelegate;
}

cocos2d::CCSize ReviseMainMessageDialog::GetDialogSize()
{
	return CCSize(370, 220);
}

void ReviseMainMessageDialog::onButtonClick(CCObject* pSender)
{
	if (m_pDelegate != NULL)
	{
		short mainType = atoi(m_pEditBoxMainType->getText());
		string mainName = m_pEditBoxMainName->getText();
		mainName = FKCW_Base_Utils::Trim(mainName);

		if (mainType <= 0)
		{
			MessageBox(NULL, L"����ȷ��д������: ��ȷ��������Ӧ���Ǵ���0��short����", L"", 0);
		}
		else
		{
			m_pDelegate->onReviseMainMessageDialogSaveMessage(this, m_mainType, atoi(m_pEditBoxMainType->getText()), m_pEditBoxMainName->getText());
		}
	}
	this->removeFromParentAndCleanup(true);
}
