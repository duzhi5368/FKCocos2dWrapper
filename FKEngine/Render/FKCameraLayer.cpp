//-------------------------------------------------------------------------
#include "FKCameraLayer.h"
//-------------------------------------------------------------------------
FKCameraLayer::FKCameraLayer( unsigned int id )
	: FKMapLayer( s_CameraLayerIDBegin + id )
{
	SetLayerDepth( s_CameraLayerIDBegin + id );
}
//-------------------------------------------------------------------------
FKCameraLayer::~FKCameraLayer()
{

}
//-------------------------------------------------------------------------
// ��ȡ��ͼ������( ���� ENUM_MapImageLayerType )
int FKCameraLayer::GetLayerType()
{
	return eMILT_Camera;
}
//-------------------------------------------------------------------------