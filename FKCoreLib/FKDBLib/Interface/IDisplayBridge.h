//*************************************************************************
//	��������:	2014-8-13   16:52
//	�ļ�����:	IDisplayBridge.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../Include/BaseMacro.h"
#include "../Include/Object.h"
#include "../Include/Matrix.h"
#include "../Include/Transform.h"
#include <string>
using std::string;
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------

class IDisplayBridge
{
public:
	IDisplayBridge(){}
	virtual ~IDisplayBridge(){}
public:
	// �Ƿ�ɼ�
	virtual bool		GetVisible() = 0;
	virtual void		SetVisible( bool p_bVisible ) = 0;

	virtual IObject*	GetDisplay() = 0;
	virtual void		SetDisplay( IObject* p_pValue ) = 0;
	virtual void		AddDisplay( IObject* p_pObject, int p_nIndex = -1 ) = 0;
	virtual void		RemoveDisplay() = 0;

	// ����Ⱦ������о���ת��
	virtual void		UpdateTransform( CMatrix& p_Matrix, CTransform& p_Transform ) = 0;

	// ������ɫ��Alphaֵ
	virtual void		UpdateColor( f32 p_fA, f32 p_fR, f32 p_fG, f32 p_fB,
		f32 p_fAMultiplier, f32 p_fRMultiplier, f32 p_fGMultiplier, f32 p_fBMultiplier ) = 0;

	// ������Ⱦģʽ
	virtual void		UpdateBlendMode( const string& p_szBlendMode ) = 0;

	// ��Դ�������
	virtual void		Clear() = 0;
};

//-------------------------------------------------------------------------

//-------------------------------------------------------------------------