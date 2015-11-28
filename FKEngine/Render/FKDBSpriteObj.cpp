//-------------------------------------------------------------------------
#include "FKDBSpriteObj.h"
//-------------------------------------------------------------------------
FKDBSpriteObj::FKDBSpriteObj( RENDER_OBJ_ID id )
	: m_unID( id )
	, m_pSprite( NULL )
{
	m_strFileName.clear();
	m_strDescName.clear();
}
//-------------------------------------------------------------------------
FKDBSpriteObj::~FKDBSpriteObj()
{

}
//-------------------------------------------------------------------------
// ����FKSprite����
bool FKDBSpriteObj::Create( const char* szPicFileName, CCPoint ptOffset )
{
	m_pSprite = new CCocos2dxDBSprite();
	if( m_pSprite == NULL )
	{
		return false;
	}
	if( !m_pSprite->create( szPicFileName, ptOffset ) )
	{
		CC_SAFE_DELETE( m_pSprite );
		return false;
	}
	m_pSprite->setID( m_unID );
	m_pSprite->setOffset( ptOffset );
	this->addChild( m_pSprite );
	return true;
}
//-------------------------------------------------------------------------
// ����
void FKDBSpriteObj::update( float dt )
{

}
//-------------------------------------------------------------------------
// �뿪�˳�
void FKDBSpriteObj::onExit()
{
	CCNode::onExit();
	CC_SAFE_DELETE( m_pSprite );
}
//-------------------------------------------------------------------------
// ��ȡID
RENDER_OBJ_ID FKDBSpriteObj::GetID()
{
	if( m_pSprite )
		return m_pSprite->getID();
	return m_unID;
}
//-------------------------------------------------------------------------
// ����ID
void FKDBSpriteObj::SetID( RENDER_OBJ_ID unID )
{
	m_unID = unID;
	if( m_pSprite )
		m_pSprite->setID( unID );
}
//-------------------------------------------------------------------------
// ������ɫ
// ������tagColor ��ɫֵ
void FKDBSpriteObj::SetColor( const ccColor3B& tagColor )
{
	if( m_pSprite )
		m_pSprite->setColor( tagColor );
}
//-------------------------------------------------------------------------
// ����͸����
// ������byAlpha ͸����[0,255]
void FKDBSpriteObj::SetOpacity( unsigned char byAlpha )
{
	if( m_pSprite )
		m_pSprite->setOpacity( byAlpha );
}
//-------------------------------------------------------------------------
// ��ȡ��Ϸ������ͼ�ļ���
const std::string& FKDBSpriteObj::GetFileName()
{
	m_strFileName.clear();
	if( m_pSprite )
		m_strFileName = m_pSprite->getFileName();
	return m_strFileName;
}
//-------------------------------------------------------------------------
// ��ȡ��Ϸ������������(ȫ��Ψһ�ַ���)
const std::string& FKDBSpriteObj::GetDescName()
{
	m_strDescName.clear();
	if( m_pSprite )
		m_pSprite->getFeatureString( m_strDescName );
	return m_strDescName;
}
//-------------------------------------------------------------------------
// ��ײ���
// ������pt ����
// ����ֵ��true ��ʾ��ײ��false ��ʾδ��ײ
bool FKDBSpriteObj::HitTest( const CCPoint& pt )
{
	if( m_pSprite )
		return m_pSprite->hitTest( pt );
	return false;
}
//-------------------------------------------------------------------------
// ��ײ���
// ������rt ������
// ����ֵ��true ��ʾ��ײ��false ��ʾδ��ײ
bool FKDBSpriteObj::HitTest( const CCRect& rt )
{
	if( m_pSprite )
		return m_pSprite->hitTest( rt );
	return false;
}
//-------------------------------------------------------------------------
// ��ȡ�����Χ��
bool FKDBSpriteObj::GetBoundingBox( CCRect& rt )
{
	if( m_pSprite )
		return m_pSprite->getBoundingBox( rt );
	return false;
}
//-------------------------------------------------------------------------
// ����ƫ����
void FKDBSpriteObj::SetOffset( CCPoint& ptOffset )
{
	if( m_pSprite )
		m_pSprite->setOffset( ptOffset );
}
//-------------------------------------------------------------------------
// ��ȡƫ����
bool FKDBSpriteObj::GetOffset( CCPoint& ptOffset )
{
	if( m_pSprite )
	{
		m_pSprite->getOffset( ptOffset );
		return true;
	}
	return false;
}
//-------------------------------------------------------------------------
// ��ȡ��������
IAnimation* FKDBSpriteObj::GetAnimation()
{
	if( m_pSprite )
		return m_pSprite->getAnimation();
	return NULL;
}
//-------------------------------------------------------------------------