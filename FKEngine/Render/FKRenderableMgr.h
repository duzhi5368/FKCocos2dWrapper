//*************************************************************************
//	��������:	2015-1-19
//	�ļ�����:	FKRenderableMgr.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../FKEngineCommonHead.h"
//-------------------------------------------------------------------------
class FKRenderableMgr
{
protected:
	FKRenderableMgr();
	~FKRenderableMgr();
public:
	// ��������
	static FKRenderableMgr& GetInstance()
	{
		static FKRenderableMgr s_FKRenderableMgrInstance;
		return s_FKRenderableMgrInstance;
	}
public:
	// ��ȡ��Ⱦ����
	IRenderable*			GetRenderable( RENDER_OBJ_ID id );
	// ɾ����Ⱦ����
	void					RemoveRenderable( RENDER_OBJ_ID id );

	// ������̬�������
	ISprite*				CreateSprite( const char* szPicFileName, 
		const CCRect& rect, CCPoint ptOffset = CCPointZero );
	// ����֡�������
	IFrameSprite*			CreateFrameSprite( const char* szFrameFileName, CCPoint ptOffset = CCPointZero );
	// ����DB��������
	IDragonBonesSprite*		CreateDBSprite( const char* szDBFileName, CCPoint ptOffset = CCPointZero );
	// ����CocosBuilder������������
	IArmatureSprite*		CreateArmaSprite( const char* szArmaFileName, CCPoint ptOffset = CCPointZero );
	// ������Ч����
	IEffect*				CreateEffect( const char* szEffectFileName, CCPoint ptOffset = CCPointZero );
private:
	typedef map<RENDER_OBJ_ID, IRenderable*>	RenderableMap;
	RenderableMap			m_mapRenderables;	// ��ǰ��������Ⱦ�����
	RENDER_OBJ_ID			m_unCurID;			// ��ǰ��Ⱦ������
};