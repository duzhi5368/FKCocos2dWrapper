//*************************************************************************
//	��������:	2015-1-17
//	�ļ�����:	IRenderable.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../../FKCWLib/FKCocos2dxWrapper.h"
#include "IRenderObj.h"
#include "../../FKCoreLib/FKDBLib/Interface/IAnimation.h"
//-------------------------------------------------------------------------
// ��Ⱦ��������
enum ENUM_RenderObjType
{
	eROT_Sprite		= 0,		// ��ͨ�ľ�̬�������
	eROT_DB			= 1,		// DragonBones��������
	eROT_Effect		= 2,		// ��Ч����
	eROT_Ani		= 3,		// ��ͳ֡��������
	eROT_Armature	= 4,		// cocosStudio��������

	eROT_Max,
};
//-------------------------------------------------------------------------
class IEffectProp;
class IRenderable : public CCNode
{
public:
	// ��ȡ��Ⱦ��������
	virtual ENUM_RenderObjType	GetRenderObjType() = 0;
	// ��ȡID
	virtual RENDER_OBJ_ID		GetID() = 0;
	// ����ID
	virtual void				SetID( RENDER_OBJ_ID unID ) = 0;

	// ������ɫ
	// ������tagColor ��ɫֵ
	virtual void				SetColor( const ccColor3B& tagColor ) = 0;
	// ����͸����
	// ������byAlpha ͸����[0,255]
	virtual void				SetOpacity( unsigned char byAlpha ) = 0;
	// ��ȡ��Ϸ������ͼ�ļ���
	virtual const std::string&	GetFileName() = 0;
	// ��ȡ��Ϸ������������(ȫ��Ψһ�ַ���)
	virtual const std::string&	GetDescName() = 0;

	// ��ײ���
	// ������pt ����
	// ����ֵ��true ��ʾ��ײ��false ��ʾδ��ײ
	virtual bool				HitTest( const CCPoint& pt ) = 0;
	// ��ײ���
	// ������rt ������
	// ����ֵ��true ��ʾ��ײ��false ��ʾδ��ײ
	virtual bool				HitTest( const CCRect& rt ) = 0;
	// ��ȡ�����Χ��
	virtual bool				GetBoundingBox( CCRect& rt ) = 0;
	// ����ƫ����
	virtual void				SetOffset( CCPoint& ptOffset ) = 0;
	// ��ȡƫ����
	virtual bool				GetOffset( CCPoint& ptOffset ) = 0;

	// ��ȡ����
	virtual CCSprite*			GetSprite() = 0;
	// ��ȡ��������
	virtual IAnimation*			GetAnimation() = 0;
	// ��ȡ��Ч����
	virtual IEffectProp*		GetEffectProp() = 0;
};
//-------------------------------------------------------------------------
// ��̬�������
class ISprite : public IRenderable
{
public:
	// ��ȡ��Ⱦ��������
	virtual ENUM_RenderObjType	GetRenderObjType(){ return eROT_Sprite; }
	// ��ȡ��������
	virtual IAnimation*			GetAnimation(){return NULL;};
	// ��ȡ��Ч����
	virtual IEffectProp*		GetEffectProp(){return NULL;};
};
//-------------------------------------------------------------------------
// DB��������
class IDragonBonesSprite : public IRenderable
{
public:
	// ��ȡ��Ⱦ��������
	virtual ENUM_RenderObjType	GetRenderObjType(){ return eROT_DB; }
	// ��ȡ����
	virtual CCSprite*			GetSprite(){return NULL;};
	// ��ȡ��Ч����
	virtual IEffectProp*		GetEffectProp(){return NULL;};
};
//-------------------------------------------------------------------------
// ֡��������
class IFrameSprite : public IRenderable
{
public:
	// ��ȡ��Ⱦ��������
	virtual ENUM_RenderObjType	GetRenderObjType(){ return eROT_Ani; }
	// ��ȡ��Ч����
	virtual IEffectProp*		GetEffectProp(){return NULL;};
};
//-------------------------------------------------------------------------
// cocosBuilder������������
class IArmatureSprite : public IRenderable
{
public:
	// ��ȡ��Ⱦ��������
	virtual ENUM_RenderObjType	GetRenderObjType(){ return eROT_Armature; }
	// ��ȡ����
	virtual CCSprite*			GetSprite(){return NULL;};
	// ��ȡ��Ч����
	virtual IEffectProp*		GetEffectProp(){return NULL;};
};
//-------------------------------------------------------------------------
// ��Ч����
class IEffect : public IRenderable
{
public:
	// ��ȡ��Ⱦ��������
	virtual ENUM_RenderObjType	GetRenderObjType(){ return eROT_Effect; }
	// ��ȡ����
	virtual CCSprite*			GetSprite(){return NULL;};
	// ��ȡ��������
	virtual IAnimation*			GetAnimation(){return NULL;};
};
//-------------------------------------------------------------------------