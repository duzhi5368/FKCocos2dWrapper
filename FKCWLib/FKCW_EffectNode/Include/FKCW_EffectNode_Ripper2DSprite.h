//*************************************************************************
//	��������:	2014-11-18
//	�ļ�����:	FKCW_EffectNode_Ripper2DSprite.h
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
class FKCW_EffectNode_Ripple2DSprite:public CCSprite
{
public:
	FKCW_EffectNode_Ripple2DSprite();
	virtual~FKCW_EffectNode_Ripple2DSprite();

	void init(const string&texFileName);
	// ��������h_press����0�����ʾ��ˮ���ϰ��£���h_pressС��0�����ʾ��ˮ�а���
	// ������x ���ڸ��ռ���x����
	void pressAtX(float x,float h_press,float r_press=120);
	void draw();
	void drawWire();
	void update(float dt);
	bool getIsDrawDebug()const {return m_isDrawDebug;}
	void setIsDrawDebug(bool value){m_isDrawDebug=value;}
protected:
	void _InitMesh();
	void _UpdateMesh();
	void _UpdateRipple();
protected:
	vector<CCPoint>				m_surfacePointList_reduced;
	int							m_reduceStep;
	vector<CCPoint>				m_surfacePointList;
	vector<CCPoint>				m_surfacePointList_back;		// ��̨����
	float						m_dx;
	FKCW_EffectNode_Mesh*		m_mesh;
	FKCW_EffectNode_IndexVBO*	m_indexVBO;
	bool						m_isDrawDebug;
};