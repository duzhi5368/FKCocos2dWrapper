//-------------------------------------------------------------------------
#include "FKRenderText.h"
//-------------------------------------------------------------------------
FKRenderText::FKRenderText( RENDER_OBJ_ID unID )
	: m_unID( unID )
	, m_pLabelBMP( NULL )
	, m_pLabelTTF( NULL )
	, m_tagPos( CCPointZero )
	, m_pParent( NULL )
	, m_byAlpha( 255 )
	, m_eHA( eTHA_Left )
	, m_eVA( eTVA_Center )
{
	m_strContent.clear();
	m_tagColor = ccc3( 255, 255, 255 );
}
//-------------------------------------------------------------------------
FKRenderText::~FKRenderText()
{

}
//-------------------------------------------------------------------------
// ��������
bool FKRenderText::Create( const char* szString, const char* szFontName, 
	int nFontSize,  CCSize tagDimentions )
{
	if( szString == NULL )
		return false;
	if( szFontName == NULL )
		return false;

	m_pLabelTTF = CCLabelTTF::create( szString, szFontName, (float)nFontSize,
		tagDimentions, (CCTextAlignment)m_eHA, (CCVerticalTextAlignment)m_eVA );
	if( m_pLabelTTF == NULL )
		return false;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    m_pLabelTTF->enableStroke(ccc3(10,0,10),0.5f);
    m_pLabelTTF->enableShadow(CCSizeMake(2, -2), 255, 2);
#endif
	return true;
}
//-------------------------------------------------------------------------
// ����BMP����
bool FKRenderText::CreateByBMP( const char* szString, const char* szFontName, 
	int nFontSize,  CCSize tagDimentions )
{
	if( szString == NULL )
		 return false;
	if( szFontName == NULL )
		return false;

	m_pLabelBMP = CCLabelBMFont::create( szString, szFontName,
		kCCLabelAutomaticWidth, kCCTextAlignmentCenter );
	if( m_pLabelBMP == NULL )
		return false;

	return true;
}
//-------------------------------------------------------------------------
// ��ȡID
RENDER_OBJ_ID FKRenderText::GetID()
{
	return m_unID;
}
//-------------------------------------------------------------------------
// �ͷ�
void FKRenderText::Release()
{
	Detach();

	m_pLabelBMP = NULL;
	m_pLabelTTF = NULL;

	delete this;
}
//-------------------------------------------------------------------------
// �󶨵�������
bool FKRenderText::Attach( CCNode* pParentNode, int nZOrder, int nTag )
{
	if( pParentNode == nullptr )
		return false;
	if( m_pParent == pParentNode )
		return true;

	// ������
	if( m_pParent )
	{
		if( m_pLabelTTF )
		{
			m_pLabelTTF->retain();
			m_pParent->removeChild( m_pLabelTTF );
		}
		if( m_pLabelBMP )
		{
			m_pLabelBMP->retain();
			m_pParent->removeChild( m_pLabelBMP );
		}
	}

	if( m_pLabelBMP )
		pParentNode->addChild( m_pLabelBMP, nZOrder, nTag );
	if( m_pLabelTTF )
		pParentNode->addChild( m_pLabelTTF, nZOrder, nTag );

	m_pParent = pParentNode;
	return true;
}
//-------------------------------------------------------------------------
// �ӳ����н��
void FKRenderText::Detach()
{
	if( m_pParent )
	{
		if( m_pLabelTTF )
			m_pParent->removeChild( m_pLabelTTF );
		if( m_pLabelBMP )
			m_pParent->removeChild( m_pLabelBMP );

		m_pParent = NULL;
		m_pLabelBMP = NULL;
		m_pLabelTTF = NULL;
	}
}
//-------------------------------------------------------------------------
// ����λ��
void FKRenderText::SetPos( const CCPoint& tagPos )
{
	if( m_pLabelTTF )
		m_pLabelTTF->setPosition( tagPos );
	if( m_pLabelBMP )
		m_pLabelBMP->setPosition( tagPos );
}
//-------------------------------------------------------------------------
// �����ַ���
void FKRenderText::SetString( const char* szText )
{
	if( szText == NULL )
		return;
	if( m_strContent == szText )
		return;

	m_strContent = szText;

	if( m_pLabelTTF )
		m_pLabelTTF->setString( m_strContent.c_str() );
	if( m_pLabelBMP )
		m_pLabelBMP->setString( m_strContent.c_str() );
}
//-------------------------------------------------------------------------
// ������ɫ
void FKRenderText::SetColor( const ccColor3B& color )
{
	if( m_pLabelTTF )
		m_pLabelTTF->setColor( color );
	if( m_pLabelBMP )
		m_pLabelBMP->setColor( color );
}
//-------------------------------------------------------------------------
// ����͸����
void FKRenderText::SetOpacity( unsigned char byAlpha )
{
	if( m_pLabelTTF )
		m_pLabelTTF->setOpacity( byAlpha );
	if( m_pLabelBMP )
		m_pLabelBMP->setOpacity( byAlpha );
}
//-------------------------------------------------------------------------
// ���������ʽ
void FKRenderText::SetFont( const char* szFont )
{
	if( m_pLabelTTF )
		m_pLabelTTF->setFontName( szFont );
}
//-------------------------------------------------------------------------
// ������ʾ����
void FKRenderText::SetDeimensions( const CCSize& tagDeimensions )
{
	if( m_tagDimentions.equals(tagDeimensions) )
		return;

	m_tagDimentions = tagDeimensions;

	if( m_pLabelTTF )
		m_pLabelTTF->setDimensions( m_tagDimentions );
}
//-------------------------------------------------------------------------
// ��������ˮƽ���뷽ʽ
void FKRenderText::SetHorizontalAlignment( ENUM_TextHorizontalAlignment eType )
{
	if( m_eHA == eType )
		return;

	m_eHA = eType;

	if( m_pLabelTTF )
		m_pLabelTTF->setHorizontalAlignment( (CCTextAlignment) eType );
	if( m_pLabelBMP )
		m_pLabelBMP->setAlignment( (CCTextAlignment) eType );
}
//-------------------------------------------------------------------------
// �������ִ�ֱ���뷽ʽ
void FKRenderText::SetVerticalAlignment( ENUM_TextVerticalAlignment eType )
{
	if( m_eVA == eType )
		return;

	m_eVA = eType;

	if( m_pLabelTTF )
		m_pLabelTTF->setVerticalAlignment( (CCVerticalTextAlignment) eType );
}
//-------------------------------------------------------------------------