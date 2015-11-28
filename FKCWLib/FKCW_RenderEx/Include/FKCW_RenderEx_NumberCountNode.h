//*************************************************************************
//	��������:	2014-11-28
//	�ļ�����:	FKCW_RenderEx_NumberCountNode.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_RenderEx_Macros.h"
#include "cocos-ext.h"
//-------------------------------------------------------------------------
USING_NS_CC_EXT;
//-------------------------------------------------------------------------
/**
 * @brief һ�����ֱ�ǩ����ǿ������
 *
 * ���ܣ������ֱ�ǩ���趨������һ������
 *       ���ֻ�ÿ��m_timeDeltaʱ��,����m_numberDelta,ֱ���ܹ�����m_increment
 *
 * Ӧ�÷�Χ���������ڷ�������ʾ
 * ���Թ��� cocos2d �� CCLabelAtlas ��
 * �� cocostudio ������ ui::LabelAtlas
 */
class FKCW_RenderEx_NumberCountNode : public CCObject
{
public:
	FKCW_RenderEx_NumberCountNode();
	~FKCW_RenderEx_NumberCountNode();

	// ��������ͼƬ ��0123456789��������ͼ
	void setLabelAtlas(CCLabelAtlas* ccLabelAtlas);
	void setLabelAtlas(ui::LabelAtlas* uiLabelAtlas);

	// �������ֵ�����m_increment�������Ϊ�ٶȣ�
	void setIncrement(int increment)   {m_increment   = increment;}
	// �������ֵ�����m_increment����ԭ����m_increment���ټ�increment��
	void addIncrement(int increment)   {m_increment += increment;}

	/**
	 * ��������ÿһ�����ӵ������ľ���ֵm_numberDelta
	 * ���ֻ�ÿ��m_timeDeltaʱ��,����m_numberDelta,ֱ���ܹ�����m_increment
	 * �����Ϊ���ٶ�
	 */
	void setNumberDelta(int delta)     {m_numberDelta = abs(delta);}
	
	/**
	 * ��������ÿһ�����ӵ�ʱ����m_timeDelta
	 * ���ֻ�ÿ��m_timeDeltaʱ��,����m_numberDelta,ֱ���ܹ�����m_increment
	 */
	void setTimeDelta(float timeDelta) {m_timeDelta   = timeDelta;}

	// ��ȡ��ǰ����
	int	getNumber(){return m_number;}
	/**
	 * ��������
	 *@param number Ŀ������
	 *@param bGradually �ǲ����ɵ�ǰ����һ��һ�����ӵ�Ŀ������
	 */
	bool setNumber(int number, bool bGradually);

	// schedule����,�������ӵļ����������ʵ��
	void updateNumber(float fInterval);

private:
	CCLabelAtlas*	m_pLabelAtlas;
	int				m_number;
	int				m_increment;
	int				m_numberDelta;
	float			m_timeDelta;
	float			m_timeEscape;
};