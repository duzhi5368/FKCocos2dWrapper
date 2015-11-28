/**************************************************************************
***************************************************************************/
#pragma once

//-------------------------------------------------------------------------
enum ID_VIEW
{
	ID_FILE_VIEW = 3001 ,		//�ļ�View ID
	ID_MESSAGE_LIST_VIEW,		//��Ϣ�б�View
	ID_ATTRIBUTE_LIST_VIEW,		//�����б�View
	ID_ATTRIBUTE_EDIT_VIEW,		//���Ա༭View

	ID_CONNECT_VIEW,			//����View
	ID_LISTEN_VIEW,				//����View

	ID_CLIENT_LOG_VIEW,			//�ͻ���Log View
	ID_SERVER_LOG_VIEW,			//�ͻ���Log View

	ID_SEND_MESSAGE_BUTTON,		//���Ͱ�ť
	ID_ADD_MAIN_MESSAGE_BUTTON, //�������Ϣ��ť
	ID_REVISE_SUB_MESSAGE_BUTTON, //�޸�����Ϣ��ť
};

// add your res here.
static const char s_szSprite9Btn1Path[]				= "sprite9_btn1.png";
static const char s_szSprite9Btn2Path[]				= "sprite9_btn2.png";
static const char s_szCloseButton[]					= "close_but.png";

static const int s_iFontSizeBig = 28;
static const int s_iFontSizeNormal = 18;
static const int s_iFontSizeSmall = 14;
static const int s_iFontSizeSuperSmall = 12;