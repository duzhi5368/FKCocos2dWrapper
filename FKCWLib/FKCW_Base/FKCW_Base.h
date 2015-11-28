//*************************************************************************
//	��������:	2014-10-25
//	�ļ�����:	FKCW_Base.h
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
	������Ŀ⣬����FKCW����á�
====================================
�ڲ��ļ�����˵����
====================================
	FKCW_Base_Macro
		������һЩ�궨��
	FKCW_Base_Types
		һЩ���������Ͷ���
	FKCW_Base_ColorConvert
		��ɫ��ص�һЩ����ͱ�ݺ���
	FKCW_Base_Utils
		�����Ļ����������������Ļ�ǳ����õģ����൱���Ķ��������
		��ʱ���� �ַ���������غ�����·���ļ���׺�������������ַ��������������ַ������봦������
				������ѧ�������������ڵ㴦������һЩ�򵥵ĸ������ܺ�����
	FKCW_Base_StringConvert
		�ַ��� gb2312 �� utf8 ��ת�뺯��
	FKCW_Base_Geometry
		������ѧ����������CCPoint,CCSize,CCRect֮��ļ��׺�����
	FKCW_Base_Data
		һ��������������
	FKCW_Base_DrawingPrimitives
		���ƻ���Ԫ�ط����ࡣ�Ƕ�CCDrawingPrimitives��һ���Ż������⻹�� ����Ԫ�� ���Σ��ߣ��� �Ļ��ƽڵ�֧�֡�
	FKCW_Base_ResourceLoader
		һ������ά�ֶ����̵߳���Դ�����ࡣ���Լ��ز�ͬ������Դ��
	FKCW_Base_PointList
		һ��ccpoint�������࣬��װ�˻��������������
	FKCW_Base_MD5
		�򵥵ķ�װMD5���ܺ��������Խ�һ����������ݼ����һ��128λ����ϢժҪ���ݡ�����������ǩ���㷨��
	FKCW_Base_Base64
		�򵥵ķ�װBase64���ܽ��ܺ�����
	FKCW_Base_Memory
		�ڴ����ϵͳ������Э�������ڴ��죬й¶��⡣
	FKCW_Base_Localization
		������Ի���֧�֡���Ҫ������׼��strings.xml���ñ�
	FKCW_Base_SecureUserDefault
		�������ñ�����CCUserDefault��������������һ��value�ļ��ܽ��ܹ��ܡ�
	FKCW_Base_Bundle
		Key-Valueһ�����ķ�װ������������һ������������ָ�ʽ���͵�Value��
	FKCW_Base_CSVLoader
		CSV��ʽ������
	FKCW_Base_SHA1
	FKCW_Base_HMAC_SHA1
		SHA1�㷨�����Խ�һ����������ݼ����һ��160λ����ϢժҪ���ݡ�����������ǩ���㷨��
	FKCW_Base_AStar
		һ���򵥵�AStar�㷨
====================================
������Ŀ/�⣺
====================================
	�ޣ�����cocos2dx��׼�ⲻ�㣩
====================================
todo:
====================================
	ƽ̨������ڶ๦�ܣ�������ϵͳ�ڴ���������ϵͳ����messageBox�ȣ�
*/ 
//-------------------------------------------------------------------------
#include "Include/FKCW_Base_Macro.h"
#include "Include/FKCW_Base_Memory.h"
#include "Include/FKCW_Base_Types.h"
#include "Include/FKCW_Base_ColorConvert.h"

#include "Include/FKCW_Base_Utils.h"
#include "Include/FKCW_Base_Data.h"
#include "Include/FKCW_Base_Geometry.h"
#include "Include/FKCW_Base_StringConvert.h"

#include "Include/FKCW_Base_DrawingPrimitives.h"
#include "Include/FKCW_Base_ResourceLoader.h"
#include "Include/FKCW_Base_PointList.h"
#include "Include/FKCW_Base_MD5.h"
#include "Include/FKCW_Base_Base64.h"
#include "Include/FKCW_Base_SHA1.h"
#include "Include/FKCW_Base_Localization.h"
#include "Include/FKCW_Base_SecureUserDefault.h"
#include "Include/FKCW_Base_Bundle.h"
#include "Include/FKCW_Base_CSVLoader.h"
#include "Include/FKCW_Base_AStar.h"
#include "Include/FKCW_Base_DecodeHtmlEntitiesUTF8.h"
#include "Include/FKCW_Base_PinYinUtils.h"
#include "Include/FKCW_Base_FileZip.h"
#include "Include/FKCW_Base_ByteBuffer.h"