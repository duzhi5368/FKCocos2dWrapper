//*************************************************************************
//	��������:	2015-1-3
//	�ļ�����:	FKCW_Story_Layer.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_Story_Macros.h"
//-------------------------------------------------------------------------
class FKCW_Story_Player;
class FKCW_Story_Layer : public CCLayer 
{
	friend class FKCW_Story_Player;

private:
	FKCW_Story_Player* m_player;		// ��Ա			
	bool m_playing;						// �Ƿ�����update
	vector<string> m_loadedImageFiles;	// �Ѽ��ص�ͼƬ

protected:
	FKCW_Story_Layer();

	// ���½����ٵ�
	void onStoryDone();
	// ж���Ѽ��ص�ͼƬ
	void unloadImageFiles();

public:
	virtual ~FKCW_Story_Layer();
	static FKCW_Story_Layer* create();

	// ȫ�ֲ���
	static string getParameter(const string& key);
	static void setParameter(const string& key, const string& value);

	virtual bool init();
	virtual void onExit();
	virtual void onEnter();

	// ���ļ���Ԥ����һ�����½ű�
	bool preloadStoryFile(const string& storyScriptFile,DECRYPT_FUNC decFunc = NULL);
	// Ԥ����һ�ι��½ű��ַ���
	bool preloadStoryString(const string& storyScript);

	// ��ʼ���й��²���
	void playStory();
	// ����ֹͣ����
	void stopPlay();

	// ������ɵĻص�����
	CC_SYNTHESIZE_RETAIN(CCCallFunc*, m_doneFunc, DoneFunction);
	// ��ѹ��Դ�Ľ�ѹ����
	CC_SYNTHESIZE(DECRYPT_FUNC, m_decFunc, DecryptFunction);
};
//-------------------------------------------------------------------------