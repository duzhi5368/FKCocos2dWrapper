//*************************************************************************
//	��������:	2014-12-29
//	�ļ�����:	FKCW_3D_DefaultPassUniformCallback.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_3D_Macro.h"
#include "FKCW_3D_Programs.h"
#include "FKCW_3D_MatStackInfoGetor.h"
//-------------------------------------------------------------------------
class FKCW_3D_Node;
//-------------------------------------------------------------------------
void PassUnifoCallback_TexOnly(FKCW_3D_Node* node,FKCW_3D_Program* program);
void PassUnifoCallback_ClassicLighting(FKCW_3D_Node* node,FKCW_3D_Program* program);
//-------------------------------------------------------------------------