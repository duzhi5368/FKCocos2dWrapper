#ifndef _FILE_VIEW_H_
#define _FILE_VIEW_H_

#include "FKCWLib/FKCocos2dxWrapper.h"

class ComboBox;

class FileViewDelegate
{
public:
	virtual void onFileViewNewFileMessage(string strFilePathName) = 0;
	virtual void onFileViewOpenFileMessage(string strFilePathName) = 0;
};

/**
 * FileView
 * �ļ����
 */
class FileView : public FKCW_UIWidget_WidgetWindow
{
public:
	CREATE_FUNC(FileView);
	//�����¼�ί��Ŀ��
	void setDelegate(FileViewDelegate* pDelegate);
	//�����ļ�ѡ�������
	void setText(const char* title);
protected:
	FileView();
	virtual bool init();
private:
	void onFileComboBoxChange(CCObject* pSender, int tag, const char* text);
private:
	FileViewDelegate* m_pDelegate;
	ComboBox* m_pFileMenuComboBox;
	ComboBox* m_pFileSelectComboBox;
};

#endif