//-------------------------------------------------------------------------
#include "FKCameraMaskLayer.h"
//-------------------------------------------------------------------------
FKCameraMaskLayer::FKCameraMaskLayer()
	: FKImageLayer( s_CameraMaskLayerID )
{
	SetLayerDepth( s_CameraMaskLayerID );
}
//-------------------------------------------------------------------------
FKCameraMaskLayer::FKCameraMaskLayer( vector<string>& vecImage )
	: FKImageLayer( s_CameraMaskLayerID, vecImage )
{

}
//-------------------------------------------------------------------------
FKCameraMaskLayer::~FKCameraMaskLayer()
{

}
//-------------------------------------------------------------------------
// ��ȡ��ͼ������( ���� ENUM_MapImageLayerType )
int FKCameraMaskLayer::GetLayerType()
{
	return eMILT_CameraMask;
}
//-------------------------------------------------------------------------
// �����������Ұ�ü�
void FKCameraMaskLayer::CullVisiableChunks()
{
	return;
}
//-------------------------------------------------------------------------