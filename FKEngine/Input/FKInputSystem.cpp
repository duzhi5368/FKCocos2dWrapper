//-------------------------------------------------------------------------
#include "FKInputSystemMacros.h"
#include "FKInputSystem.h"
//-------------------------------------------------------------------------
IInputSystem* gs_pInputSystem;
FKInputSystem gs_FKInputSystem;
//-------------------------------------------------------------------------
// ��ȡ���������
IInputSystem* GetInputSystem()
{
	return gs_pInputSystem;
}
//-------------------------------------------------------------------------
FKInputSystem::FKInputSystem()
	: m_pMsgCallback( NULL )
{
	gs_pInputSystem = this;
}
//-------------------------------------------------------------------------
FKInputSystem::~FKInputSystem()
{
	gs_pInputSystem = NULL;
}
//-------------------------------------------------------------------------
// ��ʼ������
bool FKInputSystem::Init()
{
	// ��Ӽ��̷���
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	CCDirector::sharedDirector()->getOpenGLView()->setAccelerometerKeyHook( FKInputSystem::WinKeyboardHook ); 
#endif
	
	// UI���ڵ�
	if( GetUISystem() == NULL )
	{
		FKLOG("�뱣֤UIϵͳ����Input֮ǰ����");
	}
	else
	{
		if( GetUISystem()->GetRoot() == NULL )
		{
			FKLOG("UIϵͳ������δ����֮ǰ����������ʶ���޷�֧��");
		}
		else
		{
			/*
			//����
			FKCW_GR_LongPressGestureRecognizer* grLongPress = FKCW_GR_LongPressGestureRecognizer::create();
			grLongPress->SetTarget( this, callfuncO_selector(FKInputSystem::onLongPress));
			GetUISystem()->GetRoot()->addChild(grLongPress);

			//��������,��������
			FKCW_GR_PanGestureRecognizer* grPan = FKCW_GR_PanGestureRecognizer::create();
			grPan->SetTarget(this, callfuncO_selector(FKInputSystem::onPan));
			GetUISystem()->GetRoot()->addChild(grPan);

			//���
			FKCW_GR_PinchGestureRecognizer* grPinch = FKCW_GR_PinchGestureRecognizer::create();
			grPinch->SetTarget(this, callfuncO_selector(FKInputSystem::onPinch));
			GetUISystem()->GetRoot()->addChild(grPinch);

			//���ٻ�������pan��ͬ���ٶ�
			FKCW_GR_SwipeGestureRecognizer* grSwipe = FKCW_GR_SwipeGestureRecognizer::create();
			grSwipe->SetTarget(this, callfuncO_selector(FKInputSystem::onSwipe));
			GetUISystem()->GetRoot()->addChild(grSwipe);

			//���
			FKCW_GR_TapGestureRecognizer* grTap = FKCW_GR_TapGestureRecognizer::create();
			grTap->SetTarget(this, callfuncO_selector(FKInputSystem::onTap));
			GetUISystem()->GetRoot()->addChild(grTap);
			*/
		}
	}
	return true;
}
//-------------------------------------------------------------------------
// �����ͷ�
void FKInputSystem::Release()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	if( pDirector == NULL )
		return;
	pDirector->getTouchDispatcher()->removeDelegate( (CCTargetedTouchDelegate*)this );
	pDirector->getKeypadDispatcher()->removeDelegate( (CCKeypadDelegate*)this );
}
//-------------------------------------------------------------------------
// ������Ϣ�ص�������
void FKInputSystem::SetInputMsgCallback( IInputMsgHandler* pInputMsgCallback )
{
	m_pMsgCallback = pInputMsgCallback;
}
//-------------------------------------------------------------------------
// �����Ƿ��������봦��
void FKInputSystem::SetInputEnabled( bool bEnable )
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	if( pDirector == NULL )
		return;

	if( bEnable )
	{
		pDirector->getTouchDispatcher()->addTargetedDelegate((CCTargetedTouchDelegate*)this, 0, true);
		pDirector->getKeypadDispatcher()->addDelegate( (CCKeypadDelegate*)this );
	}
	else
	{
		pDirector->getTouchDispatcher()->removeDelegate((CCTargetedTouchDelegate*)this);
		pDirector->getKeypadDispatcher()->removeDelegate( (CCKeypadDelegate*)this );
	}
}
//-------------------------------------------------------------------------
// ��ȡ��Ϣ�ص�������
IInputMsgHandler* FKInputSystem::GetInputMsgCallback() const
{
	return m_pMsgCallback;
}
//-------------------------------------------------------------------------
// ������ʼ�ص�
bool FKInputSystem::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	if( m_pMsgCallback == NULL || touch == NULL )
		return false;

	// ������Ϣ����Ҫ��������
	m_pMsgCallback->OnInputMessage( eIMT_TouchBegin, touch->getID(),
		touch->getLocation().x, touch->getLocation().y, NULL );

	return false;
}
//-------------------------------------------------------------------------
// �����ƶ��ص�
void FKInputSystem::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	if( m_pMsgCallback == NULL || touch == NULL )
		return;

	// ������Ϣ����Ҫ��������
	m_pMsgCallback->OnInputMessage( eIMT_TouchMove, touch->getID(),
		touch->getLocation().x, touch->getLocation().y, NULL );
}
//-------------------------------------------------------------------------
// ���������ص�
void FKInputSystem::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	if( m_pMsgCallback == NULL || touch == NULL )
		return;

	// ������Ϣ����Ҫ��������
	m_pMsgCallback->OnInputMessage( eIMT_TouchEnd, touch->getID(),
		touch->getLocation().x, touch->getLocation().y, NULL );
}
//-------------------------------------------------------------------------
// Android��iOS�ϵĺ��˼����»ص�
void FKInputSystem::keyBackClicked()
{
	if( m_pMsgCallback == NULL )
		return;

	m_pMsgCallback->OnInputMessage( eIMT_BackKey, 0, 0.0f, 0.0f, NULL );
}
//-------------------------------------------------------------------------
// Android��iOS�ϵ�Menu�����»ص�
void FKInputSystem::keyMenuClicked()
{
	if( m_pMsgCallback == NULL )
		return;

	m_pMsgCallback->OnInputMessage( eIMT_MenuKey, 0, 0.0f, 0.0f, NULL );
}
//-------------------------------------------------------------------------
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	// WINDOWS ��Ϣ
	void FKInputSystem::WinKeyboardHook( UINT message,WPARAM wParam, LPARAM lParam )
	{
		if( gs_pInputSystem->GetInputMsgCallback() == NULL )
			return;
		switch ( message )
		{
		case WM_KEYDOWN:
			{
				gs_pInputSystem->GetInputMsgCallback()->OnInputMessage( eIMT_AnyKeyDown, 0, 0.0f, 0.0f, NULL );
			}
			break;
		case WM_KEYUP:
			{
				switch ( wParam )
				{
				case VK_F1:
					gs_pInputSystem->GetInputMsgCallback()->OnInputMessage( eIMT_KeyF1, 0, 0.0f, 0.0f, NULL );
					break;
				case VK_F2:
					gs_pInputSystem->GetInputMsgCallback()->OnInputMessage( eIMT_KeyF2, 0, 0.0f, 0.0f, NULL );
					break;
				case VK_F3:
					gs_pInputSystem->GetInputMsgCallback()->OnInputMessage( eIMT_KeyF3, 0, 0.0f, 0.0f, NULL );
					break;
				case VK_F4:
					gs_pInputSystem->GetInputMsgCallback()->OnInputMessage( eIMT_KeyF4, 0, 0.0f, 0.0f, NULL );
					break;
				case VK_F5:
					gs_pInputSystem->GetInputMsgCallback()->OnInputMessage( eIMT_KeyF5, 0, 0.0f, 0.0f, NULL );
					break;
				case VK_F6:
					gs_pInputSystem->GetInputMsgCallback()->OnInputMessage( eIMT_KeyF6, 0, 0.0f, 0.0f, NULL );
					break;
				case VK_F7:
					gs_pInputSystem->GetInputMsgCallback()->OnInputMessage( eIMT_KeyF7, 0, 0.0f, 0.0f, NULL );
					break;
				case VK_F8:
					gs_pInputSystem->GetInputMsgCallback()->OnInputMessage( eIMT_KeyF8, 0, 0.0f, 0.0f, NULL );
					break;
				case 'W':
					gs_pInputSystem->GetInputMsgCallback()->OnInputMessage( eIMT_KeyW, 0, 0.0f, 0.0f, NULL );
					break;
				case 'S':
					gs_pInputSystem->GetInputMsgCallback()->OnInputMessage( eIMT_KeyS, 0, 0.0f, 0.0f, NULL );
					break;
				case 'A':
					gs_pInputSystem->GetInputMsgCallback()->OnInputMessage( eIMT_KeyA, 0, 0.0f, 0.0f, NULL );
					break;
				case 'D':
					gs_pInputSystem->GetInputMsgCallback()->OnInputMessage( eIMT_KeyD, 0, 0.0f, 0.0f, NULL );
					break;
				case VK_UP:
					gs_pInputSystem->GetInputMsgCallback()->OnInputMessage( eIMT_KeyUp, 0, 0.0f, 0.0f, NULL );
					break;
				case VK_DOWN:
					gs_pInputSystem->GetInputMsgCallback()->OnInputMessage( eIMT_KeyDown, 0, 0.0f, 0.0f, NULL );
					break;
				case VK_LEFT:
					gs_pInputSystem->GetInputMsgCallback()->OnInputMessage( eIMT_KeyLeft, 0, 0.0f, 0.0f, NULL );
					break;
				case VK_RIGHT:
					gs_pInputSystem->GetInputMsgCallback()->OnInputMessage( eIMT_KeyRight, 0, 0.0f, 0.0f, NULL );
					break;
				case VK_SPACE:
					gs_pInputSystem->GetInputMsgCallback()->OnInputMessage( eIMT_KeySpace, 0, 0.0f, 0.0f, NULL );
					break;
				default:
					break;
				}

				gs_pInputSystem->GetInputMsgCallback()->OnInputMessage( eIMT_AnyKeyUp, 0, 0.0f, 0.0f, NULL );
			}
			break;
		case WM_MOUSEWHEEL:
			{
				SMouseWheelParam tagParam;
				tagParam.m_sDelta = LOWORD(wParam);
				if( tagParam.m_sDelta >= 0 )
				{
					tagParam.m_bIsFront = true;
				}
				else
				{
					tagParam.m_bIsFront = false;
				}
				gs_pInputSystem->GetInputMsgCallback()->OnInputMessage( eIMT_MouseWheel, 0, 
					LOWORD(lParam), HIWORD(lParam), &tagParam );
			}
			break;
		default:
			break;
		}
	}
#endif
//-------------------------------------------------------------------------
void FKInputSystem::onLongPress(CCObject* object)
{
	FKCW_GR_LongPress* p = dynamic_cast<FKCW_GR_LongPress*>(object);
	if( p == NULL )
		return;
	if( m_pMsgCallback == NULL )
		return;
	m_pMsgCallback->OnInputMessage( eIMT_LongPress, 0, 
		p->m_tagLocation.x, p->m_tagLocation.y, NULL );
}
//-------------------------------------------------------------------------
void FKInputSystem::onPan(CCObject* object)
{
	FKCW_GR_Pan* p = dynamic_cast<FKCW_GR_Pan*>(object);
	if( p == NULL )
		return;
	if( m_pMsgCallback == NULL )
		return;
	SPanParam tagParam;
	tagParam.m_fDeltaX = p->m_tagDelta.x;
	tagParam.m_fDeltaY = p->m_tagDelta.y;
	m_pMsgCallback->OnInputMessage( eIMT_Pan, 0, 
		p->m_tagLocation.x, p->m_tagLocation.y, &tagParam );
}
//-------------------------------------------------------------------------
void FKInputSystem::onPinch(CCObject* object)
{
	FKCW_GR_Pinch* p = dynamic_cast<FKCW_GR_Pinch*>(object);
	if( p == NULL )
		return;
	if( m_pMsgCallback == NULL )
		return;
	SPinchParam tagParam;
	if( p->m_eType == eGRPinchType_Open )
	{
		tagParam.m_bIsOpen = true;
	}
	else
	{
		tagParam.m_bIsOpen = false;
	}
	m_pMsgCallback->OnInputMessage( eIMT_Pinch, 0, 0.0f, 0.0f, &tagParam );
}
//-------------------------------------------------------------------------
void FKInputSystem::onSwipe(CCObject* object)
{
	FKCW_GR_Swipe* p = dynamic_cast<FKCW_GR_Swipe*>(object);
	if( p == NULL )
		return;
	if( m_pMsgCallback == NULL )
		return;
	SSwipeParam tagParam;
	if( (p->m_eDirection & eSwipeDirection_Right) == eSwipeDirection_Right )
		tagParam.m_bIsRight = true;
	if( (p->m_eDirection & eSwipeDirection_Left) == eSwipeDirection_Left )
		tagParam.m_bIsLeft = true;
	if( (p->m_eDirection & eSwipeDirection_Up) == eSwipeDirection_Up )
		tagParam.m_bIsUp = true;
	if( (p->m_eDirection & eSwipeDirection_Down) == eSwipeDirection_Down )
		tagParam.m_bIsDown = true;
	m_pMsgCallback->OnInputMessage( eIMT_Swipe, 0, 
		p->m_tagLocation.x, p->m_tagLocation.y, &tagParam );
}
//-------------------------------------------------------------------------
void FKInputSystem::onTap(CCObject* object)
{
	FKCW_GR_Tap* p = dynamic_cast<FKCW_GR_Tap*>(object);
	if( p == NULL )
		return;
	if( m_pMsgCallback == NULL )
		return;
	m_pMsgCallback->OnInputMessage( eIMT_Tap, 0, 
		p->m_tagLocation.x, p->m_tagLocation.y, NULL );
}
//-------------------------------------------------------------------------