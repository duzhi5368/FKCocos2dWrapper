//*************************************************************************
//	��������:	2015-1-26
//	�ļ�����:	FKMapSystemMacros.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
// ��ͼ������
enum ENUM_MapChunkType
{
	eMCT_Barrier = 0,			// �ϰ���
	eMCT_Camera,				// ����������
	eMCT_Mask,					// ���ָ�
	eMCT_Event,					// �¼���
	eMCT_Image,					// ��ͨ��ͼƬ��

	eMCT_Max,
};
//-------------------------------------------------------------------------
// debugָʾ����ɫ
const static ccColor4F s_BrrierGridDebugColor = { 1.0f, 0.0f, 0.0f, 0.5f };
const static ccColor4F s_CameraGridDebugColor = { 0.0f, 1.0f, 0.0f, 0.5f };
const static ccColor4F s_MaskGridDebugColor =	{ 0.0f, 0.0f, 1.0f, 0.5f };
const static ccColor4F s_EventGridDebugColor =	{ 1.0f, 0.0f, 1.0f, 0.5f };
//-------------------------------------------------------------------------
// ��ͼͼƬ������
enum ENUM_MapImageLayerType
{
	eMILT_Barrier = 0,				// �ϰ���
	eMILT_Camera,					// ����������
	eMILT_Mask,						// ���ָ�
	eMILT_Event,					// �¼���

	eMILT_CameraMask,				// ��������ֲ㣨����ˮ��ӣ������Чר�ã�
	eMILT_Front,					// ǰ����
	eMILT_Normal,					// �м��
	eMILT_Far,						// Զ����
	eMILT_Background,				// ������

	eMILT_Max,
};
//-------------------------------------------------------------------------
// ��ͼ����ID ���� zOrder
const static unsigned int	s_BackgroundLayerID		= 10000;	// ����

const static unsigned int	s_FarLayerIDBegin		= 11000;
const static unsigned int	s_FarLayerIDEnd			= 12999;
const static unsigned int	s_NormalLayerIDBegin	= 14000;
const static unsigned int	s_NormalLayerIDEnd		= 15999;
const static unsigned int	s_FrontLayerIDBegin		= 17000;
const static unsigned int	s_FrontLayerIDEnd		= 18999;

const static unsigned int	s_CameraMaskLayerID		= 19000;	// ����

const static unsigned int	s_EventLayerID			= 20000;	// ����
const static unsigned int	s_MaskLayerID			= 19999;	// ����
const static unsigned int	s_BarrierLayerID		= 19998;	// ����

const static unsigned int	s_CameraLayerIDBegin	= 19500;
const static unsigned int	s_CameraLayerIDEnd		= 19600;
//-------------------------------------------------------------------------
// �ϰ�����
const static int		s_BarrierGridSize = 16;
// �ϰ���������ϰ��������������
const static int		s_BarrierGridRowNumInChunk = 32;
const static int		s_BarrierGridColNumInChunk = 32;
// �ϰ������
const static int		s_BarrierChunkWidth	= 512;	// s_BarrierGridSize * s_BarrierGridRowNumInChunk
const static int		s_BarrierChunkHeight = 512;	// s_BarrierGridSize * s_BarrierGridColNumInChunk
// ���������
const static int		s_CameraGridSize = 16;
// ������������������������������
const static int		s_CameraGridRowNumInChunk = 32;
const static int		s_CameraGridColNumInChunk = 32;
// ����������			
const static int		s_CameraChunkWidth	= 512;	// s_CameraGridSize * s_CameraGridRowNumInChunk
const static int		s_CameraChunkHeight = 512;	// s_CameraGridSize * s_CameraGridColNumInChunk
// �ɰ����
const static int		s_MaskGridSize = 16;
// �ɰ���������ɰ�������������
const static int		s_MaskGridRowNumInChunk = 32;
const static int		s_MaskGridColNumInChunk = 32;
// �ɰ������			
const static int		s_MaskChunkWidth	= 512;	// s_MaskGridSize * s_MaskGridRowNumInChunk
const static int		s_MaskChunkHeight	= 512;	// s_MaskGridSize * s_MaskGridColNumInChunk
// �¼�����
const static int		s_EventGridSize = 16;
// �¼���������¼��������������
const static int		s_EventGridRowNumInChunk = 32;
const static int		s_EventGridColNumInChunk = 32;
// �¼������			
const static int		s_EventChunkWidth	= 512;	// s_EventGridSize * s_EventGridRowNumInChunk
const static int		s_EventChunkHeight	= 512;	// s_EventGridSize * s_EventGridColNumInChunk

// ͼƬ�����
const static int		s_PicChunkWidth		= 512;
const static int		s_PicChunkHeight	= 512;
//-------------------------------------------------------------------------