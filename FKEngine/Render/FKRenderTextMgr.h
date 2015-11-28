//*************************************************************************
//	��������:	2015-1-19
//	�ļ�����:	FKRenderTextMgr.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKRenderText.h"
//-------------------------------------------------------------------------
class FKRenderTextMgr
{
public:
	FKRenderTextMgr();
	~FKRenderTextMgr();
public:
	// ������Ⱦ����
	// ������szString ����
	// ������szFontName ��������
	// ������nFontSize �����С
	// ������tagDimentions ����ߴ�
	// ������bIsBmpFont �Ƿ���BMP����
	IRenderText*	CreateRenderText( const char* szString, const char* szFontName, 
		int nFontSize,  CCSize tagDimentions, bool bIsBMPFont = false );
	// ɾ����Ⱦ����
	// ������pRenderText ��Ҫɾ������Ⱦ����
	bool			RemoveRenderText( IRenderText* pRenderText );
	// ɾ����Ⱦ����
	// ������id ΨһID
	bool			RemoveRenderTextByID( RENDER_OBJ_ID id );
private:
	typedef map< RENDER_OBJ_ID, IRenderText* >		RenderTextMap;
	RenderTextMap					m_mapRenderText;
};