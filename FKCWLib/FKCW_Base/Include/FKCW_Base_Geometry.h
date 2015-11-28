//*************************************************************************
//	��������:	2014-11-14
//	�ļ�����:	FKCW_Base_Geometry.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_Base_Macro.h"
//-------------------------------------------------------------------------
// ����������Ĳ���Ϊʸ��
CCSize ccpDiff(const CCPoint& tPoint1, const CCPoint& tPoint2);
// ������ָ�������ƶ���ĵ�����
CCPoint ccpShift(const CCPoint& tPoint, const CCSize& tSize);
// ���ظ��������ı�׼����ĵ�
CCPoint ccpNormalizeTo(const CCPoint& tPoint, const CCSize& tNorm);
// ���ظ���������ȥ��׼����ĵ�
CCPoint ccpDenormalizeTo(const CCPoint& tPoint, const CCSize& tNorm);
// ת��CCPoint -> CCSize
CCSize cczFromPoint(const CCPoint& tPoint);
// ������������
float cczLength(const CCSize& tSize);
// �����������ĺ�
CCSize cczAdd(const CCSize& tSize1, const CCSize& tSize2);
// ����������������
CCSize cczSub(const CCSize& tSize1, const CCSize& tSize2);
// ����ָ��������׼����ֵ
CCSize cczNormalizeTo(const CCSize& tSize, const CCSize& tNorm);
// ����ָ������ȥ��׼����ֵ
CCSize cczDenormalizeTo(const CCSize& tSize, const CCSize& tNorm);
// �������������ļ�����
CCSize cczClamp(const CCSize& tSize, const CCSize& tLimit1, const CCSize& tLimit2);
// ���������Ӧ�������Сֵ����
CCSize cczMin(const CCSize& tSize1, const CCSize& tSize2);
// ���������Ӧ��������ֵ����
CCSize cczMax(const CCSize& tSize1, const CCSize& tSize2);
// ���ݸ��������ĵ�ʹ�С������һ������
CCRect ccRectMakeWithCenterAndSize(const CCPoint& tCenter, const CCSize& tSize);
// ���ݸ����Ļ�׼ԭ��ʹ�С������һ������
CCRect ccRectMakeWithOriginAndSize(const CCPoint& tOrigin, const CCSize& tSize);
// ����һ�����ε����ĵ�����
CCPoint ccRectGetCenter(const CCRect& tRect);
// ����һ�����εĴ�С
CCSize ccRectGetSize(const CCRect& tRect);
// �ж�һ�������Ƿ��ǿվ���
bool ccIsZeroRect(const CCRect& tRect);