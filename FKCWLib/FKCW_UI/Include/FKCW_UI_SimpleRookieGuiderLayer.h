//*************************************************************************
//	��������:	2014-11-6
//	�ļ�����:	FKCW_UI_SimpleRookieGuiderLayer.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_UI_RookieGuideLayer.h"
#include "FKCW_UI_Macros.h"
//-------------------------------------------------------------------------
// һ���򵥵��Զ������������㣬����ʾһ����ǩ�ͼ�ͷ
class FKCW_UI_SimpleRookieGuiderLayer : public FKCW_UI_RookieGuideLayer
{
private:
	CC_SYNTHESIZE_SETTER(CCSprite*, m_pArrow, Arrow);		// ��ͷ����
	CC_SYNTHESIZE_SETTER(CCNode*, m_pHint, Hint);			
protected:
	FKCW_UI_SimpleRookieGuiderLayer();
public:
	virtual ~FKCW_UI_SimpleRookieGuiderLayer();
	static FKCW_UI_SimpleRookieGuiderLayer* Create();
	// ���Ǹ��ຯ��
	virtual void	FadeIn( float duration, float delay = 0  );
	// ����ͷ��׼���������ģ����ض��ĽǶȺ;���
	// ������regionIndex ��������� distance �������ĺͼ�ͷ�������ĵľ��� degree ��������ָ���ͷ�м�ĽǶ���������ֵΪ��ʱ�룩
	//		arrowPresetRotation ��ͷ�������ת�Ƕȣ���ֵΪ��ʱ�룩
	void			PointToRegionCenter(int regionIndex, float distance, float degree, float arrowPresetRotation = 0);
	// ������ʾ��Ϣλ�ã�����ڼ�ͷ�����꣩
	void			ShiftHint(float dx, float dy);
};