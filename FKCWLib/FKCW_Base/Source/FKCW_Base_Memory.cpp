//--------------------------------------------------------------------
#include "../Include/FKCW_Base_Memory.h"
#include <memory.h>
//--------------------------------------------------------------------
bool g_bIsFlagAllocationLog = false;
//--------------------------------------------------------------------
#ifdef FKCW_MEMORY_TRACKING
//--------------------------------------------------------------------
// ����ڴ����
#define MEMORY_RECORD_INDEX_SIZE 0x10000
#define MEMORY_RECORD_INDEX_MASK 0xFFFF
//--------------------------------------------------------------------
// �ڴ��¼�ṹ
struct SMemoryRecord
{
	void*			m_pStart;			// �����ڴ����ʼλ
	int				m_nSize;			// �ڴ��С
	const char*		m_szFile;			// ������ڴ���ļ���
	int				m_nLine;			// ������ڴ������
	SMemoryRecord*	m_pNext;			// ��һ���ڴ���Ϣ��
};
//--------------------------------------------------------------------
static SMemoryRecord* s_MemoryRecord[MEMORY_RECORD_INDEX_SIZE] = { 0 };
static int s_TotalUsedMemory = 0;		// ��ʹ���ڴ���		
static int s_MaxUsedMemory = 0;			// ���ʹ�õ��ڴ���
static int s_TotalAlloc = 0;			// �ܷ���Ŀ���
static int s_TotalFree = 0;				// ���ͷŵĿ���
//--------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

void AddRecord( SMemoryRecord* r )
{
	// ��ȡhashλ��
	int hash = (uintptr_t)r->m_pStart & MEMORY_RECORD_INDEX_MASK;
	SMemoryRecord* pTemp = s_MemoryRecord[hash];
	SMemoryRecord* pPrev = NULL;

	// �ҵĿ���ʼ��С�Ƿ�ȴ���Ŀ���ʼ��С��
	while (pTemp) 
	{
		if (pTemp->m_pStart > r->m_pStart) 
		{
			break;
		}
		pPrev = pTemp;
		pTemp = pTemp->m_pNext;
	}

	// ���������ݵ���¼����
	if (pPrev == NULL) 
	{
		s_MemoryRecord[hash] = r;
		if (pTemp) 
		{
			r->m_pNext = pTemp;
		}
	} 
	else 
	{
		r->m_pNext = pPrev->m_pNext;
		pPrev->m_pNext = r;
	}

	// ����ͳ������
	s_TotalUsedMemory += r->m_nSize;
	s_MaxUsedMemory = (s_MaxUsedMemory > s_TotalUsedMemory ? s_MaxUsedMemory : s_TotalUsedMemory);
	s_TotalAlloc++;
}

SMemoryRecord* FindRecord( void* p ) 
{
	int hash = (uintptr_t)p & MEMORY_RECORD_INDEX_MASK;
	SMemoryRecord* pTemp = s_MemoryRecord[hash];
	SMemoryRecord* r = NULL;
	while (pTemp) 
	{
		if (pTemp->m_pStart == p) 
		{
			r = pTemp;
			break;
		}
		pTemp = pTemp->m_pNext;
	}
	return r;
}

SMemoryRecord* RemoveRecord(SMemoryRecord* r) 
{
	int hash = (uintptr_t)r->m_pStart & MEMORY_RECORD_INDEX_MASK;
	SMemoryRecord* pTemp = s_MemoryRecord[hash];
	SMemoryRecord* pPrev = NULL;
	while(pTemp) {
		if(pTemp == r) {
			break;
		}
		pPrev = pTemp;
		pTemp = pTemp->m_pNext;
	}

	// û�ҵ�
	if(pTemp != r) {
		CCLOG("[MEMRECORD] Unmatched record (%p)(record=%p):Size=%d [%s:Line=%d]", 
			r->m_pStart, r, r->m_nSize, r->m_szFile, r->m_nLine);
		return NULL;
	}

	// ɾ����¼
	if(pTemp == s_MemoryRecord[hash]) 
	{
		s_MemoryRecord[hash] = pTemp->m_pNext;
	}
	else 
	{
		pPrev->m_pNext = pTemp->m_pNext;
	}

	// ͬ����Ϣ
	s_TotalUsedMemory -= r->m_nSize;
	s_TotalFree++;

	r->m_pNext = NULL;
	return r;
}

void* _ccMalloc(size_t size, const char* file, int line, const char* logTag) 
{
	if (size == 0)
		return NULL;

	void* p = malloc(size);
	if (p) 
	{
		SMemoryRecord* r = (SMemoryRecord*)malloc(sizeof(SMemoryRecord));
		if(!r) 
		{
			free(p);
			p = NULL;
		} 
		else 
		{
			r->m_pStart = p;
			r->m_nSize = size;
			r->m_szFile = file;
			r->m_nLine = line;
			r->m_pNext = NULL;
			AddRecord(r);
		}

		if( g_bIsFlagAllocationLog )
		{
			CCLOG("[%s](%p)(record=%p):%d [%s:%d]", 
				logTag, r->m_pStart, r, r->m_nSize, r->m_szFile, r->m_nLine );
		}
	}

	return p;
}


void* _ccCalloc(size_t nitems, size_t size, const char* file, int line) 
{
	void* ptr = _ccMalloc(nitems * size, file, line, "CALLOC");
	memset(ptr, 0, nitems * size);
	return ptr;
}

void* _ccRealloc(void* ptr, size_t size, const char* file, int line) 
{
	SMemoryRecord* r = FindRecord(ptr);
	if(r) 
	{
		// ʵ�ʷ���
		void* newPtr = _ccMalloc(size, file, line, "REALLOC");
		memcpy(newPtr, ptr, r->m_nSize);
		free(ptr);

		// �Ƴ���¼
		RemoveRecord(r);
		free(r);

		return newPtr;
	} 
	else 
	{
		return realloc(ptr, size);
	}
}

void _ccFree(void* ptr, const char* file, int line) 
{
	if(!ptr)
		return;

	// ���Ҽ�¼��ɾ��
	SMemoryRecord* r = FindRecord(ptr);
	if(r) 
	{
		if( g_bIsFlagAllocationLog)
			CCLOG("[FREE](%p)(record=%p):%d [%s:%d]", r->m_pStart, r, r->m_nSize, r->m_szFile, r->m_nLine);
		RemoveRecord(r);
		free(r);
	}

	// ��ʹ�Ҳ�����¼�����Ǳ���ҲҪ�ͷ��ڴ�
	free(ptr);
}

#ifdef __cplusplus
}
#endif
//--------------------------------------------------------------------
#endif
//--------------------------------------------------------------------
// FKCW_Base_Memory
//--------------------------------------------------------------------
// ����ڴ�ʹ���б�
void FKCW_Base_Memory::PrintUasge()
{
#ifdef FKCW_MEMORY_TRACKING
	CCLOG("-----------------------------FKCW_Memory Uasge--------------------------------");
	CCLOG("[MEMREPORT] peak %d bytes, now %d bytes, alloc %d times, free %d times",
		s_MaxUsedMemory, s_TotalUsedMemory, s_TotalAlloc, s_TotalFree);
	CCLOG("------------------------------------------------------------------------------");
#endif
}
//--------------------------------------------------------------------
// ����ڴ�й¶��¼
void FKCW_Base_Memory::PrintDump()
{
#ifdef FKCW_MEMORY_TRACKING
	CCLOG("-----------------------------FKCW_Memory Dump--------------------------------");
	int leak = 0;
	int leakNum = 0;
	for (int i = 0; i < MEMORY_RECORD_INDEX_SIZE; i++) 
	{
		SMemoryRecord* r = s_MemoryRecord[i];
		while(r) 
		{
			CCLOG("%d.[MEMRECORD](%p)(record=%p):Size=%d [%s:Line=%d]", ++leakNum, 
				r->m_pStart, r, r->m_nSize, r->m_szFile, r->m_nLine );
			leak += r->m_nSize;
			r = r->m_pNext;
		}
	}

	if(leakNum > 0) 
	{
		CCLOG("[MEMRECORD] total leak = %d", leak);
	}
	else 
	{
		CCLOG("[MEMRECORD] no memory leak, congratulations!");
	}
	CCLOG("------------------------------------------------------------------------------");
#endif
}
//--------------------------------------------------------------------