//-------------------------------------------------------------------------
#include "FKRenderObj.h"
#include "FKRenderObjMgr.h"
#include "FKRenderableMgr.h"
#include "FKRenderObjModel.h"
#include "FKMapObj.h"
#include "FKMapMgr.h"
//-------------------------------------------------------------------------
FKRenderObj::FKRenderObj( RENDER_OBJ_ID id )
	: m_unID( id )
	, m_pUserData( nullptr )
	, m_pRootRenderable( nullptr )
	, m_pModel( nullptr )
	, m_bIsNeedUpdate( false )
	, m_bIsCanbeSelected( false )
	, m_bIsInScene( false )
{
	m_strFKOFileName.clear();
	m_strCurAniName.clear();

	m_tagPos = CCPointZero;
	m_tagOffset = CCPointZero;

	m_mapObjParts.clear();
	m_mapObjLocators.clear();
	m_mapObjEffects.clear();
	m_mapObjLinks.clear();
	m_setObjRenderTexts.clear();
}
//-------------------------------------------------------------------------
FKRenderObj::~FKRenderObj()
{

}
//-------------------------------------------------------------------------
// ���º���
void FKRenderObj::update( float delta )
{
	// �������
	ObjPartMap::iterator ItePart = m_mapObjParts.begin();
	for( ; ItePart !=  m_mapObjParts.end(); ++ItePart )
	{
		if( ItePart->second )
		{
			ItePart->second->update( delta );
		}
	}
	// ������Ч
	ObjEffectMap::iterator IteEffect = m_mapObjEffects.begin();
	for( ; IteEffect !=  m_mapObjEffects.end(); ++IteEffect )
	{
		if( IteEffect->second )
		{
			IteEffect->second->update( delta );
		}
	}
	// �������Ӷ���
	ObjLinkMap::iterator IteLink = m_mapObjLinks.begin();
	for( ; IteLink !=  m_mapObjLinks.end(); ++IteLink )
	{
		if( IteLink->second.m_pLinkObj )
		{
			IteLink->second.m_pLinkObj->update( delta );
		}
	}
}
//-------------------------------------------------------------------------
// ��������
bool FKRenderObj::Create( const char* szFKOFileName )
{
	if( szFKOFileName == NULL )
		return false;

	string strPathName, strFileName, strExt;
	string strFKOFileName = szFKOFileName;
	if( !FKCW_Base_Utils::ParseFilePathName( strFKOFileName, strPathName, strFileName, strExt ) )
		return false;

	FKCW_Base_Utils::ToLowerCase( strExt );
	if( strExt != "fko" )
	{
		CCRect tagRect = CCRectZero;
		ISprite* pSprite = FKRenderableMgr::GetInstance().CreateSprite( szFKOFileName, tagRect );
		if( pSprite == NULL )
			return false;

		addChild( pSprite );
		pSprite->release();

		m_strFKOFileName = szFKOFileName;
		m_pRootRenderable = pSprite;
		return true;
	}

	__CreateParts();
	__CreateEffects();

	m_strFKOFileName = szFKOFileName;
	return true;
}
//-------------------------------------------------------------------------
// �ͷź���
void FKRenderObj::onExit()
{
	removeAllChildren();

	if( m_pModel )
	{
		m_pModel->release();
		m_pModel = NULL;
	}

	m_mapObjLinks.clear();
}
//-------------------------------------------------------------------------
// ��ȡID
RENDER_OBJ_ID FKRenderObj::GetID()
{
	return m_unID;
}
//-------------------------------------------------------------------------
// �����û�����
// ������pData �Զ����û�����
void FKRenderObj::SetUserData( void* pData )
{
	m_pUserData = pData;
}
//-------------------------------------------------------------------------
// ��ȡ�û�����
void* FKRenderObj::GetUserData()
{
	return m_pUserData;
}
//-------------------------------------------------------------------------
// ��ȡ��Ϸ������ͼ�ļ���
const std::string& FKRenderObj::GetFileName()
{
	return m_strFKOFileName;
}
//-------------------------------------------------------------------------
// ��ȡ��Ϸ������������(ȫ��Ψһ�ַ���)
const std::string& FKRenderObj::GetDescName()
{
	return m_strFKOFileName;
}
//-------------------------------------------------------------------------
// ���ȫ���ҽӶ��󣬽������ն���
void FKRenderObj::Clear()
{
	ObjPartMap::iterator ItePart = m_mapObjParts.begin();
	for( ; ItePart !=  m_mapObjParts.end(); ++ItePart )
	{
		if( ItePart->second )
		{
			removeChild( ItePart->second );
			ItePart->second = NULL;
		}
	}
	m_mapObjParts.clear();
	ObjEffectMap::iterator IteEffect = m_mapObjEffects.begin();
	for( ; IteEffect !=  m_mapObjEffects.end(); ++IteEffect )
	{
		if( IteEffect->second )
		{
			removeChild( IteEffect->second );
			IteEffect->second = NULL;
		}
	}
	m_mapObjEffects.clear();

	RemoveAllLinkObj();
}
//-------------------------------------------------------------------------
// ��ȫ����
void FKRenderObj::Release()
{
	Clear();
	this->release();
}
//-------------------------------------------------------------------------
// �󶨵�������
// ������pParentNode ���ڵ�
// ������nZOrder ���Zֵ
// ������nTag ��ǩ
void FKRenderObj::Attach( CCNode* pParentNode, int nZOrder, int nTag )
{
	if( pParentNode == NULL )
		return;
	pParentNode->addChild( this, nZOrder, nTag );
}
//-------------------------------------------------------------------------
// �ӳ������Ƴ�
// ������bIsRemove �Ƴ����Ƿ����ɾ��
void FKRenderObj::Detach( bool bIsRemove )
{
	CCNode* pParentNode = getParent();
	if( pParentNode == NULL )
		return;
	if( !bIsRemove )
		retain();	// ע�⣬�����Ҫ���ⲿ�ֶ�release��
	pParentNode->removeChild( this );
}
//-------------------------------------------------------------------------
// ����λ��
// ������tagPoint λ��
void FKRenderObj::SetPos( const CCPoint& tagPoint )
{
	if( m_bIsInScene )
	{
		if( GetRenderSystem() )
		{
			FKMapObj* pCurMap = (FKMapObj*)(GetRenderSystem()->GetCurrentMap());
			if( pCurMap )
				pCurMap->SetObjPos( m_unID, tagPoint );
		}
	}
	else
	{
		setPosition( tagPoint );
	}
	m_tagPos = tagPoint;
}
//-------------------------------------------------------------------------
// ��ȡλ��
// ������[out]tagPoint λ��
void FKRenderObj::GetPos( CCPoint& tagPoint )
{
	tagPoint = m_tagPos;
}
//-------------------------------------------------------------------------
// ����ƫ����
void FKRenderObj::SetOffset( CCPoint& tagPoint )
{
	ObjPartMap::iterator Ite = m_mapObjParts.begin();
	for( ; Ite != m_mapObjParts.end(); ++Ite )
	{
		if( Ite->second )
			Ite->second->SetOffset( tagPoint );
	}
	m_tagOffset = tagPoint;
}
//-------------------------------------------------------------------------
// ��ȡƫ����			 
CCPoint FKRenderObj::GetOffset()
{
	if( m_pRootRenderable == NULL )
		return CCPointZero;
	CCPoint ptRet;
	m_pRootRenderable->GetOffset( ptRet );
	return ptRet;
}
//-------------------------------------------------------------------------
// ������ɫ
// ������tagColor ��ɫֵ
void FKRenderObj::SetColor( const ccColor3B& tagColor )
{
	ObjPartMap::iterator ItePart = m_mapObjParts.begin();
	for( ; ItePart !=  m_mapObjParts.end(); ++ItePart )
	{
		if( ItePart->second )
		{
			ItePart->second->SetColor( tagColor );
		}
	}
	ObjEffectMap::iterator IteEffect = m_mapObjEffects.begin();
	for( ; IteEffect !=  m_mapObjEffects.end(); ++IteEffect )
	{
		if( IteEffect->second )
		{
			IteEffect->second->SetColor( tagColor );
		}
	}
	ObjLinkMap::iterator IteLink = m_mapObjLinks.begin();
	for( ; IteLink !=  m_mapObjLinks.end(); ++IteLink )
	{
		if( IteLink->second.m_pLinkObj )
		{
			IteLink->second.m_pLinkObj->SetColor( tagColor );
		}
	}
}
//-------------------------------------------------------------------------
// ����͸����
// ������byAlpha ͸����[0,255]
void FKRenderObj::SetOpacity( unsigned char byAlpha )
{
	ObjPartMap::iterator ItePart = m_mapObjParts.begin();
	for( ; ItePart !=  m_mapObjParts.end(); ++ItePart )
	{
		if( ItePart->second )
		{
			ItePart->second->SetOpacity( byAlpha );
		}
	}
	ObjEffectMap::iterator IteEffect = m_mapObjEffects.begin();
	for( ; IteEffect !=  m_mapObjEffects.end(); ++IteEffect )
	{
		if( IteEffect->second )
		{
			IteEffect->second->SetOpacity( byAlpha );
		}
	}
	ObjLinkMap::iterator IteLink = m_mapObjLinks.begin();
	for( ; IteLink !=  m_mapObjLinks.end(); ++IteLink )
	{
		if( IteLink->second.m_pLinkObj )
		{
			IteLink->second.m_pLinkObj->SetOpacity( byAlpha );
		}
	}
}
//-------------------------------------------------------------------------
// ��������
void FKRenderObj::SetScale( CCPoint& tagPoint )
{
	ObjPartMap::iterator ItePart = m_mapObjParts.begin();
	for( ; ItePart !=  m_mapObjParts.end(); ++ItePart )
	{
		if( ItePart->second )
		{
			ItePart->second->setScaleX( tagPoint.x );
			ItePart->second->setScaleY( tagPoint.y );
		}
	}
	ObjEffectMap::iterator IteEffect = m_mapObjEffects.begin();
	for( ; IteEffect !=  m_mapObjEffects.end(); ++IteEffect )
	{
		if( IteEffect->second )
		{
			IteEffect->second->setScaleX( tagPoint.x );
			IteEffect->second->setScaleY( tagPoint.y );
		}
	}
	ObjLinkMap::iterator IteLink = m_mapObjLinks.begin();
	for( ; IteLink !=  m_mapObjLinks.end(); ++IteLink )
	{
		if( IteLink->second.m_pLinkObj )
		{
			IteLink->second.m_pLinkObj->SetScale( tagPoint );
		}
	}
}
//-------------------------------------------------------------------------
// �Ƿ�ɼ�
// ������bIsVisible �Ƿ�ɼ�
void FKRenderObj::IsVisible( bool bIsVisible )
{
	setVisible( bIsVisible );
}
//-------------------------------------------------------------------------
// �Ƿ�����Update
void FKRenderObj::SetEnableUpdate( bool bIsEnable )
{
	if( m_bIsNeedUpdate == bIsEnable )
		return;

	if( bIsEnable )
		scheduleUpdate();
	else
		unscheduleUpdate();

	m_bIsNeedUpdate = bIsEnable;
}
//-------------------------------------------------------------------------
// ��ײ���
// ������pt ����
// ����ֵ��true ��ʾ��ײ��false ��ʾδ��ײ
bool FKRenderObj::HitTest( const CCPoint& pt )
{
	if( m_pRootRenderable == NULL )
		return false;

	CCRect tagRect;
	m_pRootRenderable->GetBoundingBox( tagRect );
	tagRect = CCRectApplyAffineTransform( tagRect, nodeToParentTransform() );
	return tagRect.containsPoint( pt );
}
//-------------------------------------------------------------------------
// ��ײ���
// ������rt ������
// ����ֵ��true ��ʾ��ײ��false ��ʾδ��ײ
bool FKRenderObj::HitTest( const CCRect& rt )
{
	if( m_pRootRenderable == NULL )
		return false;

	CCRect tagRect;
	m_pRootRenderable->GetBoundingBox( tagRect );
	tagRect = CCRectApplyAffineTransform( tagRect, nodeToParentTransform() );
	return tagRect.intersectsRect( rt );
}
//-------------------------------------------------------------------------
// �����Ƿ���Ա�ѡ��
// ������bIsEnable �Ƿ�����ѡ�м��
void FKRenderObj::SetEnableSelect( bool bIsEnable )
{
	m_bIsCanbeSelected = bIsEnable;
}
//-------------------------------------------------------------------------
// �ҽӶ���
RENDER_OBJ_ID FKRenderObj::AddLinkObj( const char* szLinkObjName, const char* szLocator,
								 int nDepth, ccColor4B color )
{
	if( m_pModel == NULL )
		return 0;
	IRenderSystem* pRenderSystem = GetRenderSystem();
	if( pRenderSystem == NULL )
		return 0;

	SLinkObj tagLinkObj;
	tagLinkObj.m_pLinkObj = (FKRenderObj*)pRenderSystem->CreateRenderObj( szLinkObjName );
	if( tagLinkObj.m_pLinkObj == NULL )
		return 0;
	tagLinkObj.m_strLocator = "";

	CCPoint ptLoc = CCPointZero;
	if( szLocator != NULL )
	{
		tagLinkObj.m_strLocator = szLocator;
		FKRenderObjModel::ObjLocatorMap::iterator Ite = m_pModel->m_mapObjLocators.find( tagLinkObj.m_strLocator );
		if( Ite != m_pModel->m_mapObjLocators.end() )
		{
			ptLoc = Ite->second.m_tagOffset;
		}
	}

	addChild( tagLinkObj.m_pLinkObj, nDepth );
	tagLinkObj.m_pLinkObj->release();

	tagLinkObj.m_pLinkObj->SetPos( ptLoc );
	tagLinkObj.m_pLinkObj->SetColor( ccc3(color.r, color.g, color.b) );
	tagLinkObj.m_pLinkObj->SetOpacity( color.a );

	m_mapObjLinks[tagLinkObj.m_pLinkObj->GetID()] = tagLinkObj;
	return tagLinkObj.m_pLinkObj->GetID();
}
//-------------------------------------------------------------------------
// �ҽӶ���
RENDER_OBJ_ID FKRenderObj::AddLinkObj( IRenderObj* pRenderObj, const char* szLocator,
								  int nDepth, ccColor4B color )
{
	if( m_pModel == NULL || pRenderObj == NULL )
		return 0;
	SLinkObj tagLinkObj;
	tagLinkObj.m_pLinkObj = (FKRenderObj*)pRenderObj;
	tagLinkObj.m_strLocator = "";

	CCPoint ptLoc = CCPointZero;
	if( szLocator != NULL )
	{
		tagLinkObj.m_strLocator = szLocator;
		FKRenderObjModel::ObjLocatorMap::iterator Ite = m_pModel->m_mapObjLocators.find( tagLinkObj.m_strLocator );
		if( Ite != m_pModel->m_mapObjLocators.end() )
		{
			ptLoc = Ite->second.m_tagOffset;
		}
	}

	addChild( tagLinkObj.m_pLinkObj, nDepth );
	tagLinkObj.m_pLinkObj->release();

	tagLinkObj.m_pLinkObj->SetPos( ptLoc );
	tagLinkObj.m_pLinkObj->SetColor( ccc3(color.r, color.g, color.b) );
	tagLinkObj.m_pLinkObj->SetOpacity( color.a );

	m_mapObjLinks[tagLinkObj.m_pLinkObj->GetID()] = tagLinkObj;
	return tagLinkObj.m_pLinkObj->GetID();
}
//-------------------------------------------------------------------------
// ɾ��һ���ҽӶ���
// ������unLinkObjID �ҽӶ����ID
bool FKRenderObj::RemoveLinkObj( RENDER_OBJ_ID unLinkObjID )
{
	ObjLinkMap::iterator Ite = m_mapObjLinks.find( unLinkObjID );
	if( Ite == m_mapObjLinks.end() )
		return true;
	if( Ite->second.m_pLinkObj == NULL )
		return true;

	removeChild( Ite->second.m_pLinkObj );
	m_mapObjLinks.erase( Ite );
	return true;
}
//-------------------------------------------------------------------------
// ɾ��һ���ҽӶ���
// ������unLinkObjID �ҽӶ����ID
// ������bIsRemove �Ƿ�ɾ�����ҽڶ���
IRenderObj* FKRenderObj::RemoveLinkObj( RENDER_OBJ_ID unLinkObjID, bool bIsRemove )
{
	IRenderObj* pRet = NULL;
	ObjLinkMap::iterator Ite = m_mapObjLinks.find( unLinkObjID );
	if( Ite == m_mapObjLinks.end() )
		return NULL;
	if( Ite->second.m_pLinkObj == NULL )
		return NULL;
	if( !bIsRemove )
		Ite->second.m_pLinkObj->retain();

	pRet = Ite->second.m_pLinkObj;
	removeChild( Ite->second.m_pLinkObj );
	m_mapObjLinks.erase( Ite );
	return pRet;
}
//-------------------------------------------------------------------------
// ɾ��ȫ���ҽӶ���
void FKRenderObj::RemoveAllLinkObj()
{
	ObjLinkMap::iterator Ite = m_mapObjLinks.begin();
	for( ; Ite != m_mapObjLinks.end(); ++Ite )
	{
		if( Ite->second.m_pLinkObj )
			removeChild( Ite->second.m_pLinkObj );
	}
	m_mapObjLinks.clear();
}
//-------------------------------------------------------------------------
// ��ȡһ���ҽڶ���
// ������RENDER_OBJ_ID �ҽڶ���ID
IRenderObj* FKRenderObj::GetLinkObjByID( RENDER_OBJ_ID unID )
{
	ObjLinkMap::iterator Ite = m_mapObjLinks.find( unID );
	if( Ite != m_mapObjLinks.end() )
		return Ite->second.m_pLinkObj;
	return NULL;
}
//-------------------------------------------------------------------------
// ����һ������
void FKRenderObj::ChangePart( const char* szPartObjName, const char* szPartPlaceName, int nDepth )
{
	if( szPartObjName == NULL || szPartPlaceName == NULL || m_pModel == NULL )
		return;

	string strPartObjName = szPartObjName;
	string strPartPlaceName = szPartPlaceName;
	FKRenderObjModel::ObjPartMap::iterator Ite = m_pModel->m_mapObjParts.find( szPartPlaceName );
	if( Ite == m_pModel->m_mapObjParts.end() )
	{
		m_pModel->AddPart( strPartPlaceName, strPartObjName, nDepth );
		Ite = m_pModel->m_mapObjParts.find( szPartPlaceName );
	}
	else
	{
		if( Ite->second.m_strFile == strPartObjName && Ite->second.m_nDepth == nDepth )
			return;
	}

	float fAniSpeed = 1.0f;
	if( m_pRootRenderable && ( m_pRootRenderable->GetRenderObjType() == eROT_Ani 
		|| m_pRootRenderable->GetRenderObjType() == eROT_Armature 
		|| m_pRootRenderable->GetRenderObjType() == eROT_DB ) )
	{
		IRenderable* pObj = m_pRootRenderable;
		IAnimation* pAni = pObj->GetAnimation();
		if( pAni )
		{
			fAniSpeed = pAni->GetSpeed();
		}
	}

	string strPart = Ite->second.m_strFile;
	Ite->second.m_strFile = szPartObjName;
	Ite->second.m_nDepth = nDepth;
	if( !__CreatePart(Ite->second) )
	{
		// �ָ�
		Ite->second.m_strFile = strPart;
	}

	//  ���Ŷ���
	Play( m_strCurAniName.c_str(), fAniSpeed, -1, true );
}
//-------------------------------------------------------------------------
// ����һ����Ч
void FKRenderObj::ChangeEffect( const string& strEffectName, const string& strLocatorName, 
									 const string& strEffectFileName, CCPoint& tagOffset,
									 ccColor4B& color, CCPoint& tagScale, int nDepth )
{
	if( m_pModel == NULL )
		return;
	FKRenderObjModel::ObjEffectMap::iterator Ite = m_pModel->m_mapObjEffects.find( strEffectName );
	if( Ite == m_pModel->m_mapObjEffects.end() )
	{
		m_pModel->AddEffect( strEffectName, strLocatorName, strEffectFileName,
			tagOffset, color, tagScale, nDepth );
		Ite = m_pModel->m_mapObjEffects.find( strEffectName );
	}

	ObjEffectMap::iterator IteObj = m_mapObjEffects.find( strEffectName );
	if( IteObj != m_mapObjEffects.end() )
	{
		if( IteObj->second != NULL )
		{
			removeChild( IteObj->second );
			IteObj->second = NULL;
		}
	}

	Ite->second.m_strName		= strEffectName;
	Ite->second.m_strFileName	= strEffectFileName;
	Ite->second.m_strLocator	= strLocatorName;
	Ite->second.m_tagOffset		= tagOffset;
	Ite->second.m_tagColor		= color;
	Ite->second.m_tagScale		= tagScale;
	Ite->second.m_nDepth		= nDepth;

	__CreateEffect( Ite->second );
}
//-------------------------------------------------------------------------

// ���ö��������ٶ�
void FKRenderObj::SetAnimationSpeed( float fSpeed )
{
	ObjPartMap::iterator ItePart = m_mapObjParts.begin();
	for( ; ItePart !=  m_mapObjParts.end(); ++ItePart )
	{
		if( ItePart->second && ( ItePart->second->GetRenderObjType() == eROT_Ani 
			|| ItePart->second->GetRenderObjType() == eROT_Armature 
			|| ItePart->second->GetRenderObjType() == eROT_DB ))
		{
			IRenderable* pObj = ItePart->second;
			IAnimation* pAni = pObj->GetAnimation();
			if( pAni )
			{
				pAni->SetSpeed( fSpeed );
			}
		}
	}
	ObjEffectMap::iterator IteEffect = m_mapObjEffects.begin();
	for( ; IteEffect !=  m_mapObjEffects.end(); ++IteEffect )
	{
		if( IteEffect->second && ( IteEffect->second->GetRenderObjType() == eROT_Ani 
			|| IteEffect->second->GetRenderObjType() == eROT_Armature 
			|| IteEffect->second->GetRenderObjType() == eROT_DB ))
		{
			IRenderable* pObj = IteEffect->second;
			IAnimation* pAni = pObj->GetAnimation();
			if( pAni )
			{
				pAni->SetSpeed( fSpeed );
			}
		}
	}
	ObjLinkMap::iterator IteLink = m_mapObjLinks.begin();
	for( ; IteLink !=  m_mapObjLinks.end(); ++IteLink )
	{
		if( IteLink->second.m_pLinkObj )
		{
			IteLink->second.m_pLinkObj->SetAnimationSpeed( fSpeed );
		}
	}
}
//-------------------------------------------------------------------------
// ���ö������Żص�
void FKRenderObj::SetAnimationCallback( IAnimationCallback* pCallback, void* pContext )
{
	if( m_pRootRenderable == NULL )
		return;

	if( m_pRootRenderable->GetRenderObjType() == eROT_Ani 
		|| m_pRootRenderable->GetRenderObjType() == eROT_Armature 
		|| m_pRootRenderable->GetRenderObjType() == eROT_DB )
	{
		IRenderable* pObj = m_pRootRenderable;
		IAnimation* pAni = pObj->GetAnimation();
		if( pAni )
		{
			pAni->SetAniCallback( pCallback, pContext );
		}
	}
}
//-------------------------------------------------------------------------
// ���Ŷ���������������ֹͣ״̬����Ĭ�ϼ������ţ�Ҳ��ǿ�ƴ�ͷ���ţ�
// ������szAniName ������
// ������fSpeed �����ٶ�
// ������nLoops �����ظ���������Ϊ-1��ʾ����ѭ��
// ������bIsForceUpdate �Ƿ�ǿ�ƴ�ͷ����
void FKRenderObj::Play( const char* szAniName, float fSpeed, int nLoops, bool bIsForceUpdate )
{
	ObjPartMap::iterator ItePart = m_mapObjParts.begin();
	for( ; ItePart !=  m_mapObjParts.end(); ++ItePart )
	{
		if( ItePart->second && ( ItePart->second->GetRenderObjType() == eROT_Ani 
			|| ItePart->second->GetRenderObjType() == eROT_Armature 
			|| ItePart->second->GetRenderObjType() == eROT_DB ))
		{
			IRenderable* pObj = ItePart->second;
			IAnimation* pAni = pObj->GetAnimation();
			if( pAni )
			{
				pAni->Play( szAniName, fSpeed, nLoops, bIsForceUpdate );
			}
		}
	}
	ObjEffectMap::iterator IteEffect = m_mapObjEffects.begin();
	for( ; IteEffect !=  m_mapObjEffects.end(); ++IteEffect )
	{
		if( IteEffect->second && ( IteEffect->second->GetRenderObjType() == eROT_Ani 
			|| IteEffect->second->GetRenderObjType() == eROT_Armature 
			|| IteEffect->second->GetRenderObjType() == eROT_DB ))
		{
			IRenderable* pObj = IteEffect->second;
			IAnimation* pAni = pObj->GetAnimation();
			if( pAni )
			{
				pAni->Play( szAniName, fSpeed, nLoops, bIsForceUpdate );
			}
		}
	}
	ObjLinkMap::iterator IteLink = m_mapObjLinks.begin();
	for( ; IteLink !=  m_mapObjLinks.end(); ++IteLink )
	{
		if( IteLink->second.m_pLinkObj )
		{
			IteLink->second.m_pLinkObj->Play( szAniName, fSpeed, nLoops, bIsForceUpdate );
		}
	}
}
//-------------------------------------------------------------------------
// ��ͣ��������
void FKRenderObj::Pause()
{
	ObjPartMap::iterator ItePart = m_mapObjParts.begin();
	for( ; ItePart !=  m_mapObjParts.end(); ++ItePart )
	{
		if( ItePart->second && ( ItePart->second->GetRenderObjType() == eROT_Ani 
			|| ItePart->second->GetRenderObjType() == eROT_Armature 
			|| ItePart->second->GetRenderObjType() == eROT_DB ))
		{
			IRenderable* pObj = ItePart->second;
			IAnimation* pAni = pObj->GetAnimation();
			if( pAni )
			{
				pAni->Pause();
			}
		}
	}
	ObjEffectMap::iterator IteEffect = m_mapObjEffects.begin();
	for( ; IteEffect !=  m_mapObjEffects.end(); ++IteEffect )
	{
		if( IteEffect->second && ( IteEffect->second->GetRenderObjType() == eROT_Ani 
			|| IteEffect->second->GetRenderObjType() == eROT_Armature 
			|| IteEffect->second->GetRenderObjType() == eROT_DB ))
		{
			IRenderable* pObj = IteEffect->second;
			IAnimation* pAni = pObj->GetAnimation();
			if( pAni )
			{
				pAni->Pause();
			}
		}
	}
	ObjLinkMap::iterator IteLink = m_mapObjLinks.begin();
	for( ; IteLink !=  m_mapObjLinks.end(); ++IteLink )
	{
		if( IteLink->second.m_pLinkObj )
		{
			IteLink->second.m_pLinkObj->Pause();
		}
	}
}
//-------------------------------------------------------------------------
// ��ȡ���������б�
// ������[out]AnimationNameList ���������б�
void FKRenderObj::GetAnimationNames( list<string>& AnimationNameList )
{
	if( m_pRootRenderable == nullptr )
		return;

	if( m_pRootRenderable->GetRenderObjType() != eROT_Ani 
		&& m_pRootRenderable->GetRenderObjType() != eROT_Armature 
		&& m_pRootRenderable->GetRenderObjType() != eROT_DB )
		return;

	IRenderable* pObj = m_pRootRenderable;
	IAnimation* pAni = pObj->GetAnimation();

	pAni->GetAnimationList( AnimationNameList );
}
//-------------------------------------------------------------------------
// ���������Ⱦ����
// ������pRenderText ������Ⱦ����
// ������szLocator �ҽڵ�����
// ������tagOffset �ҽ�ƫ��
bool FKRenderObj::AddLinkRenderText( IRenderText* pRenderText, const char* szLocator,
										  const CCPoint& tagOffset )
{
	if( pRenderText == NULL || m_pRootRenderable == NULL )
		return false;

	CCPoint ptLoc = tagOffset;
	if( (szLocator != "") && (szLocator != NULL) )
	{
		FKRenderObjModel::ObjLocatorMap::iterator Ite = m_pModel->m_mapObjLocators.find( szLocator );
		if( Ite != m_pModel->m_mapObjLocators.end() )
		{
			ptLoc = ptLoc + Ite->second.m_tagOffset;
		}
	}
	pRenderText->SetPos( ptLoc );
	pRenderText->Attach( m_pRootRenderable, 1000 );

	m_setObjRenderTexts.insert( pRenderText );
	return true;
}
//-------------------------------------------------------------------------
// ɾ��������Ⱦ����
// ������pRenderText ��Ҫɾ����������Ⱦ����
void FKRenderObj::RemveLinkRenderText( IRenderText* pRenderText )
{
	IRenderSystem* pSystem = GetRenderSystem();
	if( pSystem == NULL )
		return;
	if( pRenderText == NULL )
		return;

	m_setObjRenderTexts.erase( pRenderText );
	pSystem->RemoveRenderText( pRenderText );
}
//-------------------------------------------------------------------------
// ����ģ������
void FKRenderObj::SetObjModel( IRenderObjModel* pObjModel )
{
	if( m_pModel )
	{
		m_pModel->release();
	}
	m_pModel = (dynamic_cast<FKRenderObjModel*>(pObjModel));
	if( m_pModel )
	{
		m_pModel->retain();
	}
}
//-------------------------------------------------------------------------
// ��ȡģ������
IRenderObjModel* FKRenderObj::GetObjModel()
{
	return (dynamic_cast<IRenderObjModel*>(m_pModel));
}
//-------------------------------------------------------------------------
// �����Ƿ��ڳ���
void FKRenderObj::SetInScene( bool bIsInScene )
{
	m_bIsInScene = bIsInScene;
}
//-------------------------------------------------------------------------
// �ж��Ƿ��ڳ�����
bool FKRenderObj::IsInScene()
{
	return m_bIsInScene;
}
//-------------------------------------------------------------------------
// �Ƿ�ѡ��
bool FKRenderObj::IsSelected()
{
	return m_bIsCanbeSelected;
}
//-------------------------------------------------------------------------
// ����������
void FKRenderObj::__CreateParts()
{
	if( m_pModel == NULL )
		return ;

	FKRenderObjModel::ObjPartMap::iterator Ite = m_pModel->m_mapObjParts.begin();
	for( ; Ite != m_pModel->m_mapObjParts.end(); ++Ite )
	{
		__CreatePart( Ite->second );
	}
}
//-------------------------------------------------------------------------
// ��ȡ��������
FKRenderObjModel::ObjPartMap&	FKRenderObj::GetParts()
{
	CCAssert( m_pModel != NULL, "����ģ�����ݲ�Ӧ��Ϊ��" );
	return m_pModel->m_mapObjParts;
}
//-------------------------------------------------------------------------
// ��ȡ�󶨵�����
FKRenderObjModel::ObjLocatorMap& FKRenderObj::GetLocators()
{
	CCAssert( m_pModel != NULL, "����ģ�����ݲ�Ӧ��Ϊ��" );
	return m_pModel->m_mapObjLocators;
}
//-------------------------------------------------------------------------
// ��ȡ��Ч����
FKRenderObjModel::ObjEffectMap& FKRenderObj::GetEffects()
{
	CCAssert( m_pModel != NULL, "����ģ�����ݲ�Ӧ��Ϊ��" );
	return m_pModel->m_mapObjEffects;
}
//-------------------------------------------------------------------------
// ɾ������
bool FKRenderObj::RemovePart( const string& strName, bool bRemoveData )
{
	if( m_pRootRenderable == nullptr )
		return false;
	if( strName == "Main" )
	{
		if( m_pRootRenderable )
		{
			m_pRootRenderable->GetOffset( m_pModel->m_pOffset );
			m_pRootRenderable = NULL;
		}
	}
	ObjPartMap::iterator ItePart = m_mapObjParts.begin();
	for( ; ItePart !=  m_mapObjParts.end(); ++ItePart )
	{
		if( ItePart->second )
		{
			removeChild( ItePart->second );
		}
	}
	if( m_pModel && bRemoveData )
	{
		m_pModel->RemovePart( strName );
		m_mapObjParts.erase( strName );
	}
	return true;
}
//-------------------------------------------------------------------------
// ɾ���󶨵�
bool FKRenderObj::RemoveLocator( const string& strName, bool bRemoveData )
{
	if( m_pRootRenderable == nullptr )
		return false;
	// ��Ч�б�
	string strEffectName;
	FKRenderObjModel::ObjEffectMap::iterator IteEffect = m_pModel->m_mapObjEffects.begin();
	for( ; IteEffect != m_pModel->m_mapObjEffects.end(); ++IteEffect )
	{
		if( IteEffect->second.m_strLocator == strName )
		{
			strEffectName = IteEffect->second.m_strName;

			ObjEffectMap::iterator IteEffectObj = m_mapObjEffects.find( strEffectName );
			if( IteEffectObj != m_mapObjEffects.end() )
			{
				if( IteEffectObj->second )
				{
					IteEffectObj->second->setPosition( IteEffect->second.m_tagOffset );
				}
			}
		}
	}
	// �ҽӶ���
	ObjLinkMap::iterator IteLink = m_mapObjLinks.begin();
	ObjLinkMap::iterator IteLink2;
	for( ; IteLink != m_mapObjLinks.end(); )
	{
		IteLink2 = IteLink++;
		if( IteLink2->second.m_strLocator == strName )
		{
			removeChild( IteLink->second.m_pLinkObj );
			m_mapObjLinks.erase( IteLink2 );
		}
	}

	// ����
	if( bRemoveData && m_pModel )
	{
		m_pModel->RemoveLocator( strName );
	}
	return true;
}
//-------------------------------------------------------------------------
// ɾ����Ч
bool FKRenderObj::RemoveEffect( const string& strName, bool bRemoveData )
{
	if( m_pRootRenderable == nullptr )
		return false;
	ObjEffectMap::iterator IteEffect = m_mapObjEffects.begin();
	for( ; IteEffect !=  m_mapObjEffects.end(); ++IteEffect )
	{
		if( IteEffect->second )
		{
			removeChild( IteEffect->second );
		}
	}
	if( m_pModel && bRemoveData )
	{
		m_pModel->RemoveEffect( strName );
		m_mapObjEffects.erase( strName );
	}
	return true;
}
//-------------------------------------------------------------------------
// ���浽�ļ���
bool FKRenderObj::SaveToFile( const string& strFileName )
{
	if( m_pModel == NULL )
		return false;

	if( !m_tagOffset.equals(CCPointZero) )
	{
		m_pModel->m_pOffset = GetOffset();
	}

	return m_pModel->SaveToFKOFile( strFileName );
}
//-------------------------------------------------------------------------
// ������Ч��
void FKRenderObj::__CreateEffects()
{
	if( m_pModel == NULL )
		return ;

	FKRenderObjModel::ObjEffectMap::iterator Ite = m_pModel->m_mapObjEffects.begin();
	for( ; Ite != m_pModel->m_mapObjEffects.end(); ++Ite )
	{
		__CreateEffect( Ite->second );
	}
}
//-------------------------------------------------------------------------
// ��������
bool FKRenderObj::__CreatePart( FKRenderObjModel::SObjPart& tagPart )
{
	IRenderable* pRenderable = NULL;
	if( m_pModel == NULL )
		return false;

	ObjPartMap::iterator Ite = m_mapObjParts.find( tagPart.m_strName );
	if( Ite != m_mapObjParts.end() )
	{
		removeChild( Ite->second );
		if( tagPart.m_strName == "Main" )
			m_pRootRenderable = NULL;
		Ite->second = NULL;
	}

	string strPathName, strFileName, strExtName;
	FKCW_Base_Utils::ParseFilePathName( tagPart.m_strFile, strPathName, strFileName, strExtName );
	FKCW_Base_Utils::ToLowerCase( strExtName );

	if( strExtName == "xml" )
	{
		// DragonBones�����ļ�
		pRenderable = FKRenderableMgr::GetInstance().CreateDBSprite( tagPart.m_strFile.c_str(), m_pModel->m_pOffset );
	}
	else if( strExtName == "png" || strExtName == "fkp" || strExtName == "jpg" || strExtName == "bmp" )
	{
		// ��̬�����ļ�
		CCRect tagRect = CCRectZero;
		pRenderable = FKRenderableMgr::GetInstance().CreateSprite( tagPart.m_strFile.c_str(), tagRect, m_pModel->m_pOffset );
	}
	else if( strExtName == "fke" )
	{
		// ��Ч�ļ�
		pRenderable = FKRenderableMgr::GetInstance().CreateEffect( tagPart.m_strFile.c_str(), m_pModel->m_pOffset );
	}
	else if( strExtName == "fka" )
	{
		// ֡�����ļ�
		pRenderable = FKRenderableMgr::GetInstance().CreateFrameSprite( tagPart.m_strFile.c_str(), m_pModel->m_pOffset );
	}
	else if( strExtName == "json" || strExtName == "exportjson" )
	{
		// cocosStduio�����ļ�
		pRenderable = FKRenderableMgr::GetInstance().CreateArmaSprite( tagPart.m_strFile.c_str(), m_pModel->m_pOffset );
	}
	else 
	{
		return false;
	}

	if( pRenderable == NULL )
		return false;

	if( tagPart.m_strName == "Main" )
		m_pRootRenderable = pRenderable;

	addChild( pRenderable, tagPart.m_nDepth );
	pRenderable->release();

	m_mapObjParts[tagPart.m_strName] = pRenderable;
	return true;
}
//-------------------------------------------------------------------------
// ������Ч
bool FKRenderObj::__CreateEffect( FKRenderObjModel::SObjEffect& tagEffect )
{
	IRenderable* pRenderable = NULL;
	if( m_pModel == NULL )
		return false;

	string strPathName, strFileName, strExtName;
	FKCW_Base_Utils::ParseFilePathName( tagEffect.m_strFileName, strPathName, strFileName, strExtName );
	FKCW_Base_Utils::ToLowerCase( strExtName );

	if( strExtName == "fke" )
	{
		// ��Ч��
		pRenderable = FKRenderableMgr::GetInstance().CreateEffect( tagEffect.m_strFileName.c_str() );
	}
	else if( strExtName == "fka" )
	{
		// ֡������
		pRenderable = FKRenderableMgr::GetInstance().CreateFrameSprite( tagEffect.m_strFileName.c_str() );
	}
	else if( strExtName == "png" || strExtName == "fkp" || strExtName == "jpg" || strExtName == "bmp" )
	{
		// ��̬�����ļ�
		CCRect tagRect = CCRectZero;
		pRenderable = FKRenderableMgr::GetInstance().CreateSprite( tagEffect.m_strFileName.c_str(), tagRect );
	}
	else
	{
		return false;
	}

	CCPoint ptLoc = tagEffect.m_tagOffset;
	if(( !tagEffect.m_strLocator.empty() ) && ( tagEffect.m_strLocator != "" ))
	{
		FKRenderObjModel::ObjLocatorMap::iterator Ite = m_pModel->m_mapObjLocators.find( tagEffect.m_strLocator );
		if( Ite != m_pModel->m_mapObjLocators.end() )
		{
			ptLoc = ptLoc + Ite->second.m_tagOffset;
		}
	}

	addChild( pRenderable, tagEffect.m_nDepth );
	pRenderable->release();

	pRenderable->setPosition( ptLoc );
	pRenderable->SetColor( ccc3( tagEffect.m_tagColor.r, tagEffect.m_tagColor.g, tagEffect.m_tagColor.b ) );
	pRenderable->SetOpacity( tagEffect.m_tagColor.a );
	pRenderable->setScaleX( tagEffect.m_tagScale.x );
	pRenderable->setScaleY( tagEffect.m_tagScale.y );

	m_mapObjEffects[ tagEffect.m_strName ] = pRenderable;
	return true;
}
//-------------------------------------------------------------------------