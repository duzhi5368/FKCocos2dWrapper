//*************************************************************************
//	��������:	2015-1-10
//	�ļ�����:	FKTimerSystem.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../FKEngineCommonHead.h"
//-------------------------------------------------------------------------
class FKTimerSystem : public ITimerSystem
{
public:
	FKTimerSystem();
	~FKTimerSystem();
public:
	// ����
	virtual void		Release();
	// ����һ����ʱ��
	// ������unTimerID - ��ʱ��ID
	//		 unIntervalTime - ��ʱ�����ü��ʱ��
	//		 pHandler - �ص������ӿ���
	//		 unCallTime - �ص����ٴ�
	//		 szDebugInfo - ������Ϣ
	virtual bool		CreateTimer( unsigned int unTimerID, unsigned int unIntervalTime,
		ITimerHander* pHandler, unsigned int unCallTime = gs_INFINITY_CALLTIME, const char* szDebugInfo = 0 );
	// ����һ����ʱ��
	// ������unTimerID - ��ʱ��ID
	//		 pHandler - �ص������ӿ���
	virtual bool		DestroyTimer( unsigned int unTimerID, ITimerHander* pHandler );
	// �߼�����
	virtual void		UpdateTimer();
protected:
	struct STimerInfo
	{
		unsigned int		m_unTimerID;				// �û��Զ��嶨ʱ��ID
		unsigned int		m_unIntervalTime;			// �������ʱ��
		unsigned int		m_unCallTimes;				// ���ô���
		unsigned int		m_unLastCallTick;			// ���һ�α����õ�ʱ��
		unsigned int		m_unTimerGridIndex;			// ���ڵ�ʱ��̶�
		ITimerHander*		m_pHandler;					// ��Ϣ�ص�������
		string				m_strDebugInfo;				// debug��Ϣ
		list<STimerInfo*>::iterator m_ItePos;			// ��ʱ��̶��е�λ�ã������ֵΪ��������
	};
	typedef list<STimerInfo>	TIMER_INFOS;			// ��һ��ITimerHandler�еĶ�ʱ����ʱ��Ϣ
	typedef list<STimerInfo*>	TIMER_LIST;				// һ��ʱ��̶��еĶ�ʱ���б�
	typedef vector<TIMER_LIST>	TIMER_AXIS;				// ����ȫ��ʱ��̶ȵ�ʱ����ṹ
protected:
	TIMER_AXIS				m_TimerAxis;				// ����ȫ��ʱ��̶ȵ�ʱ����ṹ
	unsigned int			m_unLastCheckTick;			// ���һ�μ���ʱ��
	unsigned int			m_unInitializeTime;			// ʱ�����ʼʱ��
};
//-------------------------------------------------------------------------
extern FKTimerSystem gs_FKTimerSystem;
//-------------------------------------------------------------------------