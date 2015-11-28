//-------------------------------------------------------------------------
#include "../Include/FKCW_3D_SubMeshData.h"
//-------------------------------------------------------------------------
void FKCW_3D_SubMeshData::initIDtriList(const short indexArray[],int indexArrayLen){
	assert(indexArrayLen%3==0);
	m_IDtriList.clear();
	for(int i=0;i<indexArrayLen;i+=3){
		FKCW_3D_IDTriangle IDtri(indexArray[i],indexArray[i+1],indexArray[i+2]);
		m_IDtriList.push_back(IDtri);
	}
}
//-------------------------------------------------------------------------
void FKCW_3D_SubMeshData::initPositionList(const float positionArray[],int positionArrayLen){
	m_positionList.clear();
	for(int i=0;i<positionArrayLen;i+=4){
		FKCW_3D_Vector4 pos(positionArray[i],positionArray[i+1],positionArray[i+2],positionArray[i+3]);
		m_positionList.push_back(pos);
	}
}
//-------------------------------------------------------------------------
void FKCW_3D_SubMeshData::initTexCoordList(const float texCoordArray[],int texCoordArrayLen){
	m_texCoordList.clear();
	for(int i=0;i<texCoordArrayLen;i+=2){
		FKCW_3D_Vector2 texCoord(texCoordArray[i],texCoordArray[i+1]);
		m_texCoordList.push_back(texCoord);
	}
}
//-------------------------------------------------------------------------
void FKCW_3D_SubMeshData::initNormalList(const float normalArray[],int normalArrayLen){
	m_normalList.clear();
	for(int i=0;i<normalArrayLen;i+=4){
		FKCW_3D_Vector4 normal(normalArray[i],normalArray[i+1],normalArray[i+2],normalArray[i+3]);
		m_normalList.push_back(normal);
	}
}
//-------------------------------------------------------------------------
void FKCW_3D_SubMeshData::initColorList(const float colorArray[],int colorArrayLen){
	m_colorList.clear();
	for(int i=0;i<colorArrayLen;i+=4){
		FKCW_3D_Vector4 color(colorArray[i],colorArray[i+1],colorArray[i+2],colorArray[i+3]);
		m_colorList.push_back(color);
	}
}
//-------------------------------------------------------------------------