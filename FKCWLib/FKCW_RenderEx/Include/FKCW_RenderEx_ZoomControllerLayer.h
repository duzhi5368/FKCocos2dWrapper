//*************************************************************************
//	��������:	2014-11-22
//	�ļ�����:	FKCW_RenderEx_ZoomControllerLayer.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_RenderEx_Macros.h"
//-------------------------------------------------------------------------
#define MaxZoomControllerLayerHistoryCount 12
//-------------------------------------------------------------------------
struct CCPanZoomTimePointStamp
{
	float time;
	CCPoint pt;
};
//-------------------------------------------------------------------------
class FKCW_RenderEx_ZoomControllerLayer : public CCLayer 
{
public:
	FKCW_RenderEx_ZoomControllerLayer();
	~FKCW_RenderEx_ZoomControllerLayer();

	// ����һ�����Ų㣬��ҽӵĽڵ㽫֧�����ź͹���
	static FKCW_RenderEx_ZoomControllerLayer* controllerWithNode(CCNode* node);
	bool initWithNode(CCNode* node);

	virtual void registerWithTouchDispatcher(void);
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);

public:
	bool      centerOnPinch;			/*!< Should zoom center on pinch pts, default is YES */
	bool      zoomOnDoubleTap;			/*!< Should we zoom in/out on double-tap */
	float     zoomRate;					/*!< How much to zoom based on movement of pinch */
	float     zoomInLimit;				/*!< The smallest zoom level */
	float     zoomOutLimit;				/*!< The hightest zoom level */
	float     swipeVelocityMultiplier;	/*!< The velocity factor of the swipe's scroll action */
	float     scrollDuration;			/*!< Duration of the scroll action after a swipe */
	float     scrollDamping;			/*!< When scrolling around, this will dampen the movement */
	float     pinchDamping;				/*!< When zooming, this will dampen the zoom */
	float     pinchDistanceThreshold;	/*!< The distance moved before a pinch is recognized */
	float     doubleTapZoomDuration;	/*!< Duration of zoom after double-tap */

public:
	// �����������Χ
	void	setBoundingRect(CCRect rect);
	CCRect	getBoundingRect();
	// �û��Լ���Ⱦ���ڴ�С��Ĭ���������CCDirector��winSize��С��
	void	setWindowRect(CCRect rect);
	CCRect	getWindowRect();
	// ��ȡ��ǰ����������Ʊ�
	float	getOptimalZoomOutLimit();
	// �۽���ָ����
	void	centerOnPoint(CCPoint pt, float damping);
	// �ƶ���ָ��λ��
	void	updatePosition(CCPoint pos);
	// ����ָ����Ϊ��ͼ�������ĵ�
	void	centerOnPoint(CCPoint pt);
	// ����ָ����Ϊ��ͼ�������ĵ㣬��ָ������Ϊʱ��
	void	centerOnPoint(CCPoint pt, float duration, float rate);
	// ��ָ��λΪ���ĵ���Сָ��ʱ��
	void	zoomInOnPoint(CCPoint pt, float duration);
	// ��ָ��λΪ���ĵ�Ŵ�ָ��ʱ��
	void	zoomOutOnPoint(CCPoint pt, float duration);
	// ��ָ��λΪ���ĵ����ŵ�ָ����С
	void	zoomOnPoint(CCPoint pt, float duration, float scale);
	// ����touch��Ϣ��ȡ
	void	enableWithTouchPriority(int priority, bool swallowsTouches);
	// �ر�touch��Ϣ��ȡ
	void	disable();
private:
	CCNode*			_node;			// ����
	CCPoint			_tr;			// �����Χ��
	CCPoint			_bl;			// �����Χ��
	CCPoint			_winTr;			// ���ڴ�С
	CCPoint			_winBl;			// ���ڴ�С
	CCPoint			_firstTouch;	// �״δ�����
	float			_firstLength;	// �ƶ�����
	float			_oldScale;		// ֮ǰ������
	CCDictionary*	_touchesDic;	// ���津�����
	// internals
	float			_time;
	int				_timePointStampCounter;
	CCPanZoomTimePointStamp _history[MaxZoomControllerLayerHistoryCount];
	CCAction*		_lastScrollAction;
private:
	void			updateTime(float dt);
	CCPoint			boundPos(CCPoint pos);
	void			recordScrollPoint(CCTouch* touch);
	CCPoint			getHistoricSpeed();

	void			handleDoubleTapAt(CCPoint pt);

	void			beginScroll(CCPoint pos);
	void			moveScroll(CCPoint pos);
	void			endScroll(CCPoint pos);

	void			beginZoom(CCPoint pt, CCPoint pt2);
	void			moveZoom(CCPoint pt, CCPoint pt2);
	void			endZoom(CCPoint pt, CCPoint pt2);
};
//-------------------------------------------------------------------------
// ��������Ŷ�������֤��ͼ���ľ۽���һ��������
class FKCW_RenderEx_ZoomControllerLayerScaleAction : public CCScaleTo 
{
public:
	FKCW_RenderEx_ZoomControllerLayerScaleAction();
	~FKCW_RenderEx_ZoomControllerLayerScaleAction();
	static FKCW_RenderEx_ZoomControllerLayerScaleAction* actionWithDuration(float duration, float s, FKCW_RenderEx_ZoomControllerLayer* controller, CCPoint pt);
	bool initWithDuration(float duration, float s, FKCW_RenderEx_ZoomControllerLayer* controller, CCPoint pt);

	void update(float t);
public:
	FKCW_RenderEx_ZoomControllerLayer*	m_pControllerLayer;
	CCPoint								m_tagCenterPoint;
};
//-------------------------------------------------------------------------