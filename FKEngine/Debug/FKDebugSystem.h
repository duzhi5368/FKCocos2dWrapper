//*************************************************************************
//	��������:	2015-1-16
//	�ļ�����:	FKDebugSystem.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../FKEngineCommonHead.h"
//-------------------------------------------------------------------------
class FKDebugSystem : public IDebugSystem
{
public:
	FKDebugSystem();
	~FKDebugSystem();
public:
	// �����ͷ�
	virtual void	Release();
	// �ر�ȫ��Debug��Ϊ
	virtual void	CloseDebugSystem();

	// ��ʾ/������Ϸ�п���̨���
	virtual bool	EnableGameConsole( bool bIsEnable );
	// ����/�ر� Log ��־��¼
	virtual bool	EnableLogFile( bool bIsEnable );
	// ����/�ر� WinConsole
	virtual bool	EnableWinConsole( bool bIsEnable );
	// ����/�ر� FPS ����Ⱦ������ʾ
	virtual bool	EnableFPS( bool bIsEnable );

	// �����Ϸ���ڴ�ռ��״��
	virtual void	DumpMemoryUse();
	// �����Ϸ���ڴ�й¶״��
	virtual void	DumpMemoryLeak();
	// �����Ϸ��Node��Ϣ
	virtual void	DumpNodeInfo();
	// �����Ϸ��Touch��Ϣ
	virtual void	DumpTouchInfo();
	// �����Ϸ������ʹ����Ϣ
	virtual void	DumpTextureInfo();
	// ���Ӳ��״����Ϣ
	virtual void	DumpConfigurationInfo();
	// ���ȫ��Dump
	virtual void	DumpAll();

	// �����ͨ������Log
	virtual void	LogDebug( const char* pszFormat, ... );
	// �����ϢʽLog
	virtual void	LogInfo( const char* pszFormat, ... );
	// ��Ӵ���Log
	virtual void	LogError( const char* pszFormat, ... );
private:
	bool			m_bIsUseLogFile;		// �Ƿ�ʹ��LogFile
};
//-------------------------------------------------------------------------
extern FKDebugSystem gs_FKDebugSystem;
//-------------------------------------------------------------------------