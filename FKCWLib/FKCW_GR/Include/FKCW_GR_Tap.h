/********************************************************************
	created:	2014/11/05
	file base:	FKCW_GR_Tap
	author:		FreeKnight
	
	purpose:	
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include "FKCW_GR_GestureRecognizer.h"
//--------------------------------------------------------------------
static const int		s_TapMaxDuration			= 150;	// ���ε�����µ��ſ��ļ��ʱ�䣨������������Ϊ�������¼���
static const int		s_TapMaxDurationBetweenTaps	= 220;	// ���ε�����µļ��ʱ�䣨������������Ϊ�����������
static const int		s_TapMaxDistance			= 20;	// ���ε�����µ��ſ��ļ��ʱ�䣨������������Ϊ�������¼���
static const int		s_TapMaxDistanceBetweenTaps	= 20;	// ���ε�����µľ��루��������ֵ������Ϊ��ͬһ������
//--------------------------------------------------------------------
class FKCW_GR_Tap : public CCObject
{
public:
	bool init() {return true;}
	CREATE_FUNC(FKCW_GR_Tap);
	CCPoint m_tagLocation;
};
//--------------------------------------------------------------------
// ����¼�
// ע��Ĭ�ϴ�������Ϣ;������˫���¼�������Ҫ���� setNumberOfTapsRequired(2)
class FKCW_GR_TapGestureRecognizer : public FKCW_GR_GestureRecognizer
{
public:
	bool init();
	~FKCW_GR_TapGestureRecognizer();
	CREATE_FUNC(FKCW_GR_TapGestureRecognizer);

	virtual bool ccTouchBegan(CCTouch * pTouch, CCEvent * pEvent);
	virtual void ccTouchMoved(CCTouch * pTouch, CCEvent * pEvent){};
	virtual void ccTouchEnded(CCTouch * pTouch, CCEvent * pEvent);
private:
	void	__StopGestureRecognition();
private:
	int		m_nTaps;
	CCPoint m_tagInitialPosition;
	CCPoint	m_tagFinalPosition;
	struct cc_timeval m_tagStartTime, m_tagEndTime;
	CC_SYNTHESIZE(unsigned int, m_unNumberOfTapsRequired, NumberOfTapsRequired);
};