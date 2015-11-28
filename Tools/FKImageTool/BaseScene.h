#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
//-------------------------------------------------------------------------
#include "cocos2d.h"
#include "../../FKCWLib/FKCocos2dxWrapper.h"
#include "../../FKCoreLib/FKPicLib/FKPicLib.h"
//-------------------------------------------------------------------------
class BaseLayer : public cocos2d::CCLayer
{
public:
    virtual bool init();  
    static cocos2d::CCScene* scene();
	BaseLayer();
public:
	bool	InitUI();
public:
	// Ԥ��ĳһͼƬ�ļ�
	void onPreviewFile(CCObject* pSender);
	// ��ĳ��һ�ļ�
	void onOpenFile(CCObject* pSender);
	// ��ĳ�ļ���
	void onOpenDir(CCObject* pSender);
	// ���е��ļ�ת��
	void onConvertFile(CCObject* pSender);
	// �����ļ�������ת��
	void onConvertDir(CCObject* pSender);
	// ������Zipѹ������
	void onChangeZipRatio(CCObject* sender, CCControlEvent controlEvent);
	// ������Jpegѹ������
	void onChangeJpegRatio(CCObject* sender, CCControlEvent controlEvent);
protected:
	// ģ��windows��ʾ��Ϣ��������ռ����
	void _MessageInfo( string strTile, string strContext );
	void _MessageInfo( const char* szTile, const char* context );
	// ��ȡһ���ļ���ʽ�����ĺ�׺��
	string _GetConvertedName( string strSrcFilePathName, string strExt );
private:
	// �ݹ��ļ��н��и�ʽת��
	bool __RecurrenceConvertDir( const char* szPath, int p_nSrcType, int p_nDstType, int& p_nFileCount, int& p_nFileError );
public:
    CREATE_FUNC(BaseLayer);
public:
	FKCW_UIWidget_WidgetWindow* m_pRootWindow;

	CCControlSlider*			m_pZipSlider;
	FKCW_UIWidget_Label*		m_pZipRatioValue;
	CCControlSlider*			m_pJpegSlider;
	FKCW_UIWidget_Label*		m_pJpegRatioValue;

	CCEditBox*					m_pSingleFileEdit;
	FKCW_UIWidget_Button*		m_pSelSingleFileBtn;
	FKCW_UIWidget_Button*		m_pConvertFileBtn;

	CCEditBox*					m_pSrcDirEdit;
	CCEditBox*					m_pDstDirEdit;
	FKCW_UIWidget_Button*		m_pConvertDirBtn;
	FKCW_UIWidget_Button*		m_pSelSrcDirBtn;
	FKCW_UIWidget_Button*		m_pSelDstDirBtn;

	CCEditBox*					m_pPreviewFileEdit;
	FKCW_UIWidget_Button*		m_pSelPreviewFileBtn;
	FKCW_UIWidget_Button*		m_pPreviewFileBtn;

	CCSprite*					m_pPreviewSprite;	// �ȴ���Ԥ����ͼƬ����
public:
	int							m_nZipRatio;		// zipѹ������
	int							m_nJpegRatio;		// jpegѹ������
	string						m_szSingleFile;		// ���ļ�ת��ʱ���ļ�
	CFKImage*					m_pImage;			// ��Ҫ��ת�����ļ�
	string						m_szSrcDir;			// ��Ҫ��ת����ԴĿ¼
	string						m_szDstDir;			// ��Ҫ��ת����Ŀ��Ŀ¼
	bool						m_bIsOpeningDir;	// �Ƿ�ǰ�ļ��б�����״̬
	string						m_szPreviewFile;	// �ȴ�Ԥ����ͼƬ�ļ�
};
//-------------------------------------------------------------------------
#endif // __HELLOWORLD_SCENE_H__
