//-------------------------------------------------------------------------
#include "../Include/FKCW_UI_RookieGuideLayer.h"
#include "../../FKCW_Base/Include/FKCW_Base_ColorConvert.h"
#include "../../FKCW_Base/Include/FKCW_Base_Utils.h"
//-------------------------------------------------------------------------
// ��춯��tag
#define TAG_ENABLE_REGIN_CHECK		1000
//-------------------------------------------------------------------------
FKCW_UI_RookieGuideLayer::FKCW_UI_RookieGuideLayer()
	: m_pClickedRegion( NULL )
	, m_tagBgColor( ccc4(0, 0, 0, 0x7f ))		// Ĭ�ϻ�ɫ
	, m_bIsAnyTouchMode( false )
	, m_bIsShouldCheckRegion( true )
	, m_pStencil( NULL )
	, m_pContent( NULL )
	, m_pClipper( NULL )
	, m_pOnExitFunc( NULL )
	, m_pOnEnterFunc( NULL )
{

}
//-------------------------------------------------------------------------
// ��������ʾ��ᱻ���ã�������Ը�д�ú�����ִ���Զ�����Ϊ
void FKCW_UI_RookieGuideLayer::_OnFadeInDone()
{
	// �����κ��£���������ʵ�־ͺ�
}
//-------------------------------------------------------------------------
FKCW_UI_RookieGuideLayer::~FKCW_UI_RookieGuideLayer()
{
	for( RegionList::iterator Ite = m_vecRegions.begin();
		Ite != m_vecRegions.end(); Ite++ )
	{
		SRegion& r = *Ite;
		CC_SAFE_RELEASE( r.m_pFunc );
	}
	CC_SAFE_RELEASE( m_pOnEnterFunc );
	CC_SAFE_RELEASE( m_pOnExitFunc );
}
//-------------------------------------------------------------------------
FKCW_UI_RookieGuideLayer* FKCW_UI_RookieGuideLayer::Create()
{
	FKCW_UI_RookieGuideLayer* l = new FKCW_UI_RookieGuideLayer();
	l->init();
	return (FKCW_UI_RookieGuideLayer*)l->autorelease();
}
//-------------------------------------------------------------------------
bool FKCW_UI_RookieGuideLayer::init()
{
	if(!CCLayer::init()) 
	{
		return false;
	}

	// ���
	m_pStencil = CCDrawNode::create();
	m_pStencil->setPosition(CCPointZero);

	// ��������
	m_pClipper = CCClippingNode::create();
	m_pClipper->setPosition(CCPointZero);
	m_pClipper->setStencil(m_pStencil);
	m_pClipper->setInverted(true);
	addChild(m_pClipper);

	// ������ɫ��
	m_pContent = CCLayerColor::create(m_tagBgColor);
	m_pClipper->addChild(m_pContent);

	// ������Ϣ���գ���������Ϣ���ղ㼶Ϊ���
	setTouchEnabled(true);
	setTouchMode(kCCTouchesOneByOne);
	setTouchPriority(-MAX_INT);
	setKeypadEnabled(true);

	return true;
}
//-------------------------------------------------------------------------
void FKCW_UI_RookieGuideLayer::onEnter()
{
	CCLayer::onEnter();

	if(m_pOnEnterFunc)
		m_pOnEnterFunc->execute();
}
//-------------------------------------------------------------------------
void FKCW_UI_RookieGuideLayer::onExit()
{
	if(m_pOnExitFunc)
		m_pOnExitFunc->execute();

	CCLayer::onExit();
}
//-------------------------------------------------------------------------
bool FKCW_UI_RookieGuideLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint loc = pTouch->getLocation();

	// ����������κ�����, �ͷŸ���Ϣ
	if(!m_bIsAnyTouchMode && m_bIsShouldCheckRegion) 
	{
		m_pClickedRegion = NULL;
		for(RegionList::iterator iter = m_vecRegions.begin(); iter != m_vecRegions.end(); iter++) 
		{
			SRegion& r = *iter;
			if(r.m_tagRect.containsPoint(loc)) 
			{
				if(r.m_pFunc) 
				{
					m_pClickedRegion = &r;
					break;
				} 
				else if(r.m_pRemoveOnTouch)
				{
					removeFromParent();
					return false;
				}
			}
		}
	}

	return true;
}
//-------------------------------------------------------------------------
void FKCW_UI_RookieGuideLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{

}
//-------------------------------------------------------------------------
void FKCW_UI_RookieGuideLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	if(m_bIsAnyTouchMode && m_bIsShouldCheckRegion) 
	{
		removeFromParent();
	} 
	else if(m_pClickedRegion) 
	{
		m_pClickedRegion->m_pFunc->execute();
		removeFromParent();
	}
}
//-------------------------------------------------------------------------
void FKCW_UI_RookieGuideLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{

}
//-------------------------------------------------------------------------
// ������ʾ��������������
// ע���ú�����Ҫ�����ñ���ɫ֮�����
// ������duration �������ʱ��  delay ���붯��֮ǰ���ӳ�ʱ��
void FKCW_UI_RookieGuideLayer::FadeIn( float duration, float delay )
{
	FKCW_Base_Utils::SetOpacityRecursively(this, 0);
	m_pContent->runAction(CCSequence::create(CCDelayTime::create(delay),
		CCFadeTo::create(duration, m_tagBgColor.a),
		CCCallFunc::create(this, callfunc_selector(FKCW_UI_RookieGuideLayer::_OnFadeInDone)),
		NULL));
}
//-------------------------------------------------------------------------
// ���һ���ɵ������
// ע: ������Ӧ��������ռ����ꡣ
//		��������ɵ�������������֮�����������㽫�Զ�ɾ������
// ������r ����ռ����꣬����Ӧ����
//		func ���򱻵����Ļص�����������ֵΪNULL��������Ϊ���ɵ��
//		removeOnTouch ���ص�������ΪNULLʱ����ֵ��Ч�����ص�����ΪNULLʱ����ֵ��Ϊtrue��
//				��ʾ�������򱻵�������Ƴ�������
void FKCW_UI_RookieGuideLayer::AddRegion(const CCRect& r, CCCallFunc* func, bool removeOnTouch )
{
	// �������
	SRegion tagRegion;
	tagRegion.m_pFunc = func;
	tagRegion.m_pRemoveOnTouch = removeOnTouch;
	tagRegion.m_tagRect = r;
	CC_SAFE_RETAIN(func);
	m_vecRegions.push_back(tagRegion);

	// �������
	CCPoint v[] =
	{
		r.origin,
		ccpAdd(r.origin, ccp(r.size.width, 0)),
		ccpAdd(r.origin, ccp(r.size.width, r.size.height)),
		ccpAdd(r.origin, ccp(0, r.size.height))
	};
	m_pStencil->drawPolygon(v, 4, cc4fGREEN, 0, cc4fTRANSPARENT);
}
//-------------------------------------------------------------------------
// ͨ��һ���ڵ����һ���ɵ������
// ע���������С����ڵ�İ�Χ�о�����ͬ
void FKCW_UI_RookieGuideLayer::AddRegion(CCNode* n, CCCallFunc* func, bool removeOnTouch )
{
	CCRect b = CCRectMake(0, 0, n->getContentSize().width, n->getContentSize().height);
	CCAffineTransform t = n->nodeToWorldTransform();
	b = CCRectApplyAffineTransform(b, t);
	AddRegion(b, func, removeOnTouch);
}
//-------------------------------------------------------------------------
// ����һ�����������Ƴ��������д����ص�����ɾ���ûص���
void FKCW_UI_RookieGuideLayer::SetRegionRemoveOnTouch(int index)
{
	if(index < 0 || index >= static_cast<int>(m_vecRegions.size()))
		return;

	SRegion& reg = m_vecRegions.at(index);
	reg.m_pRemoveOnTouch = true;
	CC_SAFE_RELEASE(reg.m_pFunc);
}
//-------------------------------------------------------------------------
// ��ȡָ���������
const CCRect& FKCW_UI_RookieGuideLayer::GetRegionRect(int index)
{
	if(index < 0 || index >= static_cast<int>(m_vecRegions.size()))
		return CCRectZero;

	SRegion& reg = m_vecRegions.at(index);
	return reg.m_tagRect;
}
//-------------------------------------------------------------------------
// ��Ч��һ������ֱ������ָ��ʱ��
void FKCW_UI_RookieGuideLayer::EnableRegionCheckAfter(float seconds)
{
	// ֹ֮ͣǰ��һ������
	stopActionByTag(TAG_ENABLE_REGIN_CHECK);

	// ִ���¶�������
	setShouldCheckRegion(false);
	CCAction* a = CCSequence::createWithTwoActions(CCDelayTime::create(seconds),
		CCCallFunc::create(this, callfunc_selector(FKCW_UI_RookieGuideLayer::markShouldCheckRegion)));
	a->setTag(TAG_ENABLE_REGIN_CHECK);
	runAction(a);
}
//-------------------------------------------------------------------------
void FKCW_UI_RookieGuideLayer::setBgColor( const ccColor4B& var )
{
	m_tagBgColor = var;
	m_pContent->setColor(ccc3(m_tagBgColor.r, m_tagBgColor.g, m_tagBgColor.b));
	m_pContent->setOpacity(m_tagBgColor.a);
}
//-------------------------------------------------------------------------