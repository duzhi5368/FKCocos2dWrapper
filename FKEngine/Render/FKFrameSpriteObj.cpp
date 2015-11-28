//-------------------------------------------------------------------------
#include "FKFrameSpriteObj.h"
#include "FKSpriteEx.h"
#include "FKAnimateExResMgr.h"
//-------------------------------------------------------------------------
FKFrameSpriteObj::FKFrameSpriteObj( RENDER_OBJ_ID id )
	: m_unID( id )
	, m_pSprite( NULL )
{
	m_strPicFileName.clear();
}
//-------------------------------------------------------------------------
FKFrameSpriteObj::~FKFrameSpriteObj()
{

}
//-------------------------------------------------------------------------
// ����FKSprite����
bool FKFrameSpriteObj::Create( const char* szPicFileName, CCPoint ptOffset )
{
	if( szPicFileName == NULL )
		return false;

	m_pSprite = FKSpriteEx::Create();
	if( m_pSprite == NULL )
		return false;

	FKAnimateExRes* pAniRes = FKAnimateExResMgr::GetInstance().GetAnimateExRes( szPicFileName );
	m_Animate.SetAnimateExRes( pAniRes );
	m_Animate.SetTargetNode( m_pSprite );

	addChild( m_pSprite );
	m_pSprite->setPosition( ptOffset );

	m_strPicFileName = szPicFileName;
	return true;
}
//-------------------------------------------------------------------------
// ����
void FKFrameSpriteObj::update( float dt )
{
	m_Animate.Update( dt );
}
//-------------------------------------------------------------------------
// �뿪�˳�
void FKFrameSpriteObj::onExit()
{
	if( m_pSprite )
	{
		removeChild( m_pSprite );
		m_pSprite = NULL;
	}
}
//-------------------------------------------------------------------------
// ��ȡID
RENDER_OBJ_ID FKFrameSpriteObj::GetID()
{
	return m_unID;
}
//-------------------------------------------------------------------------
// ����ID
void FKFrameSpriteObj::SetID( RENDER_OBJ_ID unID )
{
	m_unID = unID;
}
//-------------------------------------------------------------------------
// ������ɫ
// ������tagColor ��ɫֵ
void FKFrameSpriteObj::SetColor( const ccColor3B& tagColor )
{
	if( m_pSprite )
		m_pSprite->setColor( tagColor );
}
//-------------------------------------------------------------------------
// ����͸����
// ������byAlpha ͸����[0,255]
void FKFrameSpriteObj::SetOpacity( unsigned char byAlpha )
{
	if( m_pSprite )
		m_pSprite->setOpacity( byAlpha );
}
//-------------------------------------------------------------------------
// ��ȡ��Ϸ������ͼ�ļ���
const std::string& FKFrameSpriteObj::GetFileName()
{
	return m_strPicFileName;
}
//-------------------------------------------------------------------------
// ��ȡ��Ϸ������������(ȫ��Ψһ�ַ���)
const std::string& FKFrameSpriteObj::GetDescName()
{
	return m_strPicFileName;
}
//-------------------------------------------------------------------------
// ��ײ���
// ������pt ����
// ����ֵ��true ��ʾ��ײ��false ��ʾδ��ײ
bool FKFrameSpriteObj::HitTest( const CCPoint& pt )
{
	if( m_pSprite == NULL )
		return false;

	CCRect rect = m_pSprite->boundingBox();
	return rect.containsPoint( pt );
}
//-------------------------------------------------------------------------
// ��ײ���
// ������rt ������
// ����ֵ��true ��ʾ��ײ��false ��ʾδ��ײ
bool FKFrameSpriteObj::HitTest( const CCRect& rt )
{
	if( m_pSprite == NULL )
		return false;

	CCRect rect = m_pSprite->boundingBox();
	return rect.intersectsRect( rect );
}
//-------------------------------------------------------------------------
// ��ȡ�����Χ��
bool FKFrameSpriteObj::GetBoundingBox( CCRect& rt )
{
	if( m_pSprite )
	{
		rt = m_pSprite->boundingBox();
		rt = CCRectApplyAffineTransform( rt, nodeToParentTransform() );
		return true;
	}
	return false;
}
//-------------------------------------------------------------------------
// ����ƫ����
void FKFrameSpriteObj::SetOffset( CCPoint& ptOffset )
{
	if( m_pSprite )
		m_pSprite->setPosition( ptOffset );
}
//-------------------------------------------------------------------------
// ��ȡƫ����
bool FKFrameSpriteObj::GetOffset( CCPoint& ptOffset )
{
	if( m_pSprite )
	{
		ptOffset = m_pSprite->getPosition();
		return true;
	}
	return false;
}
//-------------------------------------------------------------------------
// ��ȡ��������
IAnimation* FKFrameSpriteObj::GetAnimation()
{
	return (IAnimation*)&m_Animate;
}
//-------------------------------------------------------------------------
// ��ȡ����
CCSprite* FKFrameSpriteObj::GetSprite()
{
	return (CCSprite*)m_pSprite;
}
//-------------------------------------------------------------------------