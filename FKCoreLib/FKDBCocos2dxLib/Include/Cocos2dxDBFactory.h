//*************************************************************************
//	��������:	2014-8-19   17:31
//	�ļ�����:	Cocos2dxDBFactory.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "CommonHead.h"
//-------------------------------------------------------------------------
#pragma warning ( disable : 4251 )
//-------------------------------------------------------------------------
class CCocos2dxDBFactory : public CBaseFactory
{
public:
	CCocos2dxDBFactory();
	virtual ~CCocos2dxDBFactory();
public:
	static CCocos2dxDBFactory*	GetInstance();
	static void					DestroyInstance();
public:
	ITextureAtlas*	GenerateTextureAtlas( IObject* p_pContent, CTextureAtlasData* p_pTextureAtlasData );
	CArmature*		GenerateArmature( const string& p_szPicName );
	CSlot*			GenerateSlot();
	IObject*		GenerateDisplay( ITextureAtlas* p_pTextureAtlas, const string& p_szFullName, f32 p_fPivotX, f32 p_fPivotY );
	void			LoadSkeletonFile( const string& p_szSkeletonFile, const string& p_szName = "" );
	void			LoadTextureAtlasFile( const string& p_szTextureAtlasFile, const string& p_szName = "");
protected:
	static			CCocos2dxDBFactory*		ms_Cocos2dxDBFactory;
};
//-------------------------------------------------------------------------