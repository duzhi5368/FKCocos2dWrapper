//*************************************************************************
//	��������:	2015-1-22
//	�ļ�����:	FKDBSpriteObj.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../FKEngineCommonHead.h"
#include "../../FKCoreLib/FKDBCocos2dxLib/FKDBCocos2dxLib.h"
//-------------------------------------------------------------------------
class FKDBSpriteObj : public IDragonBonesSprite
{
public:
	FKDBSpriteObj( RENDER_OBJ_ID id );
	~FKDBSpriteObj();
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
private:
	CCocos2dxDBSprite*			m_pSprite;				// ʵ��DB����
	RENDER_OBJ_ID				m_unID;
	string						m_strFileName;
	string						m_strDescName;
};