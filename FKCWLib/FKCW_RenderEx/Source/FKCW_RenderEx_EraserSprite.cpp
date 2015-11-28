//-------------------------------------------------------------------------
#include "../Include/FKCW_RenderEx_EraserSprite.h"
//-------------------------------------------------------------------------
FKCW_RenderEx_EraserSprite::FKCW_RenderEx_EraserSprite()
{

}
//-------------------------------------------------------------------------
FKCW_RenderEx_EraserSprite::~FKCW_RenderEx_EraserSprite()
{
	m_pEraser->release();
}
//-------------------------------------------------------------------------
FKCW_RenderEx_EraserSprite* FKCW_RenderEx_EraserSprite::create( const char *pszFileName, const bool& eraserImmediately, 
								   const unsigned int& drawType, const float& p_fSize)
{
	FKCW_RenderEx_EraserSprite* pRet = new FKCW_RenderEx_EraserSprite();
	if (pRet && pRet->init(pszFileName, eraserImmediately, drawType, p_fSize))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}
//-------------------------------------------------------------------------
bool FKCW_RenderEx_EraserSprite::init( const char *pszFileName, const bool& eraserImmediately, 
						const unsigned int& drawType, const float& p_fSize )
{
	if (!CCSprite::init())
	{
		return false;
	}

	initData(pszFileName, eraserImmediately, drawType, p_fSize);
	return true;
}
//-------------------------------------------------------------------------
void FKCW_RenderEx_EraserSprite::onEnter()
{
	CCSprite::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}
//-------------------------------------------------------------------------
void FKCW_RenderEx_EraserSprite::onExit()
{
	CCSprite::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}
//-------------------------------------------------------------------------
bool FKCW_RenderEx_EraserSprite::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	if (m_bEraser)
	{
		CCPoint point = pTouch->getLocation(); 
		// ע�����spriteSize/2.f��������Ϊ����֮ǰ���������ĵ�����������(0,0);
		/*		m_pEraser->setPosition(-this->getPosition() + point + spriteSize/2.f);*/
		CCPoint tempPos = -this->getPosition() + point + m_tagSpriteSize/2.f;
		eraseByBlend(tempPos);
		m_touchPoint = point;
		return true;
	}
	return false;
}
//-------------------------------------------------------------------------
void FKCW_RenderEx_EraserSprite::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	if (m_bEraser)
	{
		CCPoint point = pTouch->getLocation(); 
		CCPoint normal = ccpNormalize(point-m_touchPoint);
		CCPoint tempPos;
		// ����һ���ƶ����࣬����м�����©�����߾������
		while(1)
		{
			if (ccpDistance(point, m_touchPoint) < 1.f)
			{
				tempPos = -this->getPosition() + point + m_tagSpriteSize/2.f;
				eraseByBlend(tempPos);
				break;
			}
			m_touchPoint = m_touchPoint + normal*1.f;
			tempPos = -this->getPosition() + m_touchPoint + m_tagSpriteSize/2.f;
			eraseByBlend(tempPos);
		}

		m_touchPoint = point;
	}
}
//-------------------------------------------------------------------------
void FKCW_RenderEx_EraserSprite::initData( const char *pszFileName, const bool& eraserImmediately, 
							const unsigned int& drawType, const float fSize )
{
	m_bEraser		= eraserImmediately;
	m_uiDrawType	= drawType;
	m_fDrawWidth	= fSize;

	CCSprite* sprite = CCSprite::create(pszFileName);
	m_tagSpriteSize = sprite->getContentSize();
	// �������������������ĵ�����Ӧ�������ڣ�0,0������ ����������������ĵ��ڣ�0,0������Ȼ������ͨ��������ƫ������ʵ�֣�
	sprite->setAnchorPoint(ccp(0.f, 0.f));

	m_pRTex = CCRenderTexture::create((int)m_tagSpriteSize.width, (int)m_tagSpriteSize.height);
	m_pRTex->setPosition(CCPointZero);
	this->addChild(m_pRTex);

	m_pRTex->begin();
	sprite->visit();
	m_pRTex->end();

	m_pEraser = CCDrawNode::create();
	setDrawWidth(m_fDrawWidth);
	m_pEraser->retain();

	// �Զ���ͼƬ
	m_drawTextture = new CCTexture2D();
	m_drawTextture->retain();

}
//-------------------------------------------------------------------------
void FKCW_RenderEx_EraserSprite::setEraser(bool var)
{
	this->m_bEraser = var;
}
//-------------------------------------------------------------------------
bool FKCW_RenderEx_EraserSprite::getEraser()
{
	return m_bEraser;
}
//-------------------------------------------------------------------------
// ���û��ģʽ��ʵ�ֲ���Ч��
void FKCW_RenderEx_EraserSprite::eraseByBlend(CCPoint& point)
{
	switch (m_uiDrawType)
	{
	case 2:
		{
			CCSprite* drawSprite = CCSprite::createWithTexture(m_drawTextture);
			drawSprite->setPosition(point);
			ccBlendFunc blendFunc = { GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA };	// ���û��ģʽ, Դ---1-alpha�� Ŀ��---alpha
			drawSprite->setBlendFunc(blendFunc);
			m_pRTex->begin();
			drawSprite->visit();
			m_pRTex->end();
		}
		break;
	default:
		{
			m_pEraser->setPosition(point);
			ccBlendFunc blendFunc = { GL_ONE, GL_ZERO };	// ���û��ģʽ, Դ---1�� Ŀ��---0
			m_pEraser->setBlendFunc(blendFunc);
			m_pRTex->begin();
			m_pEraser->visit();
			m_pRTex->end();
		}
		break;
	}
}
//-------------------------------------------------------------------------
void FKCW_RenderEx_EraserSprite::eraseByColorMask()
{
	m_pRTex->begin();
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_TRUE);
	m_pEraser->visit();
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	m_pRTex->end();
}
//-------------------------------------------------------------------------
void FKCW_RenderEx_EraserSprite::setDrawWidth(float var)
{
	this->m_fDrawWidth = var;

	switch (m_uiDrawType)
	{
	case 0:	//< ������ģʽ
		{
			m_pEraser->drawDot(CCPointZero, m_fDrawWidth, ccc4f(0,0,0,0));
		}
		break;
	case 1:
		{
			// ����Բ������
			float fRadius		= m_fDrawWidth;					// Բ�İ뾶
			const int nCount	= 100;							// ����100������ģ��԰
			const float coef	= 2.0f * (float)M_PI/nCount;	// ����ÿ�������ڶ��������ĵļн�
			static CCPoint circle[nCount];						// ��������
			for(unsigned int i = 0;i <nCount; i++) {
				float rads = i*coef;							// ����
				circle[i].x = fRadius * cosf(rads);				// ��Ӧ�����x
				circle[i].y = fRadius * sinf(rads);				// ��Ӧ�����y
			}
			m_pEraser->drawPolygon(circle, nCount, ccc4f(0, 0, 0, 0), 0, ccc4f(0, 0, 0, 0));//������������!
		}
		break;
	case 2:
		{
			/// ��Ҫ�Զ������ͼƬ
		}
		break;
	default:
		break;
	}
}
//-------------------------------------------------------------------------
float FKCW_RenderEx_EraserSprite::getDrawWidth()
{
	return this->m_fDrawWidth;
}
//-------------------------------------------------------------------------
void FKCW_RenderEx_EraserSprite::setEraserOk(bool var)
{
	this->m_bEraserOk = var;
}
//-------------------------------------------------------------------------
bool FKCW_RenderEx_EraserSprite::getEraserOk()
{
	m_bEraserOk = false;

	CCImage* image = new CCImage();
	image = m_pRTex->newCCImage(true);

	int m = 3;
	if (image->hasAlpha())
	{
		m = 4;
	}

	unsigned char *data_= image->getData();
	int x = 0, y = 0;
	// ����Ҫһ�㣬��Opengl�£������ĵ����������Ͻ�
	for (x = 0; x < m_tagSpriteSize.width; ++x)
	{
		for (y = 0 ; y < m_tagSpriteSize.height; ++y)
		{

			unsigned char *pixel = data_ + (x + y * image->getWidth()) * m;

			unsigned int r = (unsigned int)*pixel;
			unsigned int g = (unsigned int)*(pixel + 1);
			unsigned int b = (unsigned int)*(pixel + 2) ;
			unsigned int a = (unsigned int)*(pixel + 3);

			if (r != 0 && g != 0 && b != 0 && a != 0)
			{
				m_bEraserOk = false;
				break;
			}
		}
		if (m_tagSpriteSize.height != y)
		{
			break;
		}
	}
	if (x == m_tagSpriteSize.width && y == m_tagSpriteSize.height)
	{
		m_bEraserOk = true;
	}

	delete image;

	return this->m_bEraserOk;
}
//-------------------------------------------------------------------------
// �Զ��������״
void FKCW_RenderEx_EraserSprite::setDrawStencil( const char *pszFileName )
{
	m_drawTextture = CCTextureCache::sharedTextureCache()->addImage(pszFileName);
}
//-------------------------------------------------------------------------