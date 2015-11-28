//*************************************************************************
//	��������:	2014-11-5
//	�ļ�����:	FKCW_UI_ToastLayer.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	����һ��Tip��Ϣ
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_UI_Macros.h"
//-------------------------------------------------------------------------
// ����dialog����Ϣ���ڣ�����ռ�н��㣬�ҹ�һ��ʱ����Զ���ʧ
class FKCW_UI_ToastLayer : public CCLayer
{
protected:
	FKCW_UI_ToastLayer();
public:
	virtual ~FKCW_UI_ToastLayer();
	// ����һ��Toast����ʵ��
	// ������owner		�����߽ڵ㣨toast������Ϊ�ӽڵ���ӵ� owner�У�������Ϊ���Zֵ��
	//		content		���ݽڵ㣨���������ʾ����ʵ��Ϣ�����û���Ҫ���úú��ʵ�ê���λ�ã�
	//		tag			�����ǩ�������ֵΪ-1�����ͬʱ��ʾ���ʵ�������򲻿�ͬʱ��ʾ��
	//		duration	��ʾʱ������ΪĬ��0�����ʾ��ʾ3�룩
	//		inAction	��ʾʱ�Ķ�������ΪĬ��0�����ʾʹ�õ��붯����
	//		outAction	��ʧʱ�Ķ�������ΪĬ��0�����ʾʹ�õ���������
	static FKCW_UI_ToastLayer* Create(CCNode* owner, CCNode* content, int tag = -1,
		float duration = 0, CCFiniteTimeAction* inAction = NULL, CCFiniteTimeAction* outAction = NULL);

	// ǿ���Ƴ�һ��Toast( ͨ��tag���� )
	static void					ForceRemove( CCNode* p_pOwner, int p_nTag );
};