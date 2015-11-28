//*************************************************************************
//	��������:	2015-1-27
//	�ļ�����:	FKMapStruct.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../FKEngineCommonHead.h"
#include "FKMapSystemMacros.h"
//-------------------------------------------------------------------------
// ��ͼ��
struct SMapGridInfo : public IMapGridInfo
{
	CCPoint				tagPos;			// ��������λ�����ĵ㣨��Ա�����
	unsigned short		usMainValue;	// ������ֵ
	unsigned short		usSubValue;		// ������ֵ
	SMapGridInfo()
		: usMainValue( 0 )
		, usSubValue( 0 )
	{
		tagPos = CCPointZero;
	}

	// ��ȡ��������
	virtual ENUM_MapChunkType	GetGridType() = 0;
};
// �ϰ���
struct SBarrierGridInfo : public SMapGridInfo
{
	// �ж��Ƿ����ϰ�
	bool		IsBarrier()
	{
		return (usMainValue != 0);
	}
	// ��ȡ����ID����IDӦ���ڱ�Chunk��Ψһ
	virtual unsigned short		GetGridID()
	{
		return ((((unsigned short)tagPos.x / s_BarrierGridSize )<< 8) 
			| ((unsigned short)tagPos.y / s_BarrierGridSize ));
	}
	// ��ȡ���Ӵ�С
	virtual void				GetSize( CCSize& tagSize )
	{
		tagSize = CCSizeMake( s_BarrierGridSize, s_BarrierGridSize );
	}
	// ��ȡ��������
	virtual void				GetRectInChunk( CCRect& tagRect )
	{
		tagRect = CCRectMake( tagPos.x - s_BarrierGridSize / 2,
			tagPos.y - s_BarrierGridSize / 2, s_BarrierGridSize, s_BarrierGridSize );
	}
	// ��ȡ��������
	virtual ENUM_MapChunkType	GetGridType()
	{
		return eMCT_Barrier;
	}
};
// �������
struct SCameraGridInfo : public SMapGridInfo
{
	// �ж��Ƿ���ֹ������ƶ�
	bool		IsCameraBarrier()
	{
		return (usMainValue != 0);
	}
	// ��ȡ����ID����IDӦ���ڱ�Chunk��Ψһ
	virtual unsigned short		GetGridID()
	{
		return ((((unsigned short)tagPos.x / s_CameraGridSize )<< 8) 
			| ((unsigned short)tagPos.y / s_CameraGridSize ));
	}
	// ��ȡ���Ӵ�С
	virtual void				GetSize( CCSize& tagSize )
	{
		tagSize = CCSizeMake( s_CameraGridSize, s_CameraGridSize );
	}
	// ��ȡ��������
	virtual void				GetRectInChunk( CCRect& tagRect )
	{
		tagRect = CCRectMake( tagPos.x - s_CameraGridSize / 2,
			tagPos.y - s_CameraGridSize / 2, s_CameraGridSize, s_CameraGridSize );
	}
	// ��ȡ��������
	virtual ENUM_MapChunkType	GetGridType()
	{
		return eMCT_Camera;
	}
};
// �¼���
struct SEventGridInfo : public SMapGridInfo
{
	// �ж��¼�����
	void 		GetEventType( unsigned short& sMainEventType, unsigned short& sSubEventType )
	{
		sMainEventType = usMainValue;
		sSubEventType = usSubValue;
	}
	// ��ȡ����ID����IDӦ���ڱ�Chunk��Ψһ
	virtual unsigned short		GetGridID()
	{
		return ((((unsigned short)tagPos.x / s_EventGridSize )<< 8) 
			| ((unsigned short)tagPos.y / s_EventGridSize ));
	}
	// ��ȡ���Ӵ�С
	virtual void				GetSize( CCSize& tagSize )
	{
		tagSize = CCSizeMake( s_EventGridSize, s_EventGridSize );
	}
	// ��ȡ��������
	virtual void				GetRectInChunk( CCRect& tagRect )
	{
		tagRect = CCRectMake( tagPos.x - s_EventGridSize / 2,
			tagPos.y - s_EventGridSize / 2, s_EventGridSize, s_EventGridSize );
	}
	// ��ȡ��������
	virtual ENUM_MapChunkType	GetGridType()
	{
		return eMCT_Event;
	}
};
// �ɰ����ָ�
struct SMaskGridInfo : public SMapGridInfo
{
	// �Ƿ��ɰ�����
	bool		IsMask()
	{
		return (usMainValue != 0);
	}
	// ��ȡ����ID����IDӦ���ڱ�Chunk��Ψһ
	virtual unsigned short		GetGridID()
	{
		return ((((unsigned short)tagPos.x / s_MaskGridSize )<< 8) 
			| ((unsigned short)tagPos.y / s_MaskGridSize ));
	}
	// ��ȡ���Ӵ�С
	virtual void				GetSize( CCSize& tagSize )
	{
		tagSize = CCSizeMake( s_MaskGridSize, s_MaskGridSize );
	}
	// ��ȡ��������
	virtual void				GetRectInChunk( CCRect& tagRect )
	{
		tagRect = CCRectMake( tagPos.x - s_MaskGridSize / 2,
			tagPos.y - s_MaskGridSize / 2, s_MaskGridSize, s_MaskGridSize );
	}
	// ��ȡ��������
	virtual ENUM_MapChunkType	GetGridType()
	{
		return eMCT_Mask;
	}
};
//-------------------------------------------------------------------------
// ����
//-------------------------------------------------------------------------
// ��ͼ������Ϣ
struct SMapChunkInfo
{
	CCPoint				tagPos;		// ������������λ�ã�����������磩
	RENDER_MAP_CHUNK_ID	unChunkID;	// �����ţ������ڲ�Ӧ����Ψһ�ԣ�
	SMapChunkInfo()
		: unChunkID( 0 )
	{
		tagPos = CCPointZero;
	}
	// ��ȡ����ID����IDӦ���ڱ�������Ψһ
	virtual unsigned int		GetChunkID(){ return unChunkID; }
	// ��ȡ�����С
	virtual void				GetSize( CCSize& tagSize ){ return; };
	// ��ȡ����Χ
	virtual void				GetRect( CCRect& tagRect ){ return; };
	// ��ȡ��������
	virtual ENUM_MapChunkType	GetType(){ return eMCT_Max; };
};
// �ϰ�������Ϣ
struct SBarrierChunkInfo : public SMapChunkInfo
{
	// ��ȡ�����С
	virtual void				GetSize( CCSize& tagSize )
	{
		tagSize = CCSizeMake( s_BarrierChunkWidth, s_BarrierChunkHeight );
	}
	// ��ȡ����Χ
	virtual void				GetRect( CCRect& tagRect ) 
	{
		tagRect = CCRectMake( tagPos.x - s_BarrierChunkWidth / 2,
			tagPos.y - s_BarrierChunkHeight / 2,
			s_BarrierChunkWidth, s_BarrierChunkHeight );
	}
	// ��ȡ��������
	virtual ENUM_MapChunkType	GetType()
	{
		return eMCT_Barrier;
	}
};
// ������ϰ�������Ϣ
struct SCameraChunkInfo : public SMapChunkInfo
{
	// ��ȡ�����С
	virtual void				GetSize( CCSize& tagSize )
	{
		tagSize = CCSizeMake( s_CameraChunkWidth, s_CameraChunkHeight );
	}
	// ��ȡ����Χ
	virtual void				GetRect( CCRect& tagRect ) 
	{
		tagRect = CCRectMake( tagPos.x - s_CameraChunkWidth / 2,
			tagPos.y - s_CameraChunkHeight / 2,
			s_CameraChunkWidth, s_CameraChunkHeight );
	}
	// ��ȡ��������
	virtual ENUM_MapChunkType	GetType()
	{
		return eMCT_Camera;
	}
};
// �¼�������Ϣ
struct SEventChunkInfo : public SMapChunkInfo
{
	// ��ȡ�����С
	virtual void				GetSize( CCSize& tagSize )
	{
		tagSize = CCSizeMake( s_EventChunkWidth, s_EventChunkHeight );
	}
	// ��ȡ����Χ
	virtual void				GetRect( CCRect& tagRect ) 
	{
		tagRect = CCRectMake( tagPos.x - s_EventChunkWidth / 2,
			tagPos.y - s_EventChunkHeight / 2,
			s_EventChunkWidth, s_EventChunkHeight );
	}
	// ��ȡ��������
	virtual ENUM_MapChunkType	GetType()
	{
		return eMCT_Event;
	}
};
// ����������Ϣ
struct SMaskBarrierChunkInfo : public SMapChunkInfo
{
	// ��ȡ�����С
	virtual void				GetSize( CCSize& tagSize )
	{
		tagSize = CCSizeMake( s_MaskChunkWidth, s_MaskChunkHeight );
	}
	// ��ȡ����Χ
	virtual void				GetRect( CCRect& tagRect ) 
	{
		tagRect = CCRectMake( tagPos.x - s_MaskChunkWidth / 2,
			tagPos.y - s_MaskChunkHeight / 2,
			s_MaskChunkWidth, s_MaskChunkHeight );
	}
	// ��ȡ��������
	virtual ENUM_MapChunkType	GetType()
	{
		return eMCT_Mask;
	}
};
// ͼƬ������Ϣ
struct SImageChunkInfo : public SMapChunkInfo
{
	// ��ȡ�����С
	virtual void				GetSize( CCSize& tagSize )
	{
		tagSize = CCSizeMake( s_PicChunkWidth, s_PicChunkHeight );
	}
	// ��ȡ����Χ
	virtual void				GetRect( CCRect& tagRect ) 
	{
		tagRect = CCRectMake( tagPos.x - s_PicChunkWidth / 2,
			tagPos.y - s_PicChunkHeight / 2,
			s_PicChunkWidth, s_PicChunkHeight );
	}
	// ��ȡ��������
	virtual ENUM_MapChunkType	GetType()
	{
		return eMCT_Image;
	}
};
//-------------------------------------------------------------------------
// ��
//-------------------------------------------------------------------------
// ��
struct SMapLayerInfo
{
	RENDER_MAP_LAYER_ID		unLayerID;
	float					fHeightParallax;		// �߶��Ӳ�
	float					fWidthParallax;			// �����Ӳ�
	int						nDepth;					// Zorder���

	SMapLayerInfo()
		: unLayerID( 0 )
		, fWidthParallax( 1.0f )
		, fHeightParallax( 0.0f )
	{
	}
};
//-------------------------------------------------------------------------
// ��ͼ
//-------------------------------------------------------------------------
struct SMapInfo
{
	RENDER_MAP_ID			unMapID;
	string					strMapFileName;			// ��ͼ�ļ���

	SMapInfo()
		: unMapID( 0 )
	{
		strMapFileName.clear();
	}
};