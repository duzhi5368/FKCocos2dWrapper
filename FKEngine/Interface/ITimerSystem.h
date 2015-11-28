//*************************************************************************
//	��������:	2015-1-10
//	�ļ�����:	ITimerSystem.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
/*
	TODO
*/
//-------------------------------------------------------------------------
// ��ʱ�����ص�����
const static unsigned int	gs_INFINITY_CALLTIME		= 0xffffffff;
//-------------------------------------------------------------------------
// ��ʱ���ص��ӿ�
class ITimerHander
{
public:
	// ��ʱ��ʱ�䴥���ص�
	virtual void		OnTimer( unsigned int unTimerID ) = 0;


	// ������һЩ��㷽�����û��������
public:
	virtual void**		GetTimerInfoPtr(){ return &m_pTmpInfoPtr; }
public:
	ITimerHander():m_pTmpInfoPtr( 0 ){}
protected:
	void*	m_pTmpInfoPtr;
};
//-------------------------------------------------------------------------
// ��ʱ��ϵͳ
struct ITimerSystem
{
public:
	// ����
	virtual void		Release() = 0;
	// ����һ����ʱ��
	// ������unTimerID - ��ʱ��ID
	//		 unIntervalTime - ��ʱ�����ü��ʱ��
	//		 pHandler - �ص������ӿ���
	//		 unCallTime - �ص����ٴ�
	//		 szDebugInfo - ������Ϣ
	virtual bool		CreateTimer( unsigned int unTimerID, unsigned int unIntervalTime,
		ITimerHander* pHandler, unsigned int unCallTime = gs_INFINITY_CALLTIME, const char* szDebugInfo = 0 ) = 0;
	// ����һ����ʱ��
	// ������unTimerID - ��ʱ��ID
	//		 pHandler - �ص������ӿ���
	virtual bool		DestroyTimer( unsigned int unTimerID, ITimerHander* pHandler ) = 0;
	// �߼�����
	virtual void		UpdateTimer() = 0;
};
//-------------------------------------------------------------------------
// ��ȡ��ʱ��ϵͳ�ӿ�
extern ITimerSystem* GetTimerSystem();
//-------------------------------------------------------------------------