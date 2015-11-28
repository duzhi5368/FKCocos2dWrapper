//*************************************************************************
//	��������:	2015-1-22
//	�ļ�����:	FKAnimateExRes.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../FKEngineCommonHead.h"
//-------------------------------------------------------------------------
// �����ص�����
struct SAnimationCallback
{
	float	m_fCallbackTime;		// �ص��¼�
	string	m_strName;				// �ص�����
	SAnimationCallback()
		: m_fCallbackTime( 0.0f )
	{
		m_strName.clear();
	}
};
//-------------------------------------------------------------------------
// ������Ϣ
struct SAnimate
{
	string	m_strName;				// ������
	float	m_fDelay;				// ������ʱ
	bool	m_bIsFlipX;				// �Ƿ�X��Գ�
	bool	m_bIsFlipY;				// �Ƿ�Y��Գ�
	vector<string>	m_vecSpriteFrame;	// ���鶯��֡
	SAnimate()
		: m_fDelay( 0.0f )
		, m_bIsFlipX( false )
		, m_bIsFlipY( false )
	{
		m_strName.clear();
		m_vecSpriteFrame.clear();
	}
};
//-------------------------------------------------------------------------
// ������
class FKAnimateSaxDelegator : public CCSAXDelegator
{
public:
	enum ENUM_State
	{
		eState_None		= 0,
		eState_Plist,
		eState_Animation,
		eState_Name,
		eState_Delay,
		eState_FlipX,
		eState_FlipY,
		eState_Sprite_Frame,
	};
public:
	virtual void startElement(void *ctx, const char *name, const char **atts) ;
	virtual void endElement(void *ctx, const char *name) ;
	virtual void textHandler(void *ctx, const char *s, int len) ;
public:
	vector<string>		m_vecPlists;		// ȫ����Plist�б�����
	vector<SAnimate>	m_vecAnimates;		// ȫ���Ķ���������
	ENUM_State			m_eCurState;		// ��ǰ����ı�ǩ״̬
};
//-------------------------------------------------------------------------
class FKAnimateExRes : public CCObject
{
public:
	// ������Ϣ
	struct SAnimationInfo
	{
		CCAnimation*	m_pAnimation;
		bool			m_bIsFlipX;
		bool			m_bIsFlipY;
		vector<SAnimationCallback>	m_vecCallbacks;

		SAnimationInfo()
			: m_pAnimation( NULL )
			, m_bIsFlipY( false )
			, m_bIsFlipX( false )
		{
			m_vecCallbacks.clear();
		}
	};
public:
	FKAnimateExRes();
	~FKAnimateExRes();
public:
	// �ͷ�
	virtual void		release();
public:
	// ����һ����Դ
	bool				LoadRes( const char* szResName );
	// ��ȡ��Դ����
	const string&		GetResFileName();
	// ��ȡ��������
	SAnimationInfo*		GetAnimation( const char* szAnimationName );
	// ��ȡ�������б�
	set<string>&		GetAniNameList();
	// �ж���Դ�Ƿ�ȫ��˳������
	bool				IsValid();
protected:
	// ���ػص�����
	void				_LoadCallback( const char* szResName );
	// ������ͼ
	void				_LoadTextureAsync( const char* szResName );
	// ������Դ
	void				_LoadRes( const char* szResName );
	// ͼƬ������ϻص�
	void				_OnImageLoadOver( CCObject* pObj );
private:
	typedef map<string, SAnimationInfo>		AnimationMap;	// �����б�
	typedef map<string, bool>				PlistTextureMap;// ��ͼ�Ƿ���سɹ���ʾ

	bool							m_bIsVaild;				// �Ƿ���Դȫ���������
	string							m_strAniResName;		// ������Դ��

	map<string, SAnimate>			m_mapAnimateNameToAnimate;
	map<string, vector<string> >	m_mapXMLPathToPlists;
	set<string>						m_setAnimationName;		// �����б�
	PlistTextureMap					m_mapTextureLoadInfo;	// ��Դ����״��
	AnimationMap					m_mapAnimation;			// �����б�

	CCSAXParser						m_SaxParser;			// xml������
	FKAnimateSaxDelegator			m_SaxDelegator;			// �Զ���xml������
};