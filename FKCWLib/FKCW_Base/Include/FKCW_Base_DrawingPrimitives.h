//*************************************************************************
//	��������:	2014-11-3
//	�ļ�����:	FKCW_Base_DrawingPrimitives.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_Base_Macro.h"
//-------------------------------------------------------------------------
// ���ƻ���Ԫ�ط����ࡣ�Ƕ�CCDrawingPrimitives��һ���Ż���
class FKCW_Base_DrawingPrimitives
{
public:
	// ������ɫ
	static void DrawColor4BEx(GLubyte r, GLubyte g, GLubyte b, GLubyte a);
	// ����һ��ʵ��Բ/��
	static void DrawSolidCircle(const CCPoint& center, float radius, float angle, unsigned int segments, bool drawLineToCenter, float scaleX, float scaleY);
	// ����һ��ʵ�ľ���
	static void DrawSolidRoundRect(CCPoint origin, CCPoint destination, float cornerRadius, ccColor4B color);
};
//-------------------------------------------------------------------------
// ����Ԫ�� ���Σ��ߣ��� �Ļ��ƽڵ�
class CCRectNode : public CCNodeRGBA
{
public:
	static CCRectNode* createWithSize(const CCSize& tSize, const ccColor4F& tColor, bool bFill = false);
	static CCRectNode* createWithRect(const CCRect& tRect, const ccColor4F& tColor, bool bFill = false);
	bool initWithSize(const CCSize& tSize, const ccColor4F& tColor, bool bFill = false);
	bool initWithRect(const CCRect& tRect, const ccColor4F& tColor, bool bFill = false);
	virtual void draw();

private:
	bool m_bFill;		// �Ƿ���ʵ
};
//-------------------------------------------------------------------------
class CCLineNode : public CCNodeRGBA
{
public:
	static CCLineNode* createWithPoints(const CCPoint& tBeginPoint, const CCPoint& tEndPoint, const ccColor4F& tColor);
	bool initWithPoints(const CCPoint& tBeginPoint, const CCPoint& tEndPoint, const ccColor4F& tColor);
	virtual void draw();
};
//-------------------------------------------------------------------------
class CCDotNode : public CCNodeRGBA
{
public:
	static CCDotNode* createWithPoint(const CCPoint& tPoint, const ccColor4F& tColor);
	bool initWithPoint(const CCPoint& tPoint, const ccColor4F& tColor);
	virtual void draw();
};
//-------------------------------------------------------------------------