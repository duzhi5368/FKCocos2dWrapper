//*************************************************************************
//	��������:	2015-1-8
//	�ļ�����:	FKCW_RenderEx_SwayNode.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	ҡҷ�ľ���
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_RenderEx_Macros.h"
//-------------------------------------------------------------------------
class FKCW_RenderEx_SwayNode : public CCNode
{
public:
	FKCW_RenderEx_SwayNode();
	~FKCW_RenderEx_SwayNode();

	static FKCW_RenderEx_SwayNode* create( const char* p_szSpriteFile );
	virtual bool init( const char* p_szSpriteFile );

	// �ú���ÿ֡���ᱻ����
	void UpdatePos( float delta );
protected:
	int			m_nTimeUniformLocation;
	float		m_fTime;
	CCSprite*	m_pSprite;
};