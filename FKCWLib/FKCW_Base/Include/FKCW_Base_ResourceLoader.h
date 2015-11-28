//*************************************************************************
//	��������:	2014-10-28
//	�ļ�����:	FKCW_Base_ResourceLoader.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	һ������ά�ֵ���Դ������
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_Base_Macro.h"
#include "FKCW_Base_Types.h"
#include "FKCW_Base_ResourceLoaderListener.h"
//-------------------------------------------------------------------------
// һ������ά�ֵ���Դ������
// ����OepnGL�߳���ÿ֡������Դ���ع�����һ����Դ��һ��Task����
// �߼�������Ա����Ҫ�������ڲ����ط�ʽ��
// ע�⣺��Ϊ��������CPU��λʱ�������Ĺ��󣬽������ÿ���ʱ�������̶߳���������
// ע�⣺�������������������в��Ŷ������ɣ��벻Ҫʹ��CCAction���ƣ�
//		��Ϊ���̳߳���ռ��CPU���ᵼ�¶�����֡������ʹ��SetDisplayFrame���ж������š�
// ˵���������ָ������/���ܺ������޸���Դ���ط�����
// ֧�ֵ���Դ����:
//		1��XML�ļ�
//		2��������ͼƬ��ʽ�ļ��������Ƿ���ܡ�
//		3��ͼƬ��
//		4��������
//		5��cocosDenshion֧�ֵ���Ƶ�ļ�
//	˵��������в�֧�ֵĸ�ʽ�������һ��task��֧������
class FKCW_Base_ResourceLoader : public CCObject
{
public:
	struct SLoadTask
	{
		float		m_fIdle;		// ������Ϻ�����ʱ��
		SLoadTask() : m_fIdle( 0.1f ){};
		virtual ~SLoadTask(){}
		virtual void Load(){}
	};
private:
	// ƽ̨xml�ļ���������
	struct SPlatformStringLoadTask : public SLoadTask
	{
		string		m_strLanguage;			// ����
		string		m_strPath;				// ��Դ·��
		bool		m_bIsMerge;				// �Ƿ���ϡ� True��ʾ�����ǰ�ַ����Ѿ����ڣ����ַ�������ϲ���ȥ��
											//		false��ʾ����ǰ�ַ����Ѿ����ڣ������ַ�����ֱ�����ԭ�ַ�����

		virtual ~SPlatformStringLoadTask(){}
		virtual void Load();
	};

	// cocosDenshion֧�ֵ����ּ�������
	struct SMusicTask : public SLoadTask
	{
		string		m_strName;				// ������

		virtual		~SMusicTask(){}
		virtual void Load();
	};

	// cocosDenshion֧�ֵ���Ч��������
	struct SEffectTask : public SLoadTask
	{
		string		m_strName;				// ��Ч��

		virtual		~SEffectTask(){}
		virtual void Load();
	};

	// λͼ�ַ���������
	struct SBMPFontLoadTask : public SLoadTask
	{
		string		m_strName;				// fnt�ļ���

		virtual		~SBMPFontLoadTask(){}
		virtual void Load();
	};

	// ���ܵ�λͼ�ַ���������
	struct SEncryptedBMPFontLoadTask : public SLoadTask
	{
		string			m_strName;			// ���ܺ��fnt�ļ���
		DECRYPT_FUNC	m_pDeFunc;			// ���ܺ���

		virtual		~SEncryptedBMPFontLoadTask(){}
		virtual void Load();
	};

	// ͼƬ��������
	struct SImageLoadTask : public SLoadTask
	{
		string		m_strName;				// image�ļ���

		virtual		~SImageLoadTask(){}
		virtual void Load();
	};

	// ����ͼƬ��������
	struct SEncryptedImageLoadTask : public SLoadTask
	{
		string			m_strName;			// ���ܺ��image�ļ���
		DECRYPT_FUNC	m_pDeFunc;			// ���ܺ���

		virtual		~SEncryptedImageLoadTask(){}
		virtual void Load();
	};

	// ͼƬ����������( TexturePacker Ҳʹ�����)
	struct SZwoptexLoadTask : public SLoadTask
	{
		string		m_strName;				// plist�ļ���

		virtual		~SZwoptexLoadTask(){}
		virtual void Load();
	};

	// ����ͼƬ����������
	struct SEncryptedZwoptexLoadTask : public SLoadTask
	{
		string			m_strPlistName;		// plist�ļ�����δ���ܶ���
		string			m_strPicName;		// ͼƬ���������ܶ���
		DECRYPT_FUNC	m_pDeFunc;			// ���ܺ���

		virtual		~SEncryptedZwoptexLoadTask(){}
		virtual void Load();
	};

	// Zwoptex��������
	struct SZwoptexAnimLoadTask : public SLoadTask
	{
		typedef vector<string>	StringList;
		StringList		m_vecFrames;		// ����֡���б�
		string			m_strName;			// ������
		float			m_fUnitDelay;		// ֡���ʱ��
		bool			m_bRestorOriginalFrame;		// �Ƿ��ڶ���������ʱ�ָ���ʼ֡

		SZwoptexAnimLoadTask():
			m_fUnitDelay( 0 ), m_bRestorOriginalFrame( false ){}
		virtual		~SZwoptexAnimLoadTask(){};
		virtual void Load();
	};

	// Zwoptex��������{ ÿһ֡�ж����ļ��ʱ�� }
	struct SZwoptexHighAnimLoadTask : public SLoadTask
	{
		typedef vector<string>	StringList;
		StringList		m_vecFrames;		// ����֡���б�
		typedef vector<float>	TimeList;
		TimeList		m_vecDelays;		// ֡���ʱ���б�
		string			m_strName;			// ������
		bool			m_bRestorOriginalFrame;		// �Ƿ��ڶ���������ʱ�ָ���ʼ֡

		SZwoptexHighAnimLoadTask():
			 m_bRestorOriginalFrame( false ){}
		virtual		~SZwoptexHighAnimLoadTask(){};
		virtual void Load();
	};

	// ������������
	struct SArmatureLoadTask : public SLoadTask
	{
		string			m_strConfigFilePath;	// �����ļ�

		virtual		~SArmatureLoadTask(){}
		virtual void Load();
	};

	// �����Զ����ʽ����
	struct SCustomTask : public SLoadTask
	{
		CCCallFunc*			m_pLoadFunc;		// �����ļ��ĺ���

		SCustomTask() : m_pLoadFunc( NULL )
		{
		}
		virtual ~SCustomTask()
		{
			if( m_pLoadFunc )
			{
				m_pLoadFunc->release();
				m_pLoadFunc = NULL;
			}
		}
		virtual void Load();
	};


private:
	typedef vector<SLoadTask*>				VecLoadTaskPtr;
	VecLoadTaskPtr							m_vecLoadTaskList;		// ��Ҫ���ص���Դ�����б�
	FKCW_Base_ResourceLoaderListener*		m_pListener;			// �����¼�������
	float									m_fRemainingIdle;		// ʣ����ӳ�ʱ��
	int										m_nNextLoad;			// ��һ�����ض���
	bool									m_bIsLoading;			// ��ʾ��ǰ�Ƿ��ڼ�����Դ
	CC_SYNTHESIZE(float, m_fDelay, Delay);							// ���м�������ǰ������ʱ��
private:
	// ʵ�ʼ���
	void					__DoLoad( float p_fDelta );
public:
	FKCW_Base_ResourceLoader( FKCW_Base_ResourceLoaderListener* p_pListener );
	virtual ~FKCW_Base_ResourceLoader();

	// ֹͣȫ����Դ����
	static void AbortAll();
	// ����һ����Դ��������ԭʼ����
	// ������p_strName ��Դ·���� p_pSize ���ݳ��� p_pFunc ��ѹ����ָ��
	// ע�⣺������Ӧ�����𷵻�ֵ���ͷ�
	static unsigned char*	LoadRow( const string& p_strName, unsigned long* p_pSize, DECRYPT_FUNC p_pFunc = NULL );
	// ����һ����Դ����C�ַ�����ʽ����
	// ע�⣺������Ӧ�����𷵻�ֵ���ͷ�
	static char*			LoadCString( const string& p_strName, DECRYPT_FUNC p_pFunc = NULL );
	// ����һ����Դ����C++�ַ�����ʽ����
	// ע�⣺������Ӧ�����𷵻�ֵ���ͷ�
	static string			LoadString( const string& p_strName, DECRYPT_FUNC p_pFunc = NULL );

	// ����һ��ͼƬ��Դ
	static void				LoadImage( const string& p_strName, DECRYPT_FUNC p_pFunc );
	// ����һ��Zwoptex�����Դ
	// ע��plist�ļ���������ܣ�pic���Ա����ܡ����ܺ�������pic�ļ���Ч
	static void				LoadZwoptex( const string& p_strPlistName, const string& p_strPicName, DECRYPT_FUNC p_pFunc );

	// ж��ͼƬ
	static void				UnloadImages( const string& p_strPic );
	// ����ж��ͼƬ��Ҫ��ָ��printf��ʽ
	static void				UnloadImages( const string& p_strPicPattern, int p_nStart, int p_nEnd );
	// ж��֡����
	static void				UnloadSpriteFrames( const string& p_strPlistPattern, const string& p_PicPattern,
		int p_nStart, int p_nEnd );
	// ж�عǼ�
	static void				UnloadArmatures( string p_strPlistPattern, string p_strPicPattern, 
		int p_nStart, int p_nEnd, string p_strConfig );
public:
	// ��ʼ����
	void					Run();
	// ��ģ��ֶμ���
	void					RunInBlockMode();
	// ��ֹ����
	// ע�⣺����ڷֶη�ģ����أ����޷���ֹ
	void					Abort();
	// ���һ����������
	void					AddLoadTask( SLoadTask* p_pTask );
	// ���һ���Զ����ʽ�ļ�������
	void					AddCustomLoadTask( CCCallFunc* p_pFunc );
	// ���һ��ͼƬ�����������
	// ������p_fIdle �����굱ǰ��������ö�ü�����һ����
	void					AddBMPFontTask( const string& p_strFntFile, float p_fIdle = 0.0f );
	// ���һ�������ܵ�ͼƬ�����������
	void					AddEncrypeBMPFontTask( const string& p_strFntFile, DECRYPT_FUNC p_pDeFunc, float p_fIdle = 0.0f );
	// ���һ��ƽ̨�ַ���strings.xml�ļ���������
	void					AddPlatformStringTask( const string& p_strLanguage, const string& p_strPath, bool p_bIsMerge = false );
	// ���һ��ͼƬ�ļ���������
	void					AddImageTask( const string& p_strName, float p_fIdle = 0.0f );
	// ���һ�����ܵ�ͼƬ�ļ���������
	void					AddEncrypeImageTask( const string& p_strName, DECRYPT_FUNC p_pDeFunc, float p_fIdle = 0.0f );
	// ���һ��zwoptexͼƬ��������
	void					AddZwoptexTask( const string& p_strName, float p_fIdle = 0.0f );
	// ���һ�鱻���ܵ�zwoptexͼƬ��������ָ��sprintf��ʽ��
	void					AddZwoptexTask( const string& p_strPattern, int p_nStart, int p_nEnd, float p_fIdle = 0.0f );
	// ���һ��zwoptexͼƬ�������������
	// ע��plist�ļ���������ܣ�pic���Ա����ܡ����ܺ�������pic�ļ���Ч
	void					AddZwoptexTask( const string& p_strPlistName, const string& p_strPicName, DECRYPT_FUNC p_pFunc, float p_fIdle = 0.0f );
	// ���һ��zwoptexͼƬ�������������
	// ע��plist�ļ���������ܣ�pic���Ա����ܡ����ܺ�������pic�ļ���Ч
	void					AddZwoptexTask( const string& p_strPlistPattern, const string& p_PicPattern,
		int p_nStart, int p_nEnd, DECRYPT_FUNC p_pFunc, float p_fIdle = 0.0f );
	// ���һ����Ч��������
	void					AddCocosDenshionEffectTask( const string& p_strName, float p_fIdle = 0.0f );
	// ���һ�����ּ�������
	void					AddCocosDenshionMusicTask( const string& p_strName, float p_fIdle = 0.0f );
	// ���һ��zwoptex����
	// ע��p_nEndIndex ������
	// ������p_fUnitDalay �ӳ�ʱ��
	// ������p_bIsRestoreOriginalFrame �Ƿ��ڶ���������ʱ�ָ���ʼ֡
	void					AddZwoptexAnimTask( const string& p_strName, float p_fUnitDalay, const string& p_strPattern,
		int p_nStartIndex, int p_nEndIndex, bool p_bIsRestoreOriginalFrame = false, float p_fIdle = 0.0f );
	// ���һ��zwoptex����
	// ע���ö�����������ʼ/����ʱ�䣬���Զ��������������׶�
	void					AddZwoptexAnimTask( const string& p_strName, float p_fUnitDalay, const string& p_strPattern,
		int p_nStartIndex, int p_nEndIndex, int p_nStartIndex2, int p_nEndIndex2, bool p_bIsRestoreOriginalFrame = false, float p_fIdle = 0.0f );
	// ���һ��zwoptex����
	// ע���ö���ÿ֡���ж������ʱ��
	void					AddZwoptexAnimTask( const string& p_strName,  const string& p_strPattern, int p_nStartIndex, int p_nEndIndex,
		const CCArray& p_vecDelays, bool p_bIsRestoreOriginalFrame = false, float p_fIdle = 0.0f );
	// ���һ�����ع������������ļ�������
	// ע��������û���Զ���Ӷ�ӦͼƬ����Ҫ�û����ⴴ�����ض�ӦͼƬ������
	void					AddArmatureTask( string p_strConfig, float p_fIdle = 0.0f );
	// ���һ�����ع������������ļ�������
	// ע��plist�ļ���config�ļ�����������
	void					AddArmatureTask( string p_strPlist, string p_strPic, string p_strConfig, DECRYPT_FUNC p_pDeFunc = NULL, float p_fIdle = 0.0f );
	// ���һ�����ع������������ļ�������
	void					AddArmatureTask( string p_strPlistPattern, string p_strPicPattern, int p_nStartIndex, int p_nEndIndex,
		string p_strConfig, DECRYPT_FUNC p_pDeFunc = NULL, float p_fIdle = 0.0f );
};