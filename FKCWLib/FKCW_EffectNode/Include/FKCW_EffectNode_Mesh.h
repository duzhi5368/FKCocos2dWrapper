//*************************************************************************
//	��������:	2014-11-15
//	�ļ�����:	FKCW_EffectNode_Mesh.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_EffectNode_Macros.h"
//-------------------------------------------------------------------------
class FKCW_EffectNode_Mesh:public CCObject
{
public:
	vector<Cv2> vlist;
	vector<Cv2> texCoordList;
	vector<Cv4> colorList;
	vector<CIDTriangle> IDtriList;
	void clear(){
		vlist.clear();
		texCoordList.clear();
		colorList.clear();
		IDtriList.clear();
	}
};
//-------------------------------------------------------------------------
class FKCW_EffectNode_MeshWire:public CCObject
{
public:
	vector<Cv2> vlist;
	vector<Cv2> texCoordList;
	vector<Cv4> colorList;
	vector<CIDLine> IDlineList;
	void clear(){
		vlist.clear();
		texCoordList.clear();
		colorList.clear();
		IDlineList.clear();
	}
};
//-------------------------------------------------------------------------
class FKCW_EffectNode_MeshGeneral:public CCObject
{
public:
	vector<Cv2> vlist;
	vector<Cv2> texCoordList;
	vector<Cv4> colorList;
	vector<short> indexList;
	void clear(){
		vlist.clear();
		texCoordList.clear();
		colorList.clear();
		indexList.clear();
	}
};
//-------------------------------------------------------------------------