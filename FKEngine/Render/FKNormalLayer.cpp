//-------------------------------------------------------------------------
#include "FKNormalLayer.h"
//-------------------------------------------------------------------------
FKNormalLayer::FKNormalLayer( unsigned int id )
	: FKMapLayer( s_NormalLayerIDBegin + id )
{
	SetLayerDepth( s_NormalLayerIDBegin + id );
}
//-------------------------------------------------------------------------
FKNormalLayer::~FKNormalLayer()
{

}
//-------------------------------------------------------------------------
// ��ȡ��ͼ������( ���� ENUM_MapImageLayerType )
int FKNormalLayer::GetLayerType()
{
	return eMILT_Normal;
}
//-------------------------------------------------------------------------