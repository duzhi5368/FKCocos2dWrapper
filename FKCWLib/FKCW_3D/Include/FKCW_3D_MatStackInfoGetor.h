//*************************************************************************
//	��������:	2014-12-14
//	�ļ�����:	FKCW_3D_MatStackInfoGetor.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_3D_Matrix4.h"
#include "FKCW_3D_Macro.h"
//-------------------------------------------------------------------------
class FKCW_3D_MatStackInfoGetor
{
public:
	FKCW_3D_MatStackInfoGetor();
	virtual~FKCW_3D_MatStackInfoGetor();
public:
	static FKCW_3D_MatStackInfoGetor* sharedMatStackInfoGetor();
public:
	bool init();
	FKCW_3D_Matrix4 getTopMat(ENUM_FKCW_3D_MatStackName eMatStackName);
};
//-------------------------------------------------------------------------