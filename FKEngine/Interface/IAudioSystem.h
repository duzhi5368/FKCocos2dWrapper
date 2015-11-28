//*************************************************************************
//	��������:	2015-1-9
//	�ļ�����:	IAudioSystem.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	��Ƶģ��ӿ�
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
/*
	�ⶫ��ûʲô��˵���˰�...
*/
//-------------------------------------------------------------------------
// ��Ƶģ��ӿ�
class IAudioSystem
{
public:
	// �ͷ�����
	virtual void			Release() = 0;

	// ���ű�������
	virtual void			PlayBackgroundMusic(const char* pszFilePath, bool bLoop) = 0;

	// ֹͣ��������
	// ������bReleaseData ֹͣ���ֺ��Ƿ�����������ֻ����ڴ棬Ĭ��ֵΪfalse
    virtual void			StopBackgroundMusic(bool bReleaseData) = 0;

	// ��ȡ������������
	// ����ֵ��	��0.0f, 1.0f��
	virtual float			GetBackgroundMusicVolume() = 0;

	// ���ñ�����������
	// ������	��0.0f, 1.0f��
    virtual void			SetBackgroundMusicVolume(float volume) = 0;

	// ��ȡ��Ч����
	// ����ֵ��	��0.0f, 1.0f��
    virtual float			GetEffectsVolume() = 0;

	// ������Ч����
	// ������	��0.0f, 1.0f��
    virtual void			SetEffectsVolume(float volume) = 0;

	// ������Ч
    virtual unsigned int	PlayEffect(const char* pszFilePath, bool bLoop) = 0;

	// Resumeָ����Ч
	// ������PlayEffect���ص�EffectID
    virtual void			ResumeEffect(unsigned int nSoundId) = 0;

	// Resumeȫ����Ч
    virtual void			ResumeAllEffects() = 0;

	// ָֹͣ����Ч
	// ������PlayEffect���ص�EffectID
    virtual void			StopEffect(unsigned int nSoundId) = 0;

	// ֹͣȫ����Ч
    virtual void			StopAllEffects() = 0;

	// ϵͳ����
	// �������Ƿ���
	virtual void			MuteAllSounds( bool bMute ) = 0;
};
//-------------------------------------------------------------------------
// ��ȡ��Ƶ�ӿ�
extern IAudioSystem* GetAudioSystem();
//-------------------------------------------------------------------------