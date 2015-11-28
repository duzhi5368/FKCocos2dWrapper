//*************************************************************************
//	��������:	2015-2-2
//	�ļ�����:	FKMapMgr.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../FKEngineCommonHead.h"
//-------------------------------------------------------------------------
class FKBannerReelMapMgr
{
public:
	FKBannerReelMapMgr();
	~FKBannerReelMapMgr();
public:
	// ���ø���Ⱦ�ڵ㣬���г���ȫ���ҽ��ڱ��ڵ���
	void				SetRoot( CCNode* pMapRootNode );
	// ��ȡ��ǰ�����еĵ�ͼ����
	IMapObj*			GetCurrentMap();
	// ���½����³���
	// ������szFKMFileName ��ͼ�����ļ�
	RENDER_MAP_ID		EnterMap( const char* szFKMFileName );
	// �Ƿ�����Update
	void				SetEnableUpdate( bool bIsEnable );
private:
	CCNode*						m_pMapRootNode;		// ȫ�������ҽӵ�Ψһ���ڵ�
	IMapObj*					m_pCurMapObj;		// ��ǰ�����еĳ���
	unsigned int				m_unMapID;			// map id������
};