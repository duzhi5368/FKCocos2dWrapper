//*************************************************************************
//	��������:	2015-1-29
//	�ļ�����:	FKCameraMaskLayer.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKImageLayer.h"
//-------------------------------------------------------------------------
class FKCameraMaskLayer : public FKImageLayer
{
public:
	FKCameraMaskLayer();
	FKCameraMaskLayer( vector<string>& vecImage );
	~FKCameraMaskLayer();
public:
	// ��ȡ��ͼ������( ���� ENUM_MapImageLayerType )
	virtual int				GetLayerType();

	// �����������Ұ�ü�
	virtual void			CullVisiableChunks();
};