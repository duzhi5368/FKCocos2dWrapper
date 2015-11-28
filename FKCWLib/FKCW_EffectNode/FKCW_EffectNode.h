//*************************************************************************
//	��������:	2014-11-15
//	�ļ�����:	FKCW_EffectNode.h
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
	һЩ����Ч��Node�ķ�װ֧��
====================================
�ڲ��ļ�����˵����
====================================
	FKCW_EffectNode_IndexVBO
		����VBO������
	FKCW_EffectNode_GLProgramWithUnifos
		��������ŵ�Shader Program
	FKCW_EffectNode_Mesh
		�������
	FKCW_EffectNode_MeshWire
		��״�������
	FKCW_EffectNode_MeshGeneral
		�������������������

	����ЧЧ��
		FKCW_EffectNode_2DSoftShadow
			2D����Ӱ��ʵʱ���㡣������һ�����գ����������Ӱ�Ķ��󣬻���һ������Ӱ���ڵ�
		FKCW_EffectNode_BreakSprite
			������侫�飬��������Ϊ���ǿ鲢�����𲽵���Ч��
		FKCW_EffectNode_ColorAdjustSprite
			��ɫ�������顣�ɵ�����HSL����ʵ�ֱ�ɫ�������䰵��Ч��
		FKCW_EffectNode_GhostLikeSprite
			����ʽ�����顣��������һ�����澫����Ӿ��飬�ͽ����볣�澫����ȫһ�µ���Ϊ������ɫ��С�ɶ������
		FKCW_EffectNode_Laser
			����ʽ�����顣
		FKCW_EffectNode_LightingBoltNode
			������ʽ���顣
		FKCW_EffectNode_NormalMappedSprite
			��������ͼ����ʵ��������Ӱ��Ⱦ�ľ���
		FKCW_EffectNode_Ripper2DSprite
			2D��ֱˮ�澫�飬�ܵ�Ӱ�������ˮƽ��Ĳ���
		FKCW_EffectNode_RippleSprite
			ˮ�沨�˾��飬�������������Ч����
		FKCW_EffectNode_Shatter
			����Ч�����飬�������������Χ���ѵ�Ч����
		FKCW_EffectNode_TailSprite
			��βЧ�����飬������ƶ��ٶ��ں�������׷βЧ����
			ע�⣺�� FKCW_RenderEx_TiledSprite ��ͬ��Tiled�ǲ�����Ӱ����������ɵ�����βЧ����
		FKCW_EffectNode_TinyWingsTerrainSprite
			����������Ϸ��TinyWings�� �ĵ���Ч���ľ��顣
====================================
������Ŀ/�⣺
====================================
	FKCW_Base
====================================
todo:
====================================

*/ 
//-------------------------------------------------------------------------
#include "Include/FKCW_EffectNode_IndexVBO.h"
#include "Include/FKCW_EffectNode_GLProgramWithUnifos.h"
#include "Include/FKCW_EffectNode_Mesh.h"
//-------------------------------------------------------------------------
#include "Include/FKCW_EffectNode_2DSoftShadow.h"
#include "Include/FKCW_EffectNode_BreakSprite.h"
#include "Include/FKCW_EffectNode_ColorAdjustSprite.h"
#include "Include/FKCW_EffectNode_GhostLikeSprite.h"
#include "Include/FKCW_EffectNode_Laser.h"
#include "Include/FKCW_EffectNode_LightingBoltNode.h"
#include "Include/FKCW_EffectNode_NormalMappedSprite.h"
#include "Include/FKCW_EffectNode_Ripper2DSprite.h"
#include "Include/FKCW_EffectNode_RippleSprite.h"
#include "Include/FKCW_EffectNode_Shatter.h"
#include "Include/FKCW_EffectNode_TailSprite.h"
#include "Include/FKCW_EffectNode_TinyWingsTerrainSprite.h"