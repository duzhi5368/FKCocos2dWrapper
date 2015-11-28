//*************************************************************************
//	��������:	2015-1-12
//	�ļ�����:	IEventSystem.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
/*
	���ͣ�
		Q1��ʲô��voteͶƱ�¼�����ʲô�ġ�
		A1��������һ����ͶƱ��Ҫ��һ�����顣���й������������˶�����ӵ��ͶƱȨ��
			һ�����˲�֧��������飬�������Ͳ���ִ�С���ͶƱ�¼�����ģ�����������ġ�
			������Ϸ�����Ҫ����һ������BuySth( ... )���ú����ڿɽ���ͶƱ�¼�����
					GetEventSystem()->FireVote( BUY_EVENT_ID, .. )
			���ĵ��߹������Ϳ����ڹ��캯���н��и��¼��Ķ��ģ�
					GetEventSystem()->SubscibeVote( BUY_EVENT_ID, ... )
			һ�����ģ����κζ���Ҫ�������ʱ������������֪ͨ�������ཫ�õ�
					IVoteEventHandler::OnVote( BUY_EVENT_ID, ... )
			����Ϣ���õ�����Ϣ��ɽ��м�飬�����ͨ������ֵ��֪�������Լ��Ƿ�������¼�������
			���磬����Ǯ��������Ϊ��ҹ������ʱ��Ǯ����100���ֹ��������ߣ���α����Ϊ
					IVoteEventHandler::OnVote( BUY_EVENT_ID, ... ){ if(Gold<100)return false; else return true;}
			һ�������¼����ܲ������ǽ�Ǯ������ҪͶƱ���������������Ҳ�ᶩ�Ĳ�ͶƱ��
			�κ�һ��ͶƱ��Ͷ����Ʊ(return false;)�����˵õ���( fireVote���� )�������ֵ��Ϊfalse.
		Q2��ʲô��execִ���¼�����ʲô�ġ�
		A2������һ����Ϣ֪ͨ���ơ�ֻҪĳ�ඩ����ָ���¼������¼�����ʱ�����ཫ�õ�һ��֪ͨ��onExec() ��,
			ע����ˣ��κ����κεص㣨�κδ��봦�������Է����¼���֪ͨ��
			�յ�֪ͨ��(OnExec������)����Ȼ���Դ����µ�֪ͨ��ͨ��( GetEventSystem()->SubscibeExec( BUY_EVENT_ID, ... ))����,
			������Ҫ����A֪ͨB��B��֪ͨA��������ѭ���ص����֣��¼��յ����ò㼶�ı�����
		Q3����������ͬ��������ǣ�
		A3�����߶��Ǽ�ʱ֪ͨ�ģ�����Ҳ����һ�£������ڶ��������յ��¼�ʱ�����������Լ����߼�����( onVoteͬ��Ҳ���ԣ����ո���һ������Ʊ�ͺ��ˣ������Ƽ� )��
			�����������ߵĹ��ܣ���ΪVote��һƱ������ƣ����Ե�һ��������Ͷ�����Ʊ��
			���¼��Ѿ�ȷ�����������Vote����֪ͨ���������ߣ����ԣ����ĳ������OnVote�����߼�����
			�����ܲ��ܱ�֪ͨ������ȡ������֮ǰ�Ķ�����ͶƱ���������ͶƱ��˳���Ǽ�Ϊ���ҵģ���ʱû�����ȼ��ͱ�Ÿ��
			��Exec��Ȼ���Ա�֤ÿ�������߶������յ��¼�֪ͨ��
		Q4�����Ǽ�ʱ(�����õ�ͶƱ���������֪ͨ��ִ��)�ģ�������ʱ(�첽)�ģ�
		A4�����Ǽ�ʱ�ģ����̵߳ģ����̵õ�����ģ�������Ҫ�ȴ���һ�߼�֡��һ��ʱ�䡣
	ע�⣺IExecEventHandler ��Ҫ��������Ϣ�ַ�������Ҫ������Ϣ�ַ�����ʹ��IMsgDispatchSystem
*/
//-------------------------------------------------------------------------
// ��Ϣ���Ͷ���
typedef unsigned short EVENT_TYPE;
//-------------------------------------------------------------------------
// ͶƱ�¼���Ϣ����
class IVoteEventHandler
{
public:
	// �յ�ͶƱ��Ϣ����ص�
	// ������usID �¼�ID
	// ������usSrcType ������Դ���ͣ��μ����ö�٣�
	// ������unSrcID ������Ψһ��ʾ�������ǽ�ɫUID����ƷUID��
	//		�Լ�ĳ����ָ��ȣ�����Ϣ�����߼�����Ա�Լ��涨��
	// ������szEvent ��Ϣ��������ָ��
	// ������nEventLen ��Ϣ���ݵĳ���
	// ����ֵ���Ƿ�������¼�����( һƱ����� )
	virtual bool	OnVote( EVENT_TYPE usID, unsigned short usSrcType,
		unsigned int unSrcID, const char* szEvent, int nEventLen ) = 0;
};
//-------------------------------------------------------------------------
// ִ���¼���Ϣ����
class IExecEventHandler
{
public:
	// �յ�ִ����Ϣ����ص�
	// ������usID �¼�ID
	// ������usSrcType ������Դ���ͣ��μ����ö�٣�
	// ������unSrcID ������Ψһ��ʾ�������ǽ�ɫUID����ƷUID��
	//		�Լ�ĳ����ָ��ȣ�����Ϣ�����߼�����Ա�Լ��涨��
	// ������szEvent ��Ϣ��������ָ��
	// ������nEventLen ��Ϣ���ݵĳ���
	virtual void	OnExec( EVENT_TYPE usID, unsigned short usSrcType,
		unsigned int unSrcID, const char* szEvent, int nEventLen ) = 0;
};
//-------------------------------------------------------------------------
// �¼�ϵͳ
class IEventSystem
{
public:
	// �ͷ�
	virtual void		Release() = 0;
	// ����ͶƱ�¼�
	// ����˵���μ����� OnVote
	// ����ֵ���Ƿ�ȫԱͶƱͨ��
	virtual bool		FireVote( EVENT_TYPE usID, unsigned short usSrcType,
		unsigned int unSrcID, const char* szEvent, int nEventLen ) = 0;
	// ����ִ���¼�
	// ����˵���μ����� OnExec
	virtual void		FireExec( EVENT_TYPE usID, unsigned short usSrcType,
		unsigned int unSrcID, const char* szEvent, int nEventLen ) = 0;
	// ����ͶƱ�¼�
	// ������pHandler ��������
	// ������usSrcType ������Դ���ͣ��μ����ö�٣�
	// ������unSrcID ������Ψһ��ʾ�������ǽ�ɫUID����ƷUID��
	//		�Լ�ĳ����ָ��ȣ�����Ϣ�����߼�����Ա�Լ��涨��
	//		��ֵ����Ϊ0�����ʾ����ȫ���������޶�ָ��ID
	// ������szDesc ��������Ķ��������������������log
	// ����ֵ���Ƿ�ɹ�����
	virtual bool		SubscibeVote( IVoteEventHandler* pHandler, EVENT_TYPE usID, 
		unsigned short usSrcType, unsigned int unSrcID = 0, const char* szDesc = NULL ) = 0;
	// ����ִ���¼�
	// ��������ֵ��ͬ�Ϻ���
	virtual bool		SubscibeExec( IExecEventHandler* pHandler, EVENT_TYPE usID, 
		unsigned short usSrcType, unsigned int unSrcID = 0, const char* szDesc = NULL ) = 0;
	// ȡ��һ��ͶƱ����
	virtual bool		UnSubscibeVote( IVoteEventHandler* pHandler, EVENT_TYPE usID, 
		unsigned short usSrcType, unsigned int unSrcID = 0 ) = 0;
	// ȡ��һ��ִ�ж���
	virtual bool		UnSubscibeExec( IExecEventHandler* pHandler, EVENT_TYPE usID, 
		unsigned short usSrcType, unsigned int unSrcID = 0 ) = 0;
};
//-------------------------------------------------------------------------
// ��ȡ�¼��ַ����ӿ�
extern IEventSystem* GetEventSystem();
//-------------------------------------------------------------------------