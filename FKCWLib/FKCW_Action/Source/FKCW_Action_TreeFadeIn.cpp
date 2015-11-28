//--------------------------------------------------------------------
#include "../Include/FKCW_Action_TreeFadeIn.h"
#include "cocos-ext.h"
//--------------------------------------------------------------------
using namespace cocos2d::ui;
//--------------------------------------------------------------------
FKCW_Action_TreeFadeIn::FKCW_Action_TreeFadeIn()
	: m_bIsRecursivelyExclude( false )
{

}
//--------------------------------------------------------------------
// �ݹ齥��
void FKCW_Action_TreeFadeIn::FadeInRecursively( CCNode* p_pRoot, float p_fTime )
{
	CCRGBAProtocol* p = dynamic_cast<CCRGBAProtocol*>(p_pRoot);
	if(p)
	{
		p->setOpacity((GLubyte)(255 * p_fTime));
	}

	CCArray* children = p_pRoot->getChildren();
	int cc = p_pRoot->getChildrenCount();
	for(int i = 0; i < cc; i++)
	{
		CCNode* child = (CCNode*)children->objectAtIndex(i);
		if(!m_vecExcludeList.containsObject(child)) 
		{
			FadeInRecursively(child, p_fTime);
		} 
		else if(!m_bIsRecursivelyExclude) 
		{
			FadeInRecursively(child, p_fTime);
		}
	}

	// ���UI
	Widget* w = dynamic_cast<Widget*>(p_pRoot);
	if(w) 
	{
		if(w->getVirtualRenderer()) 
		{
			CCRGBAProtocol* p = dynamic_cast<CCRGBAProtocol*>(w->getVirtualRenderer());
			if(p) 
			{
				p->setOpacity((GLubyte)(255 * p_fTime));
			}
		}

		CCArray* children = w->getNodes();
		int cc = children->count();
		for(int i = 0; i < cc; i++) 
		{
			CCNode* child = (CCNode*)children->objectAtIndex(i);
			FadeInRecursively(child, p_fTime);
		}
	}
}
//--------------------------------------------------------------------
FKCW_Action_TreeFadeIn* FKCW_Action_TreeFadeIn::Create( float p_fDuration )
{
	FKCW_Action_TreeFadeIn* pAction = new FKCW_Action_TreeFadeIn();
	pAction->initWithDuration(p_fDuration);
	pAction->autorelease();
	return pAction;
}
//--------------------------------------------------------------------
// �����Ҫ���ų��Ľڵ��б�
void FKCW_Action_TreeFadeIn::ExcludeNode( CCNode* p_pRoot, bool p_bIsRecursively )
{
	m_vecExcludeList.addObject(p_pRoot);
	m_bIsRecursivelyExclude = p_bIsRecursively;
}
//--------------------------------------------------------------------
void FKCW_Action_TreeFadeIn::update(float time)
{
	CCFadeIn::update(time);
	FadeInRecursively(getTarget(), time);
}
//--------------------------------------------------------------------
CCActionInterval* FKCW_Action_TreeFadeIn::reverse(void)
{
	return FKCW_Action_TreeFadeIn::Create(m_fDuration);
}
//--------------------------------------------------------------------