//*************************************************************************
//	��������:	2015-1-21
//	�ļ�����:	FKImageLayer.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKMapLayer.h"
#include "FKImageChunk.h"
//-------------------------------------------------------------------------
// �����ľ�̬ͼƬ��[ ��Ϊ������ �� ������ʹ�� ]
class FKImageLayer : public FKMapLayer
{
public:
	FKImageLayer( RENDER_MAP_LAYER_ID id );
	FKImageLayer( RENDER_MAP_LAYER_ID id, vector<string>& vecImage );
	~FKImageLayer();
public:
	// ��ȡ������Ӳ�
	virtual float			GetLayerHeightParallax();
	// ��ȡ�������Ӳ�
	virtual float			GetLayerWidthParallax();
	// ���ò�����Ӳ�
	virtual void			SetLayerHeightParallax( float fParallax );
	// ���ò������Ӳ�
	virtual void			GetLayerHeightParallax( float fParallax );
public:
	// ��ʼ������
	bool					InitImageLayer( vector<string>& vecImage );
};