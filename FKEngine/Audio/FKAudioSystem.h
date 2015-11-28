//*************************************************************************
//	��������:	2015-1-9
//	�ļ�����:	FKAudioSystem.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../FKEngineCommonHead.h"
//-------------------------------------------------------------------------
class FKAudioSystem : public IAudioSystem
{
public:
	FKAudioSystem();
	~FKAudioSystem();
public:
	// �ͷ�����
	virtual void			Release();
	// ���ű�������
	virtual void			PlayBackgroundMusic(const char* pszFilePath, bool bLoop);
	// ֹͣ��������
	// ������bReleaseData ֹͣ���ֺ��Ƿ�����������ֻ����ڴ棬Ĭ��ֵΪfalse
	virtual void			StopBackgroundMusic(bool bReleaseData);
	// ��ȡ������������
	// ����ֵ��	��0.0f, 1.0f��
	virtual float			GetBackgroundMusicVolume();
	// ���ñ�����������
	// ������	��0.0f, 1.0f��
	virtual void			SetBackgroundMusicVolume(float volume);
	// ��ȡ��Ч����
	// ����ֵ��	��0.0f, 1.0f��
	virtual float			GetEffectsVolume();
	// ������Ч����
	// ������	��0.0f, 1.0f��
	virtual void			SetEffectsVolume(float volume);
	// ������Ч
	virtual unsigned int	PlayEffect(const char* pszFilePath, bool bLoop);
	// Resumeָ����Ч
	// ������PlayEffect���ص�EffectID
	virtual void			ResumeEffect(unsigned int nSoundId);
	// Resumeȫ����Ч
	virtual void			ResumeAllEffects();
	// ָֹͣ����Ч
	// ������PlayEffect���ص�EffectID
	virtual void			StopEffect(unsigned int nSoundId);
	// ֹͣȫ����Ч
	virtual void			StopAllEffects();
	// ϵͳ����
	// �������Ƿ���
	virtual void			MuteAllSounds( bool bMute );
private:
	float					m_fEffectVolume;			// ��Ч����
	float					m_fBackgroundMusicVolume;	// ������������
};
//-------------------------------------------------------------------------
extern FKAudioSystem gs_FKAudioSystem;
//-------------------------------------------------------------------------