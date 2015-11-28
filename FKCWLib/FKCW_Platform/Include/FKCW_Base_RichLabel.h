//*************************************************************************
//	��������:	2014-10-27
//	�ļ�����:	FKCW_Base_RichLabel.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "cocos2d.h"
#include <vector>
#include "FKCW_Base_Types.h"
#include "FKCW_Base_Macro.h"
//-------------------------------------------------------------------------
USING_NS_CC;
using std::vector;
//-------------------------------------------------------------------------
// �����������Ԫ��Ϣ
struct SLinkMeta
{
	int			m_nTag;					// �����ӱ�ǩ�����������ͬһ��ǩ��
	int			m_nNormalBGColor;
	int			m_nSelectedBGColor;
	// ������
	float		m_fX;
	float		m_fY;
	float		m_fWidth;
	float		m_fHeight;
};
typedef vector<SLinkMeta>		LinkMetaList;
//-------------------------------------------------------------------------
class FKCW_Base_RichLabel : public CCImage
{
public:
	FKCW_Base_RichLabel();
	virtual ~FKCW_Base_RichLabel();
public:
	// ����һ�����ı��ַ�����ռ��ʾ��С������Ҫʹ��openGL������㣩
	/* ������
	* p_szText ���ı��ַ���
	* p_szFontName ��������
	* p_nSize �����С
	* p_nMaxWidth �����ʾ��ȡ�0��ʾ�����ı�
	* p_fShadowOffsetX ��ӰXƫ��
	* p_fShadowOffsetY ��ӰYƫ��
	* p_fStrokeSize �߿��߿��
	* p_fLineSpacing �м��
	* p_fGlobalImageScaleFactor���ı��е�ͼƬ���ű�
	* p_pDecryptFunc ������ı�����ͼƬ���ܣ�����Ҫ�ṩ���ܺ���
	*/
	static CCSize MeasureRichString( const char* p_szText, const char* p_szFontName = NULL,
		int p_nSize = 0, int p_nMaxWidth = 0, float p_fShadowOffsetX = 0.0f, float p_fShadowOffsetY = 0.0f,
		float p_fStrokeSize = 0.0f, float p_fLineSpacing = 0.0f, 
		float p_fGlobalImageScaleFactor = 1.0f, DECRYPT_FUNC p_pDecryptFunc = NULL );
public:
	bool InitWithRichStringShadowStroke( const char* p_szText,
		int			p_nWidth			= 0,
		int			p_nHeight			= 0,
		ETextAlign	p_eAlignMask		= kAlignCenter,
		const char* p_szFontName		= NULL,
		int			p_nSize				= 0,
		float		p_fTextTintR		= 0.0f,
		float		p_fTextTintG		= 0.0f,
		float		p_fTextTintB		= 0.0f,
		bool		p_nShadow			= false,
		float		p_fShadowOffsetX	= 0.0f,
		float		p_fShadowOffsetY	= 0.0f,
		int			p_nShadowColor		= 0,
		float		p_nShadowBlur		= 0.0f,
		bool		p_nStroke			= false,
		float		p_fStrokeR			= 1.0f,
		float		p_fStrokeG			= 1.0f,
		float		p_fStrokeB			= 1.0f,
		float		p_fStrokeSize		= 1.0f,
		float		p_fLineSpacing		= 0.0f,
		float		p_fGlobalImageScale	= 1.0f,
		int			p_nToCharIndex		= -1,
		float		p_fElapsedTime		= 0.0f,
		DECRYPT_FUNC p_pDecryptFunc		= NULL
		);

public:
	// ��Ӱ�ͱ߿���ֵ
	CC_SYNTHESIZE_READONLY_PASS_BY_REF(CCPoint, m_tagShadowStrokePadding, ShadowStrokePadding);
	// ����Ԫ��
	CC_SYNTHESIZE_READONLY_PASS_BY_REF(LinkMetaList, m_vecLinkMetas, LinkMetas);
	// ͼƬԪ��
	CC_SYNTHESIZE_READONLY_PASS_BY_REF(vector<CCRect>, m_vecImageRects, ImageRects);
	// ��������ʽ���ַ�������
	CC_SYNTHESIZE(int, m_nRealLength, RealLength);
	// �Ƿ���Ҫÿ֡����( ������Чʱ����ֵΪtrue�������֡����)
	CC_SYNTHESIZE_BOOL(m_bIsNeedUpdate, NeedUpdate);
};