//*************************************************************************
//	��������:	2015-1-22
//	�ļ�����:	FKFrameSpriteObj.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../FKEngineCommonHead.h"
#include "FKAnimateEx.h"
//-------------------------------------------------------------------------
class FKFrameSpriteObj : public IFrameSprite
{
public:
	FKFrameSpriteObj( RENDER_OBJ_ID id );
	~FKFrameSpriteObj();
public:
	// ����FKSprite����
	bool Create( const char* szPicFileName, CCPoint ptOffset = CCPointZero );
	// ����
	virtual void				update( float dt );
	// �뿪�˳�
	virtual void				onExit();
public:
	// ��ȡID
	virtual RENDER_OBJ_ID		GetID();
	// ����ID
	virtual void				SetID( RENDER_OBJ_ID unID );

	// ������ɫ
	// ������tagColor ��ɫֵ
	virtual void				SetColor( const ccColor3B& tagColor );
	// ����͸����
	// ������byAlpha ͸����[0,255]
	virtual void				SetOpacity( unsigned char byAlpha );
	// ��ȡ��Ϸ������ͼ�ļ���
	virtual const std::string&	GetFileName();
	// ��ȡ��Ϸ������������(ȫ��Ψһ�ַ���)
	virtual const std::string&	GetDescName();

	// ��ײ���
	// ������pt ����
	// ����ֵ��true ��ʾ��ײ��false ��ʾδ��ײ
	virtual bool				HitTest( const CCPoint& pt );
	// ��ײ���
	// ������rt ������
	// ����ֵ��true ��ʾ��ײ��false ��ʾδ��ײ
	virtual bool				HitTest( const CCRect& rt );
	// ��ȡ�����Χ��
	virtual bool				GetBoundingBox( CCRect& rt );
	// ����ƫ����
	virtual void				SetOffset( CCPoint& ptOffset );
	// ��ȡƫ����
	virtual bool				GetOffset( CCPoint& ptOffset );

	// ��ȡ��������
	virtual IAnimation*			GetAnimation();
	// ��ȡ����
	virtual CCSprite*			GetSprite();
private:
	RENDER_OBJ_ID				m_unID;				// ����ID
	CCSprite*					m_pSprite;			// �������
	string						m_strPicFileName;	// ��ͼ�ļ���
	FKAnimateEx					m_Animate;			// ����
};