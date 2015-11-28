/********************************************************************
	created:	2014/11/03
	file base:	FKCW_Action_TrailMoveTo
	author:		FreeKnight
	
	purpose:	���ƶ��켣���ƶ�����
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include "FKCW_Action_Macros.h"
//--------------------------------------------------------------------
// �����ƶ�����������������ƶ��켣�Ķ���
// ע�⣺���ƶ�������CCArmatureʱ����β�켣������ӵ���Node�У��뱣֤Ԥ�����㹻��Z���ֵ
class FKCW_Action_TrailMoveTo : public CCMoveTo
{
private:
	enum ENUM_TrailMode
	{
		eTrailMode_SpriteFrameName,
		eTrailMode_FileName,
		eTrailMode_Armature,
	};
protected:
	CCArray			m_vecTrails;			// �켣
	float			m_fAlphaStep;			// ÿ����Alpha
	CCPoint			m_tagDirection;			// �ƶ�����
	float			m_fSpeed;				// �ƶ��ٶ�
	float			m_fDistance;			// ����
	bool			m_bIsEnd;				// �Ƿ����ѽ���
	ENUM_TrailMode	m_eTrailMode;			// ��β��ʽ
	string			m_strSpriteName;		// ��βʹ�õľ�����/ͼƬ��/֡��
	int				m_nVisibleArmIndex;		// ��ǰ�ɼ���Armature��β����

	CC_SYNTHESIZE(float, m_fTrailDistance, trailDistance);						// ��β�������
	CC_SYNTHESIZE(int, m_nTrailSegments, TrailSegments);						// ��β�켣����
	CC_SYNTHESIZE_PASS_BY_REF(ccColor3B, m_tagTrailColor, TrailColor);			// ��β�켣��ɫ
	CC_SYNTHESIZE_PASS_BY_REF(ccColor4B, m_tagTrailColorScale, TrailColorScale);// ��β�켣�����ɫ
	CC_SYNTHESIZE(int, m_nAnimationIndex, AnimationIndex);						// ������������ʹ�ö������켣��
	CC_SYNTHESIZE_PASS_BY_REF(string, m_strAnimationName, AnimationName);		// ����������ʹ�ö������켣��
	CC_SYNTHESIZE_BOOL(m_bIsRemoveWhenDone, RemoveWhenDone);					// ����ֵΪtrue���ʾ�����ƶ��������ʱ����β�����
protected:
	FKCW_Action_TrailMoveTo();
	// ����������������ȫ����β�켣
	void			CleanTrails();
	// Ԥ��Ⱦ
	void			OnPreDraw( CCObject* p_pSender );
	// �Ƴ�һ����β
	void			RemoveTrail( CCNode* p_pTrail );
public:
	virtual ~FKCW_Action_TrailMoveTo();

	// ����һ����β�켣����ʵ��
	/* ������
		duration		����ʱ��
		position		Ŀ��ص�
		trailFrameName	����Դ���е���β����֡��
		trailDistance	������β�켣֮��ļ������
		trailSegments	��β�켣�θ���
		trailColor		��β�켣��ɫ��Ĭ�ϰ�ɫ��ʾ����ɫ�仯
		trailColorScale	��β�켣���ӻ����ɫ��Ĭ�ϰ�ɫ��ʾ����ɫ�仯
		removeWhenDone	����ֵΪtrue���ʾ�����ƶ��������ʱ����β�����
	*/
	static FKCW_Action_TrailMoveTo* CreateWithSpriteFrameName(float duration, const CCPoint& position, const string& trailFrameName,
		float trailDistance, int trailSegments, ccColor3B trailColor = ccWHITE, ccColor4B trailColorScale = cc4BLACK, bool removeWhenDone = false);

	static FKCW_Action_TrailMoveTo* CreateWithFileName(float duration, const CCPoint& position, const string& fileName,
		float trailDistance, int trailSegments, ccColor3B trailColor = ccWHITE, ccColor4B trailColorScale = cc4BLACK, bool removeWhenDone = false);

	static FKCW_Action_TrailMoveTo* CreateWithArmature(float duration, const CCPoint& position, const string& armatureName, int animationIndex,
		float trailDistance, int trailSegments, ccColor3B trailColor = ccWHITE, ccColor4B trailColorScale = cc4BLACK, bool removeWhenDone = false);

	static FKCW_Action_TrailMoveTo* CreateWithArmature(float duration, const CCPoint& position, const string& armatureName, const string& animationName,
		float trailDistance, int trailSegments, ccColor3B trailColor = ccWHITE, ccColor4B trailColorScale = cc4BLACK, bool removeWhenDone = false);


	bool InitWithDurationAndSpriteTrail(float duration, const CCPoint& position, const string& spriteName,
		float trailDistance, int trailSegments, ccColor3B trailColor,
		ccColor4B trailColorScale, bool removeWhenDone);

	bool InitWithDurationAndArmatureTrail(float duration, const CCPoint& position, const string& armatureName,
		const string& animationName, float trailDistance, int trailSegments,
		ccColor3B trailColor, ccColor4B trailColorScale, bool removeWhenDone);

	bool InitWithDurationAndArmatureTrail(float duration, const CCPoint& position, const string& armatureName,
		int animationIndex, float trailDistance, int trailSegments,
		ccColor3B trailColor, ccColor4B trailColorScale, bool removeWhenDone);

	virtual CCObject* copyWithZone(CCZone* pZone);
	virtual void startWithTarget(CCNode* pTarget);
	virtual void update(float time);
};
//--------------------------------------------------------------------