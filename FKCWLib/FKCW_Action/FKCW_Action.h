/********************************************************************
	created:	2014/11/04
	file base:	FKCW_Action
	author:		FreeKnight
	
	purpose:	
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
/* 
====================================
ģ��˵����	
====================================
	��װ��һЩ�����Ķ�����һЩ���������Ч����
====================================
�ڲ��ļ�����˵����
====================================
	FKCW_Action_CallfuncT
		һ���ص�������װģ���࣬�̳���CCCallFunc��������ص���������һ���������͵Ĳ�����
	FKCW_Action_CallfuncNT
		һ���ص�������װģ���࣬�̳���CCCallFunc��������ص���������һ���ڵ�����һ���������͵Ĳ�����
	FKCW_Action_ClipIn
		��һ����������ʾһ������ԭ������������һ���û���������ֲ㣬�ƶ������ֲ㡣
	FKCW_Action_ClipOut
		��һ������������һ������ԭ������������һ���û���������ֲ㣬�ƶ������ֲ㡣
	FKCW_Action_TreeFadeIn
		����һ�����󡣺�CCFadeIn�������ƣ�������ʹ�ñ���������Ϊ���������Զ��Զ����ӽڵ㶼���н��Բ�����
		�� CCFadeIn����������ӽڵ����á�
	FKCW_Action_TreeFadeOut
		����һ�����󡣲μ� FKCW_Action_TreeFadeIn ������
	FKCW_Action_Flash
		��˸��������һ���ڵ㵥λ������˸��ɫ��
	FKCW_Action_Missile
		׷���������ýڵ㰴һ���Ƕȵĵ����켣�Զ�׷����һ���ڵ㡣
	FKCW_Action_Shake
		�𶯶������ýڵ���һ����ΧԲ�����λ�ƣ������Ч����
	FKCW_Action_Shine
		��̬���߶�������һ���ڵ�����ʾһϵ�й���Ч�������߻���ݶ��ƶ������ɱ�����Ϊ���������ɫ��
	FKCW_Action_Blur
		ģ����������һ���ڵ����ģ��Ч�������Զ�̬�ĸ���ģ����ģ���ȡ�
	FKCW_Action_Count
		���ַ����������ö���ֻ��Label���á�
	FKCW_Action_TrailMoveTo
		����β��Ӱ���ƶ��������ڵ��ƶ���һ��ָ��Ŀ�꣬ͬʱ�����һϵ�в�ӰЧ����
	FKCW_Action_Curl
		������ת������
	FKCW_Action_Suck
		�ڶ�����Ч��
====================================
������Ŀ/�⣺
====================================
	FKCW_Base
	FKCW_Shader
	FKCW_RenderEx
====================================
todo:
====================================

*/ 
//--------------------------------------------------------------------
#include "Include/FKCW_Action_CallfuncT.h"
#include "Include/FKCW_Action_CallfuncNT.h"

#include "Include/FKCW_Action_ClipIn.h"
#include "Include/FKCW_Action_ClipOut.h"
#include "Include/FKCW_Action_TreeFadeIn.h"
#include "Include/FKCW_Action_TreeFadeOut.h"
#include "Include/FKCW_Action_Flash.h"
#include "Include/FKCW_Action_Missile.h"
#include "Include/FKCW_Action_Shake.h"
#include "Include/FKCW_Action_Shine.h"
#include "Include/FKCW_Action_Blur.h"
#include "Include/FKCW_Action_Count.h"
#include "Include/FKCW_Action_TrailMoveTo.h"
#include "Include/FKCW_Action_Curl.h"
#include "Include/FKCW_Action_Suck.h"