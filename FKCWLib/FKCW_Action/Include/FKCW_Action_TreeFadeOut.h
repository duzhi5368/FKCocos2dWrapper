/********************************************************************
	created:	2014/11/03
	file base:	FKCW_Action_TreeFadeOut
	author:		FreeKnight
	
	purpose:	
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include "FKCW_Action_Macros.h"
//--------------------------------------------------------------------
// ����һ������ͬʱ��������ȫ���ӽڵ�
// ע��CCFadeOut ���ὥ�����ӽڵ�
class FKCW_Action_TreeFadeOut : public CCFadeOut
{
private:
	CCArray			m_vecExcludeList;			// �ų��Ľڵ��б�
	bool			m_bIsRecursivelyExclude;	// ��ֵΪtrue���ʾ���ų��Ľڵ������ӽڵ�Ҳ�����ų�����
protected:
	FKCW_Action_TreeFadeOut();
	// �ݹ齥��
	void FadeOutRecursively( CCNode* p_pRoot, float p_fTime );
public:
	static FKCW_Action_TreeFadeOut* Create( float p_fDuration );
	// �����Ҫ���ų��Ľڵ��б�
	void ExcludeNode( CCNode* p_pRoot, bool p_bIsRecursively = true );

	virtual void update(float time);
	virtual CCActionInterval* reverse(void);
};