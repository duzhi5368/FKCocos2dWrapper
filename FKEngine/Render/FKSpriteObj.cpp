//-------------------------------------------------------------------------
#include "FKSpriteObj.h"
#include "FKSpriteEx.h"
//-------------------------------------------------------------------------
FKSpriteObj::FKSpriteObj( RENDER_OBJ_ID id )
	: m_pSprite( NULL )
	, m_unID( id )
{
	m_strSpriteName.clear();
	m_strPicFileName.clear();
}
//-------------------------------------------------------------------------
FKSpriteObj::~FKSpriteObj()
{

}
//-------------------------------------------------------------------------
// ����FKSpriteObj����
bool FKSpriteObj::Create( const char* szPicFileName, const CCRect& rect, CCPoint ptOffset )
{
	if( szPicFileName == NULL )
		return false;

	if( rect.getMinX() == 0 && rect.getMinY() == 0 && 
		rect.getMaxX() == 0 && rect.getMaxY() == 0 )
	{
		m_pSprite = FKSpriteEx::Create( szPicFileName );
	}
	else
	{
		m_pSprite = FKSpriteEx::Create( szPicFileName, rect );
	}

	if( m_pSprite == NULL )
		return false;

	addChild( m_pSprite );
	m_pSprite->setPosition( ptOffset );

	m_strPicFileName = szPicFileName;

	static int nPicFileIndex = 0;
	++nPicFileIndex;
	char szBuf[1024] = {0};
	sprintf( szBuf, "%s_%d_%d_%d_%d_%d", szPicFileName, rect.getMinX(),
		rect.getMinY(), rect.getMaxX(), rect.getMaxY(), nPicFileIndex );
	m_strSpriteName = szBuf;

	return true;
}
//-------------------------------------------------------------------------
// ����
void FKSpriteObj::update( float dt )
{

}
//-------------------------------------------------------------------------
// �뿪�˳�
void FKSpriteObj::onExit()
{
	if( m_pSprite )
	{
		removeChild( m_pSprite, true );
		m_pSprite = NULL;
	}
}
//-------------------------------------------------------------------------
// ��ȡID
RENDER_OBJ_ID FKSpriteObj::GetID()
{
	return m_unID;
}
//-------------------------------------------------------------------------
// ����ID
void FKSpriteObj::SetID( RENDER_OBJ_ID unID )
{
	m_unID = unID;
}
//-------------------------------------------------------------------------
// ������ɫ
// ������tagColor ��ɫֵ
void FKSpriteObj::SetColor( const ccColor3B& tagColor )
{
	if( m_pSprite )
		m_pSprite->setColor( tagColor );
}
//-------------------------------------------------------------------------
// ����͸����
// ������byAlpha ͸����[0,255]
void FKSpriteObj::SetOpacity( unsigned char byAlpha )
{
	if( m_pSprite )
		m_pSprite->setOpacity( byAlpha );
}
//-------------------------------------------------------------------------
// ��ȡ��Ϸ������ͼ�ļ���
const std::string& FKSpriteObj::GetFileName()
{
	return m_strPicFileName;
}
//-------------------------------------------------------------------------
// ��ȡ��Ϸ������������(ȫ��Ψһ�ַ���)
const std::string& FKSpriteObj::GetDescName()
{
	return m_strSpriteName;
}
//-------------------------------------------------------------------------
// ��ײ���
// ������pt ����
// ����ֵ��true ��ʾ��ײ��false ��ʾδ��ײ
bool FKSpriteObj::HitTest( const CCPoint& pt )
{
	if( m_pSprite == nullptr )
		return false;

	CCRect rect = m_pSprite->boundingBox();
	return rect.containsPoint( pt );
}
//-------------------------------------------------------------------------
// ��ײ���
// ������rt ������
// ����ֵ��true ��ʾ��ײ��false ��ʾδ��ײ
bool FKSpriteObj::HitTest( const CCRect& rt )
{
	if( m_pSprite == nullptr )
		return false;

	CCRect rect = m_pSprite->boundingBox();
	return rect.intersectsRect( rt );
}
//-------------------------------------------------------------------------
// ��ȡ�����Χ��
bool FKSpriteObj::GetBoundingBox( CCRect& rt )
{
	if( m_pSprite == NULL )
		return false;

	rt = m_pSprite->boundingBox();
	rt = CCRectApplyAffineTransform( rt, nodeToParentTransform() );
	return true;
}
//-------------------------------------------------------------------------
// ����ƫ����
void FKSpriteObj::SetOffset( CCPoint& ptOffset )
{
	if( m_pSprite )
		m_pSprite->setPosition( ptOffset );
}
//-------------------------------------------------------------------------
// ��ȡƫ����
bool FKSpriteObj::GetOffset( CCPoint& ptOffset )
{
	if( m_pSprite )
	{
		ptOffset = m_pSprite->getPosition();
		return true;
	}
	return false;
}
//-------------------------------------------------------------------------
// ��ȡ����
CCSprite* FKSpriteObj::GetSprite()
{
	return ( dynamic_cast<CCSprite*>(m_pSprite) );
}
//-------------------------------------------------------------------------