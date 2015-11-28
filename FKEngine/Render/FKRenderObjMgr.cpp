//-------------------------------------------------------------------------
#include "FKRenderObjMgr.h"
#include "FKRenderObj.h"
//-------------------------------------------------------------------------
FKRenderObjMgr::FKRenderObjMgr()
{
	m_mapRenderObjs.clear();
	m_mapRenderObjModels.clear();
}
//-------------------------------------------------------------------------
FKRenderObjMgr::~FKRenderObjMgr()
{

}
//-------------------------------------------------------------------------
// ������Ⱦ����
// ������szGameObjName ��Ϸ������
FKRenderObj* FKRenderObjMgr::CreateRenderObj( const char* szGameObjName )
{
	if( szGameObjName == NULL )
		return NULL;
	
	static RENDER_OBJ_ID s_RenderObjID = 0;
	if( ++s_RenderObjID == 0 )
		s_RenderObjID++;

	FKRenderObj* pRenderObj = GetRenderObj( s_RenderObjID );
	while( pRenderObj != NULL )
	{
		// һ��Ҫ�ҵ�һ���յ�
		++s_RenderObjID;
		pRenderObj = GetRenderObj( s_RenderObjID );
	}

	string strPathName, strFileName, strExtName;
	FKCW_Base_Utils::ParseFilePathName( szGameObjName, strPathName, strFileName, strExtName );
	FKCW_Base_Utils::ToLowerCase( strExtName );

	if( strExtName != "fko" )
	{
		pRenderObj = new FKRenderObj( s_RenderObjID );
		if( pRenderObj == NULL )
		{
			return NULL;
		}
		pRenderObj->Create( szGameObjName );
	}
	else
	{
		RenderObjModelMap::iterator IteObjModel = m_mapRenderObjModels.find( szGameObjName );
		if( IteObjModel == m_mapRenderObjModels.end() )
		{
			FKRenderObjModel* pRenderObjModel = new FKRenderObjModel();
			if( pRenderObjModel == NULL )
				return NULL;

			string strObjName = szGameObjName;
			if( !pRenderObjModel->LoadFromFKOFile( strObjName ) )
			{
				return NULL;
			}
			else
			{
				m_mapRenderObjModels[ strObjName ] = pRenderObjModel;
				IteObjModel = m_mapRenderObjModels.find( strObjName );
			}
		}

		pRenderObj = new FKRenderObj( s_RenderObjID );
		if( pRenderObj == NULL )
			return NULL;

		pRenderObj->SetObjModel( (IRenderObjModel*)IteObjModel->second );
		pRenderObj->Create( szGameObjName );
	}

	m_mapRenderObjs[s_RenderObjID] = pRenderObj;
	return pRenderObj;
}
//-------------------------------------------------------------------------
// ɾ����Ⱦ����
// ����: id ��Ҫɾ������Ⱦ����ID
bool FKRenderObjMgr::RemoveRenderObj( RENDER_OBJ_ID id )
{
	RenderObjMap::iterator Ite = m_mapRenderObjs.find( id );
	if( Ite == m_mapRenderObjs.end() )
		return true;

	FKRenderObj* pObj = Ite->second;
	if( pObj == NULL )
		return true;

	if( pObj->isSingleReference() )
		m_mapRenderObjs.erase( Ite );

	pObj->release();
	return true;
}
//-------------------------------------------------------------------------
// ��ȡ��Ⱦ����
FKRenderObj* FKRenderObjMgr::GetRenderObj( RENDER_OBJ_ID id )
{
	RenderObjMap::iterator Ite = m_mapRenderObjs.find( id );
	if( Ite == m_mapRenderObjs.end() )
		return NULL;

	return Ite->second;
}
//-------------------------------------------------------------------------
// �ͷ�δʹ�õ�ģ�Ͷ�������
void FKRenderObjMgr::ReleaseUnusedObjModel()
{
	RenderObjModelMap::iterator IteModel = m_mapRenderObjModels.begin();
	RenderObjModelMap::iterator IteSave;
	for( ; IteModel != m_mapRenderObjModels.end(); )
	{
		IteSave = IteModel++;
		if( IteSave->second && IteSave->second->isSingleReference() )
		{
			IteSave->second->release();
			m_mapRenderObjModels.erase( IteSave );
		}
	}
	if( !m_mapRenderObjModels.empty() )
	{
		FKLOG("Error: FKRenderObjMgr::ReleaseUnusedObjModel() already exist memorys!");
	}
}
//-------------------------------------------------------------------------
// �Ƿ�����Update
void FKRenderObjMgr::SetEnableUpdate( bool bIsEnable )
{
	RenderObjMap::iterator Ite = m_mapRenderObjs.begin();
	for( ; Ite != m_mapRenderObjs.end(); ++Ite )
	{
		if( Ite->second )
		{
			Ite->second->SetEnableUpdate( bIsEnable );
		}
	}
}
//-------------------------------------------------------------------------