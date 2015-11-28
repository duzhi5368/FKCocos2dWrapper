//-------------------------------------------------------------------------
#include "../Include/FKCW_Base_ResourceLoader.h"
#include "../Include/FKCW_Base_Localization.h"
#include "SimpleAudioEngine.h"
#include "CocoStudio/Armature/utils/CCArmatureDataManager.h"
//-------------------------------------------------------------------------
#pragma warning( disable : 4244 )
#pragma warning( disable : 4018 )
//-------------------------------------------------------------------------
using namespace CocosDenshion;
using namespace cocos2d::extension;
//-------------------------------------------------------------------------
void FKCW_Base_ResourceLoader::SPlatformStringLoadTask::Load()
{
	FKCW_Base_Localization::GetInstance()->AddPlatformString( m_strLanguage, m_strPath, m_bIsMerge );
}
//-------------------------------------------------------------------------
void FKCW_Base_ResourceLoader::SMusicTask::Load()
{
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic( m_strName.c_str() );
}
//-------------------------------------------------------------------------
void FKCW_Base_ResourceLoader::SEffectTask::Load()
{
	SimpleAudioEngine::sharedEngine()->preloadEffect( m_strName.c_str() );
}
//-------------------------------------------------------------------------
void FKCW_Base_ResourceLoader::SBMPFontLoadTask::Load()
{
	CCBMFontConfiguration* p = FNTConfigLoadFile( m_strName.c_str() );
	CCTextureCache::sharedTextureCache()->addImage( p->getAtlasName() );
}
//-------------------------------------------------------------------------
void FKCW_Base_ResourceLoader::SEncryptedBMPFontLoadTask::Load()
{
	CCBMFontConfiguration* conf = FNTConfigLoadFile( m_strName.c_str() );

	unsigned long len;
	char* data = (char*)CCFileUtils::sharedFileUtils()->getFileData(conf->getAtlasName(), "rb", &len);

	// ��������
	int decLen;
	const char* dec = NULL;
	if(m_pDeFunc) 
	{
		dec = (*m_pDeFunc)(data, len, &decLen);
	} 
	else 
	{
		dec = data;
		decLen = (int)len;
	}
	CCImage* image = new CCImage();
	image->initWithImageData((void*)dec, decLen);
	image->autorelease();
	CCTextureCache::sharedTextureCache()->addUIImage(image, conf->getAtlasName());

	if(dec != data)
		free((void*)dec);
	free(data);
}
//-------------------------------------------------------------------------
void FKCW_Base_ResourceLoader::SImageLoadTask::Load()
{
	CCTextureCache::sharedTextureCache()->addImage( m_strName.c_str() );
}
//-------------------------------------------------------------------------
void FKCW_Base_ResourceLoader::SEncryptedImageLoadTask::Load()
{
	unsigned long len;
	char* data = (char*)CCFileUtils::sharedFileUtils()->getFileData( m_strName.c_str(), "rb", &len );

	// ��������
	int decLen;
	const char* dec = NULL;
	if(m_pDeFunc) 
	{
		dec = (*m_pDeFunc)(data, len, &decLen);
	} 
	else 
	{
		dec = data;
		decLen = (int)len;
	}
	CCImage* image = new CCImage();
	image->initWithImageData((void*)dec, decLen);
	image->autorelease();
	CCTextureCache::sharedTextureCache()->addUIImage(image, m_strName.c_str());

	if(dec != data)
		free((void*)dec);
	free(data);
}
//-------------------------------------------------------------------------
void FKCW_Base_ResourceLoader::SZwoptexLoadTask::Load()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile( m_strName.c_str() );
}
//-------------------------------------------------------------------------
void FKCW_Base_ResourceLoader::SEncryptedZwoptexLoadTask::Load()
{
	// ���ؼ����ļ�
	unsigned long len;
	char* data = (char*)CCFileUtils::sharedFileUtils()->getFileData( m_strPicName.c_str(), "rb", &len );

	// ��������
	int decLen;
	const char* dec = NULL;
	if(m_pDeFunc) 
	{
		dec = (*m_pDeFunc)(data, len, &decLen);
	} 
	else 
	{
		dec = data;
		decLen = (int)len;
	}
	CCImage* image = new CCImage();
	image->initWithImageData((void*)dec, decLen);
	image->autorelease();
	CCTexture2D* tex = CCTextureCache::sharedTextureCache()->addUIImage(image, m_strPicName.c_str());

	if(dec != data)
		free((void*)dec);
	free(data);

	// ��ȡplist
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile( m_strPlistName.c_str(), tex );
}
//-------------------------------------------------------------------------
void FKCW_Base_ResourceLoader::SZwoptexAnimLoadTask::Load()
{
	if(!CCAnimationCache::sharedAnimationCache()->animationByName(m_strName.c_str()))
	{
		CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
		CCArray* array = CCArray::create();
		for(StringList::iterator iter = m_vecFrames.begin(); iter != m_vecFrames.end(); iter++) 
		{
			CCSpriteFrame* f = cache->spriteFrameByName(iter->c_str());
			array->addObject(f);
		}
		CCAnimation* anim = CCAnimation::createWithSpriteFrames(array, m_fUnitDelay);
		anim->setRestoreOriginalFrame(m_bRestorOriginalFrame);
		CCAnimationCache::sharedAnimationCache()->addAnimation(anim, m_strName.c_str());
	}
}
//-------------------------------------------------------------------------
void FKCW_Base_ResourceLoader::SZwoptexHighAnimLoadTask::Load()
{
	if(!CCAnimationCache::sharedAnimationCache()->animationByName( m_strName.c_str() ) ) 
	{
		CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
		CCArray* array = CCArray::create();
		int size = m_vecFrames.size();
		for(int i = 0; i < size; i++) 
		{
			CCSpriteFrame* sf = cache->spriteFrameByName(m_vecFrames.at(i).c_str());
			float& delay = m_vecDelays.at(i);
			CCAnimationFrame* af = new CCAnimationFrame();
			af->initWithSpriteFrame(sf, delay, NULL);
			af->autorelease();
			array->addObject(af);
		}
		CCAnimation* anim = CCAnimation::createWithSpriteFrames(array, 1);
		anim->setRestoreOriginalFrame(m_bRestorOriginalFrame);
		CCAnimationCache::sharedAnimationCache()->addAnimation(anim, m_strName.c_str());
	}
}
//-------------------------------------------------------------------------
void FKCW_Base_ResourceLoader::SArmatureLoadTask::Load()
{
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(m_strConfigFilePath.c_str());
}
//-------------------------------------------------------------------------
void FKCW_Base_ResourceLoader::SCustomTask::Load()
{
	if( m_pLoadFunc )
		m_pLoadFunc->execute();
}
//-------------------------------------------------------------------------
// FKCW_Base_ResourceLoader
//-------------------------------------------------------------------------
static CCArray s_ActiveLoaders;
//-------------------------------------------------------------------------
FKCW_Base_ResourceLoader::FKCW_Base_ResourceLoader( FKCW_Base_ResourceLoaderListener* p_pListener )
	: m_pListener( p_pListener )
	, m_fDelay( 0.0f )
	, m_fRemainingIdle( 0.0f )
	, m_nNextLoad( 0 )
	, m_bIsLoading( false )
{
	s_ActiveLoaders.addObject( this );
	release();
}
//-------------------------------------------------------------------------
FKCW_Base_ResourceLoader::~FKCW_Base_ResourceLoader()
{
	for( VecLoadTaskPtr::iterator Ite = m_vecLoadTaskList.begin(); Ite != m_vecLoadTaskList.end(); ++Ite )
	{
		delete *Ite;
	}
	s_ActiveLoaders.removeObject( this, false );
}
//-------------------------------------------------------------------------
// ֹͣȫ����Դ����
void FKCW_Base_ResourceLoader::AbortAll()
{
	CCArray tmp;
	tmp.addObjectsFromArray(&s_ActiveLoaders);
	CCObject* obj;
	CCARRAY_FOREACH(&s_ActiveLoaders, obj) 
	{
		FKCW_Base_ResourceLoader* loader = (FKCW_Base_ResourceLoader*)obj;
		loader->Abort();
	}
}
//-------------------------------------------------------------------------
// ����һ����Դ��������ԭʼ����
// ������p_strName ��Դ·���� p_pSize ���ݳ��� p_pFunc ��ѹ����ָ��
// ע�⣺������Ӧ�����𷵻�ֵ���ͷ�
unsigned char* FKCW_Base_ResourceLoader::LoadRow( const string& p_strName, unsigned long* p_pSize, DECRYPT_FUNC p_pFunc )
{
	// ���ؼ��ܺ���ļ�
	unsigned long len;
	char* data = (char*)CCFileUtils::sharedFileUtils()->getFileData( p_strName.c_str(), "rb", &len);

	int decLen;
	const char* dec = NULL;
	if(p_pFunc) 
	{
		dec = (*p_pFunc)(data, len, &decLen);
	} 
	else 
	{
		dec = data;
		decLen = (int)len;
	}

	if(dec != data)
		free(data);

	// �������ݴ�С
	if(p_pSize)
		*p_pSize = decLen;

	return (unsigned char*)dec;
}
//-------------------------------------------------------------------------
// ����һ����Դ����C�ַ�����ʽ����
// ע�⣺������Ӧ�����𷵻�ֵ���ͷ�
char* FKCW_Base_ResourceLoader::LoadCString( const string& p_strName, DECRYPT_FUNC p_pFunc )
{
	unsigned long len;
	char* data = (char*)CCFileUtils::sharedFileUtils()->getFileData(p_strName.c_str(), "rb", &len);

	int decLen;
	const char* dec = NULL;
	if(p_pFunc) 
	{
		dec = (*p_pFunc)(data, len, &decLen);
	} 
	else 
	{
		dec = data;
		decLen = (int)len;
	}

	// ����
	char* ret = (char*)malloc((decLen + 1) * sizeof(char));
	memcpy(ret, dec, decLen);
	ret[decLen] = 0;

	if(dec != data)
		free((void*)dec);
	free(data);

	return ret;
}
//-------------------------------------------------------------------------
// ����һ����Դ����C++�ַ�����ʽ����
// ע�⣺������Ӧ�����𷵻�ֵ���ͷ�
string FKCW_Base_ResourceLoader::LoadString( const string& p_strName, DECRYPT_FUNC p_pFunc )
{
	char* buf = LoadCString(p_strName, p_pFunc);
	string ret = buf;
	free(buf);
	return ret;
}
//-------------------------------------------------------------------------
// ����һ��ͼƬ��Դ
void FKCW_Base_ResourceLoader::LoadImage( const string& p_strName, DECRYPT_FUNC p_pFunc )
{
	unsigned long len;
	char* data = (char*)CCFileUtils::sharedFileUtils()->getFileData(p_strName.c_str(), "rb", &len);

	// ��������
	int decLen;
	const char* dec = NULL;
	if(p_pFunc) 
	{
		dec = (*p_pFunc)(data, len, &decLen);
	} 
	else 
	{
		dec = data;
		decLen = (int)len;
	}
	CCImage* image = new CCImage();
	image->initWithImageData((void*)dec, decLen);
	image->autorelease();
	CCTextureCache::sharedTextureCache()->addUIImage(image, p_strName.c_str());

	if(dec != data)
		free((void*)dec);
	free(data);
}
//-------------------------------------------------------------------------
// ����һ��Zwoptex�����Դ
// ע��plist�ļ���������ܣ�pic���Ա����ܡ����ܺ�������pic�ļ���Ч
void FKCW_Base_ResourceLoader::LoadZwoptex( const string& p_strPlistName, const string& p_strPicName, DECRYPT_FUNC p_pFunc )
{
	unsigned long len;
	char* data = (char*)CCFileUtils::sharedFileUtils()->getFileData(p_strPicName.c_str(), "rb", &len);

	// ��������
	int decLen;
	const char* dec = NULL;
	if(p_pFunc) 
	{
		dec = (*p_pFunc)(data, len, &decLen);
	} 
	else 
	{
		dec = data;
		decLen = (int)len;
	}
	CCImage* image = new CCImage();
	image->initWithImageData((void*)dec, decLen);
	image->autorelease();
	CCTexture2D* tex = CCTextureCache::sharedTextureCache()->addUIImage(image, p_strPicName.c_str());

	if(dec != data)
		free((void*)dec);
	free(data);

	// ���List�ļ�
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(p_strPlistName.c_str(), tex);
}
//-------------------------------------------------------------------------
// ж��ͼƬ
void FKCW_Base_ResourceLoader::UnloadImages( const string& p_strPic )
{
	CCTextureCache::sharedTextureCache()->removeTextureForKey(p_strPic.c_str());
}
//-------------------------------------------------------------------------
// ����ж��ͼƬ��Ҫ��ָ��printf��ʽ
void FKCW_Base_ResourceLoader::UnloadImages( const string& p_strPicPattern, int p_nStart, int p_nEnd )
{
	char buf[512];
	for(int i = p_nStart; i <= p_nEnd; i++) 
	{
		sprintf(buf, p_strPicPattern.c_str(), i);
		CCTextureCache::sharedTextureCache()->removeTextureForKey(buf);
	}
}
//-------------------------------------------------------------------------
// ж��֡����
void FKCW_Base_ResourceLoader::UnloadSpriteFrames( const string& p_strPlistPattern, const string& p_PicPattern,
										   int p_nStart, int p_nEnd )
{
	char buf[512];
	for(int i = p_nStart; i <= p_nEnd; i++) {
		sprintf(buf, p_strPlistPattern.c_str(), i);
		CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(buf);
		sprintf(buf, p_PicPattern.c_str(), i);
		CCTextureCache::sharedTextureCache()->removeTextureForKey(buf);
	}
}
//-------------------------------------------------------------------------
// ж�عǼ�
void FKCW_Base_ResourceLoader::UnloadArmatures( string p_strPlistPattern, string p_strPicPattern, 
										int p_nStart, int p_nEnd, string p_strConfig )
{
	CCArmatureDataManager::sharedArmatureDataManager()->removeArmatureFileInfo(p_strConfig.c_str());
	char buf[512];
	for(int i = p_nStart; i <= p_nEnd; i++) 
	{
		sprintf(buf, p_strPlistPattern.c_str(), i);
		CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(buf);
		sprintf(buf, p_strPicPattern.c_str(), i);
		CCTextureCache::sharedTextureCache()->removeTextureForKey(buf);
	}
}
//-------------------------------------------------------------------------
// ʵ�ʼ���
void FKCW_Base_ResourceLoader::__DoLoad( float p_fDelta )
{
	if(m_fRemainingIdle > 0) 
	{
		m_fRemainingIdle -= p_fDelta;
	} 
	else if(m_vecLoadTaskList.size() <= m_nNextLoad) 
	{
		if(m_bIsLoading) {
			m_bIsLoading = false;
			CCScheduler* scheduler = CCDirector::sharedDirector()->getScheduler();
			scheduler->unscheduleSelector(schedule_selector(FKCW_Base_ResourceLoader::__DoLoad), this);
			autorelease();
		}

		if(m_pListener)
			m_pListener->OnResourceLoadingDone();
	} 
	else 
	{
		SLoadTask* lp = m_vecLoadTaskList.at(m_nNextLoad++);
		m_fRemainingIdle = lp->m_fIdle;

		lp->Load();
		if(m_pListener)
			m_pListener->OnResourceLoadingProgress(m_nNextLoad * 100 / m_vecLoadTaskList.size(), p_fDelta);
	}
}
//-------------------------------------------------------------------------
// ��ʼ����
void FKCW_Base_ResourceLoader::Run()
{
	if(m_bIsLoading)
		return;
	m_bIsLoading = true;

	CCScheduler* scheduler = CCDirector::sharedDirector()->getScheduler();
	scheduler->scheduleSelector(schedule_selector(FKCW_Base_ResourceLoader::__DoLoad), this, 0, kCCRepeatForever, m_fDelay, false);
}
//-------------------------------------------------------------------------
// ��ģ��ֶμ���
void FKCW_Base_ResourceLoader::RunInBlockMode()
{
	m_bIsLoading = true;
	for(VecLoadTaskPtr::iterator iter = m_vecLoadTaskList.begin(); iter != m_vecLoadTaskList.end(); iter++) 
	{
		SLoadTask* lp = *iter;
		lp->Load();
		if(m_pListener)
			m_pListener->OnResourceLoadingProgress(m_nNextLoad * 100 / m_vecLoadTaskList.size(), 0);
	}
	m_bIsLoading = false;
}
//-------------------------------------------------------------------------
// ��ֹ����
// ע�⣺����ڷֶη�ģ����أ����޷���ֹ
void FKCW_Base_ResourceLoader::Abort()
{
	if(!m_bIsLoading)
		return;
	m_bIsLoading = false;

	CCScheduler* scheduler = CCDirector::sharedDirector()->getScheduler();
	scheduler->unscheduleSelector(schedule_selector(FKCW_Base_ResourceLoader::__DoLoad), this);
	autorelease();
}
//-------------------------------------------------------------------------
// ���һ����������
void FKCW_Base_ResourceLoader::AddLoadTask( SLoadTask* p_pTask )
{
	m_vecLoadTaskList.push_back( p_pTask );
}
//-------------------------------------------------------------------------
// ���һ���Զ����ʽ�ļ�������
void FKCW_Base_ResourceLoader::AddCustomLoadTask( CCCallFunc* p_pFunc )
{
	SCustomTask* t = new SCustomTask();
	t->m_pLoadFunc = p_pFunc;
	CC_SAFE_RETAIN(t->m_pLoadFunc);
	AddLoadTask(t);
}
//-------------------------------------------------------------------------
// ���һ��ͼƬ�����������
// ������p_fIdle �����굱ǰ��������ö�ü�����һ����
void FKCW_Base_ResourceLoader::AddBMPFontTask( const string& p_strFntFile, float p_fIdle )
{
	SBMPFontLoadTask* t = new SBMPFontLoadTask();
	t->m_fIdle				= p_fIdle;
	t->m_strName			= p_strFntFile;
	AddLoadTask(t);
}
//-------------------------------------------------------------------------
// ���һ�������ܵ�ͼƬ�����������
void FKCW_Base_ResourceLoader::AddEncrypeBMPFontTask( const string& p_strFntFile, DECRYPT_FUNC p_pDeFunc, float p_fIdle )
{
	SEncryptedBMPFontLoadTask* t = new SEncryptedBMPFontLoadTask();
	t->m_fIdle				= p_fIdle;
	t->m_strName			= p_strFntFile;
	t->m_pDeFunc			= p_pDeFunc;
	AddLoadTask(t);
}
//-------------------------------------------------------------------------
// ���һ��ƽ̨�ַ���strings.xml�ļ���������
void FKCW_Base_ResourceLoader::AddPlatformStringTask( const string& p_strLanguage, const string& p_strPath, bool p_bIsMerge )
{
	SPlatformStringLoadTask* t = new SPlatformStringLoadTask();
	t->m_strLanguage		= p_strLanguage;
	t->m_strPath			= p_strPath;
	t->m_bIsMerge			= p_bIsMerge;
	AddLoadTask(t);
}
//-------------------------------------------------------------------------
// ���һ��ͼƬ�ļ���������
void FKCW_Base_ResourceLoader::AddImageTask( const string& p_strName, float p_fIdle )
{
	SImageLoadTask* t = new SImageLoadTask();
	t->m_fIdle				= p_fIdle;
	t->m_strName			= p_strName;
	AddLoadTask(t);
}
//-------------------------------------------------------------------------
// ���һ�����ܵ�ͼƬ�ļ���������
void FKCW_Base_ResourceLoader::AddEncrypeImageTask( const string& p_strName, DECRYPT_FUNC p_pDeFunc, float p_fIdle )
{
	SEncryptedImageLoadTask* t = new SEncryptedImageLoadTask();
	t->m_fIdle				= p_fIdle;
	t->m_strName			= p_strName;
	t->m_pDeFunc			= p_pDeFunc;
	AddLoadTask(t);
}
//-------------------------------------------------------------------------
// ���һ��zwoptexͼƬ��������
void FKCW_Base_ResourceLoader::AddZwoptexTask( const string& p_strName, float p_fIdle )
{
	SZwoptexLoadTask* t = new SZwoptexLoadTask();
	t->m_fIdle				= p_fIdle;
	t->m_strName			= p_strName;
	AddLoadTask(t);
}
//-------------------------------------------------------------------------
// ���һ�鱻���ܵ�zwoptexͼƬ��������ָ��sprintf��ʽ��
void FKCW_Base_ResourceLoader::AddZwoptexTask( const string& p_strPattern, int p_nStart, int p_nEnd, float p_fIdle )
{
	char buf[512];
	for(int i = p_nStart; i <= p_nEnd; i++) 
	{
		sprintf(buf, p_strPattern.c_str(), i);
		AddZwoptexTask(buf, p_fIdle);
	}
}
//-------------------------------------------------------------------------
// ���һ��zwoptexͼƬ�������������
// ע��plist�ļ���������ܣ�pic���Ա����ܡ����ܺ�������pic�ļ���Ч
void FKCW_Base_ResourceLoader::AddZwoptexTask( const string& p_strPlistName, const string& p_strPicName,
											  DECRYPT_FUNC p_pFunc, float p_fIdle )
{
	SEncryptedZwoptexLoadTask* t = new SEncryptedZwoptexLoadTask();
	t->m_fIdle				= p_fIdle;
	t->m_strPicName			= p_strPicName;
	t->m_strPlistName		= p_strPlistName;
	t->m_pDeFunc			= p_pFunc;
	AddLoadTask(t);
}
//-------------------------------------------------------------------------
// ���һ��zwoptexͼƬ�������������
// ע��plist�ļ���������ܣ�pic���Ա����ܡ����ܺ�������pic�ļ���Ч
void FKCW_Base_ResourceLoader::AddZwoptexTask( const string& p_strPlistPattern, const string& p_PicPattern,
									   int p_nStart, int p_nEnd, DECRYPT_FUNC p_pFunc, float p_fIdle )
{
	char buf1[512], buf2[512];
	for(int i = p_nStart; i <= p_nEnd; i++) 
	{
		sprintf(buf1, p_strPlistPattern.c_str(), i);
		sprintf(buf2, p_PicPattern.c_str(), i);
		AddZwoptexTask(buf1, buf2, p_pFunc, p_fIdle);
	}
}
//-------------------------------------------------------------------------
// ���һ����Ч��������
void FKCW_Base_ResourceLoader::AddCocosDenshionEffectTask( const string& p_strName, float p_fIdle )
{
	SEffectTask* t = new SEffectTask();
	t->m_fIdle				= p_fIdle;
	t->m_strName			= p_strName;
	AddLoadTask(t);
}
//-------------------------------------------------------------------------
// ���һ�����ּ�������
void FKCW_Base_ResourceLoader::AddCocosDenshionMusicTask( const string& p_strName, float p_fIdle )
{
	SMusicTask* t = new SMusicTask();
	t->m_fIdle				= p_fIdle;
	t->m_strName			= p_strName;
	AddLoadTask(t);
}
//-------------------------------------------------------------------------
// ���һ��zwoptex����
// ע��p_nEndIndex ������
// ������p_fUnitDalay �ӳ�ʱ��
// ������p_bIsRestoreOriginalFrame �Ƿ��ڶ���������ʱ�ָ���ʼ֡
void FKCW_Base_ResourceLoader::AddZwoptexAnimTask( const string& p_strName, float p_fUnitDalay, const string& p_strPattern,
										   int p_nStartIndex, int p_nEndIndex, bool p_bIsRestoreOriginalFrame, float p_fIdle )
{
	SZwoptexAnimLoadTask* t = new SZwoptexAnimLoadTask();
	t->m_strName					= p_strName;
	t->m_fUnitDelay					= p_fUnitDalay;
	t->m_bRestorOriginalFrame		= p_bIsRestoreOriginalFrame;
	t->m_fIdle						= p_fIdle;
	char buf[256];
	for(int i = p_nStartIndex; i <= p_nEndIndex; i++) 
	{
		sprintf(buf, p_strPattern.c_str(), i);
		t->m_vecFrames.push_back(buf);
	}
	AddLoadTask(t);
}
//-------------------------------------------------------------------------
// ���һ��zwoptex����
// ע���ö�����������ʼ/����ʱ�䣬���Զ��������������׶�
void FKCW_Base_ResourceLoader::AddZwoptexAnimTask( const string& p_strName, float p_fUnitDalay, const string& p_strPattern,
										   int p_nStartIndex, int p_nEndIndex, int p_nStartIndex2, int p_nEndIndex2, 
										   bool p_bIsRestoreOriginalFrame, float p_fIdle )
{
	SZwoptexAnimLoadTask* t = new SZwoptexAnimLoadTask();
	t->m_strName					= p_strName;
	t->m_fUnitDelay					= p_fUnitDalay;
	t->m_bRestorOriginalFrame		= p_bIsRestoreOriginalFrame;
	t->m_fIdle						= p_fIdle;
	char buf[256];
	for(int i = p_nStartIndex; i <= p_nEndIndex; i++) 
	{
		sprintf(buf, p_strPattern.c_str(), i);
		t->m_vecFrames.push_back(buf);
	}
	for(int i = p_nStartIndex2; i <= p_nEndIndex2; i++) 
	{
		sprintf(buf, p_strPattern.c_str(), i);
		t->m_vecFrames.push_back(buf);
	}
	AddLoadTask(t);
}
//-------------------------------------------------------------------------
// ���һ��zwoptex����
// ע���ö���ÿ֡���ж������ʱ��
void FKCW_Base_ResourceLoader::AddZwoptexAnimTask( const string& p_strName,  const string& p_strPattern, int p_nStartIndex, int p_nEndIndex,
										   const CCArray& p_vecDelays, bool p_bIsRestoreOriginalFrame, float p_fIdle )
{
	SZwoptexHighAnimLoadTask* t = new SZwoptexHighAnimLoadTask();
	t->m_strName					= p_strName;
	t->m_bRestorOriginalFrame		= p_bIsRestoreOriginalFrame;
	t->m_fIdle						= p_fIdle;

	char buf[256];
	for(int i = p_nStartIndex; i <= p_nEndIndex; i++) 
	{
		sprintf(buf, p_strPattern.c_str(), i);
		t->m_vecFrames.push_back(buf);
	}

	CCObject* obj;
	CCARRAY_FOREACH(&p_vecDelays, obj) 
	{
		CCFloat* f = (CCFloat*)obj;
		t->m_vecDelays.push_back(f->getValue());
	}

	AddLoadTask(t);
}
//-------------------------------------------------------------------------
// ���һ�����ع������������ļ�������
// ע��������û���Զ���Ӷ�ӦͼƬ����Ҫ�û����ⴴ�����ض�ӦͼƬ������
void FKCW_Base_ResourceLoader::AddArmatureTask( string p_strConfig, float p_fIdle )
{
	SArmatureLoadTask* t = new SArmatureLoadTask();
	t->m_fIdle						= p_fIdle;
	t->m_strConfigFilePath			= p_strConfig;
	AddLoadTask(t);
}
//-------------------------------------------------------------------------
// ���һ�����ع������������ļ�������
// ע��plist�ļ���config�ļ�����������
void FKCW_Base_ResourceLoader::AddArmatureTask( string p_strPlist, string p_strPic, string p_strConfig,
											   DECRYPT_FUNC p_pDeFunc, float p_fIdle )
{
	if(!p_strPlist.empty() && !p_strPic.empty()) 
	{
		AddZwoptexTask(p_strPlist, p_strPic, p_pDeFunc);
	}

	if(!p_strConfig.empty())
		AddArmatureTask(p_strConfig);
}
//-------------------------------------------------------------------------
// ���һ�����ع������������ļ�������
void FKCW_Base_ResourceLoader::AddArmatureTask( string p_strPlistPattern, string p_strPicPattern, int p_nStartIndex, int p_nEndIndex,
										string p_strConfig, DECRYPT_FUNC p_pDeFunc, float p_fIdle )
{
	char buf1[512], buf2[512];
	for(int i = p_nStartIndex; i <= p_nEndIndex; i++) 
	{
		sprintf(buf1, p_strPlistPattern.c_str(), i);
		sprintf(buf2, p_strPicPattern.c_str(), i);
		AddZwoptexTask(buf1, buf2, p_pDeFunc, p_fIdle);
	}

	if(!p_strConfig.empty())
		AddArmatureTask(p_strConfig);
}
//-------------------------------------------------------------------------