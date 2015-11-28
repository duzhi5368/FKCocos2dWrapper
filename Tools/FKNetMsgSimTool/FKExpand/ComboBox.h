#ifndef _COMBO_BOX_H_
#define _COMBO_BOX_H_

#include "FKCWLib/FKCW_UIWidget/FKCW_UIWidget.h"

typedef void (CCObject::*SEL_ComboBoxChangeHandler)(CCObject* pSender, int tag, const char* text);
#define fkcw_uiwidget_combobox_change_selector(_SELECTOR_)	(SEL_ComboBoxChangeHandler)(&_SELECTOR_)

/**
 * ComboBox
 * ������
 */
class ComboBox : public FKCW_UIWidget_Layout
{
public:
	static ComboBox* create(CCSize& size, int spreadSize);
	//���һ��ѡ��
	void addString(const char* text);
	//���
	void clear();
	//����ѡ��ı�ʱ��
	void setOnComboBoxChangeListener(CCObject* pListener, SEL_ComboBoxChangeHandler handler);
	//��ȡ��ǰѡ����
	int getSelect();
	//��ȡ��ǰ����
	const char* getText();
	//���ñ���
	void setText(const char* text);
	//��ȡ������ĸ���
	int getSize();
protected:
	ComboBox(){}
	virtual ~ComboBox(){}
	virtual bool init(CCSize& size, int spreadSize);

	void onButtonClickListener(CCObject* pSender);
	void onListClickListener( CCObject* pSender );
private:
	FKCW_UIWidget_Button* m_pButton;
	FKCW_UIWidget_ListView* m_listView;
	CCSize m_everySize;
	bool m_listViewIsVisible;
	int m_select;
	CCObject* m_pListener;
	SEL_ComboBoxChangeHandler m_handler;
	const char* m_text;
};

#endif