//-------------------------------------------------------------------------
#include "../Include/FKCW_Action_Missile.h"
//-------------------------------------------------------------------------
// ����һ���������ٶ�������
// ������velocity �ƶ��ٶ� aimed Ŀ����� 
//	targetPresetDegree ����ڵ����Ŀ��ڵ����ת�Ƕȣ���ֵ��ʾ˳ʱ��
FKCW_Action_Missile* FKCW_Action_Missile::Create( float velocity, CCNode* aimed, float targetPresetDegree, CCCallFunc* doneCallFunc )
{
	FKCW_Action_Missile* p = new FKCW_Action_Missile();
	p->InitWithVelocity( velocity, aimed, targetPresetDegree, doneCallFunc );
	return ( FKCW_Action_Missile* )p->autorelease();
}
//-------------------------------------------------------------------------
FKCW_Action_Missile::FKCW_Action_Missile()
	: m_bIsDone( false )
	, m_pAimedNode( NULL )
	, m_pDoneCallFunc( NULL )
{

}
//-------------------------------------------------------------------------
FKCW_Action_Missile::~FKCW_Action_Missile()
{
	CC_SAFE_RELEASE( m_pDoneCallFunc );
}
//-------------------------------------------------------------------------
bool FKCW_Action_Missile::InitWithVelocity( float velocity, CCNode* aimed, float targetPresetDegree, CCCallFunc* doneCallFunc )
{
	m_fDstDegree	= 0;
	m_fVelocity		= velocity;
	m_pAimedNode	= aimed;
	m_fPresetDegree	= targetPresetDegree;
	m_pDoneCallFunc	= doneCallFunc;
	CC_SAFE_RETAIN( m_pDoneCallFunc );
	return true;
}
//-------------------------------------------------------------------------
CCObject* FKCW_Action_Missile::copyWithZone(CCZone* pZone)
{
	CCZone* pNewZone = NULL;
	FKCW_Action_Missile* pCopy = NULL;
	if(pZone && pZone->m_pCopyObject) 
	{
		// �������
		pCopy = (FKCW_Action_Missile*)(pZone->m_pCopyObject);
	} else {
		pCopy = new FKCW_Action_Missile();
		pZone = pNewZone = new CCZone(pCopy);
	}

	CCActionInterval::copyWithZone(pZone);
	pCopy->InitWithVelocity(m_fVelocity, m_pAimedNode, m_fPresetDegree, m_pDoneCallFunc);

	CC_SAFE_DELETE(pNewZone);
	return pCopy;
}
//-------------------------------------------------------------------------
void FKCW_Action_Missile::step(float dt)
{
	// �����ڵ��Ŀ��ڵ��λ��
	CCNode* target = getTarget();
	CCPoint t = target->getPosition();
	CCPoint a = m_pAimedNode->getPosition();

	// λ�������Ƕ�
	CCPoint v = ccpSub(a, t);
	float r = ccpToAngle(v);
	float d = -CC_RADIANS_TO_DEGREES(r);
	d -= m_fPresetDegree;

	// ����Ŀ��Ƕ�
	if(m_fDstDegree != d) 
	{
		m_fDstDegree = d;
	}
	if(( m_fDstDegree < -90.0f && m_fDstDegree > -180.0f )
		||
		( m_fDstDegree > 90.0f && m_fDstDegree < 180.0f ))
	{
		CCSprite* p = dynamic_cast<CCSprite*>(target);
		if( p != NULL )
			p->setFlipY( true );
	}
	else
	{
		CCSprite* p = dynamic_cast<CCSprite*>(target);
		if( p != NULL )
			p->setFlipY( false );
	}

	// ����תĿ��Ƕ�
	if(m_fDstDegree > target->getRotation()) 
	{
		float cur = MIN(m_fDstDegree, target->getRotation() + dt * 360);
		target->setRotation(cur);
	}
	else if(m_fDstDegree < target->getRotation()) 
	{
		float cur = MAX(m_fDstDegree, target->getRotation() - dt * 360);
		target->setRotation(cur);
	}

	// ͨ���ٶȼ���Ŀ���ƶ�
	float move = m_fVelocity * dt;
	float distance = ccpLength(v);
	if(move >= distance) 
	{
		target->setPosition(a);
	} 
	else 
	{
		t.x += move * cosf(r);
		t.y += move * sinf(r);
		target->setPosition(t);
	}

	// �Ƿ����
	m_bIsDone = getTarget()->getPositionX() == m_pAimedNode->getPositionX() &&
		getTarget()->getPositionY() == m_pAimedNode->getPositionY();

	// �����ص�
	if(m_bIsDone && m_pDoneCallFunc)
	{
		m_pDoneCallFunc->execute();
	}
}
//-------------------------------------------------------------------------