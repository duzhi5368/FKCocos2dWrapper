//*************************************************************************
//	��������:	2014-11-5
//	�ļ�����:	FKCW_GR_Pinch.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_GR_GestureRecognizer.h"
//-------------------------------------------------------------------------
enum ENUM_GRPinch_Type
{
	eGRPinchType_Close		= 1 << 0,
	eGRPinchType_Open		= 1 << 1,
};
//-------------------------------------------------------------------------
// ������Ϸ�ֵ
static const float		s_PinchThreshold	= 2.0f;
//-------------------------------------------------------------------------
// ��ϣ���ѹ������iOS�ﳣ������ǽ������ţ�
class FKCW_GR_Pinch : public CCObject
{
public:
	bool		init(){ return true; }
	CREATE_FUNC(FKCW_GR_Pinch);
	ENUM_GRPinch_Type	m_eType;
};
//-------------------------------------------------------------------------
class FKCW_GR_PinchGestureRecognizer : public FKCW_GR_GestureRecognizer
{
public:
	bool			init();
	~FKCW_GR_PinchGestureRecognizer();
	CREATE_FUNC(FKCW_GR_PinchGestureRecognizer) ;

	virtual bool ccTouchBegan(CCTouch * pTouch, CCEvent * pEvent);
	virtual void ccTouchMoved(CCTouch * pTouch, CCEvent * pEvent);
	virtual void ccTouchEnded(CCTouch * pTouch, CCEvent * pEvent);
private:
	int			m_nTouchNumber;
	float		m_fLastDistance;
	CCArray*	m_pTouches;
};