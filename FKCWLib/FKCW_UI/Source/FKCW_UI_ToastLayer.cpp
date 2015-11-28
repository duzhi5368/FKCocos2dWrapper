//--------------------------------------------------------------------
#include "../Include/FKCW_UI_ToastLayer.h"
#include "../../FKCW_Action/Include/FKCW_Action_TreeFadeIn.h"
#include "../../FKCW_Action/Include/FKCW_Action_TreeFadeOut.h"
#include "../../FKCW_Base/Include/FKCW_Base_Macro.h"
//--------------------------------------------------------------------
FKCW_UI_ToastLayer::FKCW_UI_ToastLayer()
{

}
//--------------------------------------------------------------------
FKCW_UI_ToastLayer::~FKCW_UI_ToastLayer()
{

}
//--------------------------------------------------------------------
// ����һ��Toast����ʵ��
// ������owner		�����߽ڵ㣨toast������Ϊ�ӽڵ���ӵ� owner�У�������Ϊ���Zֵ��
//		content		���ݽڵ㣨���������ʾ����ʵ��Ϣ�����û���Ҫ���úú��ʵ�ê���λ�ã�
//		tag			�����ǩ�������ֵΪ-1�����ͬʱ��ʾ���ʵ�������򲻿�ͬʱ��ʾ��
//		duration	��ʾʱ������ΪĬ��0�����ʾ��ʾ3�룩
//		inAction	��ʾʱ�Ķ�������ΪĬ��0�����ʾʹ�õ��붯����
//		outAction	��ʧʱ�Ķ�������ΪĬ��0�����ʾʹ�õ���������
FKCW_UI_ToastLayer* FKCW_UI_ToastLayer::Create(CCNode* owner, CCNode* content, int tag,
			float duration, CCFiniteTimeAction* inAction, CCFiniteTimeAction* outAction )
{
	// ����ǩ�Ƿ��Ѿ�����
	if(tag != -1) 
	{
		if(owner->getChildByTag(tag)) 
		{
			return NULL;
		}
	}

	FKCW_UI_ToastLayer* t = new FKCW_UI_ToastLayer();
	t->init();
	t->setTag(tag);

	// ��ӵ�owner
	owner->addChild(t, MAX_INT);

	// �������ʾ�ڵ�
	t->addChild(content);

	// ִ����ʾ���ض���
	if(inAction == NULL) 
	{
		CCNodeRGBA* n = dynamic_cast<CCNodeRGBA*>(content);
		if(n)
			n->setOpacity(0);
		inAction = FKCW_Action_TreeFadeIn::create(0.5f);
	}
	if(outAction == NULL) 
	{
		outAction = FKCW_Action_TreeFadeOut::create(0.5f);
	}
	content->runAction(CCSequence::create(inAction,
		CCDelayTime::create(duration > 0 ? duration : 3),
		outAction,
		CCCallFunc::create(t, callfunc_selector(CCNode::removeFromParent)),
		NULL));
	t->autorelease();
	return t;
}
//--------------------------------------------------------------------
// ǿ���Ƴ�һ��Toast( ͨ��tag���� )
void FKCW_UI_ToastLayer::ForceRemove( CCNode* p_pOwner, int p_nTag )
{
	CCNode* c = p_pOwner->getChildByTag(p_nTag);
	if(c) 
	{
		c->removeFromParent();
	}
}
//--------------------------------------------------------------------