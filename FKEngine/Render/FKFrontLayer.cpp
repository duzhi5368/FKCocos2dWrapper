//-------------------------------------------------------------------------
#include "FKFrontLayer.h"
//-------------------------------------------------------------------------
FKFrontLayer::FKFrontLayer( unsigned int id )
	: FKMapLayer( s_FrontLayerIDBegin + id )
{
	SetLayerDepth( s_FrontLayerIDBegin + id );
}
//-------------------------------------------------------------------------
FKFrontLayer::~FKFrontLayer()
{

}
//-------------------------------------------------------------------------
// ��ȡ��ͼ������( ���� ENUM_MapImageLayerType )
int FKFrontLayer::GetLayerType()
{
	return eMILT_Front;
}
//-------------------------------------------------------------------------