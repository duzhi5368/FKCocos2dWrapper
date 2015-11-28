//-------------------------------------------------------------------------
#include "FKTimerSystem.h"
#include "FKTimerSystemMacros.h"
//-------------------------------------------------------------------------
ITimerSystem*	gs_pTimerSystem = NULL;
FKTimerSystem	gs_FKTimerSystem;
//-------------------------------------------------------------------------
// ��ȡ��ʱ��ϵͳ�ӿ�
ITimerSystem* GetTimerSystem()
{
	return gs_pTimerSystem;
}
//-------------------------------------------------------------------------
FKTimerSystem::FKTimerSystem()
{
	m_TimerAxis.resize(( gs_MAX_TIME_AXIS_LENGTH / gs_DEFAULT_TIME_GRID - 1 ) / gs_DEFAULT_TIME_GRID);
	m_unInitializeTime = FKCW_Base_Utils::GetTimeTickCount();
	m_unLastCheckTick = m_unInitializeTime;

	gs_pTimerSystem = this;
}
//-------------------------------------------------------------------------
FKTimerSystem::~FKTimerSystem()
{
	gs_pTimerSystem = NULL;
}
//-------------------------------------------------------------------------
// ����
void FKTimerSystem::Release()
{
	for ( unsigned long i=0;i<m_TimerAxis.size();++i )
	{
		TIMER_LIST& TimerList = m_TimerAxis[i];
		TIMER_LIST::iterator it = TimerList.begin();
		for ( ;it!=TimerList.end();++it )
		{
			STimerInfo * pTimer = *it;
			if( pTimer )
			{
				DestroyTimer(pTimer->m_unTimerID,pTimer->m_pHandler);
			}
		}
	}
	m_TimerAxis.clear();
}
//-------------------------------------------------------------------------
// ����һ����ʱ��
// ������unTimerID - ��ʱ��ID
//		 unIntervalTime - ��ʱ�����ü��ʱ��
//		 pHandler - �ص������ӿ���
//		 unCallTime - �ص����ٴ�
//		 szDebugInfo - ������Ϣ
bool FKTimerSystem::CreateTimer( unsigned int unTimerID, unsigned int unIntervalTime,
						ITimerHander* pHandler, unsigned int unCallTime, const char* szDebugInfo )
{
	if( pHandler == NULL )
		return false;
	if( unIntervalTime == 0 )
		unIntervalTime = 1;

	void** ppTimerInfo = pHandler->GetTimerInfoPtr();
	if( ppTimerInfo == NULL)
		return false;

	TIMER_INFOS* pTimerInfos = *(TIMER_INFOS**)ppTimerInfo;
	if( ppTimerInfo == NULL || pTimerInfos ==0)
	{
		pTimerInfos = new TIMER_INFOS;
		*ppTimerInfo = pTimerInfos;
	}

	// ����Timer�Ƿ��Ѿ�����
	TIMER_INFOS::iterator Ite = pTimerInfos->begin();
	for( ; Ite != pTimerInfos->end(); ++Ite )
	{
		STimerInfo& tagTimer = *Ite;
		if( tagTimer.m_unTimerID == unTimerID )
		{
			return false;
		}
	}

	STimerInfo tagTimerInfo;
	tagTimerInfo.m_unTimerID		= unTimerID;
	tagTimerInfo.m_unIntervalTime	= unIntervalTime;
	tagTimerInfo.m_unCallTimes		= unCallTime;
	tagTimerInfo.m_unLastCallTick	= m_unLastCheckTick;
	tagTimerInfo.m_pHandler			= pHandler;
	if( szDebugInfo )
		tagTimerInfo.m_strDebugInfo	= szDebugInfo;
	tagTimerInfo.m_unTimerGridIndex	= (( tagTimerInfo.m_unLastCallTick + tagTimerInfo.m_unIntervalTime 
		- m_unInitializeTime ) / gs_DEFAULT_TIME_GRID ) % m_TimerAxis.size();

	pTimerInfos->push_back( tagTimerInfo );

	// ���������ٲ�ѯ��Iter
	STimerInfo& TimerRef = pTimerInfos->back();
	STimerInfo* pTimerIte = &TimerRef;
	m_TimerAxis[tagTimerInfo.m_unTimerGridIndex].push_back( pTimerIte );
	pTimerIte->m_ItePos = --m_TimerAxis[tagTimerInfo.m_unTimerGridIndex].end();

	return true;
}
//-------------------------------------------------------------------------
// ����һ����ʱ��
// ������unTimerID - ��ʱ��ID
//		 pHandler - �ص������ӿ���
bool FKTimerSystem::DestroyTimer( unsigned int unTimerID, ITimerHander* pHandler )
{
	void** ppTimerInfo = pHandler->GetTimerInfoPtr();
	if( ppTimerInfo == NULL )
		return false;

	TIMER_INFOS* pTimerInfos = *(TIMER_INFOS**)ppTimerInfo;

	// ����û���
	if( pTimerInfos == NULL )
		return false;

	// �Ƿ�����˱�Timer
	TIMER_INFOS::iterator Ite = pTimerInfos->begin();
	for( ;Ite != pTimerInfos->end(); ++Ite )
	{
		STimerInfo& tagTimer = *Ite;
		if( tagTimer.m_unTimerID == unTimerID )
		{
			// ע�⣬���ﲢô��ֱ��ɾ����Timer����Ϊ��ʱ������������DestoryTimer.
			// Ϊ����������������ﲻֱ��ɾ��TimerIte������������ΪNULL��֮����ɾ��
			*tagTimer.m_ItePos = NULL;

			pTimerInfos->erase( Ite );
			if( pTimerInfos->empty() )
			{
				delete pTimerInfos;
				*ppTimerInfo = NULL;
			}
			// �ɹ�
			return true;
		}
	}
	return false;
}
//-------------------------------------------------------------------------
// �߼�����
void FKTimerSystem::UpdateTimer()
{
	unsigned long unCurTick = FKCW_Base_Utils::GetTimeTickCount();

	// ����ָ�����Ƶ��֮��ż��
	if ( unCurTick - m_unLastCheckTick< gs_DEFAULT_CHECK_FREQUENCY )
		return;

	unsigned int unStartGrid = ( ( m_unLastCheckTick - m_unInitializeTime ) / gs_DEFAULT_TIME_GRID ) % m_TimerAxis.size();
	unsigned int unCurGrid = ( ( unCurTick - m_unInitializeTime) / gs_DEFAULT_TIME_GRID ) % m_TimerAxis.size();

	// ��¼��ǰCheckʱ��
	m_unLastCheckTick = unCurTick;

	unsigned long i = unStartGrid;

	// ����ʱ��̶�
	do
	{
		// ������ǰʱ��̶��е����д�������ʱ��
		TIMER_LIST& TimerList = m_TimerAxis[i];
		TIMER_LIST::iterator Ite = TimerList.begin();
		for ( ;Ite != TimerList.end(); )
		{
			STimerInfo* pTimer = *Ite;
			if ( pTimer == NULL )
			{
				// Ӧ����ɾ����Timer
				Ite = TimerList.erase(Ite);
				continue;
			}

			// ������ʱ��
			if ( unCurTick - pTimer->m_unLastCallTick >= pTimer->m_unIntervalTime )
			{
				// ִ�ж�ʱ���ص�
				unsigned long dwTick = FKCW_Base_Utils::GetTimeTickCount();
				pTimer->m_pHandler->OnTimer( pTimer->m_unTimerID );


				// ���һ�����Timer�Ƿ�ɾ����
				if ( *Ite == pTimer )
				{
					int nCostTime = FKCW_Base_Utils::GetTimeTickCount() - dwTick;
					if( nCostTime > 64 && nCostTime > gs_DEFAULT_TIME_GRID )
					{ 
						FKLOG("��ʱ��Ƶ�ʹ���: ID = %d, ������� = %d, ʵ�ʼ�� = %d, ���� = %s",
							pTimer->m_unTimerID, pTimer->m_unIntervalTime, nCostTime, pTimer->m_strDebugInfo.c_str() );
					}

					pTimer->m_unLastCallTick = unCurTick;
					pTimer->m_unCallTimes    -= 1;

					if ( pTimer->m_unCallTimes == 0 )
					{
						// ���ô����Ѿ����ˣ���ʼ����ɾ����
						DestroyTimer( pTimer->m_unTimerID,pTimer->m_pHandler );
					}
					else
					{
						// ��Ǩ����һ�δ�����λ��
						pTimer->m_unTimerGridIndex = ( (pTimer->m_unLastCallTick + pTimer->m_unIntervalTime - m_unInitializeTime) 
							/ gs_DEFAULT_TIME_GRID ) % m_TimerAxis.size();
						Ite = TimerList.erase(Ite);
						m_TimerAxis[pTimer->m_unTimerGridIndex].push_back(pTimer);
						pTimer->m_ItePos = --m_TimerAxis[pTimer->m_unTimerGridIndex].end();

						continue;
					}
				}
				else
				{
					// timer�Լ���ɾ����
					Ite = TimerList.erase(Ite);
					continue;
				}
			}

			// δ��������Timer��ֱ������
			++Ite;
		}

		// �ݽ�����һ���̶�
		if ( i == unCurGrid )
			break;
		i = (i+1) % m_TimerAxis.size();

	}while( i != unCurGrid);
}
//-------------------------------------------------------------------------