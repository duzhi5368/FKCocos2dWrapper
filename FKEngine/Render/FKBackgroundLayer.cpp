//-------------------------------------------------------------------------
#include "FKBackgroundLayer.h"
//-------------------------------------------------------------------------
FKBackgroundLayer::FKBackgroundLayer()
	: FKImageLayer( s_BackgroundLayerID )
{
	SetLayerDepth( s_BackgroundLayerID );
}
//-------------------------------------------------------------------------
FKBackgroundLayer::FKBackgroundLayer( vector<string>& vecImage )
	: FKImageLayer( s_BackgroundLayerID, vecImage )
{

}
//-------------------------------------------------------------------------
FKBackgroundLayer::~FKBackgroundLayer()
{

}
//-------------------------------------------------------------------------
// ��ȡ��ͼ������( ���� ENUM_MapImageLayerType )
int FKBackgroundLayer::GetLayerType()
{
	return eMILT_Background;
}
//-------------------------------------------------------------------------
// �����������Ұ�ü�
void FKBackgroundLayer::CullVisiableChunks()
{
	return;
}
//-------------------------------------------------------------------------