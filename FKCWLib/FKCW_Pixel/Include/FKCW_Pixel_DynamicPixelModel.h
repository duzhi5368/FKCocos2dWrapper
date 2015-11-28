//*************************************************************************
//	��������:	2015-1-5
//	�ļ�����:	FKCW_Pixel_DynamicPixelModel.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_Pixel_DynamicPixelSprite.h"
//-------------------------------------------------------------------------
class FKCW_Pixel_DynamicPixelModel:public CCNode
{
public:
	FKCW_Pixel_DynamicPixelModel(){};
	virtual~FKCW_Pixel_DynamicPixelModel(){}

	void							adddpSprite(FKCW_Pixel_DynamicPixelSprite* dpSprite);
	int								getdpSpriteCount()const{return (int)m_dpSpriteList.size();}
	FKCW_Pixel_DynamicPixelSprite*	getdpSpriteByIndex(int index);
	CCRect							getBoundingBoxInLocalSpace()const;
	CCRect							getBoundingBox();
	void							addCollisionRectInLocalSpace(const FKCW_Pixel_CollisionRect&localSpaceCollisionRect);
	CCRect							getCollisionRectByIndex(int index);
	CCRect							getCollisionRectByName(const string&name);
	void							draw();
protected:
	int								getCollisionRectIndexByName(const string&name);
protected:
	vector<FKCW_Pixel_DynamicPixelSprite*>	m_dpSpriteList;
	vector<FKCW_Pixel_CollisionRect>		m_collisionRectListInLocalSpace;
};