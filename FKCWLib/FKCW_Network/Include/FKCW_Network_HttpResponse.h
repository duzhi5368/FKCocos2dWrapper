/********************************************************************
	created:	2014/11/01
	file base:	FKCW_Network_HttpResponse
	author:		FreeKnight
	
	purpose:	HTTPӦ��
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include "FKCW_Network_Macros.h"
#include "FKCW_Network_HttpRequest.h"
//--------------------------------------------------------------------
class FKCW_Network_HttpResponse : public CCObject
{
private:
	FKCW_Base_Data			m_pErrorData;
	CC_SYNTHESIZE(FKCW_Base_Data*, m_pData, Data);							// ���ӵ������ݶΣ�������֪ͨ
	CC_SYNTHESIZE_READONLY(FKCW_Network_HttpRequest*, m_pRequest, Request);	// http����
	CC_SYNTHESIZE_BOOL(m_bIsSuccess, Success);								// �ɹ���־
	CC_SYNTHESIZE(int, m_nResponseCode, ResponseCode);						// Ӧ��ֵ
	CC_SYNTHESIZE_PASS_BY_REF(CCDictionary, m_vecHeaders, Headers);			// ͷ��
public:
	FKCW_Network_HttpResponse( FKCW_Network_HttpRequest* p_pRequest )
		: m_bIsSuccess ( false )
		, m_pRequest( NULL )
		, m_nResponseCode( 0 )
	{
		m_pRequest = p_pRequest;
		CC_SAFE_RETAIN( m_pRequest );
	}
	virtual ~FKCW_Network_HttpResponse()
	{
		CC_SAFE_RELEASE( m_pRequest );
	}

	// ��ȡ������
	inline const FKCW_Base_Data& GetErrorData(){
		return m_pErrorData;
	}
	// ���ô�����
	inline void SetErrorData( char* p_szBuf ){
		m_pErrorData.AppendBytes((uint8_t*)p_szBuf, strlen(p_szBuf));
	}
	// ���ͷ
	inline void AddHeader( const string& p_strName, const string& p_strValue ){
		m_vecHeaders.setObject( CCString::create(FKCW_Base_Utils::Trim(p_strValue)), p_strName );
	}
	// ��ȡͷ
	inline string GetHeader( const string& p_strName ){
		CCString* pValue = (CCString*)m_vecHeaders.objectForKey( p_strName );
		return pValue ? pValue->getCString() : "";
	}

	//bool InitWithRequest( FKCW_Network_HttpRequest* p_pRequest );
};