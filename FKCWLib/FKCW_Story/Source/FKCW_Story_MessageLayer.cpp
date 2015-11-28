//-------------------------------------------------------------------------
#include "../Include/FKCW_Story_MessageLayer.h"
#include "../Include/FKCW_Story_CommandSet.h"
#include "../Include/FKCW_Story_Player.h"
//-------------------------------------------------------------------------
FKCW_Story_MessageLayer::FKCW_Story_MessageLayer() :
	m_msgLabel(NULL),
	m_nameLabel(NULL),
	m_looping(false),
	m_player(NULL),
	m_wait(0) 
{
}
//-------------------------------------------------------------------------
FKCW_Story_MessageLayer::~FKCW_Story_MessageLayer() 
{
}
//-------------------------------------------------------------------------
FKCW_Story_MessageLayer* FKCW_Story_MessageLayer::create(FKCW_Story_Player* player) 
{
	FKCW_Story_MessageLayer* l = new FKCW_Story_MessageLayer();
	if(l->initWithPlayer(player)) 
	{
		return (FKCW_Story_MessageLayer*)l->autorelease();
	}
	CC_SAFE_RELEASE(l);
	return NULL;
}
//-------------------------------------------------------------------------
void FKCW_Story_MessageLayer::onExit()
{
	CCLayer::onExit();
}
//-------------------------------------------------------------------------
void FKCW_Story_MessageLayer::onEnter() 
{
	CCLayer::onEnter();
}
//-------------------------------------------------------------------------
bool FKCW_Story_MessageLayer::initWithPlayer(FKCW_Story_Player* player)
{
	if(!CCLayer::init())
		return false;

	m_player = player;

	setTouchEnabled(true);
	setTouchMode(kCCTouchesOneByOne);
	setKeypadEnabled(true);

	return true;
}
//-------------------------------------------------------------------------
void FKCW_Story_MessageLayer::showMessage(FKCW_Story_Command* cmd)
{
	// ���
	if(m_looping)
		return;
	m_looping = true;

	m_wait = cmd->m_param.msg.wait;

	// �������ֱ�ǩ
	m_nameLabel = CCLabelTTF::create(
		A2U(cmd->m_param.msg.name).c_str(), 
		m_player->getNameFont().c_str(),
		m_player->getNameSize());
	m_nameLabel->setAnchorPoint(m_player->getNameAnchor());
	m_nameLabel->setPosition(m_player->getNamePos());
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
	m_nameLabel->setFontFillColor(ccc3FromInt(m_player->getNameColor()));
#endif
	m_nameLabel->setOpacity((m_player->getNameColor() >> 24) & 0xff);
	addChild(m_nameLabel);

	// ������Ϣ��ǩ
	m_msgLabel = AutoNewLineText(
		A2U(cmd->m_param.msg.s),
		m_player->getMessageFont().c_str(),
		m_player->getMessageSize(),
		1,
		10,
		600,
		ccc3FromInt(m_player->getMessageColor()) );
	m_msgLabel->setColor( ccc3FromInt(m_player->getMessageColor()) );
	m_msgLabel->setAnchorPoint(m_player->getMessageAnchor());
	m_msgLabel->setPosition(m_player->getMessagePos());
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
	m_msgLabel->setFontFillColor(ccc3FromInt(m_player->getMessageColor()));
#endif
	m_msgLabel->setOpacity((m_player->getMessageColor() >> 24) & 0xff);
	addChild(m_msgLabel);

	// ��ʼѭ��
	CCArray* pTTFList = m_msgLabel->getChildren();
	CCObject* pObject = NULL;  
	CCLabelTTF* pChild = NULL;
	int nIndex = 1;
	CCARRAY_FOREACH( pTTFList, pObject )  
	{  
		pChild = (CCLabelTTF*)pObject;  
		if( pChild == NULL )  
			break;
		for( ; ; )
		{
			if( pChild == NULL )
				break;
			pChild->setVisible( false );
			CCDelayTime* pAction = CCDelayTime::create( 0.05f * nIndex );
			CCCallFuncN* pDone = CCCallFuncN::create( this, callfuncN_selector(FKCW_Story_MessageLayer::TTFItemDelayOver) );
			CCSequence* pSeq = CCSequence::create( pAction, pDone, NULL );
			pChild->runAction( pSeq );
			nIndex++;
			pChild = (CCLabelTTF*)pChild->getChildByTag( 0 );
		}
	}
	// �����ص�
	this->runAction( CCSequence::create(
		CCDelayTime::create( 0.05f * (pTTFList->count() + 1) ),
		CCCallFunc::create( this, callfunc_selector(FKCW_Story_MessageLayer::onDialogEndLooping) ),
		NULL ));
}
//------------------------------------------------------------------------
// ����Ӧ��������
/*	horizontalSpacing�� ˮƽ��� 
	verticalSpacing��   ��ֱ��� 
	lineWidth��         һ�е������ 
*/  
CCLabelTTF* FKCW_Story_MessageLayer::AutoNewLineText(std::string _string, const char *fontName, 
float fontSize, float horizontalSpacing, float verticalSpacing, float lineWidth, ccColor3B p_fontColor )
{
	CCArray* labelTTF_arr = CCArray::create();  
	int index = 0;  
	int index_max = strlen(_string.c_str());  
	bool is_end = true;  
	// ����ASCII���ҳ���Ӣ���ַ�����������һ��CCLabelTTF�������labelTTF_arr������
	while (is_end) 
	{  
		if (_string[index] >= 0 && _string[index] <= 127) 
		{  
			std::string englishStr = _string.substr(index,1);
			labelTTF_arr->addObject(CCLabelTTF::create(englishStr.c_str(), fontName, fontSize));  
			index+= 1;  
		}  
		else
		{  
			std::string chineseStr =_string.substr(index,3).c_str();  
			labelTTF_arr->addObject(CCLabelTTF::create(chineseStr.c_str(), fontName, fontSize));  
			index+= 3;  
		}  

		if (index>=index_max) {  
			is_end=false;  
		}
	}

	// ��CCLabelTTF����������Ӷ���CCLabelTTF���Դ���ϳ�һ�仰�������Ͻǵ�һ����Ϊê�㡣��  
	CCLabelTTF* returnTTF = (CCLabelTTF*)labelTTF_arr->objectAtIndex(0);  
	float nowWidth = returnTTF->getContentSize().width;                // ���е��п�
	CCLabelTTF* BeforeCurTTF = (CCLabelTTF*)labelTTF_arr->objectAtIndex(0);  
	CCLabelTTF* CurLineBeginTTF = (CCLabelTTF*)labelTTF_arr->objectAtIndex(0);       // ��������ߵ��ַ�

	int arr_count = labelTTF_arr->count();  
	for (int i=1; i < arr_count; i++)
	{  
		CCLabelTTF* CurTTF = (CCLabelTTF*)labelTTF_arr->objectAtIndex(i);  
		CurTTF->setColor( p_fontColor );
		CurTTF->setAnchorPoint(ccp(0, 0.5));  
		nowWidth+= CurTTF->getContentSize().width;  
		char* pNewLineKey = "\n";  // �÷��Ż���
		char* pMissKey = "\r";    // �÷��Ų�����
		// ��ȳ���
		if ( nowWidth >= lineWidth )
		{  
			CurTTF->setPosition(ccp( ( -nowWidth + CurTTF->getContentSize().width) - BeforeCurTTF->getContentSize().width * 0.5f, 
				-BeforeCurTTF->getContentSize().height * 0.5 -verticalSpacing));  
			nowWidth = returnTTF->getContentSize().width;  
			// ��������
			CurLineBeginTTF = CurTTF;  
		}
		//  �ǻ��з�
		else if( strcmp( CurTTF->getString() , pNewLineKey ) == 0 )
		{
			CurTTF->setPosition(ccp( ( -nowWidth + CurTTF->getContentSize().width) - BeforeCurTTF->getContentSize().width * 0.5f, 
				-BeforeCurTTF->getContentSize().height * 0.5 -verticalSpacing));  
			nowWidth = returnTTF->getContentSize().width;  
			// ��������
			CurLineBeginTTF = CurTTF;  
		}
		else if( strcmp( CurTTF->getString() , pMissKey ) == 0 )
		{
			continue;
		}
		else
		{  
			CurTTF->setPosition(ccp(BeforeCurTTF->getContentSize().width+horizontalSpacing, BeforeCurTTF->getContentSize().height*0.5f));  
		}  
		CurTTF->setTag( 0 );
		BeforeCurTTF->addChild(CurTTF);  
		BeforeCurTTF = CurTTF;  
	}  

	return returnTTF;  
}
//------------------------------------------------------------------------
// �ַ��¼��ص�
void FKCW_Story_MessageLayer::TTFItemDelayOver(CCNode* pSender)
{
	if( pSender )
		pSender->setVisible( true );
}
//------------------------------------------------------------------------
void FKCW_Story_MessageLayer::handleUserClick() 
{
	// ����ѭ������ֹͣ
	// ������ѭ�����������������Ϣ
	if(m_looping) 
	{
		m_looping = false;

		if(m_wait >= 0) {
			schedule(schedule_selector(FKCW_Story_MessageLayer::onDialogDisplayedSomeWhile), 0, 0, m_wait);
		}
	}
	else 
	{
		if(m_msgLabel) {
			unschedule(schedule_selector(FKCW_Story_MessageLayer::onDialogDisplayedSomeWhile));
			m_msgLabel->removeFromParent();
			m_msgLabel = NULL;
		}
		if(m_nameLabel) {
			m_nameLabel->removeFromParent();
			m_nameLabel = NULL;
		}
		m_player->onMessageDone();
	}
}
//-------------------------------------------------------------------------
bool FKCW_Story_MessageLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	handleUserClick();
	return true;
}
//-------------------------------------------------------------------------
void FKCW_Story_MessageLayer::keyBackClicked() 
{
	handleUserClick();
}
//-------------------------------------------------------------------------
void FKCW_Story_MessageLayer::onDialogDisplayedSomeWhile(float delta)
{
	if(m_msgLabel) {
		m_msgLabel->removeFromParent();
		m_msgLabel = NULL;
	}
	if(m_nameLabel) {
		m_nameLabel->removeFromParent();
		m_nameLabel = NULL;
	}
	m_player->onMessageDone();
}
//-------------------------------------------------------------------------
void FKCW_Story_MessageLayer::onDialogEndLooping() 
{
	m_looping = false;

	if(m_wait >= 0)
	{
		schedule(schedule_selector(FKCW_Story_MessageLayer::onDialogDisplayedSomeWhile), 0, 0, m_wait);
	}
}
//-------------------------------------------------------------------------