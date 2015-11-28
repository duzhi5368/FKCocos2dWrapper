//*************************************************************************
//	��������:	2014-8-13   14:16
//	�ļ�����:	DargonBonesObject.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "BaseMacro.h"
#include "Transform.h"
#include "Matrix.h"
#include "Object.h"
#include <string>
using std::string;
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
class CBone;
class CArmature;
class CDragonBonesObject
{
public:
	bool		m_bIsVisible;			// �Ƿ�ɼ�
	bool		m_bFixedRotation;
	bool		m_bIsColorChanged;
	string		m_szName;
	IObject*	m_pUserData;
	CTransform	m_GlobalTransform;
	CTransform	m_OriginTransform;
	CTransform	m_OffsetTransform;
	CTransform	m_TweenTransform;
	CBone*		m_pParent;
	CMatrix		m_GlobalTransformMatrix;
	int			m_nScaleType;
protected:
	CArmature*	m_pArmature;
public:
	CDragonBonesObject();
	virtual ~CDragonBonesObject();
public:
	virtual void	SetArmature( CArmature* p_pValue );
	virtual void	Clear();
	virtual void	Update();
};

//-------------------------------------------------------------------------

//-------------------------------------------------------------------------