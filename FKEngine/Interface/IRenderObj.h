//*************************************************************************
//	��������:	2015-1-17
//	�ļ�����:	IRenderObj.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../../FKCWLib/FKCocos2dxWrapper.h"
//-------------------------------------------------------------------------
// ��Ⱦ����ID
typedef unsigned int	RENDER_OBJ_ID;
//-------------------------------------------------------------------------
class IAnimationCallback;
class IRenderText;
class IRenderObjModel;
class IRenderObj
{
public:
	// ��ȡID
	virtual RENDER_OBJ_ID	GetID() = 0;
	// �����û�����
	// ������pData �Զ����û�����
	virtual void			SetUserData( void* pData ) = 0;
	// ��ȡ�û�����
	virtual void*			GetUserData() = 0;
	// ��ȡ��Ϸ������ͼ�ļ���
	virtual const std::string&	GetFileName() = 0;
	// ��ȡ��Ϸ������������(ȫ��Ψһ�ַ���)
	virtual const std::string&	GetDescName() = 0;
	// ���ȫ���ҽӶ��󣬽������ն���
	virtual void			Clear() = 0;
	// ��ȫ����
	virtual void			Release() = 0;

	// �󶨵�������
	// ������pParentNode ���ڵ�
	// ������nZOrder ���Zֵ
	// ������nTag ��ǩ
	virtual void			Attach( CCNode* pParentNode, int nZOrder, int nTag = 0 ) = 0;
	// �ӳ������Ƴ�
	// ������bIsRemove �Ƴ����Ƿ����ɾ��
	virtual void			Detach( bool bIsRemove = true ) = 0;
	// ����λ��
	// ������tagPoint λ��
	virtual void			SetPos( const CCPoint& tagPoint ) = 0;
	// ��ȡλ��
	// ������[out]tagPoint λ��
	virtual void			GetPos( CCPoint& tagPoint ) = 0;
	// ����ƫ����
	virtual void			SetOffset( CCPoint& tagPoint ) = 0;
	// ��ȡƫ����			 
	virtual CCPoint			GetOffset() = 0;
	// ������ɫ
	// ������tagColor ��ɫֵ
	virtual void			SetColor( const ccColor3B& tagColor ) = 0;
	// ����͸����
	// ������byAlpha ͸����[0,255]
	virtual void			SetOpacity( unsigned char byAlpha ) = 0;
	// ��������
	virtual void			SetScale( CCPoint& tagPoint ) = 0;
	// �Ƿ�ɼ�
	// ������bIsVisible �Ƿ�ɼ�
	virtual void			IsVisible( bool bIsVisible ) = 0;
	// �Ƿ�����Update
	virtual void			SetEnableUpdate( bool bIsEnable ) = 0;

	// ��ײ���
	// ������pt ����
	// ����ֵ��true ��ʾ��ײ��false ��ʾδ��ײ
	virtual bool			HitTest( const CCPoint& pt ) = 0;
	// ��ײ���
	// ������rt ������
	// ����ֵ��true ��ʾ��ײ��false ��ʾδ��ײ
	virtual bool			HitTest( const CCRect& rt ) = 0;
	// �����Ƿ���Ա�ѡ��
	// ������bIsEnable �Ƿ�����ѡ�м��
	virtual void			SetEnableSelect( bool bIsEnable ) = 0;

	// �ҽӶ���
	// ������szLinkObjName ���Ӷ�����
	// ������szLocator �ҽڵ�����
	// ������nDepth ���
	// ������color ��ɫ����
	// ����ֵ���ҽӶ����ID
	virtual RENDER_OBJ_ID	AddLinkObj( const char* szLinkObjName, const char* szLocator,
		int nDepth = 0, ccColor4B color = ccc4(255, 255, 255, 255) ) = 0;
	// �ҽӶ���
	// ������pRenderObj ���Ӷ���
	// ������szLocator �ҽڵ�����
	// ������nDepth ���
	// ������color ��ɫ����
	// ����ֵ���ҽӶ����ID
	virtual RENDER_OBJ_ID	AddLinkObj( IRenderObj* pRenderObj, const char* szLocator,
		int nDepth = 0, ccColor4B color = ccc4(255, 255, 255, 255) ) = 0;
	// ɾ��һ���ҽӶ���
	// ������unLinkObjID �ҽӶ����ID
	virtual bool			RemoveLinkObj( RENDER_OBJ_ID unLinkObjID ) = 0;
	// ɾ��һ���ҽӶ���
	// ������unLinkObjID �ҽӶ����ID
	// ������bIsRemove �Ƿ�ɾ�����ҽڶ���
	virtual IRenderObj*		RemoveLinkObj( RENDER_OBJ_ID unLinkObjID, bool bIsRemove ) = 0;
	// ɾ��ȫ���ҽӶ���
	virtual void			RemoveAllLinkObj() = 0;
	// ��ȡһ���ҽڶ���
	// ������RENDER_OBJ_ID �ҽڶ���ID
	virtual IRenderObj*		GetLinkObjByID( RENDER_OBJ_ID unID ) = 0;
	// ����һ������
	// ������szPartObjName ����������
	// ������szPartPlaceName ����λ����
	// ������nDepth ���
	virtual void			ChangePart( const char* szPartObjName, 
		const char* szPartPlaceName, int nDepth = 0 ) = 0;
	// ����һ����Ч
	// ������strEffectName ��Ч��
	// ������strLocatorName �󶨵���
	// ������strEffectFileName ��Ч�ļ���
	// ������tagOffset λ��ƫ����
	// ������color ��ɫֵ
	// ������tagScale ���ű���
	// ������nDepth ���
	virtual void			ChangeEffect( const string& strEffectName, const string& strLocatorName, 
		const string& strEffectFileName, CCPoint& tagOffset, ccColor4B& color, CCPoint& tagScale, int nDepth = 0 ) = 0;

	// ���ö��������ٶ�
	virtual void			SetAnimationSpeed( float fSpeed ) = 0;
	// ���ö������Żص�
	virtual void			SetAnimationCallback( IAnimationCallback* pCallback, void* pContext ) = 0;
	// ���Ŷ���������������ֹͣ״̬����Ĭ�ϼ������ţ�Ҳ��ǿ�ƴ�ͷ���ţ�
	// ������szAniName ������
	// ������fSpeed �����ٶ�
	// ������nLoops �����ظ���������Ϊ-1��ʾ����ѭ��
	// ������bIsForceUpdate �Ƿ�ǿ�ƴ�ͷ����
	virtual void			Play( const char* szAniName, float fSpeed = 1.0f, int nLoops = -1, bool bIsForceUpdate = false ) = 0;
	// ��ͣ��������
	virtual void			Pause() = 0;
	// ��ȡ���������б�
	// ������[out]AnimationNameList ���������б�
	virtual void			GetAnimationNames( list<string>& AnimationNameList ) = 0;

	// ���������Ⱦ����
	// ������pRenderText ������Ⱦ����
	// ������szLocator �ҽڵ�����
	// ������tagOffset �ҽ�ƫ��
	virtual bool			AddLinkRenderText( IRenderText* pRenderText, const char* szLocator,
		const CCPoint& tagOffset ) = 0;
	// ɾ��������Ⱦ����
	// ������pRenderText ��Ҫɾ����������Ⱦ����
	virtual void			RemveLinkRenderText( IRenderText* pRenderText ) = 0;

	// ����ģ������
	virtual void			SetObjModel( IRenderObjModel* pObjModel ) = 0;
	// ��ȡģ������
	virtual IRenderObjModel* GetObjModel() = 0;
	// �����Ƿ��ڳ���
	virtual void			SetInScene( bool bIsInScene ) = 0;
	// �ж��Ƿ��ڳ�����
	virtual bool			IsInScene() = 0;
	// �Ƿ�ѡ��
	virtual bool			IsSelected() = 0;
};