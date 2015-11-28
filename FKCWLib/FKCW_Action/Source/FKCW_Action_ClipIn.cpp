//-------------------------------------------------------------------------
#include "../Include/FKCW_Action_ClipIn.h"
#include "../../FKCW_Base/Include/FKCW_Base_ColorConvert.h"
//-------------------------------------------------------------------------
#pragma warning( disable:4244 )
//-------------------------------------------------------------------------
FKCW_Action_ClipIn::FKCW_Action_ClipIn()
	: m_tagDirection( ccp(1,0) )
{

}
//-------------------------------------------------------------------------
FKCW_Action_ClipIn::~FKCW_Action_ClipIn()
{
}
//-------------------------------------------------------------------------
// ����һ�� ClipIn ����ʵ��
// ������p_fDuration ��������ʱ��
//		p_tagV �ü������ƶ�����ʸ����Ĭ�����������(1,0)����ʾ��X���ƶ�
FKCW_Action_ClipIn* FKCW_Action_ClipIn::Create( float p_fDuration, CCPoint p_tagV )
{
	FKCW_Action_ClipIn* p = new FKCW_Action_ClipIn();
	p->InitWithDuration( p_fDuration, p_tagV );
	return ( FKCW_Action_ClipIn* )p->autorelease();
}
//-------------------------------------------------------------------------
bool FKCW_Action_ClipIn::InitWithDuration( float p_fDuration, CCPoint p_tagV )
{
	setDuration( p_fDuration );
	setDirection( p_tagV );
	return true;
}
//-------------------------------------------------------------------------
void FKCW_Action_ClipIn::update(float time)
{
	CCClippingNode* clipper = (CCClippingNode*)getTarget();
	CCDrawNode* stencil = (CCDrawNode*)clipper->getStencil();

	// �����Ȼ���
	stencil->clear();

	// ���������
	float distance = m_fDistance * time;
	CCPoint v[] = {
		m_tagP1,
		m_tagP2,
		ccp(m_tagP2.x + distance * m_fCos,
		m_tagP2.y + distance * m_fSin),
		ccp(m_tagP1.x + distance * m_fCos,
		m_tagP1.y + distance * m_fSin)
	};
	stencil->drawPolygon(v, 4, cc4fGREEN, 0, cc4fTRANSPARENT);
}
//-------------------------------------------------------------------------
void FKCW_Action_ClipIn::startWithTarget(CCNode *pTarget)
{
	CCAssert(dynamic_cast<CCClippingNode*>(pTarget) != NULL, "CCClipIn target must be a CCClippingNode instance");

	CCActionInterval::startWithTarget(pTarget);

	// ��֤���clipper��CCDrawNode
	CCClippingNode* clipper = (CCClippingNode*)pTarget;
	CCNode* stencil = clipper->getStencil();
	if(dynamic_cast<CCDrawNode*>(stencil) == NULL) 
	{
		clipper->setStencil(CCDrawNode::create());
	}

	// ���򻡶�
	float r = ccpToAngle(m_tagDirection);
	m_fCos = cosf(r);
	m_fSin = sinf(r);

	// ��ʸ������������
	const CCSize& size = pTarget->getContentSize();
	m_fDistance = size.width * fabsf(m_fCos) + size.height * fabsf(m_fSin);

	// ����̶��߶���
	if(r > M_PI_2) 
	{
		float p1Len = size.width * cosf(r - M_PI_2);
		m_tagP1.x = size.width - p1Len * cosf(r - M_PI_2);
		m_tagP1.y = -p1Len * sinf(r - M_PI_2);
		float p2Len = size.height * sinf(r - M_PI_2);
		m_tagP2.x = size.width + p2Len * cosf(r - M_PI_2);
		m_tagP2.y = p2Len * sinf(r - M_PI_2);
	} 
	else if(r >= 0) 
	{
		float p1Len = size.height * m_fCos;
		m_tagP1.x = p1Len * cosf(r + M_PI_2);
		m_tagP1.y = p1Len * sinf(r + M_PI_2);
		float p2Len = size.width * m_fSin;
		m_tagP2.x = p2Len * cosf(r - M_PI_2);
		m_tagP2.y = p2Len * sinf(r - M_PI_2);
	} 
	else if(r < -M_PI_2) 
	{
		float p1Len = size.height * sinf(-r - M_PI_2);
		m_tagP1.x = size.width + p1Len * cosf(-r - M_PI_2);
		m_tagP1.y = size.height - p1Len * sinf(-r - M_PI_2);
		float p2Len = size.width * cosf(-r - M_PI_2);
		m_tagP2.x = size.width - p2Len * cosf(-r - M_PI_2);
		m_tagP2.y = size.height + p2Len * sinf(-r - M_PI_2);
	} 
	else 
	{
		float p1Len = size.width * sinf(-r);
		m_tagP1.x = p1Len * cosf(r + M_PI_2);
		m_tagP1.y = size.height + p1Len * sinf(r + M_PI_2);
		float p2Len = size.height * cosf(-r);
		m_tagP2.x = -p2Len * cosf(r + M_PI_2);
		m_tagP2.y = size.height - p2Len * sinf(r + M_PI_2);
	}
}
//-------------------------------------------------------------------------
CCActionInterval* FKCW_Action_ClipIn::reverse()
{
	return FKCW_Action_ClipIn::Create(getDuration(), ccp(-m_tagDirection.x, -m_tagDirection.y));
}
//-------------------------------------------------------------------------