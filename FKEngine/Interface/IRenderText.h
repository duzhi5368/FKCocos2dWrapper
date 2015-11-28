//*************************************************************************
//	��������:	2015-1-17
//	�ļ�����:	IRenderText.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../../FKCWLib/FKCocos2dxWrapper.h"
//-------------------------------------------------------------------------
// ���ֶ��뷽ʽ
enum ENUM_TextHorizontalAlignment
{
	eTHA_Left,				// �����
	eTHA_Center,			// ���Ķ���
	eTHA_Right,				// �Ҷ���
};
enum ENUM_TextVerticalAlignment
{
	eTVA_Top,				// ���˶���
	eTVA_Center,			// ���Ķ���
	eTVA_Bottom,			// �ײ�����
};
//-------------------------------------------------------------------------
class IRenderText
{
public:
	// �ͷ�
	virtual void		Release() = 0;
	// �󶨵�������
	virtual bool		Attach( CCNode* pParentNode, int nZOrder, int nTag = 0 ) = 0;
	// �ӳ����н��
	virtual void		Detach() = 0;
	// ����λ��
	virtual void		SetPos( const CCPoint& tagPos ) = 0;
	// �����ַ���
	virtual void		SetString( const char* szText ) = 0;
	// ������ɫ
	virtual void		SetColor( const ccColor3B& color ) = 0;
	// ����͸����
	virtual	void		SetOpacity( unsigned char byAlpha ) = 0;
	// ���������ʽ
	virtual void		SetFont( const char* szFont ) = 0;
	// ������ʾ����
	virtual void		SetDeimensions( const CCSize& tagDeimensions ) = 0;
	// ��������ˮƽ���뷽ʽ
	virtual void		SetHorizontalAlignment( ENUM_TextHorizontalAlignment eType ) = 0;
	// �������ִ�ֱ���뷽ʽ
	virtual void		SetVerticalAlignment( ENUM_TextVerticalAlignment eType ) = 0;
};