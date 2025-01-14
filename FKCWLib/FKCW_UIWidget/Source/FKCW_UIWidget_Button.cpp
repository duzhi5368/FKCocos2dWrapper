//-------------------------------------------------------------------------
#include "../Include/FKCW_UIWidget_Button.h"
//-------------------------------------------------------------------------
#define CC_CENTER_POS(__SIZE__) CCPoint(__SIZE__.width / 2, __SIZE__.height / 2)
#define CC_SAFE_SET_VISIBLE(__ITEM__, __VAR__) if( __ITEM__ ) __ITEM__->setVisible(__VAR__)
#define CC_SAFE_REMOVE(__ITEM__) if(__ITEM__) removeChild(__ITEM__)
#define CC_SAFE_REMOVE_9ELSE(__ITEM__) if(__ITEM__ && !(dynamic_cast<FKCW_UIWidget_Scale9Sprite*>(__ITEM__))) removeChild(__ITEM__)
#define CC_SAFE_REMOVE_9SPRITE(__ITEM__) if(__ITEM__ && dynamic_cast<FKCW_UIWidget_Scale9Sprite*>(__ITEM__)) removeChild(__ITEM__)
#define CC_IS_9SPRITE(__ITEM__) __ITEM__ && dynamic_cast<FKCW_UIWidget_Scale9Sprite*>(__ITEM__) ? true : false
//-------------------------------------------------------------------------
FKCW_UIWidget_Button::FKCW_UIWidget_Button()
	: m_pNormalImage(NULL)
	, m_pDisabledImage(NULL)
	, m_pSelectedImage(NULL)
	, m_bScale9Enabled(false)
	, m_tTextOffset(CCPointZero)
	, m_pLabel(NULL)
	, m_bCascadeTextSizeEnabled(false)
{
	setThisObject(this);
	setCascadeOpacityEnabled(true);

	setAnchorPoint(FKCW_UIWIDGET_BASIC_DEFAULT_ANCHOR_POINT);
	setContentSize(FKCW_UIWIDGET_BASIC_DEFAULT_CONTENT_SIZE);
}
//-------------------------------------------------------------------------
FKCW_UIWidget_Button::~FKCW_UIWidget_Button()
{
	CC_SAFE_RELEASE(m_pLabel);
}
//-------------------------------------------------------------------------
FKCW_UIWidget_Button* FKCW_UIWidget_Button::create()
{
	FKCW_UIWidget_Button* pRet = new FKCW_UIWidget_Button();
	if( pRet && pRet->init() )
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}
//-------------------------------------------------------------------------
FKCW_UIWidget_Button* FKCW_UIWidget_Button::createWith9Sprite(const CCSize& tSize, const char* pNormal, const char* pSelected, const char* pDisabled)
{
	FKCW_UIWidget_Button* pRet = new FKCW_UIWidget_Button();
	if( pRet && pRet->initWith9Sprite(tSize, pNormal, pSelected, pDisabled) )
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}
//-------------------------------------------------------------------------
FKCW_UIWidget_Button* FKCW_UIWidget_Button::create(const char* pNormal, const char* pSelected, const char* pDisabled)
{
	FKCW_UIWidget_Button* pRet = new FKCW_UIWidget_Button();
	if( pRet && pRet->initWithFile(pNormal, pSelected, pDisabled) )
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}
//-------------------------------------------------------------------------
bool FKCW_UIWidget_Button::init()
{
	setAnchorPoint(FKCW_UIWIDGET_BASIC_DEFAULT_ANCHOR_POINT);
	setContentSize(FKCW_UIWIDGET_BASIC_DEFAULT_CONTENT_SIZE);

	return true;
}
//-------------------------------------------------------------------------
bool FKCW_UIWidget_Button::initWith9Sprite(const CCSize& tSize, const char* pNormal, const char* pSelected, const char* pDisabled)
{
	if( !pNormal || !strlen(pNormal) || !init() )
	{
		return false;
	}

	setScale9Enabled(true);
	setContentSize(tSize);
	setNormalImage(pNormal);
	setSelectedImage(pSelected);
	setDisabledImage(pDisabled);

	return true;
}
//-------------------------------------------------------------------------
bool FKCW_UIWidget_Button::initWithFile(const char* pNormal, const char* pSelected, const char* pDisabled)
{
	if( !pNormal || !strlen(pNormal) || !init() )
	{
		return false;
	}

	setScale9Enabled(false);
	setNormalImage(pNormal);
	setSelectedImage(pSelected);
	setDisabledImage(pDisabled);

	return true;
}
//-------------------------------------------------------------------------
void FKCW_UIWidget_Button::setCascadeTextSizeEnabled(bool bEnabled, const CCSize& tPadding)
{
	m_bCascadeTextSizeEnabled = bEnabled;
	m_tCascadeTextSizePadding = tPadding;

	if( bEnabled ) updateCascadeTextSize();
}
//-------------------------------------------------------------------------
void FKCW_UIWidget_Button::updateCascadeTextSize()
{
	if( m_bCascadeTextSizeEnabled && m_bScale9Enabled && m_pLabel )
	{
		const CCSize& tTextSize = m_pLabel->getContentSize();
		setContentSize(tTextSize + m_tCascadeTextSizePadding);
	}
}
//-------------------------------------------------------------------------
void FKCW_UIWidget_Button::setNormalSpriteFrame(CCSpriteFrame* pFrame)
{
	if( pFrame )
	{
		if( m_pNormalImage )
		{
			if( m_bScale9Enabled )
			{
				FKCW_UIWidget_Scale9Sprite* pImage = (FKCW_UIWidget_Scale9Sprite*) m_pNormalImage;
				pImage->initWithSpriteFrame(pFrame);
				pImage->setContentSize(m_obContentSize);
			}
			else
			{
				CCSprite* pImage = (CCSprite*) m_pNormalImage;
				pImage->setDisplayFrame(pFrame);
				setContentSize(pImage->getContentSize());
			}
		}
		else
		{
			if( m_bScale9Enabled )
			{
				m_pNormalImage = FKCW_UIWidget_Scale9Sprite::createWithSpriteFrame(pFrame);
				m_pNormalImage->setContentSize(m_obContentSize);
			}
			else
			{
				m_pNormalImage = CCSprite::createWithSpriteFrame(pFrame);
				setContentSize(m_pNormalImage->getContentSize());
			}

			m_pNormalImage->setPosition(CCPoint(m_obContentSize.width/2, m_obContentSize.height/2));
			addChild(m_pNormalImage);
		}
	}

	updateCascadeTextSize();
}
//-------------------------------------------------------------------------
void FKCW_UIWidget_Button::setSelectedSpriteFrame(CCSpriteFrame* pFrame)
{
	if( pFrame )
	{
		if( m_pSelectedImage )
		{
			if( m_bScale9Enabled )
			{
				FKCW_UIWidget_Scale9Sprite* pImage = (FKCW_UIWidget_Scale9Sprite*) m_pSelectedImage;
				pImage->initWithSpriteFrame(pFrame);
				pImage->setContentSize(m_obContentSize);
			}
			else
			{
				CCSprite* pImage = (CCSprite*) m_pSelectedImage;
				pImage->setDisplayFrame(pFrame);
			}
		}
		else
		{
			if( m_bScale9Enabled )
			{
				m_pSelectedImage = FKCW_UIWidget_Scale9Sprite::createWithSpriteFrame(pFrame);
				m_pSelectedImage->setContentSize(m_obContentSize);
			}
			else
			{
				m_pSelectedImage = CCSprite::createWithSpriteFrame(pFrame);
			}

			m_pSelectedImage->setPosition(CCPoint(m_obContentSize.width/2, m_obContentSize.height/2));
			m_pSelectedImage->setVisible(false);
			addChild(m_pSelectedImage);
		}
	}

	updateCascadeTextSize();
}
//-------------------------------------------------------------------------
void FKCW_UIWidget_Button::setDisabledSpriteFrame(CCSpriteFrame* pFrame)
{
	if( pFrame )
	{
		if( m_pDisabledImage )
		{
			if( m_bScale9Enabled )
			{
				FKCW_UIWidget_Scale9Sprite* pImage = (FKCW_UIWidget_Scale9Sprite*) m_pDisabledImage;
				pImage->initWithSpriteFrame(pFrame);
				pImage->setContentSize(m_obContentSize);
			}
			else
			{
				CCSprite* pImage = (CCSprite*) m_pDisabledImage;
				pImage->setDisplayFrame(pFrame);
			}
		}
		else
		{
			if( m_bScale9Enabled )
			{
				m_pDisabledImage = FKCW_UIWidget_Scale9Sprite::createWithSpriteFrame(pFrame);
				m_pDisabledImage->setContentSize(m_obContentSize);
			}
			else
			{
				m_pDisabledImage = CCSprite::createWithSpriteFrame(pFrame);
			}

			m_pDisabledImage->setPosition(CCPoint(m_obContentSize.width/2, m_obContentSize.height/2));
			m_pDisabledImage->setVisible(false);
			addChild(m_pDisabledImage);
		}
	}

	updateCascadeTextSize();
}
//-------------------------------------------------------------------------
void FKCW_UIWidget_Button::setNormalImage(const char* pFile)
{
	if( pFile && strlen(pFile) )
	{
		CCTexture2D* pTexture = CCTextureCache::sharedTextureCache()->addImage(pFile);
		setNormalTexture(pTexture);
	}
}
//-------------------------------------------------------------------------
void FKCW_UIWidget_Button::setSelectedImage(const char* pFile)
{
	if( pFile && strlen(pFile) )
	{
		CCTexture2D* pTexture = CCTextureCache::sharedTextureCache()->addImage(pFile);
		setSelectedTexture(pTexture);
	}
}
//-------------------------------------------------------------------------
void FKCW_UIWidget_Button::setDisabledImage(const char* pFile)
{
	if( pFile && strlen(pFile) )
	{
		CCTexture2D* pTexture = CCTextureCache::sharedTextureCache()->addImage(pFile);
		setDisabledTexture(pTexture);
	}
}
//-------------------------------------------------------------------------
void FKCW_UIWidget_Button::setNormalTexture(CCTexture2D *pTexture)
{
	if( pTexture )
	{
		if( m_pNormalImage )
		{
			if( m_bScale9Enabled )
			{
				FKCW_UIWidget_Scale9Sprite* pImage = (FKCW_UIWidget_Scale9Sprite*) m_pNormalImage;
				pImage->setTexture(pTexture);
				pImage->setContentSize(m_obContentSize);
			}
			else
			{
				CCRect rect = CCRectZero;
				rect.size = pTexture->getContentSize();
				CCSprite* pImage = (CCSprite*) m_pNormalImage;
				pImage->setTexture(pTexture);
				pImage->setTextureRect(rect);
				setContentSize(pTexture->getContentSize());
			}
		}
		else
		{
			if( m_bScale9Enabled )
			{
				m_pNormalImage = FKCW_UIWidget_Scale9Sprite::createWithTexture(pTexture);
				m_pNormalImage->setContentSize(m_obContentSize);
			}
			else
			{
				CCRect rect;
				rect.origin = CCPointZero;
				rect.size = pTexture->getContentSize();
				m_pNormalImage = CCSprite::createWithTexture(pTexture);
				setContentSize(pTexture->getContentSize());
			}

			m_pNormalImage->setPosition(CCPoint(m_obContentSize.width/2, m_obContentSize.height/2));
			addChild(m_pNormalImage);
		}
	}

	updateCascadeTextSize();
}
//-------------------------------------------------------------------------
void FKCW_UIWidget_Button::setSelectedTexture(CCTexture2D *pTexture)
{
	if( pTexture )
	{
		if( m_pSelectedImage )
		{
			if( m_bScale9Enabled )
			{
				FKCW_UIWidget_Scale9Sprite* pImage = (FKCW_UIWidget_Scale9Sprite*) m_pSelectedImage;
				pImage->setTexture(pTexture);
				pImage->setContentSize(m_obContentSize);
			}
			else
			{
				CCRect rect = CCRectZero;
				rect.size = pTexture->getContentSize();
				CCSprite* pImage = (CCSprite*) m_pSelectedImage;
				pImage->setTexture(pTexture);
				pImage->setTextureRect(rect);
			}
		}
		else
		{
			if( m_bScale9Enabled )
			{
				m_pSelectedImage = FKCW_UIWidget_Scale9Sprite::createWithTexture(pTexture);
				m_pSelectedImage->setContentSize(m_obContentSize);
			}
			else
			{
				CCRect rect;
				rect.origin = CCPointZero;
				rect.size = pTexture->getContentSize();
				m_pSelectedImage = CCSprite::createWithTexture(pTexture);
			}

			m_pSelectedImage->setPosition(CCPoint(m_obContentSize.width/2, m_obContentSize.height/2));
			m_pSelectedImage->setVisible(false);
			addChild(m_pSelectedImage);
		}
	}

	updateCascadeTextSize();
}
//-------------------------------------------------------------------------
void FKCW_UIWidget_Button::setDisabledTexture(CCTexture2D *pTexture)
{
	if( pTexture )
	{
		if( m_pDisabledImage )
		{
			if( m_bScale9Enabled )
			{
				FKCW_UIWidget_Scale9Sprite* pImage = (FKCW_UIWidget_Scale9Sprite*) m_pDisabledImage;
				pImage->setTexture(pTexture);
				pImage->setContentSize(m_obContentSize);
			}
			else
			{
				CCRect rect = CCRectZero;
				rect.size = pTexture->getContentSize();
				CCSprite* pImage = (CCSprite*) m_pDisabledImage;
				pImage->setTexture(pTexture);
				pImage->setTextureRect(rect);
			}
		}
		else
		{
			if( m_bScale9Enabled )
			{
				m_pDisabledImage = FKCW_UIWidget_Scale9Sprite::createWithTexture(pTexture);
				m_pDisabledImage->setContentSize(m_obContentSize);
			}
			else
			{
				CCRect rect;
				rect.origin = CCPointZero;
				rect.size = pTexture->getContentSize();
				m_pDisabledImage = CCSprite::createWithTexture(pTexture);
			}

			m_pDisabledImage->setPosition(CCPoint(m_obContentSize.width/2, m_obContentSize.height/2));
			m_pDisabledImage->setVisible(false);
			addChild(m_pDisabledImage);
		}
	}

	updateCascadeTextSize();
}
//-------------------------------------------------------------------------
void FKCW_UIWidget_Button::setNormalSpriteFrameName(const char* pSpriteName)
{
	CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pSpriteName);

#if COCOS2D_DEBUG > 0
	char msg[256] = {0};
	sprintf(msg, "Invalid spriteFrameName: %s", pSpriteName);
	CCAssert(pFrame != NULL, msg);
#endif

	return setNormalSpriteFrame(pFrame);
}
//-------------------------------------------------------------------------
void FKCW_UIWidget_Button::setSelectedSpriteFrameName(const char* pSpriteName)
{
	CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pSpriteName);

#if COCOS2D_DEBUG > 0
	char msg[256] = {0};
	sprintf(msg, "Invalid spriteFrameName: %s", pSpriteName);
	CCAssert(pFrame != NULL, msg);
#endif

	return setSelectedSpriteFrame(pFrame);
}
//-------------------------------------------------------------------------
void FKCW_UIWidget_Button::setDisabledSpriteFrameName(const char* pSpriteName)
{
	CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pSpriteName);

#if COCOS2D_DEBUG > 0
	char msg[256] = {0};
	sprintf(msg, "Invalid spriteFrameName: %s", pSpriteName);
	CCAssert(pFrame != NULL, msg);
#endif

	return setDisabledSpriteFrame(pFrame);
}
//-------------------------------------------------------------------------
CCNode* FKCW_UIWidget_Button::getNormalImage()
{
	return m_pNormalImage;
}
//-------------------------------------------------------------------------
CCNode* FKCW_UIWidget_Button::getSelectedImage()
{
	return m_pSelectedImage;
}
//-------------------------------------------------------------------------
CCNode* FKCW_UIWidget_Button::getDisabledImage()
{
	return m_pDisabledImage;
}
//-------------------------------------------------------------------------
void FKCW_UIWidget_Button::setContentSize(const CCSize& contentSize)
{
	CCNodeRGBA::setContentSize(contentSize);

	if( m_pNormalImage )
	{
		if( CC_IS_9SPRITE(m_pNormalImage) )
		{
			m_pNormalImage->setContentSize(m_obContentSize);
		}
		m_pNormalImage->setPosition(CC_CENTER_POS(m_obContentSize));
	}

	if( m_pSelectedImage )
	{
		if( CC_IS_9SPRITE(m_pSelectedImage) )
		{
			m_pSelectedImage->setContentSize(m_obContentSize);
		}
		m_pSelectedImage->setPosition(CC_CENTER_POS(m_obContentSize));
	}

	if( m_pDisabledImage )
	{
		if( CC_IS_9SPRITE(m_pDisabledImage) )
		{
			m_pDisabledImage->setContentSize(m_obContentSize);
		}
		m_pDisabledImage->setPosition(CC_CENTER_POS(m_obContentSize));
	}

	if( m_pLabel )
	{
		m_pLabel->setPosition(CC_CENTER_POS(m_obContentSize) + m_tTextOffset);
	}
}
//-------------------------------------------------------------------------
void FKCW_UIWidget_Button::setText(const char* pText)
{
	getLabel()->setString(pText);
	updateCascadeTextSize();
}
//-------------------------------------------------------------------------
const char* FKCW_UIWidget_Button::getText()
{
	return getLabel()->getString();
}
//-------------------------------------------------------------------------
void FKCW_UIWidget_Button::setTextFontName(const char* pTextFontName)
{
	getLabel()->setFontName(pTextFontName);
	updateCascadeTextSize();
}
//-------------------------------------------------------------------------
const char* FKCW_UIWidget_Button::getTextFontName()
{
	return getLabel()->getFontName();
}
//-------------------------------------------------------------------------
void FKCW_UIWidget_Button::setTextFontSize(float fTextFontSize)
{
	getLabel()->setFontSize(fTextFontSize);
	updateCascadeTextSize();
}
//-------------------------------------------------------------------------
float FKCW_UIWidget_Button::getTextFontSize()
{
	return getLabel()->getFontSize();
}
//-------------------------------------------------------------------------
void FKCW_UIWidget_Button::setTextColor(const ccColor3B& color)
{
	getLabel()->setColor(color);
}
//-------------------------------------------------------------------------
const ccColor3B& FKCW_UIWidget_Button::getTextColor()
{
	return getLabel()->getColor();
}
//-------------------------------------------------------------------------
void FKCW_UIWidget_Button::initText(const char* pText, const char* pFontName, float fFontSize)
{
	getLabel()->initWithString(pText, pFontName, fFontSize);
	updateCascadeTextSize();
}
//-------------------------------------------------------------------------
FKCW_UIWidget_Label* FKCW_UIWidget_Button::getLabel()
{
	if(!m_pLabel)
	{
		m_pLabel = FKCW_UIWidget_Label::create();
		m_pLabel->retain();
		m_pLabel->setFontSize(25);
		m_pLabel->setPosition(CC_CENTER_POS(m_obContentSize));
		m_pLabel->setZOrder(1);
		addChild(m_pLabel);
	}
	return m_pLabel;
}
//-------------------------------------------------------------------------
bool FKCW_UIWidget_Button::isScale9Enabled()
{
	return m_bScale9Enabled;
}
//-------------------------------------------------------------------------
void FKCW_UIWidget_Button::setScale9Enabled(bool bEnabled)
{
	if( m_bScale9Enabled != bEnabled )
	{
		if( bEnabled )
		{
			CC_SAFE_REMOVE_9ELSE(m_pNormalImage);
			CC_SAFE_REMOVE_9ELSE(m_pSelectedImage);
			CC_SAFE_REMOVE_9ELSE(m_pDisabledImage);
		}
		else
		{
			CC_SAFE_REMOVE_9SPRITE(m_pNormalImage);
			CC_SAFE_REMOVE_9SPRITE(m_pSelectedImage);
			CC_SAFE_REMOVE_9SPRITE(m_pDisabledImage);
		}
		m_bScale9Enabled = bEnabled;
	}
}
//-------------------------------------------------------------------------
void FKCW_UIWidget_Button::setEnabled(bool bEnabled)
{
	if( m_bEnabled != bEnabled )
	{
		m_bEnabled = bEnabled;
		if( bEnabled )
		{
			CC_SAFE_SET_VISIBLE(m_pNormalImage, true);
			CC_SAFE_SET_VISIBLE(m_pSelectedImage, false);
			CC_SAFE_SET_VISIBLE(m_pDisabledImage, false);
		}
		else
		{
			if( m_pDisabledImage )
			{
				CC_SAFE_SET_VISIBLE(m_pNormalImage, false);
				CC_SAFE_SET_VISIBLE(m_pSelectedImage, false);
				CC_SAFE_SET_VISIBLE(m_pDisabledImage, true);
			}
			else
			{
				CC_SAFE_SET_VISIBLE(m_pNormalImage, true);
				CC_SAFE_SET_VISIBLE(m_pSelectedImage, false);
				CC_SAFE_SET_VISIBLE(m_pDisabledImage, false);
			}
		}
	}
}
//-------------------------------------------------------------------------
void FKCW_UIWidget_Button::setLabelOffset(const CCPoint& tOffset)
{
	if( m_pLabel )
	{
		m_tTextOffset = tOffset;
		m_pLabel->setPosition(m_pLabel->getPosition() + m_tTextOffset);
	}
	else
	{
		getLabel();
		m_tTextOffset = tOffset;
		m_pLabel->setPosition(m_pLabel->getPosition() + m_tTextOffset);
	}
}
//-------------------------------------------------------------------------
ENUM_WidgetTouchModel FKCW_UIWidget_Button::onTouchBegan(CCTouch* pTouch)
{
	FKCW_UIWIDGET_LONGCLICK_ONTOUCHBEGAN;

	if( m_pSelectedImage )
	{
		CC_SAFE_SET_VISIBLE(m_pNormalImage, false);
		CC_SAFE_SET_VISIBLE(m_pDisabledImage, false);
		m_pSelectedImage->setVisible(true);
	}
	return eWidgetTouchTransient;
}
//-------------------------------------------------------------------------
void FKCW_UIWidget_Button::onTouchMoved(CCTouch* pTouch, float fDuration)
{
	FKCW_UIWIDGET_LONGCLICK_ONTOUCHMOVED;

	if( m_pSelectedImage )
	{
		CCPoint touchPointInView = m_pParent->convertToNodeSpace(pTouch->getLocation());
		if( boundingBox().containsPoint(touchPointInView) )
		{
			CC_SAFE_SET_VISIBLE(m_pNormalImage, false);
			m_pSelectedImage->setVisible(true);
		}
		else
		{
			CC_SAFE_SET_VISIBLE(m_pNormalImage, true);
			m_pSelectedImage->setVisible(false);
		}
	}
}
//-------------------------------------------------------------------------
void FKCW_UIWidget_Button::onTouchEnded(CCTouch* pTouch, float fDuration)
{
	FKCW_UIWIDGET_LONGCLICK_ONTOUCHENDED;

	if( m_pSelectedImage )
	{
		CCPoint touchPointInView = m_pParent->convertToNodeSpace(pTouch->getLocation());
		if( boundingBox().containsPoint(touchPointInView) )
		{
			CC_SAFE_SET_VISIBLE(m_pNormalImage, true);
			m_pSelectedImage->setVisible(false);
			executeClickHandler(this);
		}
		else
		{
			CC_SAFE_SET_VISIBLE(m_pNormalImage, true);
			m_pSelectedImage->setVisible(false);
		}
	}
	else
	{
		CCPoint touchPointInView = m_pParent->convertToNodeSpace(pTouch->getLocation());
		if( boundingBox().containsPoint(touchPointInView) )
		{
			CC_SAFE_SET_VISIBLE(m_pNormalImage, true);
			executeClickHandler(this);
		}
		CC_SAFE_SET_VISIBLE(m_pNormalImage, true);
	}
}
//-------------------------------------------------------------------------
void FKCW_UIWidget_Button::onTouchCancelled(CCTouch* pTouch, float fDuration)
{
	FKCW_UIWIDGET_LONGCLICK_ONTOUCHCANCELLED;

	CC_SAFE_SET_VISIBLE(m_pNormalImage, true);
	CC_SAFE_SET_VISIBLE(m_pSelectedImage, false);
}
//-------------------------------------------------------------------------