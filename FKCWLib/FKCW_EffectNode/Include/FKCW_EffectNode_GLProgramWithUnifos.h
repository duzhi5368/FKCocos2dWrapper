//*************************************************************************
//	��������:	2014-11-15
//	�ļ�����:	FKCW_EffectNode_GLProgramWithUnifos.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_EffectNode_Macros.h"
//-------------------------------------------------------------------------
// ��Program1��Program2ʹ��һ����ͬ�����ֵ�Uniform��������������������UniformID( GLint )�����ǲ�ͬ�ġ�
// ���Ե�ǰ��ȫ�ķ���������ÿ����ɫ����һ��������š�
class FKCW_EffectNode_GLProgramWithUnifos:public CCGLProgram
{
protected:
	map<string,GLint> m_mapUnifos;
public:
	FKCW_EffectNode_GLProgramWithUnifos(){};
	virtual ~FKCW_EffectNode_GLProgramWithUnifos(){};

	void attachUniform(string unifoName);
	void passUnifoValue1f(string unifoName,GLfloat v);
	void passUnifoValue1i(string unifoName,GLint v);
	void passUnifoValueMatrixNfv(string unifoName,const GLfloat *array,int arrayLen);
	void passUnifoValueNfv(string unifoName,const GLfloat *array,int arrayLen);
	void passUnifoValueNfvN(string unifoName,const GLfloat*array,int arrayLen,int arrayCount);
	void passUnifoValueNiv(string unifoName,const GLint *array,int arrayLen);
	void passUnifoValueMatrixNfv(string unifoName,const vector<GLfloat>&valueList);
	void passUnifoValueNfv(string unifoName,const vector<GLfloat>&valueList);
	void passUnifoValueNiv(string unifoName,const vector<GLint>&valueList);
};