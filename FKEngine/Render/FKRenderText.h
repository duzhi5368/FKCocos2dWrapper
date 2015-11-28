//*************************************************************************
//	��������:	2015-1-18
//	�ļ�����:	FKRenderText.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../FKEngineCommonHead.h"
//-------------------------------------------------------------------------
class FKRenderText : public IRenderText
{
public:
	FKRenderText( RENDER_OBJ_ID unID );
	~FKRenderText();
public:
	// ��������
	bool				Create( const char* szString, const char* szFontName, 
		int nFontSize,  CCSize tagDimentions );
	// ����BMP����
	bool				CreateByBMP( const char* szString, const char* szFontName, 
		int nFontSize,  CCSize tagDimentions );
public:
	// ��ȡID
	virtual RENDER_OBJ_ID	GetID();
	// �ͷ�
	virtual void		Release();
	// �󶨵�������
	virtual bool		Attach( CCNode* pParentNode, int nZOrder, int nTag = 0 );
	// �ӳ����н��
	virtual void		Detach();
	// ����λ��
	virtual void		SetPos( const CCPoint& tagPos );
	// �����ַ���
	virtual void		SetString( const char* szText );
	// ������ɫ
	virtual void		SetColor( const ccColor3B& color );
	// ����͸����
	virtual	void		SetOpacity( unsigned char byAlpha );
	// ���������ʽ
	virtual void		SetFont( const char* szFont );
	// ������ʾ����
	virtual void		SetDeimensions( const CCSize& tagDeimensions );
	// ��������ˮƽ���뷽ʽ
	virtual void		SetHorizontalAlignment( ENUM_TextHorizontalAlignment eType );
	// �������ִ�ֱ���뷽ʽ
	virtual void		SetVerticalAlignment( ENUM_TextVerticalAlignment eType );
private:
	RENDER_OBJ_ID		m_unID;			// ����ID
	CCLabelTTF*			m_pLabelTTF;	// �������
	CCLabelBMFont*		m_pLabelBMP;	// �������
	string				m_strContent;	// ��������
	CCPoint				m_tagPos;		// ����ڸ��ڵ��λ��
	CCNode*				m_pParent;		// ���ڵ�
	CCSize				m_tagDimentions;// ��ʾ����
	ccColor3B			m_tagColor;		// ��ʾ��ɫ
	unsigned char		m_byAlpha;		// ͸����
	ENUM_TextHorizontalAlignment m_eHA;	// ˮƽ���뷽ʽ
	ENUM_TextVerticalAlignment	 m_eVA; // ��ֱ���뷽ʽ
};