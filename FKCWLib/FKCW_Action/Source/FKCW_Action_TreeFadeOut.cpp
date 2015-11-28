//--------------------------------------------------------------------
#include "../Include/FKCW_Action_TreeFadeOut.h"
#include "cocos-ext.h"
//--------------------------------------------------------------------
using namespace cocos2d::ui;
//--------------------------------------------------------------------
FKCW_Action_TreeFadeOut::FKCW_Action_TreeFadeOut()
	: m_bIsRecursivelyExclude( false )
{

}
//--------------------------------------------------------------------
// �ݹ齥��
void FKCW_Action_TreeFadeOut::FadeOutRecursively( CCNode* p_pRoot, float p_fTime )
{
	CCRGBAProtocol* p = dynamic_cast<CCRGBAProtocol*>(p_pRoot);
	if(p)
	{
		p->setOpacity((GLubyte)(255 * (1 - p_fTime)));
	}

	CCArray* children = p_pRoot->getChildren();
	int cc = p_pRoot->getChildrenCount();
	for(int i = 0; i < cc; i++)
	{
		CCNode* child = (CCNode*)children->objectAtIndex(i);
		if(!m_vecExcludeList.containsObject(child)) 
		{
			FadeOutRecursively(child, p_fTime);
		} 
		else if(!m_bIsRecursivelyExclude) 
		{
			FadeOutRecursively(child, p_fTime);
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
				p->setOpacity((GLubyte)(255 * (1 - p_fTime)));
			}
		}

		CCArray* children = w->getNodes();
		int cc = children->count();
		for(int i = 0; i < cc; i++) 
		{
			CCNode* child = (CCNode*)children->objectAtIndex(i);
			FadeOutRecursively(child, p_fTime);
		}
	}
}
//--------------------------------------------------------------------
FKCW_Action_TreeFadeOut* FKCW_Action_TreeFadeOut::Create( float p_fDuration )
{
	FKCW_Action_TreeFadeOut* pAction = new FKCW_Action_TreeFadeOut();
	pAction->initWithDuration(p_fDuration);
	pAction->autorelease();
	return pAction;
}
//--------------------------------------------------------------------
// �����Ҫ���ų��Ľڵ��б�
void FKCW_Action_TreeFadeOut::ExcludeNode( CCNode* p_pRoot, bool p_bIsRecursively )
{
	m_vecExcludeList.addObject(p_pRoot);
	m_bIsRecursivelyExclude = p_bIsRecursively;
}
//--------------------------------------------------------------------
void FKCW_Action_TreeFadeOut::update(float time)
{
	CCFadeOut::update(time);
	FadeOutRecursively(getTarget(), time);
}
//--------------------------------------------------------------------
CCActionInterval* FKCW_Action_TreeFadeOut::reverse(void)
{
	return FKCW_Action_TreeFadeOut::Create(m_fDuration);
}
//--------------------------------------------------------------------