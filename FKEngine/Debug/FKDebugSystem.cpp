//*************************************************************************
//	��������:	2015-1-16
//	�ļ�����:	FKDebugSystem.cpp
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKDebugSystem.h"
//-------------------------------------------------------------------------
#ifndef MAX_LOG_LEN
#define MAX_LOG_LEN         (cocos2d::kMaxLogLen + 1)
#endif
//-------------------------------------------------------------------------
IDebugSystem* gs_pDebugSystem;
FKDebugSystem gs_FKDebugSystem;
//-------------------------------------------------------------------------
// ��ȡ���Թ�����ָ��
IDebugSystem* GetDebugSystem()
{
	return gs_pDebugSystem;
}
//-------------------------------------------------------------------------
FKDebugSystem::FKDebugSystem()
	: m_bIsUseLogFile( true )
{
	FKCW_Base_Utils::CreateWinConsole();

	gs_pDebugSystem = this;
}
//-------------------------------------------------------------------------
FKDebugSystem::~FKDebugSystem()
{
	gs_pDebugSystem = NULL;
}
//-------------------------------------------------------------------------
// �����ͷ�
void FKDebugSystem::Release()
{
	CloseDebugSystem();

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	FreeConsole();
#endif
}
//-------------------------------------------------------------------------
// �ر�ȫ��Debug��Ϊ
void FKDebugSystem::CloseDebugSystem()
{
	EnableGameConsole( false );
	EnableLogFile( false );
	EnableWinConsole( false );
	EnableFPS( false );
}
//-------------------------------------------------------------------------
// ��ʾ/������Ϸ�п���̨���
bool FKDebugSystem::EnableGameConsole( bool bIsEnable )
{
	return true;
}
//-------------------------------------------------------------------------
// ����/�ر� Log ��־��¼
bool FKDebugSystem::EnableLogFile( bool bIsEnable )
{
	m_bIsUseLogFile = bIsEnable;
	return true;
}
//-------------------------------------------------------------------------
// ����/�ر� WinConsole
bool FKDebugSystem::EnableWinConsole( bool bIsEnable )
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	if( bIsEnable )
	{
		ShowWindow(GetConsoleWindow(), SW_SHOW);
	}
	else
	{
		ShowWindow(GetConsoleWindow(), SW_HIDE);
	}
#endif
	return true;
}
//-------------------------------------------------------------------------
// ����/�ر� FPS ����Ⱦ������ʾ
bool FKDebugSystem::EnableFPS( bool bIsEnable )
{
	CCDirector *pDirector = CCDirector::sharedDirector();
	if( pDirector == NULL )
	{
		return false;
	}
	pDirector->setDisplayStats( bIsEnable );
	return true;
}
//-------------------------------------------------------------------------
// �����Ϸ���ڴ�ռ��״��
void FKDebugSystem::DumpMemoryUse()
{
	FKCW_Base_Memory::PrintUasge();
}
//-------------------------------------------------------------------------
// �����Ϸ���ڴ�й¶״��
void FKDebugSystem::DumpMemoryLeak()
{
	FKCW_Base_Memory::PrintDump();
}
//-------------------------------------------------------------------------
// �����Ϸ��Node��Ϣ
void FKDebugSystem::DumpNodeInfo()
{
	CCScene* p = CCDirector::sharedDirector()->getRunningScene();
	if( p )
		p->Dump();
}
//-------------------------------------------------------------------------
// �����Ϸ��Touch��Ϣ
void FKDebugSystem::DumpTouchInfo()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->Dump();
}
//-------------------------------------------------------------------------
// �����Ϸ������ʹ����Ϣ
void FKDebugSystem::DumpTextureInfo()
{
	CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
}
//-------------------------------------------------------------------------
// ���Ӳ��״����Ϣ
void FKDebugSystem::DumpConfigurationInfo()
{
	CCConfiguration::sharedConfiguration()->dumpInfo();
}
//-------------------------------------------------------------------------
// ���ȫ��Dump
void FKDebugSystem::DumpAll()
{
	DumpMemoryUse();
	DumpMemoryLeak();
	DumpNodeInfo();
	DumpTouchInfo();
	DumpTextureInfo();
	DumpConfigurationInfo();
}
//-------------------------------------------------------------------------
// �����ͨ������Log
void FKDebugSystem::LogDebug( const char* pszFormat, ... )
{
	char szBuf[MAX_LOG_LEN - 20] = {0};
	char szShowBuf[MAX_LOG_LEN] = { 0 };

	struct tm *tm;  
	time_t timep;  
	time(&timep);  
	tm = localtime(&timep);  
	int hour=tm->tm_hour;  
	int minute=tm->tm_min;  
	int second=tm->tm_sec;
	char szTime[10] = { 0 };
	sprintf( szTime, "%02d:%02d:%02d",  hour, minute, second );

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	
	va_list ap;
	va_start(ap, pszFormat);
	vsnprintf_s(szBuf, MAX_LOG_LEN - 20, MAX_LOG_LEN - 20, pszFormat, ap);
	va_end(ap);

	sprintf( szShowBuf, "%s - %s", szTime, szBuf );

	OutputDebugStringA(szShowBuf);
	OutputDebugStringA("\n");
	puts(szShowBuf);

#else
	va_list ap;
	va_start(ap, pszFormat);
	vsnprintf(szBuf, MAX_LOG_LEN - 20, pszFormat, ap);//MAX_LOG_LEN - 20, 
	va_end(ap);
	sprintf( szShowBuf, "%s - %s", szTime, szBuf );
	CCLOG(szBuf);
#endif

	if( m_bIsUseLogFile )
	{
		FKCW_Base_Utils::FKFileLog( szShowBuf );
	}
	
}
//-------------------------------------------------------------------------
// �����ϢʽLog
void FKDebugSystem::LogInfo( const char* pszFormat, ... )
{
	char szBuf[MAX_LOG_LEN - 20] = {0};
	char szShowBuf[MAX_LOG_LEN] = { 0 };

	struct tm *tm;  
	time_t timep;  
	time(&timep);  
	tm = localtime(&timep);  
	int hour=tm->tm_hour;  
	int minute=tm->tm_min;  
	int second=tm->tm_sec;
	char szTime[10] = { 0 };
	sprintf( szTime, "%02d:%02d:%02d",  hour, minute, second );

	

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	va_list ap;
	va_start(ap, pszFormat);
	vsnprintf_s(szBuf, MAX_LOG_LEN - 20, MAX_LOG_LEN - 20, pszFormat, ap);
	va_end(ap);

	sprintf( szShowBuf, "%s - %s [L]%d - %s", szTime, __FILE__, __LINE__, szBuf );

	OutputDebugStringA(szShowBuf);
	OutputDebugStringA("\n");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsole != INVALID_HANDLE_VALUE)
	{
		SetConsoleTextAttribute(hConsole, eConsolBKColor_Gray | eConsolTextColor_Ching );
	}
	puts(szShowBuf);
#else
	va_list ap;
	va_start(ap, pszFormat);
	vsnprintf(szBuf, MAX_LOG_LEN - 20, pszFormat, ap);// MAX_LOG_LEN - 20,
	va_end(ap);
	sprintf( szShowBuf, "%s - %s", szTime, szBuf );
	CCLOG(szBuf);
#endif

	if( m_bIsUseLogFile )
	{
		FKCW_Base_Utils::FKFileLog( szShowBuf );
	}

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	if (hConsole != INVALID_HANDLE_VALUE)
	{
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
#endif
}
//-------------------------------------------------------------------------
// ��Ӵ���Log
void FKDebugSystem::LogError( const char* pszFormat, ... )
{
	char szBuf[MAX_LOG_LEN - 20] = {0};
	char szShowBuf[MAX_LOG_LEN] = { 0 };

	struct tm *tm;  
	time_t timep;  
	time(&timep);  
	tm = localtime(&timep);  
	int hour=tm->tm_hour;  
	int minute=tm->tm_min;  
	int second=tm->tm_sec;
	char szTime[10] = { 0 };
	sprintf( szTime, "%02d:%02d:%02d",  hour, minute, second );


#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	va_list ap;
	va_start(ap, pszFormat);
	vsnprintf_s(szBuf, MAX_LOG_LEN - 20, MAX_LOG_LEN - 20, pszFormat, ap);
	va_end(ap);

	sprintf( szShowBuf, "%s - %s [L]%d - %s", szTime, __FILE__, __LINE__, szBuf );
	OutputDebugStringA(szShowBuf);
	OutputDebugStringA("\n");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsole != INVALID_HANDLE_VALUE)
	{
		SetConsoleTextAttribute(hConsole, eConsolBKColor_Yellow | eConsolTextColor_Red );
	}
	puts(szShowBuf);
#else
	va_list ap;
	va_start(ap, pszFormat);
	vsnprintf(szBuf, MAX_LOG_LEN - 20,pszFormat, ap);// MAX_LOG_LEN - 20, 
	va_end(ap);
	sprintf( szShowBuf, "%s - %s", szTime, szBuf );
	CCLOG(szBuf);
#endif
	if( m_bIsUseLogFile )
	{
		FKCW_Base_Utils::FKFileLog( szShowBuf );
	}
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	if (hConsole != INVALID_HANDLE_VALUE)
	{
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
#endif
}
//-------------------------------------------------------------------------