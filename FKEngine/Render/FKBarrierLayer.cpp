//-------------------------------------------------------------------------
#include "FKBarrierLayer.h"
//-------------------------------------------------------------------------
FKBarrierLayer::FKBarrierLayer()
	: FKMapLayer( s_BarrierLayerID )
{
	SetLayerDepth( s_BarrierLayerID );
}
//-------------------------------------------------------------------------
FKBarrierLayer::~FKBarrierLayer()
{

}
//-------------------------------------------------------------------------
// ��ȡ��ͼ������( ���� ENUM_MapImageLayerType )
int FKBarrierLayer::GetLayerType()
{
	return eMILT_Barrier;
}
//-------------------------------------------------------------------------