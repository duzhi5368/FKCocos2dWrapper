//-------------------------------------------------------------------------
#include "FKRenderSystem.h"
//-------------------------------------------------------------------------

FKRenderSystem gs_FKRenderSystem;
IRenderSystem* gs_pRenderSystem;
//-------------------------------------------------------------------------
IRenderSystem* GetRenderSystem()
{
	return gs_pRenderSystem;
}
//-------------------------------------------------------------------------
FKRenderSystem::FKRenderSystem()
{
	gs_pRenderSystem = this;
}
FKRenderSystem::~FKRenderSystem()
{
	gs_pRenderSystem = NULL;
}

//-------------------------------------------------------------------------
// ��ʼ����Ⱦϵͳ
// ������tagDesignSize ��Ⱦ���ڴ�С
void FKRenderSystem::Init( CCSize& tagDesignSize )
{

}
//-------------------------------------------------------------------------
// ���ø���Ⱦ�ڵ㣬���г���ȫ���ҽ��ڱ��ڵ���
void FKRenderSystem::SetRoot( CCNode* pMapRootNode )
{

}
//-------------------------------------------------------------------------
// ��ȡ��ǰ�����еĵ�ͼ����
IMapObj* FKRenderSystem::GetCurrentMap()
{
	return NULL;
}
//-------------------------------------------------------------------------
// ���½����³���
// ������szFKMFileName ��ͼ�����ļ�
RENDER_MAP_ID FKRenderSystem::EnterMap( const char* szFKMFileName )
{
	return 0;
}
//-------------------------------------------------------------------------
// �Ƿ�����Update
void FKRenderSystem::SetEnableUpdate( bool bIsEnable )
{

}
//-------------------------------------------------------------------------
// ���ó���������ӵ�
// ������tagLocPos ������ӵ�λ��
void FKRenderSystem::SetViewPoint( const CCPoint& tagLocPos )
{

}
//-------------------------------------------------------------------------
// ��ȡ����������ӵ�
// ������[out]tagLocPos ������ӵ�λ��
bool FKRenderSystem::GetViewPoint( const CCPoint& tagLocPos )
{
	return true;
}
//-------------------------------------------------------------------------
// ת����Ļ���굽��������
// ������[in]tagScreenPos ��Ļ����
// ������[out]tagScenePos ��������
bool FKRenderSystem::ConvertScreenPosToScenePos( const CCPoint& tagScreenPos,
									   CCPoint& tagScenePos )
{
	return true;
}
//-------------------------------------------------------------------------

// ��ȡ��ײ����
// ������ObjList ����ײ�Ķ����б�
void FKRenderSystem::HitRenderObj( const CCPoint& tagScreenPos, list<IRenderObj*>& ObjList )
{

}
//-------------------------------------------------------------------------
// ������Ⱦ����
// ������szGameObjName ��Ϸ������
IRenderObj* FKRenderSystem::CreateRenderObj( const char* szGameObjName )
{
	return NULL;
}
//-------------------------------------------------------------------------
// ɾ����Ⱦ����
// ����: pRenderObj ��Ҫɾ������Ⱦ����
bool FKRenderSystem::RemoveRenderObj( IRenderObj* pRenderObj )
{
	return true;
}
//-------------------------------------------------------------------------
// ɾ����Ⱦ����
// ����: id ��Ҫɾ������Ⱦ����ID
bool FKRenderSystem::RemoveRenderObj( RENDER_OBJ_ID id )
{
	return true;
}
//-------------------------------------------------------------------------
// ��ȡ��Ⱦ����
IRenderObj* FKRenderSystem::GetRenderObj( RENDER_OBJ_ID id )
{
	return NULL;
}
//-------------------------------------------------------------------------
// �����Ⱦ���󵽵�ǰ����
// ������pRenderObj �����Ⱦ���󵽵�ǰ����
bool FKRenderSystem::AddRenderObjToScene( IRenderObj* pRenderObj )
{
	return true;
}
//-------------------------------------------------------------------------
// �ӵ�ǰ����ɾ����Ⱦ����
// ������pRenderObj ��Ҫ�ӵ�ǰ����ɾ������Ⱦ����
bool FKRenderSystem::RemoveRenderObjFromScene( IRenderObj* pRenderObj )
{
	return true;
}
//-------------------------------------------------------------------------

// ������Ⱦ����
// ������szString ����
// ������szFontName ��������
// ������nFontSize �����С
// ������tagDimentions ����ߴ�
// ������bIsBmpFont �Ƿ���BMP����
IRenderText* FKRenderSystem::CreateRenderText( const char* szString, const char* szFontName, 
							  int nFontSize,  CCSize tagDimentions , bool bIsBmpFont  )
{
	return NULL;
}
//-------------------------------------------------------------------------
// ɾ����Ⱦ����
// ������pRenderText ��Ҫɾ������Ⱦ����
bool FKRenderSystem::RemoveRenderText( IRenderText* pRenderText )
{
	return true;
}
//-------------------------------------------------------------------------
// ɾ����Ⱦ����
// ������id ΨһID
bool FKRenderSystem::RemoveRenderTextByID( RENDER_OBJ_ID id )
{
	return true;
}
//-------------------------------------------------------------------------