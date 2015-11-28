//*************************************************************************
//	��������:	2014-11-28
//	�ļ�����:	FKCW_RenderEx_ScrollingBackgroundNode.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_RenderEx_Macros.h"
//-------------------------------------------------------------------------
typedef std::list<CCSprite*> NodeList;
typedef std::list<CCSprite*>::iterator ListIter;

//current �������������뿪��Ļ�ĵ�ͼ����
//follow  �������������뿪��Ļ�ĵ�ͼ����
//leave   ���ո��뿪��Ļ�ĵ�ͼ����
typedef void (CCObject::*SEL_BgSpriteChangeEvent)(CCSprite* current,CCSprite* follow,CCSprite* leave);
#define bgSpriteChangeEvent(_SELECTOR) (SEL_BgSpriteChangeEvent)(&_SELECTOR)

//current �������������뿪��Ļ�ĵ�ͼ����
//follow  �������������뿪��Ļ�ĵ�ͼ����
typedef void (CCObject::*SEL_BgSpriteMovbEvent)(CCSprite* current,CCSprite* follow);
#define bgSpriteMoveEvent(_SELECTOR) (SEL_BgSpriteMovbEvent)(&_SELECTOR)

///���������ķ���
enum ENUM_ScrollDirection
{
	SD_RIGHT_TO_LEFT,
	SD_LEFT_TO_RIGHT,
	SD_TOP_TO_BOTTOM,
	SD_BOTTOM_TO_TOP
};
//-------------------------------------------------------------------------
/**
 * ��������
 * ����ѡ�������,���ҵ���,���ϵ���,���µ����ĸ��������
 * ����ģʽ������ѭ��,ͨ�����ûص�����,����ʵ�ֱ߹��������ٻ�����߲��뻭��
 * ����addBackgroundBlock���ӻ���,���ÿ�ʼ����
 * ������Ҫ�������������ȷ����
 */
class ScrollingBackground : public CCNode
{
public:
	ScrollingBackground();
	virtual ~ScrollingBackground();

	// ���ӱ�������,����Ľڵ���Զ�����������Ļ,���ӵ�����β
	// ע������һ�߹���һ�����ӱ�������ڵ�,�����ǰ�ڵ�������β,��ʧ�ܲ�����false
	bool addBackgroundSprite(CCSprite* bgSprite);
	// ��ʼ��������
	bool beginContinuousScroll(float velocity);
	// �������������������ڵ��е�һ�������뿪��Ļ
	bool scrollToNextBgSprite(float velocity);
	// ���ñ����ƶ��趨�ľ���
	bool setBgSpriteScrollBy(float velocity,float distance);
	// ��ͣ����
	void pauseScroll();
	// �ָ�����
	void resumeScroll(float velocity);
	// �Ƴ������ڵ�,�����뱣֤�ڵ������ڵĽڵ�������2,�Ҳ����Ƴ���ǰ��ʾ����Ļ�ڵ������ڵ�
	bool removeBgSprite(CCSprite* bgSprite);
	// ���ñ���ȫ��������ʾ
	void setFullScreen(CCSprite* bgSprite);
	// ���ص�ͼ�������ж����ŵ�ͼ����
	int   getNumBgSprite();

	float		getVelocity();
	bool		isListBack(CCSprite* bgBlock);
	bool		isListFront(CCSprite* bgBlock);
	void		setVelocity(float velocity);

	CCSprite*	getBackBgSprite();
	CCSprite*	getFrontBgSprite();
	CCSprite*	getCurBgSprite();
	CCSprite*	getFollowBgSprite();
	
	/**
	 * ��һ�����泹���뿪��Ļ��ʱ��ᷢ�������Ϣ
	 * SEL_BgSpriteChangeEvent �� CCSprite* ������������Ļ�ڵ�������ͼ�ڵ��һ���Ѿ��뿪��Ļ�ĵ�ͼ�ڵ�
	 */
	void setBgChangeEventListener(CCObject *target, SEL_BgSpriteChangeEvent selector);

	/**
	 * ��һ�������ƶ���ʱ��ᷢ�������Ϣ
	 * SEL_BgSpriteChangeEvent �� CCSprite* ������������Ļ�ڵ�������ͼ�ڵ�
	 */
	void setBgMoveEventListener(CCObject *target, SEL_BgSpriteMovbEvent selector);

	/**
	 *  һ����̬����,���ڴ���ScrollingBackground
	 *@param type ����ģʽ
	 *@param ScrollDirection �������� 
	 */
	static ScrollingBackground* create(ENUM_ScrollDirection direction);
protected:
	ENUM_ScrollDirection	m_direction;     // ��������
	NodeList				m_bgSpriteList;  // �ڵ㴢������
	ListIter				m_curIter;       // ��ǰ��������Ļ�ϵ����������ǰһ�����������ȹ�����Ļ���Ǹ���
	ListIter				m_followIter;    // ��ǰ��������Ļ�ϵ���������ĺ�һ�������滭�棨������������Ļ���Ǹ���
	CCSize			m_visibleSize;   // ������Ļ�Ĵ�С,���ڽ������������ŵ�������Ļ
	bool					m_isScrolling;   // �Ƿ����ڹ���
	bool					m_bScrollToNext; // �Ƿ������˱������������������ڵ��е�һ�������뿪��Ļ
	bool					m_bScrollBy;     // �Ƿ��趨��������һ������
	float					m_velocity;      // �������ٶ�
	float					m_distance;      // �趨��������ƶ�����
	float					m_sensitivity;   // ����scrollToNextBgSprite������������һ��ͼƬ��ʶ��������
	CCObject*      m_changeEventListener;
    SEL_BgSpriteChangeEvent m_changeEventSelector;
	CCObject*      m_moveEventListener;
    SEL_BgSpriteMovbEvent   m_moveEventSelector;

protected:
	bool init(ENUM_ScrollDirection direct);
	// �����ڵ㲢���ڵ�����б�
	void	_AddListNode(CCSprite* bgSprite);
	// һ�����泹���뿪��Ļ��ʱ���������,�������� m_curIter �� m_followIter
	void	_ChangeCurBgSprite();
	// ÿһ֡����һ��,���û����λ��
	void	_MoveAction(float d);
	// ���ø��滭���λ��
	void	_SetFollowNodePosition();
	// �ж�һ�������Ƿ�����Ļ��Χ��
	bool	_IsChangeBg(const CCPoint& posCur,const CCPoint& achorPointCur);
	// ���ٶ�Ϊ����ʱ��,Ҫ��������һʱ�� m_curIter ��ָ��ı����ڵ��λ��
	void	_PreSetCurPos();
	// ������ʱ��Ĺ�������
	bool	_BeginScroll(float velocity);
};
