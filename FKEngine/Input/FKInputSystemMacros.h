//*************************************************************************
//	��������:	2015-1-14
//	�ļ�����:	FKInputSystemMacros.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
// �ص�������Ϣ������
enum ENUM_InputMsgType
{
	eIMT_UnknownMsg				= 0,
	eIMT_TouchBegin				= 1,		// ������ʼ
	eIMT_TouchMove				= 1,		// �����ƶ���
	eIMT_TouchEnd				= 2,		// ��������

	eIMT_LongPress				= 100,		// ��������
	eIMT_Pan					= 101,		// ��������
	eIMT_Pinch					= 102,		// ���
	eIMT_Swipe					= 103,		// ���ٻ���
	eIMT_Tap					= 104,		// ���

	eIMT_BackKey				= 200,		// Android��iOS�ϵĺ��˼�����
	eIMT_MenuKey				= 201,		// Android��iOS�ϵ�Menu������

	eIMT_KeyF1					= 300,		// Win��F1������
	eIMT_KeyF2					= 301,		// Win��F2������
	eIMT_KeyF3					= 302,		// Win��F3������
	eIMT_KeyF4					= 303,		// Win��F4������
	eIMT_KeyF5					= 304,		// Win��F5������
	eIMT_KeyF6					= 305,		// Win��F6������
	eIMT_KeyF7					= 306,		// Win��F7������
	eIMT_KeyF8					= 307,		// Win��F8������

	eIMT_KeyW					= 308,		// Win��'W'������
	eIMT_KeyS					= 309,		// Win��'S'������
	eIMT_KeyA					= 310,		// Win��'A'������
	eIMT_KeyD					= 311,		// Win��'D'������
	eIMT_KeyUp					= 312,		// Win���ϼ�ͷ������
	eIMT_KeyDown				= 313,		// Win���¼�ͷ������
	eIMT_KeyLeft				= 314,		// Win�����ͷ������
	eIMT_KeyRight				= 315,		// Win���Ҽ�ͷ������

	eIMT_KeySpace				= 316,		// Win�Ͽո������

	eIMT_AnyKeyDown				= 400,		// Win�����ⰴť������Ϣ
	eIMT_AnyKeyUp				= 401,		// Win�����ⰴţ̌����Ϣ
	eIMT_MouseWheel				= 402,		// Win�Ϲ���������Ϣ

	eIMT_UserData				= 1000,		// �û��Զ�����Ϣ
};
//-------------------------------------------------------------------------
// ������Ϣ������Ϣ
struct SMouseWheelParam
{
	bool		m_bIsFront;			// �Ƿ���ǰ������trueΪ��ǰ���ϣ�falseΪ������£�
	short		m_sDelta;			// ���ֹ����Ƕ�
	SMouseWheelParam()
		: m_bIsFront( false )
		, m_sDelta( 0 ){}
};
//-------------------------------------------------------------------------
// �������ƶ�����Ϣ
struct SPanParam
{
	float		m_fDeltaX;
	float		m_fDeltaY;
	SPanParam()
		: m_fDeltaX( 0.0f )
		, m_fDeltaY( 0.0f ){}
};
//-------------------------------------------------------------------------
// ��ѹ��϶�����Ϣ
struct SPinchParam
{
	bool		m_bIsOpen;			// �Ƿ��ǷŴ�true��ʾ�ǷŴ�false��ʾ����С��
	SPinchParam()
		: m_bIsOpen( false ){}
};
//-------------------------------------------------------------------------
// ���ٻ�����Ϣ
struct SSwipeParam
{
	bool		m_bIsRight;		// �Ƿ������һ���
	bool		m_bIsLeft;		// �Ƿ������󻬶�
	bool		m_bIsUp;		// �Ƿ������ϻ���
	bool		m_bIsDown;		// �Ƿ������»���
	SSwipeParam()
		: m_bIsDown( false )
		, m_bIsUp( false )
		, m_bIsLeft( false )
		, m_bIsRight( false ){}
};
//-------------------------------------------------------------------------