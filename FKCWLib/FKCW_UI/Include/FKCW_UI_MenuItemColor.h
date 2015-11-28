//*************************************************************************
//	��������:	2014-11-5
//	�ļ�����:	FKCW_UI_MenuItemColor.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	һ������ɫ��ʽ�Ĳ˵���
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_UI_Macros.h"
//-------------------------------------------------------------------------
class FKCW_UI_MenuItemColorStateListener;
// һ������ɫ��ʽ�Ĳ˵���
// ע����Ϊ�ò˵�������������ͼ����������Ҫָ�����С
class FKCW_UI_MenuItemColor : public CCMenuItem, public CCBlendProtocol 
{
private:
	ccColor4B				m_pNormalColor;			// ��̬�µ���ɫ
	ccColor4B				m_pSelectedColor;		// ѡ�е���ɫ
	ccColor4B				m_pDisabledColor;		// ��Чʱ����ɫ
	ccColor4B				m_pFocusColor;			// ��ý���ʱ����ɫ

	ccVertex2F				m_pSquareVertices[4];	// ����
	ccColor4F				m_pSquareColors[4];		// ��ɫ

	// �¼�״̬������
	CC_SYNTHESIZE(FKCW_UI_MenuItemColorStateListener*, m_pStateListener, StateListener);
	// �Ƿ񽹵�״̬
	CC_SYNTHESIZE_BOOL_SETTER(m_bIsFocus, Focus);
	// ��Ϸ�ʽ
	CC_PROPERTY(ccBlendFunc, m_tagBlendFunc, BlendFunc);
protected:
	FKCW_UI_MenuItemColor();
	// ������ɫ
	virtual void updateColor();
public:
	virtual ~FKCW_UI_MenuItemColor();

	static FKCW_UI_MenuItemColor* Create(ccColor4B normal);
	static FKCW_UI_MenuItemColor* Create(ccColor4B normal, ccColor4B focus);
	static FKCW_UI_MenuItemColor* Create(ccColor4B normal, ccColor4B selected, ccColor4B focus);
	static FKCW_UI_MenuItemColor* Create(ccColor4B normal, ccColor4B selected, ccColor4B focus, ccColor4B disabled);
	static FKCW_UI_MenuItemColor* Create(ccColor4B normal, CCObject* target, SEL_MenuHandler selector);
	static FKCW_UI_MenuItemColor* Create(ccColor4B normal, ccColor4B focus, CCObject* target, SEL_MenuHandler selector);
	static FKCW_UI_MenuItemColor* Create(ccColor4B normal, ccColor4B selected, ccColor4B focus, CCObject* target, SEL_MenuHandler selector);
	static FKCW_UI_MenuItemColor* Create(ccColor4B normal, ccColor4B selected, ccColor4B focus, ccColor4B disabled, CCObject* target, SEL_MenuHandler selector);

	// ��ʼ��
	void InitWithColorAndTarget(ccColor4B normal, ccColor4B focus, ccColor4B selected, ccColor4B disabled, CCObject* target, SEL_MenuHandler selector);

	// ����̳к���
	virtual void draw();
	virtual void setContentSize(const CCSize& size);
	virtual void selected();
	virtual void unselected();
	virtual void setEnabled(bool value);

	// ������״̬�¼��ĺ���
	void SelectedSilent();
	void UnselectedSilent();
	void SetEnabledSilent(bool value);
	void SetFocusSilent(bool flag);
};