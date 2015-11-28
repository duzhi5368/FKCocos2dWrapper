//*************************************************************************
//	��������:	2015-1-12
//	�ļ�����:	FKEventSystem.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../FKEngineCommonHead.h"
#include "TEventEngine.h"
//-------------------------------------------------------------------------
class OnVoteObj
{
public:
	bool operator() ( IVoteEventHandler* pHandler, EVENT_TYPE usID, unsigned short usSrcType,
		unsigned int unSrcID, const char* szEvent, int nEventLen )
	{
		if( pHandler == NULL )
			return false;
		return pHandler->OnVote( usID, usSrcType, unSrcID, szEvent, nEventLen );
	}
};
//-------------------------------------------------------------------------
class OnExecObj
{
public:
	bool operator() ( IExecEventHandler* pHandler, EVENT_TYPE usID, unsigned short usSrcType,
		unsigned int unSrcID, const char* szEvent, int nEventLen )
	{
		if( pHandler == NULL )
			return false;
		pHandler->OnExec( usID, usSrcType, unSrcID, szEvent, nEventLen );
		return true;
	}
};
//-------------------------------------------------------------------------
class FKEventSystem : public IEventSystem
{
private:
	typedef TEventEngine< IVoteEventHandler, OnVoteObj >		TCENTER_VOTE;
	typedef TEventEngine< IExecEventHandler, OnExecObj >		TCENTER_EXEC;
	TCENTER_VOTE				m_VoteCenter;		// ͶƱ����
	TCENTER_EXEC				m_ExecCenter;		// ִ������
public:
	FKEventSystem();
	~FKEventSystem();
public:
	// �ͷ�
	virtual void		Release();
	// ����ͶƱ�¼�
	// ����˵���μ����� OnVote
	// ����ֵ���Ƿ�ȫԱͶƱͨ��
	virtual bool		FireVote( EVENT_TYPE usID, unsigned short usSrcType,
		unsigned int unSrcID, const char* szEvent, int nEventLen );
	// ����ִ���¼�
	// ����˵���μ����� OnExec
	virtual void		FireExec( EVENT_TYPE usID, unsigned short usSrcType,
		unsigned int unSrcID, const char* szEvent, int nEventLen );
	// ����ͶƱ�¼�
	// ������pHandler ��������
	// ������usSrcType ������Դ���ͣ��μ����ö�٣�
	// ������unSrcID ������Ψһ��ʾ�������ǽ�ɫUID����ƷUID��
	//		�Լ�ĳ����ָ��ȣ�����Ϣ�����߼�����Ա�Լ��涨��
	//		��ֵ����Ϊ0�����ʾ����ȫ���������޶�ָ��ID
	// ������szDesc ��������Ķ��������������������log
	// ����ֵ���Ƿ�ɹ�����
	virtual bool		SubscibeVote( IVoteEventHandler* pHandler, EVENT_TYPE usID, 
		unsigned short usSrcType, unsigned int unSrcID = 0, const char* szDesc = NULL );
	// ����ִ���¼�
	// ��������ֵ��ͬ�Ϻ���
	virtual bool		SubscibeExec( IExecEventHandler* pHandler, EVENT_TYPE usID, 
		unsigned short usSrcType, unsigned int unSrcID = 0, const char* szDesc = NULL );
	// ȡ��һ��ͶƱ����
	virtual bool		UnSubscibeVote( IVoteEventHandler* pHandler, EVENT_TYPE usID, 
		unsigned short usSrcType, unsigned int unSrcID = 0 );
	// ȡ��һ��ִ�ж���
	virtual bool		UnSubscibeExec( IExecEventHandler* pHandler, EVENT_TYPE usID, 
		unsigned short usSrcType, unsigned int unSrcID = 0 );
};
//-------------------------------------------------------------------------
extern FKEventSystem gs_FKEventSystem;
//-------------------------------------------------------------------------