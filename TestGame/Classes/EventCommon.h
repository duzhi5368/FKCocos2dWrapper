//*************************************************************************
//	��������:	2015-3-23
//	�ļ�����:	EventCommon.h
//  �� �� ��:   �˹۸� Rect 	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------

enum ENMU_EVENT_SRC_ID
{
	eEvent_Src_Min = 0,
	eEvent_Scene_Switch,			// �����л���Ϣ
	eEvent_Play_ButtonClick,		// 
	eEvent_Src_Max,
};

enum ENUM_EVENT_TYPE_ID
{
	eEvent_Min = 0,
	eEvent_UIEvent,				// �û����������¼�
	eEventE_Max,
};