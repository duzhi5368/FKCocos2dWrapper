//*************************************************************************
//	��������:	2015-1-29
//	�ļ�����:	FKBackgroundLayer.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKImageLayer.h"
//-------------------------------------------------------------------------
class FKBackgroundLayer : public FKImageLayer
{
public:
	FKBackgroundLayer();
	FKBackgroundLayer( vector<string>& vecImage );
	~FKBackgroundLayer();
public:
	// ��ȡ��ͼ������( ���� ENUM_MapImageLayerType )
	virtual int				GetLayerType();

	// �����������Ұ�ü�
	virtual void			CullVisiableChunks();
};