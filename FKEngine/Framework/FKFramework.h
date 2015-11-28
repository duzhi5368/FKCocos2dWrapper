//*************************************************************************
//	��������:	2015-1-14
//	�ļ�����:	FKFramework.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../FKEngineCommonHead.h"
//-------------------------------------------------------------------------
class FKFramework : public CCApplication, public IInputMsgHandler
{
public:
	FKFramework();
	virtual ~FKFramework();
public:
	// ����̳�
	virtual bool	SubInit() = 0;
	virtual void	SubUpdate( float dt ) = 0;
	virtual void	SubRelease() = 0;
public:
	// ��ʼ��
	virtual bool	Init( float fWidth, float fHeight );
	// ��ʼ��ϵͳ( ����Init )
	virtual bool	InitSystem();
	// ֡����
	virtual void	UpdateFrame( float dt );
	// �ͷŹ���
	virtual void	Release();
	// ִ��ѭ��
	virtual int		Run();
public:
	// ����Ӧ�ó���
	bool			applicationDidFinishLaunching();
	// Ӧ�ó�������̨
    void			applicationDidEnterBackground();
	// Ӧ�ó������ǰ̨
    void			applicationWillEnterForeground();
public:
	// �յ�������Ϣ�Ļص�������
	// ������unMsgType �������Ϣ���͡��μ�ENUM_InputMsgType��
	// ������nTouchID ������Ϣ��ID����Ϊkey��Ϣ�����ֵ��ЧΪ0
	// ������fPosX xλ��
	// ������fPosY y��Ϣ
	// ��������ϸ����ָ�룬���������Ϣ�ж�������ݣ��Ŵ�����С�������Ķ������ݣ��������򣩵ȣ�����¼�ڴˡ�
	// ����ֵ��������true��ʾ���Ժ���ĵ��ã���Ϣ������󴫵ݣ�������false���ʾ��Ϣ���������´���
	virtual bool	OnInputMessage( unsigned int unMsgType, int nTouchID, 
		float fPosX, float fPosY, void* pParam );

};
//-------------------------------------------------------------------------