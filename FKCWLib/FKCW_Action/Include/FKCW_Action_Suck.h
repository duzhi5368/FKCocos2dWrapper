//*************************************************************************
//	��������:	2015-1-9
//	�ļ�����:	FKCW_Action_Suck.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_Action_Macros.h"
//-------------------------------------------------------------------------
class FKCW_Action_Suck : public CCGrid3DAction
{
public:
	static FKCW_Action_Suck* create( CCSize p_tagSize, float p_fTime, CCPoint p_tagPos ); 
	FKCW_Action_Suck* initWithGrid( CCSize p_tagSize, float p_fTime, CCPoint p_tagPos );
	virtual void update(float time);
private:
	CCPoint m_tagToPos;
	float	m_fAmplitudeRate;
};
//-------------------------------------------------------------------------