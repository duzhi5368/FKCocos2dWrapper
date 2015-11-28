/********************************************************************
	created:	2014/11/01
	file base:	FKCW_Network_FileDownLoader
	author:		FreeKnight
	
	purpose:	Http�ļ�������
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include "FKCW_Network_Macros.h"
#include "FKCW_Network_HttpClient.h"
//--------------------------------------------------------------------
// �����ص�ʵ��
class FKCW_Network_DownloadEntry : public CCObject
{
public:
	string		m_strUrl;			// ����Url
	string		m_strDstName;		// ���ر���Ŀ¼��
	size_t		m_unSize;			// �ļ���С
	bool		m_bAppend;			// �Ƿ�����Ӷ����滻
public:
	FKCW_Network_DownloadEntry();
	virtual ~FKCW_Network_DownloadEntry();
	static FKCW_Network_DownloadEntry*		Create();
};
//--------------------------------------------------------------------
// һ��ʹ��HttpЭ����ļ���������
// ������һ����Ҫ�����ļ��б����Զ�һ����һ��������ȫ���ļ���
// �����ļ����ս������ڱ��ء�
// ��iOS�У��ļ����������� ~/Documents Ŀ¼�¡�
// ��Android���ļ������������ڲ��洢���С�
// ��ǰ��Ҳ����ָ���ļ��н����ļ����棬���硰Data��Ŀ¼������iOS�У��ļ����������� ~/Documents/Data Ŀ¼��
// ����һ����������
class FKCW_Network_FileDownLoader : public CCObject
{
private:
	FKCW_Network_HttpClient*		m_pClient;		// HttpClient
	FKCW_IO_AssetOutputStream*		m_pFOS;			// ��ǰ�ļ���
	FKCW_Network_DownloadEntry*		m_pEntry;		// ��ǰ����ʵ��

	CC_SYNTHESIZE_PASS_BY_REF(string, m_strFolder, Folder);					// �ļ���ǰ׺
	CC_SYNTHESIZE_PASS_BY_REF(CCArray, m_vecEntries, DownloadEntries);		// ��Ҫ���ص�ʵ���б�
	CC_SYNTHESIZE_PASS_BY_REF(CCArray, m_vecFailedEntries, FailedEntries);	// ����ʧ�ܵ�ʵ���б�
	CC_SYNTHESIZE_BOOL(m_bIsDownloading, Downloading);						// �Ƿ���������
	CC_SYNTHESIZE_READONLY(size_t, m_nTotalSize, TotalSize);						// ��Ҫ���ص����ֽ���
	CC_SYNTHESIZE_READONLY(size_t, m_nTotalDownloadedSize, TotalDownloadedSize);	// �����ص����ֽ���
protected:
	FKCW_Network_FileDownLoader();
	// ��ʼ��
	virtual bool		_Init();

	// ֪ͨ
	void				_OnHttpDone( FKCW_Network_HttpResponse* p_pResponse );
	void				_OnHttpData( FKCW_Network_HttpResponse* p_pResponse );
	void				_OnHttpHeaders( CCObject* p );

	// ������һ��ʵ��
	void				_DownloadNext();
public:
	virtual ~FKCW_Network_FileDownLoader();
	static FKCW_Network_FileDownLoader* GetInstance();
	// ����ļ�����������
	static void		Purge();

	// ���һ����Ҫ���صĶ���
	// ������p_strUrl ��Ҫ���ص��ļ�url���ļ�������url�����һ��
	//		p_bIsAppend ����ֵΪtrue������ζ�����غ���ļ�������ڱ��ص�ͬ��ԭ�ļ����棬��Ϊfalse�����滻
	void	AddFile( const string& p_strUrl, bool p_bIsAppend = false );
	// ���һ����Ҫ���صĶ���
	// ������p_strUrl ��Ҫ���ص��ļ�url
	//		p_strFileName �����ļ��󣬸���Ϊ�µ��ļ���
	//		p_bIsAppend ����ֵΪtrue������ζ�����غ���ļ�������ڱ��ص�ͬ��ԭ�ļ����棬��Ϊfalse�����滻
	void	AddFile( const string& p_strUrl, const string& p_strFileName, bool p_bIsAppend = false );
	// ���һ����Ҫ���صĶ���
	// ������p_strUrl ��Ҫ���ص��ļ�url
	//		p_strFileName �����ļ��󣬸���Ϊ�µ��ļ���
	//		p_unSize Ҫ���ص��ļ���С
	//		p_bIsAppend ����ֵΪtrue������ζ�����غ���ļ�������ڱ��ص�ͬ��ԭ�ļ����棬��Ϊfalse�����滻
	void	AddFile( const string& p_strUrl, const string& p_strFileName, size_t p_unSize, bool p_bIsAppend = false );

	// ��ʼ����
	void	Start();
	// �ж�����
	void	Abort();

	// ��ȡ��ǰ�����ļ������صĴ�С
	size_t	GetCurrentDownloadedSize();
	// ��ȡ��ǰ�������ص��ļ���
	string	GetCurrentDownloadingFileName();
	// ��ȡ��ǰ�������ص��ļ���������ȫ��·��
	string	GetCurrentDownloadingFileFullPath();
	// ��ȡ��ǰ�����ļ����ܴ�С
	// ע������δ֪�����ļ���С�����ֵ����Ϊ0
	size_t	GetCurrentDownloadingFileSize();
};