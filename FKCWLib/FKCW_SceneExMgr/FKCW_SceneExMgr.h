//*************************************************************************
//	��������:	2014-11-12
//	�ļ�����:	FKCW_SceneExMgr.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
/* 
====================================
ģ��˵����	
====================================
	�Դ�����һ��������������ṩ��һϵ���Զ��峡�������л�����Ϣ֪ͨ����
	ʹ�÷�ʽ���£�
	�����Զ��峡��
		class CMyScene : public FKCW_SceneExMgr_SceneEx
		{
			// your code
		}
	��AppDalagate::applicationDidFinishLaunching() ���������
		REGISTER_SCENE_FUNC(CMyScene);
		CCSceneManager::sharedManager()->runWithScene(LoadScene("CMyScene"));
	֮����г����л�ʱ��
		CCSceneManager::sharedManager()->popScene(this);
		CCSceneManager::sharedManager()->runScene(LoadScene("CMyScene2"));
		��
		CCSceneManager::sharedManager()->popUIScene(this);
		CCSceneManager::sharedManager()->runUIScene(LoadScene("CMyUIScene2"));
	�Ȳ���
	ʹ��FKCW_SceneExMgr_SceneExTransitionϵ������������ʱ���ɴ���һ���µ�FKCW_SceneExMgr_SceneExTransitionOriented��
	Ȼ��ִ��CCSceneManager::sharedManager()->replaceScene( FKCW_SceneExMgr_SceneExTransition::create(...) );����
====================================
�ڲ��ļ�����˵����
====================================
	FKCW_SceneExMgr_SceneEx
		����CCScene����һ���Զ��峡������ࡣ�������CCScene����������Դ����֪ͨ��ͬ/�첽��Դ���أ����棬�����л�����
		��һϵ��ʵ�ú�������������Լ�����Ϣ���ơ�
	FKCW_SceneExMgr_SceneExTransition
		һ�����й��ɶ����ĳ�������Ҫ���볡���ͳ�������ϣ�����һϵ�ж������г����л��Ĺ��ɡ�
	FKCW_SceneExMgr_SceneExMgr
		ȫ�������Ĺ����������������Ի��泡�������Լ����������չʾ�����ٵȿ��Ʋ�����
		ͬʱ�������������л��Ļ�����Ϣ���ơ�

	������ɳ���ϵ��
		FKCW_SceneExMgr_SceneExTransitionRotoZoom
			��ת�����ŵĳ����л�Ч��������Ч����
		FKCW_SceneExMgr_SceneExTransitionJumpZoom
			��Ծ���ų����л�����
		FKCW_SceneExMgr_SceneExTransitionMoveInL
		FKCW_SceneExMgr_SceneExTransitionMoveInR
		FKCW_SceneExMgr_SceneExTransitionMoveInT
		FKCW_SceneExMgr_SceneExTransitionMoveInB
			�����л�Ч�����³�����L/R/T/B����һ�����ƶ�����ԭ������ԭ����������
		FKCW_SceneExMgr_SceneExTransitionSlideInL
		FKCW_SceneExMgr_SceneExTransitionSlideInR
		FKCW_SceneExMgr_SceneExTransitionSlideInT
		FKCW_SceneExMgr_SceneExTransitionSlideInB
			�ƶ��л�Ч�����³�����L/R/T/B����һ����ԭ�����Ƴ���Ļ��
		FKCW_SceneExMgr_SceneExTransitionShrinkGrow
			�����л�����Ч��
		FKCW_SceneExMgr_SceneExTransitionFlipX
		FKCW_SceneExMgr_SceneExTransitionFlipY
		FKCW_SceneExMgr_SceneExTransitionFlipAngular
			�� X��/Y��/�������¶Խ��� ��ת�����л�Ч��
		FKCW_SceneExMgr_SceneExTransitionZoomFlipX
		FKCW_SceneExMgr_SceneExTransitionZoomFlipY
		FKCW_SceneExMgr_SceneExTransitionZoomFlipAngular
			�� X��/Y��/�������¶Խ��� ��ת�����ų����л�Ч��
		FKCW_SceneExMgr_SceneExTransitionFadeColor
			����ɫЧ�����뵭����ԭ�����𽥼�����ɫ��ָ��ɫ������ָ��ɫ����Ϊ�³�����Ĭ�Ϻ�ɫ��
		FKCW_SceneExMgr_SceneExTransitionCrossFade
			�ںϣ���Ϸ�ʽ�л�������ԭ�����𽥱䵭���³����𽥱��
		FKCW_SceneExMgr_SceneExTransitionTurnOffTiles
			����������滻��ʽ�л���������ԭ�������³����л�Ϊ���С�������������ͼ���л�Ϊ�³�����
		FKCW_SceneExMgr_SceneExTransitionSplitCols
		FKCW_SceneExMgr_SceneExTransitionSplitRows
			����/����ԭ������Ϊ�����������������˲��滻Ϊ�³���
		FKCW_SceneExMgr_SceneExTransitionFadeTR
		FKCW_SceneExMgr_SceneExTransitionFadeBL
		FKCW_SceneExMgr_SceneExTransitionFadeUp
		FKCW_SceneExMgr_SceneExTransitionFadeDown
			������/����/��/�� ��ԳƷ����Է�������ʽ���滻
		FKCW_SceneExMgr_SceneExTransitionPageTurn
			ǰ/�� ��ҳ��ʽ�л�����
		FKCW_SceneExMgr_SceneExTransitionProgressRadialCCW
		FKCW_SceneExMgr_SceneExTransitionProgressRadialCW
		FKCW_SceneExMgr_SceneExTransitionProgressHorizontal
		FKCW_SceneExMgr_SceneExTransitionProgressVertical
		FKCW_SceneExMgr_SceneExTransitionProgressInOut
		FKCW_SceneExMgr_SceneExTransitionProgressOutIn
			�Խ�������ʽ���г����л���˳/��ʱ���ӱ���ʽ����������ֱ/�����������������������ɢ��������������ɢ��
====================================
������Ŀ/�⣺
====================================
	��
====================================
todo:
====================================

*/
//-------------------------------------------------------------------------
#include "Include/FKCW_SceneExMgr_SceneEx.h"
#include "Include/FKCW_SceneExMgr_SceneExMgr.h"

#include "Include/FKCW_SceneExMgr_SceneExTransitionCrossFade.h"
#include "Include/FKCW_SceneExMgr_SceneExTransitionFadeColor.h"
#include "Include/FKCW_SceneExMgr_SceneExTransitionFadeDir.h"
#include "Include/FKCW_SceneExMgr_SceneExTransitionFlip.h"
#include "Include/FKCW_SceneExMgr_SceneExTransitionJumpZoom.h"
#include "Include/FKCW_SceneExMgr_SceneExTransitionMoveIn.h"
#include "Include/FKCW_SceneExMgr_SceneExTransitionOriented.h"
#include "Include/FKCW_SceneExMgr_SceneExTransitionPageTurn.h"
#include "Include/FKCW_SceneExMgr_SceneExTransitionProgress.h"
#include "Include/FKCW_SceneExMgr_SceneExTransitionRotoZoom.h"
#include "Include/FKCW_SceneExMgr_SceneExTransitionShrinkGrow.h"
#include "Include/FKCW_SceneExMgr_SceneExTransitionSlideIn.h"
#include "Include/FKCW_SceneExMgr_SceneExTransitionSplit.h"
#include "Include/FKCW_SceneExMgr_SceneExTransitionTurnOffTiles.h"
//-------------------------------------------------------------------------