//*************************************************************************
//	��������:	2015-2-1
//	�ļ�����:	FKNormalLayer.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKMapLayer.h"
//-------------------------------------------------------------------------
class FKNormalLayer : public FKMapLayer
{
public:
	FKNormalLayer( unsigned int id );
	~FKNormalLayer();
public:
	// ��ȡ��ͼ������( ���� ENUM_MapImageLayerType )
	virtual int				GetLayerType();
};