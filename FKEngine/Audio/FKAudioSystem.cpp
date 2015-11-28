//-------------------------------------------------------------------------
#include "FKAudioSystem.h"
#include "SimpleAudioEngine.h"
//-------------------------------------------------------------------------
using namespace CocosDenshion;
//-------------------------------------------------------------------------
IAudioSystem*	gs_pAudioSystem = NULL;
FKAudioSystem	gs_FKAudioSystem;
//-------------------------------------------------------------------------
// ��ȡ��Ƶ�ӿ�
IAudioSystem* GetAudioSystem()
{
	return gs_pAudioSystem;
}
//-------------------------------------------------------------------------
FKAudioSystem::FKAudioSystem()
	: m_fEffectVolume(1.0f)
	, m_fBackgroundMusicVolume(1.0f)
{
	gs_pAudioSystem = this;
}
//-------------------------------------------------------------------------
FKAudioSystem::~FKAudioSystem()
{
	gs_pAudioSystem = NULL;
}
//-------------------------------------------------------------------------
// �ͷ�����
void FKAudioSystem::Release()
{
	SimpleAudioEngine::end();
}
//-------------------------------------------------------------------------
// ���ű�������
void FKAudioSystem::PlayBackgroundMusic(const char* pszFilePath, bool bLoop)
{
	if( pszFilePath == NULL )
		return;

	SimpleAudioEngine::sharedEngine()->playBackgroundMusic( pszFilePath, bLoop );
}
//-------------------------------------------------------------------------
// ֹͣ��������
// ������bReleaseData ֹͣ���ֺ��Ƿ�����������ֻ����ڴ棬Ĭ��ֵΪfalse
void FKAudioSystem::StopBackgroundMusic(bool bReleaseData)
{
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(bReleaseData);
}
//-------------------------------------------------------------------------
// ��ȡ������������
// ����ֵ��	��0.0f, 1.0f��
float FKAudioSystem::GetBackgroundMusicVolume()
{
	return SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume();
}
//-------------------------------------------------------------------------
// ���ñ�����������
// ������	��0.0f, 1.0f��
void FKAudioSystem::SetBackgroundMusicVolume(float volume)
{
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume( volume );
}
//-------------------------------------------------------------------------
// ��ȡ��Ч����
// ����ֵ��	��0.0f, 1.0f��
float FKAudioSystem::GetEffectsVolume()
{
	return SimpleAudioEngine::sharedEngine()->getEffectsVolume();
}
//-------------------------------------------------------------------------
// ������Ч����
// ������	��0.0f, 1.0f��
void FKAudioSystem::SetEffectsVolume(float volume)
{
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(volume);
}
//-------------------------------------------------------------------------
// ������Ч
unsigned int FKAudioSystem::PlayEffect(const char* pszFilePath, bool bLoop)
{
	if( pszFilePath == NULL )
	{
		return 0;
	}

	return SimpleAudioEngine::sharedEngine()->playEffect( pszFilePath, bLoop );
}
//-------------------------------------------------------------------------
// Resumeָ����Ч
// ������PlayEffect���ص�EffectID
void FKAudioSystem::ResumeEffect(unsigned int nSoundId)
{
	SimpleAudioEngine::sharedEngine()->resumeEffect( nSoundId );
}
//-------------------------------------------------------------------------
// Resumeȫ����Ч
void FKAudioSystem::ResumeAllEffects()
{
	SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}
//-------------------------------------------------------------------------
// ָֹͣ����Ч
// ������PlayEffect���ص�EffectID
void FKAudioSystem::StopEffect(unsigned int nSoundId)
{
	SimpleAudioEngine::sharedEngine()->stopEffect( nSoundId );
}
//-------------------------------------------------------------------------
// ֹͣȫ����Ч
void FKAudioSystem::StopAllEffects()
{
	SimpleAudioEngine::sharedEngine()->stopAllEffects();
}
//-------------------------------------------------------------------------
// ϵͳ����
// �������Ƿ���
void FKAudioSystem::MuteAllSounds( bool bMute )
{
	if( bMute )
	{
		m_fEffectVolume = GetEffectsVolume();
		m_fBackgroundMusicVolume = GetBackgroundMusicVolume();
		SetEffectsVolume( 0.0f );
		SetBackgroundMusicVolume( 0.0f );
	}
	else
	{
		SetEffectsVolume( m_fEffectVolume );
		SetBackgroundMusicVolume( m_fBackgroundMusicVolume );
	}
}
//-------------------------------------------------------------------------