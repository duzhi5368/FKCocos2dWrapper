//*************************************************************************
//	��������:	2015-1-26
//	�ļ�����:	FKFrontLayer.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKMapLayer.h"
//-------------------------------------------------------------------------
class FKFrontLayer : public FKMapLayer
{
public:
	FKFrontLayer( unsigned int id );
	~FKFrontLayer();
public:
	// ��ȡ��ͼ������( ���� ENUM_MapImageLayerType )
	virtual int				GetLayerType();
};