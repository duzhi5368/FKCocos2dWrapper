//*************************************************************************
//	��������:	2015-1-26
//	�ļ�����:	FKBarrierLayer.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKMapLayer.h"
//-------------------------------------------------------------------------
class FKBarrierLayer : public FKMapLayer
{
public:
	FKBarrierLayer();
	~FKBarrierLayer();
public:
	// ��ȡ��ͼ������( ���� ENUM_MapImageLayerType )
	virtual int				GetLayerType();
};