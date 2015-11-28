//*************************************************************************
//	��������:	2014-11-18
//	�ļ�����:	FKCW_EffectNode_TailSprite.h
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
enum eTurnType
{
	eTurnType_right					=0,
	eTurnType_left,
	eTurnType_straightForward,
	eTurnType_straightBack,
	eTurnType_unKnown,
};
//-------------------------------------------------------------------------
class FKCW_EffectNode_TailQuad
{
public:
	CCPoint m_posLU;
	CCPoint m_posLD;
	CCPoint m_posRU;
	CCPoint m_posRD;
	CCPoint m_texCoordLU;
	CCPoint m_texCoordLD;
	CCPoint m_texCoordRU;
	CCPoint m_texCoordRD;
	float m_opacity;	// ����alphaֵ��һ������ÿ�����ζ��ܵõ���ֵ�����ǿ������׼����������alphaֵ
	float m_opacityLU;
	float m_opacityLD;
	float m_opacityRU;
	float m_opacityRD;
	bool m_isTriangle;
public:
	FKCW_EffectNode_TailQuad();
};
//-------------------------------------------------------------------------
class FKCW_EffectNode_TailFootPrint
{
public:
	CCPoint m_tagPos;
	float	m_fOpacity;
public:
	FKCW_EffectNode_TailFootPrint();
	FKCW_EffectNode_TailFootPrint(const CCPoint&pos,float opacity);
protected:
	void _InitMembers();
};
//-------------------------------------------------------------------------
class FKCW_EffectNode_TailSprite : public CCSprite
{
public:
	FKCW_EffectNode_TailSprite();
	virtual ~FKCW_EffectNode_TailSprite();

	bool			init(const string&texFileName) ;
	virtual void	draw() ;
	void			update(float dt);

	void			clear(){m_footPrintList.clear();};
	bool			getIsEmpty(){return m_footPrintList.empty();}
	void			setMinDis(float value){m_minDis=value;}
	float			getMinDis()const{return m_minDis;}
	void			setIsShowWire(bool value){m_isShowWire=value;}
	bool			getIsShowWire()const{return m_isShowWire;}
protected:
	FKCW_EffectNode_Mesh* _GenerateMesh(const vector<FKCW_EffectNode_TailFootPrint>&footPrintList);
protected:
	float									m_opacityDamping;
	float									m_dt;			// �೤ʱ������һ���ڵ�
	float									m_disappearLengthPerSecond;
	vector<FKCW_EffectNode_TailFootPrint>	m_footPrintList;
	FKCW_EffectNode_IndexVBO*				m_indexVBO;
	FKCW_EffectNode_GLProgramWithUnifos*	m_program;
	float									m_initialOpacity;
	float									m_minDis;		// ��ʾ���������
	bool									m_isShowWire;
};
//-------------------------------------------------------------------------