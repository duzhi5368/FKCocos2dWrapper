//-------------------------------------------------------------------------
#include "FKMsgDispatchSystem.h"
//-------------------------------------------------------------------------
IMsgDispatchSystem* gs_pMsgDispatchSystem;
FKMsgDispatchSystem gs_FKMsgDispatchSystem;
//-------------------------------------------------------------------------
// ��ȡ��Ϣ�ַ����ӿ�
IMsgDispatchSystem* GetMsgDispatchSystem()
{
	return gs_pMsgDispatchSystem;
}
//-------------------------------------------------------------------------
FKMsgDispatchSystem::FKMsgDispatchSystem()
{
	gs_pMsgDispatchSystem = this;
}
//-------------------------------------------------------------------------
FKMsgDispatchSystem::~FKMsgDispatchSystem()
{
	gs_pMsgDispatchSystem = NULL;
}
//-------------------------------------------------------------------------
// �ͷ�
void FKMsgDispatchSystem::Release()
{
	m_MsgReceiverArray.clear();
}
//-------------------------------------------------------------------------
// �ַ���Ϣ
// ������szMsgData ��Ҫ�ַ�������ָ��
// ������nLen ��Ҫ�ַ������ݳ���
void FKMsgDispatchSystem::DispatchMsg( const char* szMsgData, int nLen )
{
	if( szMsgData == NULL )
		return;
	if( nLen < (sizeof(MSG_MAIN_TYPE) + sizeof(MSG_SUB_TYPE)) )
		return;

	MSG_MAIN_TYPE MainType = *(MSG_MAIN_TYPE*)szMsgData;
	MSG_SUB_TYPE SubType = *(MSG_SUB_TYPE*)( szMsgData + sizeof(MainType) );

	FKLOG("�ַ���Ϣ: MainType = %d, SubType = %d", static_cast<int>(MainType), static_cast<int>(SubType) );

	MESSAGE_RECEIVER_LIST::iterator Ite = m_MsgReceiverArray[MainType].begin();
	for (; Ite != m_MsgReceiverArray[MainType].end(); Ite++)
	{
		(*Ite)->OnNetMessage( szMsgData + sizeof(MainType), nLen - sizeof(MainType)); 
	}	
}
//-------------------------------------------------------------------------
// ע����Ϣ��������
// ������pHandler ��Ϣ��������
// ������usMainType ����Ϣ��
// ������usSubType ����Ϣ��
bool FKMsgDispatchSystem::RegisteMsgHandler( IMessageHandler* pHandler, 
											MSG_MAIN_TYPE usMainType, MSG_SUB_TYPE usSubType )
{
	if (pHandler == NULL)
	{
		return false;
	}
	
	MESSAGE_RECEIVER_ARRAY::iterator Itor = m_MsgReceiverArray.find(usMainType);
	if(Itor == m_MsgReceiverArray.end())
	{
		MESSAGE_RECEIVER_LIST list;
		list.clear();
		list.push_back(pHandler);
		m_MsgReceiverArray[usMainType] = list;
	}
	else
	{
		MESSAGE_RECEIVER_LIST::iterator Ite = std::find(
			m_MsgReceiverArray[usMainType].begin(), 
			m_MsgReceiverArray[usMainType].end(), pHandler);

		if (Ite != m_MsgReceiverArray[usMainType].end())
		{
			return false;
		}

		m_MsgReceiverArray[usMainType].push_back(pHandler);
	}

	

	return true;
}
//-------------------------------------------------------------------------
// ע����Ϣ��������
bool FKMsgDispatchSystem::UnregisterMsgHandler( IMessageHandler* pHandler, 
	MSG_MAIN_TYPE usMainType, MSG_SUB_TYPE usSubType )
{
	MESSAGE_RECEIVER_ARRAY::iterator Itor = m_MsgReceiverArray.find(usMainType);
	if(Itor == m_MsgReceiverArray.end())
	{
		return false;
	}

	MESSAGE_RECEIVER_LIST::iterator Ite = std::find(
		m_MsgReceiverArray[usMainType].begin(),
		m_MsgReceiverArray[usMainType].end(), pHandler);

	if (Ite == m_MsgReceiverArray[usMainType].end())
	{
		return false;
	}

	m_MsgReceiverArray[usMainType].erase(Ite);

	return true;
}
//-------------------------------------------------------------------------