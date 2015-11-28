//-------------------------------------------------------------------------
#include "../Include/FKCW_UI_SimpleRookieGuiderLayer.h"
#include "../../FKCW_Action/Include/FKCW_Action_TreeFadeIn.h"
//-------------------------------------------------------------------------
FKCW_UI_SimpleRookieGuiderLayer::FKCW_UI_SimpleRookieGuiderLayer()
	: m_pArrow( NULL )
	, m_pHint( NULL )
{

}
//-------------------------------------------------------------------------
FKCW_UI_SimpleRookieGuiderLayer::~FKCW_UI_SimpleRookieGuiderLayer()
{

}
//-------------------------------------------------------------------------
FKCW_UI_SimpleRookieGuiderLayer* FKCW_UI_SimpleRookieGuiderLayer::Create()
{
	FKCW_UI_SimpleRookieGuiderLayer* g = new FKCW_UI_SimpleRookieGuiderLayer();
	g->init();
	return (FKCW_UI_SimpleRookieGuiderLayer*)g->autorelease();
}
//-------------------------------------------------------------------------
// ���Ǹ��ຯ��
void FKCW_UI_SimpleRookieGuiderLayer::FadeIn( float duration, float delay )
{
	FKCW_UI_RookieGuideLayer::FadeIn(duration, delay);

	// ������ҲҪ����
	FKCW_Action_TreeFadeIn* fadeIn = FKCW_Action_TreeFadeIn::Create(duration);
	fadeIn->ExcludeNode(m_pContent, false);
	runAction(CCSequence::createWithTwoActions(CCDelayTime::create(delay),
		fadeIn));
}
//-------------------------------------------------------------------------
// ����ͷ��׼���������ģ����ض��ĽǶȺ;���
// ������regionIndex ��������� distance �������ĺͼ�ͷ�������ĵľ��� degree ��������ָ���ͷ�м�ĽǶ���������ֵΪ��ʱ�룩
//		arrowPresetRotation ��ͷ�������ת�Ƕȣ���ֵΪ��ʱ�룩
void FKCW_UI_SimpleRookieGuiderLayer::PointToRegionCenter(int regionIndex, float distance, float degree, float arrowPresetRotation )
{
	if(regionIndex < 0 || regionIndex >= static_cast<int>(m_vecRegions.size()) || !m_pArrow)
		return;

	// ��ȡָ����������
	SRegion& reg = m_vecRegions.at(regionIndex);
	CCRect& r = reg.m_tagRect;
	CCPoint center = ccpAdd(r.origin, ccp(r.size.width / 2, r.size.height / 2));

	// ��ȡ��ͷ��������
	float radian = CC_DEGREES_TO_RADIANS(degree);
	center.x += distance * cosf(radian);
	center.y += distance * sinf(radian);

	// ���ü�ͷλ��
	m_pArrow->setPosition(center);
	m_pArrow->setRotation(-(degree - 180 - arrowPresetRotation));
}
//-------------------------------------------------------------------------
// ������ʾ��Ϣλ�ã�����ڼ�ͷ�����꣩
void FKCW_UI_SimpleRookieGuiderLayer::ShiftHint(float dx, float dy)
{
	if(m_pArrow)
		m_pHint->setPosition(ccpAdd(m_pArrow->getPosition(), ccp(dx, dy)));
}
//-------------------------------------------------------------------------
void FKCW_UI_SimpleRookieGuiderLayer::setArrow(CCSprite* arrow) 
{
	if(m_pArrow) 
	{
		m_pArrow->removeFromParent();
		m_pArrow = NULL;
	}
	m_pArrow = arrow;
	m_pArrow->setAnchorPoint(ccp(0.5f, 0.5f));
	m_pArrow->ignoreAnchorPointForPosition(false);
	addChild(m_pArrow, 1);
}
//-------------------------------------------------------------------------
void FKCW_UI_SimpleRookieGuiderLayer::setHint(CCNode* hint) 
{
	if(m_pHint) 
	{
		m_pHint->removeFromParent();
		m_pHint = NULL;
	}
	m_pHint = hint;
	m_pHint->setAnchorPoint(ccp(0.5f, 0.5f));
	m_pHint->ignoreAnchorPointForPosition(false);
	addChild(m_pHint, 2);
}
//-------------------------------------------------------------------------