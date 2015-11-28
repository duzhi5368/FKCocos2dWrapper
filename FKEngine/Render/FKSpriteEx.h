//*************************************************************************
//	��������:	2015-1-21
//	�ļ�����:	FKSpriteEx.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../FKEngineCommonHead.h"
//-------------------------------------------------------------------------
/*
	��Դ�첽���ؾ��顣
	��������Զ���shader�Լ�FKCW_Shader�ľ��顣
	�����Զ������˳��ľ��顣
	���Լ������FKCW_EffectNodeЧ���ľ��顣
*/
class FKSpriteEx : public CCSprite
{
public:
	FKSpriteEx();
	~FKSpriteEx();
public:
	static FKSpriteEx* Create();
	static FKSpriteEx* Create(const char *pszFileName);
	static FKSpriteEx* Create(const char *pszFileName, const CCRect& rect);
public:
	virtual void draw();
	virtual bool init();
	virtual bool initWithFile(const char *pszFilename);
	virtual bool initWithFile(const char *pszFilename, const CCRect& rect);
protected:
	// �첽��Դ�������
	void		_OnImageLoadOver( CCObject* Sender );
private:
	bool			m_bIsVailed;		// �����Ƿ���Ч���Ƿ���Դ������ϣ�
	CCRect			m_tagRect;			// ��������  
};