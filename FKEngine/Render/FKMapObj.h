//*************************************************************************
//	��������:	2015-1-26
//	�ļ�����:	FKMapObj.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../FKEngineCommonHead.h"
//-------------------------------------------------------------------------
class FKBackgroundLayer;
class FKFarLayer;
class FKNormalLayer;
class FKFrontLayer;
class FKCameraMaskLayer;
class FKBarrierLayer;
class FKCameraLayer;
class FKMaskLayer;
class FKEventLayer;
class FKMapLayer;
struct SMapInfo;
class FKMapObj : public IMapObj, public CCNode
{
public:
	FKMapObj( RENDER_MAP_ID id );
	~FKMapObj();
public:
	virtual void			update( float dt );
	virtual void			onEnter();
	virtual void			onExit();
public:
	// ��һ��FKM��Դ�ļ�����
	virtual bool			InitFromFile( const char* szFKMFileName );
	// д�뵽һ����Դ�ļ�
	virtual bool			WriteToFile( const char* szFileName );

	// ���һ��Obj
	virtual unsigned int	AddObj( RENDER_MAP_LAYER_ID id, IRenderObj* pObj );
	// ��̬����Objλ��
	virtual void			SetObjPos( RENDER_MAP_CHUNK_ID id, const CCPoint& tagPos );
	// ��ȡ��ȾObj
	virtual IRenderObj*		GetObjByID( RENDER_MAP_CHUNK_ID id );
	// �Ƴ���ȾObj
	virtual void			RemoveObjByID( RENDER_MAP_CHUNK_ID id );

	// ��ȡָ����
	virtual IMapLayer*		GetLayerByID( RENDER_MAP_LAYER_ID id );

	// ת����Ļ���굽��������
	virtual void			ConvertScreenPos2ScenePos( const CCPoint& screenPos, 
		CCPoint& scenePos );

	// ��ײѡȡ���
	virtual void			HitTestObj( const CCPoint& pt, list<IRenderObj*>& ObjList );
	// ��ȡ����ID
	virtual RENDER_MAP_ID	GetID();
	// ��ȡ�����ļ���
	virtual void			GetSceneFileName( string& strFileName );
	// ����/�ر�DEBUG��Ⱦ
	virtual void			SetDebugRender( bool bIsUseDebugRender );
	// �Ƿ�����Update
	virtual void			SetEnableUpdate( bool bIsEnable );
private:
	// ��ȡ����ͼ��ȫ����Ⱦ�����б�
	void					GetRenderObjsSet( set<IRenderObj*>& SetRenderObjs );
private:
	SMapInfo*						m_pMapInfo;					// ����������Ϣ
	bool							m_bIsNeedUpdate;			// �Ƿ���Ҫ����
	bool							m_bIsUseDebugRender;		// �Ƿ�����debug��Ⱦ
	unsigned int					m_unRenderObjSceneID;		// ��Ⱦ���󳡾�ID

	map<RENDER_MAP_ID,FKMapLayer*>	m_AllLayers;				// ȫ����

	//FKBackgroundLayer*				m_pBackgroundLayer;			// �����㣬���㣬�̶���С������
	//vector<FKFarLayer*>				m_vecFarLayers;				// Զ���㣬���
	//vector<FKNormalLayer*>			m_vecNormalLayers;			// �о��㣬���
	//vector<FKFrontLayer*>				m_vecFrontLayers;			// ǰ���㣬���
	//FKCameraMaskLayer*				m_pCameraMaskLayer;			// ��ͷ�㣬���㣬�̶���С������

	//FKBarrierLayer*					m_pBarrierLayer;			// �ϰ��㣬����
	//vector<FKCameraLayer*>			m_vecCameraBarrierLayers;	// ��������Ʋ㣬���
	//FKMaskLayer*						m_pMaskLayer;				// �����ֲ㣬����
	//FKEventLayer*						m_pEventLayer;				// �¼��㣬����
};