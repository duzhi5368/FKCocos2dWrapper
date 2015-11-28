//*************************************************************************
//	��������:	2014-11-18
//	�ļ�����:	FKCW_EffectNode_TinyWingsTerrainSprite.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_EffectNode_Mesh.h"
#include "FKCW_EffectNode_IndexVBO.h"
#include "FKCW_EffectNode_GLProgramWithUnifos.h"
//-------------------------------------------------------------------------
class FKCW_EffectNode_TinyWingsTerrainSprite:public CCSprite
{
public:
	FKCW_EffectNode_TinyWingsTerrainSprite();
	virtual~FKCW_EffectNode_TinyWingsTerrainSprite();

	void	init(float width,float height,int insertControlPointCount);
	void	draw();
	void	drawWire();
	void	reGenerateShape(int insertControlPointCount);
	void	reGenerateColors();

	bool	getIsDrawDebug()const {return m_isDrawDebug;}
	void	setIsDrawDebug(bool value){m_isDrawDebug=value;}
	void	setTexNonlinearFactor(float value){m_texNonlinearFactor=value;}
	float	getTexNonlinearFactor()const{return m_texNonlinearFactor;}
	void	setRibbonRotation(float value){m_ribbonRotation=value;}
	float	getRibbonRotation()const{return m_ribbonRotation;}
	void	setRibbonRepeat(float value){m_ribbonRepeat=value;}
	float	getRibbonRepeat()const{return m_ribbonRepeat;}
	float	getWidth()const{return m_width;}
	float	getHeight()const{return m_height;}
	int		getInsertControlPointCount()const{return m_insertControlPointCount;}
protected:
	void	_Submit();
	void	_UpdateMesh();
protected:
	CCTexture2D*				m_texture;
	vector<vector<CCPoint> >	m_pointMat;	// ���ؿռ�
	float						m_dx;
	int							m_nRow;		// ���������� >=2
	FKCW_EffectNode_Mesh*		m_mesh;
	FKCW_EffectNode_IndexVBO*	m_indexVBO;
	bool						m_isDrawDebug;
	FKCW_EffectNode_GLProgramWithUnifos*	m_program;
	float						m_texNonlinearFactor;
	vector<ccColor4F>			m_colorList;
	float						m_ribbonRotation;
	float						m_ribbonRepeat;
	float						m_width;
	float						m_height;
	int							m_insertControlPointCount;
};