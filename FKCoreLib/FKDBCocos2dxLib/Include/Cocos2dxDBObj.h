//*************************************************************************
//	��������:	2014-8-19   17:22
//	�ļ�����:	Cocos2dxDBObj.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "CommonHead.h"
//-------------------------------------------------------------------------
USING_NS_CC;
//-------------------------------------------------------------------------
class CCocos2dxDBObj : public IObject
{
public:
	CCocos2dxDBObj( CCNode* p_pNode )
		: m_pNode( p_pNode )
	{
		if( m_pNode )
		{
			m_pNode->retain();
		}
	}
	virtual ~CCocos2dxDBObj()
	{
		if( m_pNode )
		{
			m_pNode->release();
		}
	}
public:
	const CCNode* GetNode() const
	{
		return m_pNode;
	}
	CCNode* GetNode()
	{
		return m_pNode;
	}
private:
	CCNode*			m_pNode;
};
//-------------------------------------------------------------------------