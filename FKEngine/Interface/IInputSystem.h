//*************************************************************************
//	��������:	2015-1-14
//	�ļ�����:	IInputSystem.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
// ������Ϣ�ص�
class IInputMsgHandler
{
public:
	// �յ�������Ϣ�Ļص�������
	// ������unMsgType �������Ϣ���͡��μ�ENUM_InputMsgType��
	// ������nTouchID ������Ϣ��ID����Ϊkey��Ϣ�����ֵ��ЧΪ0
	// ������fPosX xλ��
	// ������fPosY y��Ϣ
	// ��������ϸ����ָ�룬���������Ϣ�ж�������ݣ��Ŵ�����С�������Ķ������ݣ��������򣩵ȣ�����¼�ڴˡ�
	// ����ֵ��������true��ʾ���Ժ���ĵ��ã���Ϣ������󴫵ݣ�������false���ʾ��Ϣ���������´���
	virtual bool	OnInputMessage( unsigned int unMsgType, int nTouchID, 
		float fPosX, float fPosY, void* pParam ) = 0;
};
//-------------------------------------------------------------------------
// ���������
class IInputSystem
{
public:
	// ��ʼ������
	virtual bool	Init() = 0;
	// �����ͷ�
	virtual void	Release() = 0;
	// ������Ϣ�ص�������
	virtual void	SetInputMsgCallback( IInputMsgHandler* pInputMsgCallback ) = 0;
	// �����Ƿ��������봦��
	virtual void	SetInputEnabled( bool bEnable ) = 0;
	// ��ȡ��Ϣ�ص�������
	virtual IInputMsgHandler* GetInputMsgCallback() const = 0;
};
//-------------------------------------------------------------------------
// ��ȡ���������
extern IInputSystem* GetInputSystem();
//-------------------------------------------------------------------------