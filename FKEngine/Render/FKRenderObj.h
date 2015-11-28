//*************************************************************************
//	��������:	2015-1-17
//	�ļ�����:	FKRenderObj.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../FKEngineCommonHead.h"
#include "FKRenderObjModel.h"
//-------------------------------------------------------------------------
class FKRenderObj : public IRenderObj, public CCNode
{
public:
	FKRenderObj( RENDER_OBJ_ID id );
	~FKRenderObj();
public:
	// ���º���
	virtual void			update( float delta );
	// ��������
	virtual bool			Create( const char* szFKOFileName );
	// �ͷź���
	virtual void			onExit();
public:
	// ��ȡID
	virtual RENDER_OBJ_ID	GetID();
	// �����û�����
	// ������pData �Զ����û�����
	virtual void			SetUserData( void* pData );
	// ��ȡ�û�����
	virtual void*			GetUserData();
	// ��ȡ��Ϸ������ͼ�ļ���
	virtual const std::string&	GetFileName();
	// ��ȡ��Ϸ������������(ȫ��Ψһ�ַ���)
	virtual const std::string&	GetDescName();
	// ���ȫ���ҽӶ��󣬽������ն���
	virtual void			Clear();
	// ��ȫ����
	virtual void			Release();

	// �󶨵�������
	// ������pParentNode ���ڵ�
	// ������nZOrder ���Zֵ
	// ������nTag ��ǩ
	virtual void			Attach( CCNode* pParentNode, int nZOrder, int nTag = 0 );
	// �ӳ������Ƴ�
	// ������bIsRemove �Ƴ����Ƿ����ɾ��
	virtual void			Detach( bool bIsRemove = true );
	// ����λ��
	// ������tagPoint λ��
	virtual void			SetPos( const CCPoint& tagPoint );
	// ��ȡλ��
	// ������[out]tagPoint λ��
	virtual void			GetPos( CCPoint& tagPoint );
	// ����ƫ����
	virtual void			SetOffset( CCPoint& tagPoint );
	// ��ȡƫ����			 
	virtual CCPoint			GetOffset();
	// ������ɫ
	// ������tagColor ��ɫֵ
	virtual void			SetColor( const ccColor3B& tagColor );
	// ����͸����
	// ������byAlpha ͸����[0,255]
	virtual void			SetOpacity( unsigned char byAlpha );
	// ��������
	virtual void			SetScale( CCPoint& tagPoint );
	// �Ƿ�ɼ�
	// ������bIsVisible �Ƿ�ɼ�
	virtual void			IsVisible( bool bIsVisible );
	// �Ƿ�����Update
	virtual void			SetEnableUpdate( bool bIsEnable );

	// ��ײ���
	// ������pt ����
	// ����ֵ��true ��ʾ��ײ��false ��ʾδ��ײ
	virtual bool			HitTest( const CCPoint& pt );
	// ��ײ���
	// ������rt ������
	// ����ֵ��true ��ʾ��ײ��false ��ʾδ��ײ
	virtual bool			HitTest( const CCRect& rt );
	// �����Ƿ���Ա�ѡ��
	// ������bIsEnable �Ƿ�����ѡ�м��
	virtual void			SetEnableSelect( bool bIsEnable );

	// �ҽӶ���
	// ������szLinkObjName ���Ӷ�����
	// ������szLocator �ҽڵ�����
	// ������nDepth ���
	// ������color ��ɫ����
	// ����ֵ���ҽӶ����ID
	virtual RENDER_OBJ_ID	AddLinkObj( const char* szLinkObjName, const char* szLocator,
		int nDepth = 0, ccColor4B color = ccc4(255, 255, 255, 255) );
	// �ҽӶ���
	// ������pRenderObj ���Ӷ���
	// ������szLocator �ҽڵ�����
	// ������nDepth ���
	// ������color ��ɫ����
	// ����ֵ���ҽӶ����ID
	virtual RENDER_OBJ_ID	AddLinkObj( IRenderObj* pRenderObj, const char* szLocator,
		int nDepth = 0, ccColor4B color = ccc4(255, 255, 255, 255) );
	// ɾ��һ���ҽӶ���
	// ������unLinkObjID �ҽӶ����ID
	virtual bool			RemoveLinkObj( RENDER_OBJ_ID unLinkObjID );
	// ɾ��һ���ҽӶ���
	// ������unLinkObjID �ҽӶ����ID
	// ������bIsRemove �Ƿ�ɾ�����ҽڶ���
	virtual IRenderObj*		RemoveLinkObj( RENDER_OBJ_ID unLinkObjID, bool bIsRemove );
	// ɾ��ȫ���ҽӶ���
	virtual void			RemoveAllLinkObj();
	// ��ȡһ���ҽڶ���
	// ������RENDER_OBJ_ID �ҽڶ���ID
	virtual IRenderObj*		GetLinkObjByID( RENDER_OBJ_ID unID );
	// ����һ������
	// ������szPartObjName ����������
	// ������szPartPlaceName ����λ����
	// ������nDepth ���
	virtual void			ChangePart( const char* szPartObjName, const char* szPartPlaceName, int nDepth = 0 );
	// ����һ����Ч
	// ������strEffectName ��Ч��
	// ������strLocatorName �󶨵���
	// ������strEffectFileName ��Ч�ļ���
	// ������tagOffset λ��ƫ����
	// ������color ��ɫֵ
	// ������tagScale ���ű���
	// ������nDepth ���
	virtual void			ChangeEffect( const string& strEffectName, const string& strLocatorName, 
		const string& strEffectFileName, CCPoint& tagOffset, ccColor4B& color, CCPoint& tagScale, int nDepth = 0);

	// ���ö��������ٶ�
	virtual void			SetAnimationSpeed( float fSpeed );
	// ���ö������Żص�
	virtual void			SetAnimationCallback( IAnimationCallback* pCallback, void* pContext );
	// ���Ŷ���������������ֹͣ״̬����Ĭ�ϼ������ţ�Ҳ��ǿ�ƴ�ͷ���ţ�
	// ������szAniName ������
	// ������fSpeed �����ٶ�
	// ������nLoops �����ظ���������Ϊ-1��ʾ����ѭ��
	// ������bIsForceUpdate �Ƿ�ǿ�ƴ�ͷ����
	virtual void			Play( const char* szAniName, float fSpeed = 1.0f, int nLoops = -1, bool bIsForceUpdate = false );
	// ��ͣ��������
	virtual void			Pause();
	// ��ȡ���������б�
	// ������[out]AnimationNameList ���������б�
	virtual void			GetAnimationNames( list<string>& AnimationNameList );

	// ���������Ⱦ����
	// ������pRenderText ������Ⱦ����
	// ������szLocator �ҽڵ�����
	// ������tagOffset �ҽ�ƫ��
	virtual bool			AddLinkRenderText( IRenderText* pRenderText, const char* szLocator,
		const CCPoint& tagOffset );
	// ɾ��������Ⱦ����
	// ������pRenderText ��Ҫɾ����������Ⱦ����
	virtual void			RemveLinkRenderText( IRenderText* pRenderText );

	// ����ģ������
	virtual void			SetObjModel( IRenderObjModel* pObjModel );
	// ��ȡģ������
	virtual IRenderObjModel* GetObjModel();
	// �����Ƿ��ڳ���
	virtual void			SetInScene( bool bIsInScene );
	// �ж��Ƿ��ڳ�����
	virtual bool			IsInScene();
	// �Ƿ�ѡ��
	virtual bool			IsSelected();
public:
	// ��ȡ��������
	FKRenderObjModel::ObjPartMap&		GetParts();
	// ��ȡ�󶨵�����
	FKRenderObjModel::ObjLocatorMap&	GetLocators();
	// ��ȡ��Ч����
	FKRenderObjModel::ObjEffectMap&		GetEffects();
	// ɾ������
	bool RemovePart( const string& strName, bool bRemoveData = true );
	// ɾ���󶨵�
	bool RemoveLocator( const string& strName, bool bRemoveData = true );
	// ɾ����Ч
	bool RemoveEffect( const string& strName, bool bRemoveData = true );
	// ���浽�ļ���
	bool SaveToFile( const string& strFileName );
private:
	// ����������
	void					__CreateParts();
	// ������Ч��
	void					__CreateEffects();
	// ��������
	bool					__CreatePart( FKRenderObjModel::SObjPart& tagPart );
	// ������Ч
	bool					__CreateEffect( FKRenderObjModel::SObjEffect& tagEffect );
private:
	struct SLinkObj
	{
		string			m_strLocator;
		FKRenderObj*	m_pLinkObj;
	};
	typedef map<string, IRenderable*>	ObjPartMap;
	typedef map<string, IRenderable*>	ObjLocatorMap;
	typedef map<string, IRenderable*>	ObjEffectMap;
	typedef map<RENDER_OBJ_ID,SLinkObj> ObjLinkMap;
	typedef set<IRenderText*>			ObjRenderTextSet;

	RENDER_OBJ_ID		m_unID;					// ����ΨһID
	void*				m_pUserData;			// �û�����ָ��
	string				m_strFKOFileName;		// FKO�ļ���
	IRenderable*		m_pRootRenderable;		// ����Ⱦ����

	CCPoint				m_tagPos;				// ��ǰλ��
	CCPoint				m_tagOffset;			// ƫ��λ�ã���������ê��
	FKRenderObjModel*	m_pModel;				// ��ǰ��Ⱦģ��
	string				m_strCurAniName;		// ��ǰ������

	bool				m_bIsNeedUpdate;		// �Ƿ�����֡����
	bool				m_bIsCanbeSelected;		// �Ƿ���Ա�ѡ��
	bool				m_bIsInScene;			// �Ƿ��ڳ�����

	ObjPartMap			m_mapObjParts;			// ���󲿼�
	ObjLocatorMap		m_mapObjLocators;		// �󶨵�
	ObjEffectMap		m_mapObjEffects;		// ��Ч����
	ObjLinkMap			m_mapObjLinks;			// ���Ӷ���
	ObjRenderTextSet	m_setObjRenderTexts;	// ����������Ⱦ����
};