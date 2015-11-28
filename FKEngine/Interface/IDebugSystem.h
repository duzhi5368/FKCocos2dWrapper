//*************************************************************************
//	��������:	2015-1-16
//	�ļ�����:	IDebugSystem.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#define FKDEBUG( format, ... )	GetDebugSystem()->LogDebug(format, ##__VA_ARGS__)
#define FKINFO( format, ... )	GetDebugSystem()->LogInfo(format, ##__VA_ARGS__)
#define FKERROR( format, ... )	GetDebugSystem()->LogError(format, ##__VA_ARGS__)
//-------------------------------------------------------------------------
// Debug������
class IDebugSystem
{
public:
	// �����ͷ�
	virtual void	Release() = 0;
	// �ر�ȫ��Debug��Ϊ
	virtual void	CloseDebugSystem() = 0;

	// ��ʾ/������Ϸ�п���̨���
	virtual bool	EnableGameConsole( bool bIsEnable ) = 0;
	// ����/�ر� Log ��־��¼
	virtual bool	EnableLogFile( bool bIsEnable ) = 0;
	// ����/�ر� WinConsole
	virtual bool	EnableWinConsole( bool bIsEnable ) = 0;
	// ����/�ر� FPS ����Ⱦ������ʾ
	virtual bool	EnableFPS( bool bIsEnable ) = 0;
	
	// �����Ϸ���ڴ�ռ��״��
	virtual void	DumpMemoryUse() = 0;
	// �����Ϸ���ڴ�й¶״��
	virtual void	DumpMemoryLeak() = 0;
	// �����Ϸ��Node��Ϣ
	virtual void	DumpNodeInfo() = 0;
	// �����Ϸ��Touch��Ϣ
	virtual void	DumpTouchInfo() = 0;
	// �����Ϸ������ʹ����Ϣ
	virtual void	DumpTextureInfo() = 0;
	// ���ȫ��Dump
	virtual void	DumpAll() = 0;

	// �����ͨ������Log
	virtual void	LogDebug( const char* pszFormat, ... ) = 0;
	// �����ϢʽLog
	virtual void	LogInfo( const char* pszFormat, ... ) = 0;
	// ��Ӵ���Log
	virtual void	LogError( const char* pszFormat, ... ) = 0;
};
//-------------------------------------------------------------------------
// ��ȡ���Թ�����ָ��
extern IDebugSystem* GetDebugSystem();
//-------------------------------------------------------------------------