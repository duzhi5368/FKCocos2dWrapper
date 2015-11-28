//-------------------------------------------------------------------------
#include "FKCamera.h"
//-------------------------------------------------------------------------
FKCameraSystem gs_FKCameraSystem;
ICameraSystem* gs_pCameraSystem;
//-------------------------------------------------------------------------
ICameraSystem* GetCameraSystem()
{
	return gs_pCameraSystem;
}
//-------------------------------------------------------------------------
FKCameraSystem::FKCameraSystem()
{

	gs_pCameraSystem = this;
}
//-------------------------------------------------------------------------
FKCameraSystem::~FKCameraSystem()
{
	gs_pCameraSystem = NULL;
}
//-------------------------------------------------------------------------
// ��ȡ��ǰ�ӿ���������
void FKCameraSystem::GetViewport( CCPoint& pt )
{
	
}
//-------------------------------------------------------------------------
// ���õ�ǰ�ӿ���������
void FKCameraSystem::SetViewport( CCPoint& pt )
{

}
//-------------------------------------------------------------------------
// ��ȡ��ǰ�ӿڿ��ӷ�Χ
void FKCameraSystem::GetViewSize( CCSize& size )
{
	if( CCDirector::sharedDirector() == NULL )
		return;
	size = CCDirector::sharedDirector()->getVisibleSize();
}
//-------------------------------------------------------------------------
// ���õ�ǰ�ӿڿ��ӷ�Χ
void FKCameraSystem::SetViewSize( CCSize& size )
{
	if( CCDirector::sharedDirector() == NULL )
		return;
	CCDirector::sharedDirector()->setViewport();
}
//-------------------------------------------------------------------------
// ��ȡ��ǰ�������������
void FKCameraSystem::GetViewRect( CCRect& rect )
{

}
//-------------------------------------------------------------------------
// ���ӿ�
// ������fMinRange ����С��Χ
// ������fMaxRange �����Χ
// ������fTime �����¼�
void FKCameraSystem::ShakeCamera( float fMinRange, float fMaxRange, float fTime )
{

}
//-------------------------------------------------------------------------
// �����ӿڸ���
// ������pFollower �������
void FKCameraSystem::TrackCamera( CCNode* pFollower )
{

}
//-------------------------------------------------------------------------
// �����ӿ�·���������������ָ��·���ƶ�
// ������strPointListFile �㼯�ļ����ļ��ڰ������б��ʱ�䣩
void FKCameraSystem::TrackCamera( const string& strPointListFile )
{

}
//-------------------------------------------------------------------------
// �����ӿ���������Զ
// ������fScaleDis �����������Ⱦ��ľ���
void FKCameraSystem::StrechCamera( float fScaleDis )
{

}
//-------------------------------------------------------------------------