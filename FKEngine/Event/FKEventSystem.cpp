//-------------------------------------------------------------------------
#include "FKEventSystem.h"
#include "TEventEngine.h"
//-------------------------------------------------------------------------
IEventSystem* gs_pEventSystem;
FKEventSystem gs_FKEventSystem;
//-------------------------------------------------------------------------
// ��ȡ�¼��ַ����ӿ�
IEventSystem* GetEventSystem()
{
	return gs_pEventSystem;
}
//-------------------------------------------------------------------------
FKEventSystem::FKEventSystem()
{
	gs_pEventSystem = this;
}
//-------------------------------------------------------------------------
FKEventSystem::~FKEventSystem()
{
	gs_pEventSystem = NULL;
}
//-------------------------------------------------------------------------
// �ͷ�
void FKEventSystem::Release()
{

}
//-------------------------------------------------------------------------
// ����ͶƱ�¼�
// ����˵���μ����� OnVote
// ����ֵ���Ƿ�ȫԱͶƱͨ��
bool FKEventSystem::FireVote( EVENT_TYPE usID, unsigned short usSrcType,
							 unsigned int unSrcID, const char* szEvent, int nEventLen )
{
	return m_VoteCenter.Fire( usID, usSrcType, unSrcID, szEvent, nEventLen );
}
//-------------------------------------------------------------------------
// ����ִ���¼�
// ����˵���μ����� OnExec
void FKEventSystem::FireExec( EVENT_TYPE usID, unsigned short usSrcType,
							 unsigned int unSrcID, const char* szEvent, int nEventLen )
{
	m_ExecCenter.Fire( usID, usSrcType, unSrcID, szEvent, nEventLen );
}
//-------------------------------------------------------------------------
// ����ͶƱ�¼�
// ������pHandler ��������
// ������usSrcType ������Դ���ͣ��μ����ö�٣�
// ������unSrcID ������Ψһ��ʾ�������ǽ�ɫUID����ƷUID��
//		�Լ�ĳ����ָ��ȣ�����Ϣ�����߼�����Ա�Լ��涨��
//		��ֵ����Ϊ0�����ʾ����ȫ���������޶�ָ��ID
// ������szDesc ��������Ķ��������������������log
// ����ֵ���Ƿ�ɹ�����
bool FKEventSystem::SubscibeVote( IVoteEventHandler* pHandler, EVENT_TYPE usID, 
								 unsigned short usSrcType, unsigned int unSrcID, const char* szDesc )
{
	return m_VoteCenter.Subscibe( pHandler, usID, usSrcType, unSrcID, szDesc );
}
//-------------------------------------------------------------------------
// ����ִ���¼�
// ��������ֵ��ͬ�Ϻ���
bool FKEventSystem::SubscibeExec( IExecEventHandler* pHandler, EVENT_TYPE usID, 
								 unsigned short usSrcType, unsigned int unSrcID, const char* szDesc )
{
	return m_ExecCenter.Subscibe( pHandler, usID, usSrcType, unSrcID, szDesc );
}
//-------------------------------------------------------------------------
// ȡ��һ��ͶƱ����
bool FKEventSystem::UnSubscibeVote( IVoteEventHandler* pHandler, EVENT_TYPE usID, 
								   unsigned short usSrcType, unsigned int unSrcID )
{
	return m_VoteCenter.UnSubscibe( pHandler, usID, usSrcType, unSrcID );
}
//-------------------------------------------------------------------------
// ȡ��һ��ִ�ж���
bool FKEventSystem::UnSubscibeExec( IExecEventHandler* pHandler, EVENT_TYPE usID, 
								   unsigned short usSrcType, unsigned int unSrcID )
{
	return m_ExecCenter.UnSubscibe( pHandler, usID, usSrcType, unSrcID );
}
//-------------------------------------------------------------------------