//-------------------------------------------------------------------------
#include "FKFarLayer.h"
//-------------------------------------------------------------------------
FKFarLayer::FKFarLayer( unsigned int id )
	: FKMapLayer( s_FarLayerIDBegin + id )
{
	SetLayerDepth( s_FarLayerIDBegin + id );
}
//-------------------------------------------------------------------------
FKFarLayer::~FKFarLayer()
{

}
//-------------------------------------------------------------------------
// ��ȡ��ͼ������( ���� ENUM_MapImageLayerType )
int FKFarLayer::GetLayerType()
{
	return eMILT_Far;
}
//-------------------------------------------------------------------------