//*************************************************************************
//	��������:	2014-8-20   16:11
//	�ļ�����:	Cocos2dxDBSprite.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "CommonHead.h"
#include "Cocos2dxDBAnimation.h"
//-------------------------------------------------------------------------
USING_NS_CC;
//-------------------------------------------------------------------------
class CCocos2dxDBNode;
class CCocos2dxDBSprite : public CCNode
{
public:
	CCocos2dxDBSprite();
	virtual ~CCocos2dxDBSprite();
public:
	// ����DragonBones����
	// params p_szAniFileName DB�����Ĺ���xml�ļ����·��
	// params p_tagOffset ��Ⱦnode�ͻ�׼������ƫ��ֵ
	virtual bool			create( const char* p_szAniFileName, CCPoint p_tagOffset = ccp(0,0) );
	virtual void			onExit();

	// ��ײ���
	virtual bool			hitTest( const CCPoint& p_tagPos );
	virtual bool			hitTest( const CCRect& p_tagRect );

	virtual void			setColor( const ccColor3B& p_Color );
	virtual void			setID( unsigned int p_unID );
	virtual unsigned int	getID();
	virtual void			setOpacity( unsigned char p_ucAlpha );
	virtual void			getFeatureString( FK_OUT string& p_szFeature );
	virtual const string	getFileName();
	virtual CCSprite*		getSprite();
	// ��ȡDragonBones�����Χ��
	// ע�⣬�����Ǳ�����ȫ�������õ�������Χ��
	virtual bool			getBoundingBox( FK_OUT CCRect& p_tagBoundBox );
	virtual IAnimation*		getAnimation();
	virtual void			setOffset( CCPoint& p_tagOffset );
	virtual void			getOffset( FK_OUT CCPoint& p_tagOffset );

	CCocos2dxDBNode*		GetDBNode(){return m_pDBNode;}
private:
	string					m_szFileName;			// ����xml�ļ����·��
	CCocos2dxDBAnimation	m_tagAnimate;			// ����������
	CCocos2dxDBNode*		m_pDBNode;				// Dragoneʵ����Ⱦnode
};