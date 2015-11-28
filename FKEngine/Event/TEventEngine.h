//*************************************************************************
//	��������:	2015-1-12
//	�ļ�����:	TEventEngine.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKEventSystemMacros.h"
#include <map>

//#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
////#include <hash_map>
//#endif
//
//#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
////#include <ext/hash_map>
////using namespace std;
////#define stdext __gnu_cxx
//#endif
//-------------------------------------------------------------------------
// ��Ϣ���Ͷ���
typedef unsigned short EVENT_TYPE;
//-------------------------------------------------------------------------
// �¼�KeyԴ
struct SCoreEventKey
{
	unsigned int		m_unSrcID;		// ����ԴΨһ��ʾ�������ǽ�ɫUID����ƷUID���Լ�ĳ����ָ��ȣ�����Ϣ�����߼�����Ա�Լ��涨��
	unsigned short		m_usSrcType;	// ������Դ���ͣ��μ����ö�٣�
	EVENT_TYPE			m_usEventID;	// �����¼�ID
};
//-------------------------------------------------------------------------
// �¼�Key
//-------------------------------------------------------------------------
struct SEventKey
{
	union
	{
		SCoreEventKey		m_CoreKey;
		long long			m_RecalculateKey;
	};
	SEventKey(){ m_RecalculateKey = 0; }
	bool operator == ( const SEventKey& other ) const
	{
		return m_RecalculateKey == other.m_RecalculateKey;
	}
	bool operator < ( const SEventKey& other ) const
	{
		return m_RecalculateKey < other.m_RecalculateKey;
	}
};
//-------------------------------------------------------------------------
//// ��ݺ���
//#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
//	namespace stdext
//	{
//		inline size_t hash_value(const SEventKey &eventkey)
//		{
//			unsigned int k1 = (eventkey.m_CoreKey.m_unSrcID & 0xFFFF) << 16;
//			unsigned int k2 = (eventkey.m_CoreKey.m_usSrcType & 0xFF) << 8;
//			unsigned int k3 = eventkey.m_CoreKey.m_usEventID;
//			return k1 + k2 + k3;
//		}
//	}
//#else
//	namespace stdext
//	{
//		//template <>
//		//struct hash<SEventKey>
//		//{
//			inline size_t operator() (const SEventKey &eventkey) 
//			{
//				unsigned int k1 = (eventkey.m_CoreKey.m_unSrcID & 0xFFFF) << 16;
//				unsigned int k2 = (eventkey.m_CoreKey.m_usSrcType & 0xFF) << 8;
//				unsigned int k3 = eventkey.m_CoreKey.m_usEventID;
//				return k1 + k2 + k3;
//			}
//		//};
//	}
//#endif
//-------------------------------------------------------------------------
// �¼�����ģ��
template< class TRecvHander, class TFireEventObj >
class TEventEngine
{
private:
	// �¼���������Ϣ
	struct SSubscibeObjInfo
	{
		TRecvHander*		m_pHandler;		// ��������ָ��
		int					m_nCallCount;	// ����������ô���
		bool				m_bIsNeedRemove;// �Ƿ���Ҫɾ��
		char				m_szDesc[32];	// ������Ϣ������DEBUG

		SSubscibeObjInfo( TRecvHander* pHandler, const char* szDesc )
		{
			m_pHandler = pHandler;
			m_nCallCount = 0;
			m_bIsNeedRemove = false;
			memset( m_szDesc, 0, 32 );
			if( szDesc != NULL )
				memcpy( m_szDesc, szDesc, sizeof(szDesc) );
		}

		void AddRef()
		{
			m_nCallCount++;
		}
		void SubRef()
		{
			m_nCallCount--;
			if( m_nCallCount <= 0 )
				m_nCallCount = 0;
		}
	};

	// �����¼�������Key�б�
	typedef list<SSubscibeObjInfo>		LIST_SUBSCIBEOBJ_INFOS;
	// ȫ���¼�������Key�б�
	typedef std::map<SEventKey, LIST_SUBSCIBEOBJ_INFOS>	MAP_SUBSCIBEOBJ_INFOS;
private:
	MAP_SUBSCIBEOBJ_INFOS			m_mapSubsibeObjInfos;		// ȫ���¼��������б�
	TFireEventObj					m_FireEventObj;				// �¼�������
	int								m_nFiredLayerNum;			// �¼��Ѿ����͵Ĳ㼶��
public:
	TEventEngine()
		:m_nFiredLayerNum( 0 )
	{

	}
	virtual ~TEventEngine()
	{
		typename MAP_SUBSCIBEOBJ_INFOS::iterator Ite = m_mapSubsibeObjInfos.begin();
		for( ; Ite != m_mapSubsibeObjInfos.end(); ++Ite )
		{
			LIST_SUBSCIBEOBJ_INFOS* pList = &((*Ite).second);
			pList->clear();
		}
		m_mapSubsibeObjInfos.clear();
	}
	// �����¼�
	bool Subscibe( TRecvHander* pHandler, EVENT_TYPE usEventID, unsigned short usSrcType,
		unsigned int unSrcID, const char* szDesc )
	{
		if( pHandler == NULL )
			return false;
		// �¼�Key
		SEventKey tagEventKey;
		tagEventKey.m_CoreKey.m_usEventID = usEventID;
		tagEventKey.m_CoreKey.m_usSrcType = usSrcType;
		tagEventKey.m_CoreKey.m_unSrcID   = unSrcID;
		// ��������Ϣ
		SSubscibeObjInfo tagSubscibeObjInfo( pHandler, szDesc );

		// ��ӵ��������б���
		typename MAP_SUBSCIBEOBJ_INFOS::iterator Ite = m_mapSubsibeObjInfos.find( tagEventKey );
		if( Ite == m_mapSubsibeObjInfos.end() )
		{
			LIST_SUBSCIBEOBJ_INFOS tagList;
			tagList.push_front( tagSubscibeObjInfo );
			m_mapSubsibeObjInfos.insert( std::make_pair(tagEventKey, tagList) );
		}
		else
		{
			LIST_SUBSCIBEOBJ_INFOS* pList = &((*Ite).second);
			pList->push_front( tagSubscibeObjInfo );
		}
		return true;
	}
	// ȡ���¼�����
	bool UnSubscibe( TRecvHander* pHandler, EVENT_TYPE usEventID, 
		unsigned short usSrcType, unsigned int unSrcID )
	{
		if( pHandler == NULL )
			return false;
		// �¼�Key
		SEventKey tagEventKey;
		tagEventKey.m_CoreKey.m_usEventID = usEventID;
		tagEventKey.m_CoreKey.m_usSrcType = usSrcType;
		tagEventKey.m_CoreKey.m_unSrcID   = unSrcID;

		typename MAP_SUBSCIBEOBJ_INFOS::iterator Ite = m_mapSubsibeObjInfos.find( tagEventKey );
		if( Ite != m_mapSubsibeObjInfos.end() )
		{
			LIST_SUBSCIBEOBJ_INFOS* pList = &((*Ite).second);
			typename LIST_SUBSCIBEOBJ_INFOS::iterator IteList = pList->begin();
			for( ; IteList != pList->end(); ++IteList )
			{
				SSubscibeObjInfo* pInfo = &(*IteList);
				if( pInfo->m_pHandler == pHandler )
				{
					if( pInfo->m_nCallCount == 0 )
					{
						pList->erase( IteList );
					}
					else
					{
						pInfo->m_bIsNeedRemove = true;
					}
					break;
				}
			}
		}
		return true;
	}
	// ���Ͷ����¼�
	bool Fire( EVENT_TYPE usID, unsigned short usSrcType,
		unsigned int unSrcID, const char* szEventDesc, int nEventLen )
	{
		// �¼�Key
		SEventKey tagEventKey;
		tagEventKey.m_CoreKey.m_usEventID = usID;
		tagEventKey.m_CoreKey.m_usSrcType = usSrcType;
		tagEventKey.m_CoreKey.m_unSrcID   = unSrcID;

		// ����з�����ԴUID������һ�ε�������
		if( tagEventKey.m_CoreKey.m_unSrcID != 0 )
		{
			bool bRet = __Fire( tagEventKey, usID, usSrcType, unSrcID, szEventDesc, nEventLen );
			if( !bRet )
			{
				return false;
			}
		}

		// �����Ƿ��з�����ԴUID�Ķ�Ҫ����һ��ͨ�淢��
		tagEventKey.m_CoreKey.m_unSrcID = 0;
		bool bRet = __Fire( tagEventKey, usID, usSrcType, unSrcID, szEventDesc, nEventLen );
		if( !bRet )
		{
			return false;
		}

		return true;
	}
private:
	bool __Fire( SEventKey& tagEventKey, EVENT_TYPE usID, unsigned short usSrcType,
		unsigned int unSrcID, const char* szEventDesc, int nEventLen )
	{
		m_nFiredLayerNum++;		// ���Ӵ��ݲ㼶����

		if( m_nFiredLayerNum >= gs_MAX_EVENT_FIRE_LAYER_NUM )
		{
			FKLOG("�¼�������ѭ������ EventID = %d, SrcType = %d", usID, usSrcType );
			m_nFiredLayerNum--;
			return false;
		}

		typename MAP_SUBSCIBEOBJ_INFOS::iterator Ite = m_mapSubsibeObjInfos.find( tagEventKey );
		if( Ite != m_mapSubsibeObjInfos.end() )
		{
			LIST_SUBSCIBEOBJ_INFOS* pList = &((*Ite).second);
			typename LIST_SUBSCIBEOBJ_INFOS::iterator IteList = pList->begin();
			for( ; IteList != pList->end(); )
			{
				SSubscibeObjInfo* pInfo = &(*IteList);
				if( pInfo->m_nCallCount >= gs_MAX_EVENT_REF_LAYER_NUM )
				{
					FKLOG("Error:ͬһ�¼�ѭ������ EventID = %d, SrcType = %d", usID, usSrcType );
					m_nFiredLayerNum--;
					return false;
				}

				if( !pInfo->m_bIsNeedRemove )
				{
					// ����Ҫ�Ƴ�����ʵ�ʴ���
					bool bRet = false;

					try
					{
						// ����Ҫ�ݴ�������ʽϸ�= =
						pInfo->AddRef();
						bRet = m_FireEventObj(pInfo->m_pHandler, usID, usSrcType, unSrcID, szEventDesc, nEventLen );
						pInfo->SubRef();
					}
					catch ( ... )
					{
						pInfo->SubRef();
						FKLOG("�Ƿ��¼� EventID = %d, SrcType = %d", usID, usSrcType);
						return false;
					}

					{
						// ��Ϊ���������һ�������ٴα��޸�RemoveFlag��������������һ�����
						if( pInfo->m_bIsNeedRemove && pInfo->m_nCallCount == 0 )
						{
							IteList = pList->erase( IteList );
						}
						else
						{
							++IteList;
						}
					}

					if( !bRet )
					{
						m_nFiredLayerNum--;
						return false;
					}
				}
				else
				{
					// ���Ƴ���
					if( pInfo->m_nCallCount == 0 )
					{
						IteList = pList->erase( IteList );
					}
					else
					{
						++IteList;
					}
				}
			}
		}

		m_nFiredLayerNum--;

		return true;
	}
};