//*************************************************************************
//	��������:	2014-8-19   19:57
//	�ļ�����:	Cocos2dxDBDisplayBridge.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "CommonHead.h"
//-------------------------------------------------------------------------
USING_NS_CC;
//-------------------------------------------------------------------------
class CCocos2dxDBObj;
class CCocos2dxDBDisplayBridge : public IDisplayBridge
{
public:
	CCocos2dxDBDisplayBridge();
	virtual ~CCocos2dxDBDisplayBridge();
public:
	virtual bool		GetVisible();
	virtual void		SetVisible( bool p_bVisible );
	virtual IObject*	GetDisplay();
	virtual void		SetDisplay( IObject* p_pValue );
	virtual void		Clear();
	virtual void		UpdateTransform( CMatrix& p_Matrix, CTransform& p_Transform );
	virtual void		UpdateColor( f32 p_fA, f32 p_fR, f32 p_fG, f32 p_fB, 
		f32 p_fAMultiplier, f32 p_fRMultiplier, f32 p_fGMultiplier, f32 p_fBMultiplier );
	virtual void		UpdateBlendMode( const string& p_szBlendMode );
	virtual void		AddDisplay( IObject* p_pObject, int p_nIndex = -1 );
	virtual void		RemoveDisplay();
protected:
	IObject*			m_pDisplay;
	CCocos2dxDBObj*		m_pDisplayNode;
};
//-------------------------------------------------------------------------