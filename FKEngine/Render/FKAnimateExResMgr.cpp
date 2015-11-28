//-------------------------------------------------------------------------
#include "FKAnimateExResMgr.h"
#include "FKAnimateExRes.h"
//-------------------------------------------------------------------------
FKAnimateExResMgr::FKAnimateExResMgr()
{

}
//-------------------------------------------------------------------------
FKAnimateExResMgr::~FKAnimateExResMgr()
{

}
//-------------------------------------------------------------------------
// ����������Դ
// ������szAnimationExResName ������Դ�ļ���
// ע��������Դ�Ѿ����ڣ���ֱ�ӷ���ԭ��Դָ��
FKAnimateExRes* FKAnimateExResMgr::GetAnimateExRes( const char* szAnimationExResName )
{
	if( szAnimationExResName == NULL )
		return NULL;

	AnimationExResMap::iterator Ite = m_mapAnimationExRes.find( szAnimationExResName );
	if( Ite != m_mapAnimationExRes.end() )
	{
		Ite->second->retain();
		return Ite->second;
	}

	FKAnimateExRes* pAnimateExRes = new FKAnimateExRes;
	if( pAnimateExRes == nullptr )
		return NULL;
	if( !pAnimateExRes->LoadRes( szAnimationExResName ) )
		return NULL;

	m_mapAnimationExRes[szAnimationExResName] = pAnimateExRes;
	return pAnimateExRes;
}
//-------------------------------------------------------------------------
// ɾ��������Դ
void FKAnimateExResMgr::ReleaseAnimationExRes( FKAnimateExRes* pAniRes )
{
	if( pAniRes == NULL )
		return;

	if( pAniRes->isSingleReference() )
	{
		m_mapAnimationExRes.erase( pAniRes->GetResFileName() );
	}
}
//-------------------------------------------------------------------------
// �ͷ�ȫ����Դ
void FKAnimateExResMgr::ReleaseAllResource()
{
	AnimationExResMap::iterator Ite = m_mapAnimationExRes.begin();
	for( ; Ite != m_mapAnimationExRes.end(); )
	{
		if( Ite->second == NULL )
			continue;

		CCAssert( Ite->second->isSingleReference(), "�������ü�������Ϊ1" );
		Ite->second->release();
	}
	m_mapAnimationExRes.clear();
}
//-------------------------------------------------------------------------
// �ͷ�û���ͷŵ���Դ
void FKAnimateExResMgr::ReleaseUnusedResource()
{
	AnimationExResMap::iterator Ite = m_mapAnimationExRes.begin();
	for( ; Ite != m_mapAnimationExRes.end(); )
	{
		if( Ite->second == NULL )
			continue;

		if( Ite->second->isSingleReference() )
		{
			Ite->second->release();
			m_mapAnimationExRes.erase( Ite++ );
		}
		else
		{
			Ite++;
		}
	}
}
//-------------------------------------------------------------------------