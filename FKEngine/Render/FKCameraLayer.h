//*************************************************************************
//	��������:	2015-1-29
//	�ļ�����:	FKCameraLayer.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKMapLayer.h"
//-------------------------------------------------------------------------
class FKCameraLayer : public FKMapLayer
{
public:
	FKCameraLayer( unsigned int id );
	~FKCameraLayer();
public:
	// ��ȡ��ͼ������( ���� ENUM_MapImageLayerType )
	virtual int				GetLayerType();
};