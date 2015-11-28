//*************************************************************************
//	��������:	2014-11-13
//	�ļ�����:	FKCW_Base_SHA1.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
/*  ���Բο�
	SHA1("abc") =
		A9993E36 4706816A BA3E2571 7850C26C 9CD0D89D
	SHA1("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq") =
		84983E44 1C3BD26E BAAE4AA1 F95129E5 E54670F1
	SHA1(һ����� "a") =
		34AA973C D4C4DAA4 F61EEB2B DBAD2731 6534016F
*/
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_Base_Macro.h"
#ifdef _MSC_VER
	#include <stdlib.h>
#endif
//-------------------------------------------------------------------------
// ��鶨���Сβ
#if (BYTE_ORDER==LITTLE_ENDIAN)
	#define SHA1_LITTLE_ENDIAN
#endif
//-------------------------------------------------------------------------
// ���� UINT_8 �� UINT_32
#ifndef UINT_32
	#ifdef _MSC_VER
		#define UINT_8  unsigned __int8
		#define UINT_32 unsigned __int32
	#else
		#define UINT_8 unsigned char

		#if (ULONG_MAX == 0xFFFFFFFF)
			#define UINT_32 unsigned long
		#else
			#define UINT_32 unsigned int
		#endif
	#endif
#endif
//-------------------------------------------------------------------------
typedef union
{
	UINT_8  c[64];
	UINT_32 l[16];
} USHA1WorkspaceBlock;
//-------------------------------------------------------------------------
// SHA1�㷨���������ݽ���ʹ��HMAC_SHA1��װ�ӿڣ��ر������ֱ��ʹ��
class FKCW_Base_SHA1
{
public:
	// ö��hashֵ�Ķ��ַ��ط�ʽ
	enum ENUM_ReportHashFormat
	{
		eReportHashFormat_Hex = 0,
		eReportHashFormat_Digit = 1
	};
public:
	FKCW_Base_SHA1();
	~FKCW_Base_SHA1();

	UINT_32 m_state[5];
	UINT_32 m_count[2];
	UINT_32 __reserved1[1];
	UINT_8  m_buffer[64];
	UINT_8  m_digest[20];
	UINT_32 __reserved2[3];

	void Reset();

	// Hashһ������
	void SHA1Hash(UINT_8 *data, UINT_32 len);
	// Hashһ���ļ�
	bool SHA1Hash(char *szFileName);

	// ���յ�Hash�������Hashֵ
	void Final();

	// ����Hashֵ����
	void GetHashValue(char *szReport, unsigned char uReportType = eReportHashFormat_Hex);
	void GetHashValue(UINT_8 *puDest);

private:
	// ˽��SHA-1ת������
	void __Transform(UINT_32 *state, UINT_8 *buffer);

private:
	UINT_8					m_pWorkspace[64];
	USHA1WorkspaceBlock*	m_pBlock; // SHA1�ֽ�ָ��
};
//-------------------------------------------------------------------------
// ��FKCW_Base_SHA1�ķ�װ
class FKCW_Base_HMAC_SHA1 : public FKCW_Base_SHA1
{
private:
	unsigned char m_ipad[64];
	unsigned char m_opad[64];

	char * szReport ;
	char * SHA1_Key ;
	char * AppendBuf1 ;
	char * AppendBuf2 ;
public:

	enum {
		SHA1_DIGEST_LENGTH	= 20,
		SHA1_BLOCK_SIZE		= 64,
		HMAC_BUF_LEN		= 4096
	} ;

	FKCW_Base_HMAC_SHA1()
		:szReport(new char[HMAC_BUF_LEN]),
		SHA1_Key(new char[HMAC_BUF_LEN]),
		AppendBuf1(new char[HMAC_BUF_LEN]),
		AppendBuf2(new char[HMAC_BUF_LEN])
	{}

	~FKCW_Base_HMAC_SHA1()
	{
		delete[] szReport ;
		delete[] AppendBuf1 ;
		delete[] AppendBuf2 ;
		delete[] SHA1_Key ;
	}

	void HMAC_SHA1(unsigned char *text, int text_len, unsigned char *key, int key_len, unsigned char *digest);
};
//-------------------------------------------------------------------------