#ifndef _LOG_VIEW_H_
#define _LOG_VIEW_H_

#include "FKCWLib/FKCocos2dxWrapper.h"

struct SafeModeStackItem
{
	string log;
	ccColor3B fontColor;
	ccColor4B bkColor;
};

/**
 * LogView
 * ��־
 */
class LogView : public FKCW_UIWidget_Layout
{
public:
	static LogView* create(CCSize size);
public:
	//������־����
	void setTitle(const char * title);
	//���̰߳�ȫģʽ
	void openSafeMode();
	//���һ�м�¼
	void log(const char * clog);
	void log(string clog);
	void log(ccColor3B fontColor, const char * clog);
	void log(ccColor3B fontColor, string clog);
	void log(ccColor3B fontColor, ccColor4B bkColor, const char * clog);
	void log(ccColor3B fontColor, ccColor4B bkColor, string clog);
	//��ȫģʽ�����һ�м�¼
	//�����ȴ��̰߳�ȫģʽ�����򲻻���ʾ
	void safeModeLog(const char * clog);
	void safeModeLog(string clog);
	void safeModeLog(ccColor3B fontColor, const char * clog);
	void safeModeLog(ccColor3B fontColor, string clog);
	void safeModeLog(ccColor3B fontColor, ccColor4B bkColor, const char * clog);
	void safeModeLog(ccColor3B fontColor, ccColor4B bkColor, string clog);
	//�����־
	void clearLog();
protected:
	virtual bool init(CCSize size);
	virtual void update(float delta);
	LogView();
	virtual ~LogView();
private:
	CCLabelTTF* m_pLabel;
	FKCW_UIWidget_ListView* m_pListView;
	bool m_isSafeMode;
	vector<SafeModeStackItem> safeLogStringStack;
};

#endif