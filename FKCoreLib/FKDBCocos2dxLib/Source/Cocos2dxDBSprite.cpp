//-------------------------------------------------------------------------
#include "../Include/Cocos2dxDBSprite.h"
#include "../Include/Cocos2dxDBNode.h"
#include "../Include/Cocos2dxDBObj.h"
#include "../Include/Cocos2dxDBAtlasNode.h"
//-------------------------------------------------------------------------
#define SKELTETON_XML		"skeleton.xml"
#define TEXTURE_FILE		"texture.png"
#define TEXTURE_XML			"texture.xml"
//-------------------------------------------------------------------------
/// �ֽ��ļ�·���ִ�
static bool ParseFileName( const std::string& strFilePathName, std::string& strPathName, std::string& strFileName, std::string& strFileExtName )
{
	if( strFilePathName.empty() )
	{
		return false;
	}

	strPathName.clear();
	strFileName.clear();
	strFileExtName.clear();

	std::size_t point_pos = strFilePathName.rfind( '.' ); 

	std::size_t pos = strFilePathName.rfind('\\');
	if( pos == std::string::npos )
	{
		pos = strFilePathName.rfind('/');
		if( pos == std::string::npos )
		{
			if( point_pos == std::string::npos )
			{
				return false;
			}
		}
	}

	if( point_pos == std::string::npos )
	{
		strPathName = strFilePathName;
	}
	else
	{
		/// ��б�ܽ�β
		if( pos == strFilePathName.length() - 1 )
		{
			strPathName = strFilePathName.substr( 0, pos );
		}
		else
		{
			if( pos != std::string::npos )
			{
				strPathName = strFilePathName.substr( 0, pos );
			}

			strFileName = strFilePathName.substr( pos+1, point_pos - pos - 1 );
			strFileExtName = strFilePathName.substr( point_pos + 1, strFilePathName.length() - point_pos - 1 );
		}
	}

	return true;
}
// תСд
static void ChangeStringToLower( std::string& str )
{
	char* pStr = new char[str.length()+1];
	size_t size = str.length();
	for( size_t i = 0; i < size; ++i )
	{
		char cc = str.at( i );
		if( cc >= 'A' && cc <= 'Z' )
		{
			cc += 'a' - 'A';
		}

		pStr[i] = cc;
	}

	pStr[size] = 0;
	str = pStr;
	delete [] pStr;
}
//-------------------------------------------------------------------------
CCocos2dxDBSprite::CCocos2dxDBSprite()
	: m_pDBNode( NULL )
{
	m_szFileName = "";
}
//-------------------------------------------------------------------------
CCocos2dxDBSprite::~CCocos2dxDBSprite()
{
	onExit();
}
//-------------------------------------------------------------------------
bool CCocos2dxDBSprite::create( const char* p_szAniFileName, CCPoint p_tagOffset )
{
	if( p_szAniFileName == NULL )
		return true;

	m_szFileName = p_szAniFileName;

	// ������·�����õ��ļ�������Ϊ DB������
	string szPathName, szFileName, szExtName;
	ParseFileName( m_szFileName, szPathName, szFileName, szExtName );

	unsigned int unPos = szPathName.rfind("/");
	string szObjName;
	if( unPos != string::npos )
	{
		szObjName = szPathName.substr( unPos + 1, m_szFileName.length() - unPos - 1 );
	}
	else
	{
		unPos = szPathName.rfind("\\");
		if( unPos != string::npos )
		{
			szObjName = szPathName.substr( unPos + 1, m_szFileName.length() - unPos - 1 );
		}
		else
		{
			szObjName = szPathName;
		}
	}

	// ����DB����
	m_pDBNode = CCocos2dxDBNode::Create( string( szPathName + "/"+ SKELTETON_XML ).c_str(),
		string( szPathName + "/"+ TEXTURE_XML ).c_str(),
		string( szPathName + "/"+ TEXTURE_FILE ).c_str(),
		szObjName.c_str(),
		szObjName.c_str(),
		"");
	if( m_pDBNode == NULL )
	{
		// ����ʹ��Сд������
		ChangeStringToLower( szObjName );
		m_pDBNode = CCocos2dxDBNode::Create( string( szPathName + "/"+ SKELTETON_XML ).c_str(),
			string( szPathName + "/"+ TEXTURE_XML ).c_str(),
			string( szPathName + "/"+ TEXTURE_FILE ).c_str(),
			szObjName.c_str(),
			szObjName.c_str(),
			"");
		if( m_pDBNode == NULL )
		{
			// ���Ҳ���������
			//throw std::invalid_argument("create DB sprite failed.");
			//android ƽ̨��֧��c++11����
			CCLOG("create DB sprite failed.");
			return false;
		}
	}

	// ��¼��������������
	m_tagAnimate.SetDBNode( m_pDBNode );
	
	// ����ʵ��ƫ��
	m_pDBNode->setPosition( p_tagOffset );

	// ��DB������Ϊ�ӽڵ�
	addChild( m_pDBNode );
	return true;
}
//-------------------------------------------------------------------------
void CCocos2dxDBSprite::onExit()
{
	if( m_pDBNode )
	{
		removeChild( m_pDBNode );
	}
}
//-------------------------------------------------------------------------
void CCocos2dxDBSprite::setColor( const ccColor3B& p_Color )
{
	if( m_pDBNode == NULL )
	{
		return;
	}

	vector<CBone*> vecBoneList;
	vecBoneList = m_pDBNode->GetArmature()->GetBones();

	vector<CBone*>::iterator Ite = vecBoneList.begin();
	list<CSlot*> listSlots;
	for( ; Ite != vecBoneList.end(); ++Ite )
	{
		listSlots = (*Ite)->GetSlots();

		list<CSlot*>::iterator Ite2 = listSlots.begin();
		for( ; Ite2 != listSlots.end(); ++Ite2 )
		{
			(*Ite2)->m_pDisplayBridge->UpdateColor( 0, 0, 0, 0, 1,
				static_cast<float>( p_Color.r ) / 255.0f, 
				static_cast<float>( p_Color.g ) / 255.0f, 
				static_cast<float>( p_Color.b ) / 255.0f );
		}
	}
}
//-------------------------------------------------------------------------
void CCocos2dxDBSprite::setID( unsigned int p_unID )
{
	m_uID = p_unID;
}
//-------------------------------------------------------------------------
unsigned int CCocos2dxDBSprite::getID()
{
	return m_uID;
}
//-------------------------------------------------------------------------
void CCocos2dxDBSprite::setOpacity( unsigned char p_ucAlpha )
{
	if( m_pDBNode == NULL )
	{
		return;
	}

	vector<CBone*> vecBoneList;
	vecBoneList = m_pDBNode->GetArmature()->GetBones();

	vector<CBone*>::iterator Ite = vecBoneList.begin();
	list<CSlot*> listSlots;
	for( ; Ite != vecBoneList.end(); ++Ite )
	{
		listSlots = (*Ite)->GetSlots();

		list<CSlot*>::iterator Ite2 = listSlots.begin();
		for( ; Ite2 != listSlots.end(); ++Ite2 )
		{
			(*Ite2)->m_pDisplayBridge->UpdateColor( 0, 0, 0, 0, static_cast<float>( p_ucAlpha ) / 255.0f, 1, 1, 1 );
		}
	}
}
//-------------------------------------------------------------------------
void CCocos2dxDBSprite::getFeatureString( string& p_szFeature )
{
	p_szFeature = m_szFileName;
}
//-------------------------------------------------------------------------
const string CCocos2dxDBSprite::getFileName()
{
	return m_szFileName;
}
//-------------------------------------------------------------------------
bool CCocos2dxDBSprite::hitTest( const CCPoint& p_tagPos )
{
	if( m_pDBNode == NULL )
		return false;

	CCRect rc = m_pDBNode->boundingBox();
	return rc.containsPoint( p_tagPos );
}
//-------------------------------------------------------------------------
bool CCocos2dxDBSprite::hitTest( const CCRect& p_tagRect )
{
	if( m_pDBNode == NULL )
		return false;

	CCRect rc = m_pDBNode->boundingBox();
	return rc.intersectsRect( p_tagRect );
}
//-------------------------------------------------------------------------
CCSprite* CCocos2dxDBSprite::getSprite()
{
	return NULL;
}
//-------------------------------------------------------------------------
bool CCocos2dxDBSprite::getBoundingBox( FK_OUT CCRect& p_tagBoundBox )
{
	CCSize size = CCSizeZero;
	if( m_pDBNode == NULL )
		return false;
	CArmature* pArmature = m_pDBNode->GetArmature();
	if( pArmature == NULL )
		return false;
	CAnimation* pAnima = pArmature->m_pAnimation;
	if( pAnima == NULL )
		return false;

	vector<CSlot*>  slotList = pArmature->GetSlots();
	int i = slotList.size();
	while(i --)
	{
		vector<IObject*> vecObj = slotList[i]->GetDisplayList();
		int j = vecObj.size();

		while( j-- )
		{
			if(dynamic_cast<CArmature*>(vecObj[j]))
			{
				CArmature* p = (CArmature*)vecObj[j];
				vector<CSlot*>  subSlotList = p->GetSlots();
				int k = subSlotList.size();

				while( k-- )
				{
					vector<IObject*> subVecObj = subSlotList[k]->GetDisplayList();
					int l = subVecObj.size();

					while ( l-- )
					{
						CCocos2dxDBObj* pNode = (CCocos2dxDBObj*)subVecObj[l];
						CCocos2dxDBAtlasNode* pObj = (CCocos2dxDBAtlasNode*)pNode->GetNode();
						if( pObj == NULL )
						{
							continue;
						}
						CCPoint AnchorPoint = pObj->getAnchorPoint();
						CCSize ContentSize = pObj->getContentSize();
						float fMaxX = ContentSize.width;
						float fMaxY = ContentSize.height;
						if( fMaxX > size.width )
							size.width = fMaxX;
						if( fMaxY > size.height )
							size.height = fMaxY;
					}
				}
			}
			else if(dynamic_cast<CCocos2dxDBObj*>(vecObj[j]))
			{
				CCocos2dxDBObj* pNode = (CCocos2dxDBObj*)vecObj[j];
				CCocos2dxDBAtlasNode* pObj = (CCocos2dxDBAtlasNode*)pNode->GetNode();
				if( pObj == NULL )
				{
					continue;
				}
				CCPoint AnchorPoint = pObj->getAnchorPoint();
				CCSize ContentSize = pObj->getContentSize();
				float fMaxX = ContentSize.width;
				float fMaxY = ContentSize.height;
				if( fMaxX > size.width )
					size.width = fMaxX;
				if( fMaxY > size.height )
					size.height = fMaxY;
			}
			else
			{
				// ����Ԥ��
				continue;
			}
		}
	}

	p_tagBoundBox.origin = ccp( 0.0f, 0.0f );
	p_tagBoundBox.size = size;
	p_tagBoundBox = CCRectApplyAffineTransform(p_tagBoundBox, nodeToParentTransform());
	return true; 
}
//-------------------------------------------------------------------------
IAnimation* CCocos2dxDBSprite::getAnimation()
{
	return static_cast<IAnimation*>(&m_tagAnimate);
}
//-------------------------------------------------------------------------
void CCocos2dxDBSprite::setOffset( CCPoint& p_tagOffset )
{
	if( m_pDBNode )
		m_pDBNode->setPosition( p_tagOffset );
}
//-------------------------------------------------------------------------
void CCocos2dxDBSprite::getOffset( FK_OUT CCPoint& p_tagOffset )
{
	if( m_pDBNode )
		p_tagOffset = m_pDBNode->getPosition();
}
//-------------------------------------------------------------------------