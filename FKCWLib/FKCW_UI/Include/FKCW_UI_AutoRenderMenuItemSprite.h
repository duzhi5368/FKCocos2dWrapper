//*************************************************************************
//	��������:	2014-11-5
//	�ļ�����:	FKCW_UI_AutoRenderMenuItemSprite.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	һ���˵���飬�ܹ��Զ�����ѡ��״̬
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_UI_Macros.h"
//-------------------------------------------------------------------------
class FKCW_UI_AutoRenderMenuItemSprite : public CCMenuItemSprite
{
private:
	ccColor3B				m_pOldColor;				// ֮ǰ����ɫ
	bool					m_bIsFocus;					// �Ƿ�ǰ�ǽ���
	CCNode*					m_pFocusImage;				// ����״̬��ͼƬ

	CCObject*				m_pSelectedEventTarget;		// ��ѡ��֮����¼�
	SEL_MenuHandler			m_pSelectedEventSelector;	// ��ѡ��֮����¼�

	CCObject*				m_pUnselectedEventTarget;	// ȡ��ѡ�е��¼�
	SEL_MenuHandler			m_pUnselectedEventSelector;	// ȡ��ѡ�е��¼�

	CC_SYNTHESIZE_BOOL(m_bIsFocusIsAttachment, FocusIsAttachment);	// true��ʾ����״̬���Ժ���������״̬ͬʱ����
protected:
	virtual void			updateImagesVisibility();
	// ��ȫ״̬��ͼƬ���Ķ���
	void					_CenterAlignImgaes();
public:
	FKCW_UI_AutoRenderMenuItemSprite();
	virtual ~FKCW_UI_AutoRenderMenuItemSprite();
	// ����һ���˵�ѡ��
	// ������sprite ����״̬�µľ��飬target ��Ϣ�¼�֪ͨ����selector ѡ���¼��ص�����
	static FKCW_UI_AutoRenderMenuItemSprite* Create(CCNode* sprite, CCObject* target, SEL_MenuHandler selector);
	// ������normalImage ����״̬�µľ���ͼƬ��focusImage ��ý���״̬�µľ���ͼƬ
	static FKCW_UI_AutoRenderMenuItemSprite* Create(CCNode* normalImage, CCNode* focusImage);
	static FKCW_UI_AutoRenderMenuItemSprite* Create(CCNode* normalImage, CCNode* focusImage, CCObject* target, SEL_MenuHandler selector);
	static FKCW_UI_AutoRenderMenuItemSprite* Create(CCNode* normalImage, CCNode* selectedImage,
		CCNode* focusImage, CCObject* target, SEL_MenuHandler selector);
	static FKCW_UI_AutoRenderMenuItemSprite* Create(CCNode* normalImage, CCNode* selectedImage, 
		CCNode* disabledImage, CCNode* focusImage, CCObject* target, SEL_MenuHandler selector);

	// ����ѡ���¼���Ϣ����ͻص�
	void	SetSelectedEvent(CCObject* target, SEL_MenuHandler selector);
	// ����ȡ��ѡ���¼���Ϣ����ͻص�
	void	SetUnselectedEvent(CCObject* target, SEL_MenuHandler selector);
	
	virtual void selected();
	virtual void unselected();

	// ����Ϊ����/ȡ������
	void	SetFocus( bool p_bFlag );
	// �Ƿ��ǽ���
	bool	IsFocus();
	// ���ý���״̬ͼƬ
	void	SetFocusImage( CCNode* focusImage );
	// ��ȡ����״̬ͼƬ
	CCNode*	GetFocusImage();
};