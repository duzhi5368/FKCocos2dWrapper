//*************************************************************************
//	��������:	2014-11-6
//	�ļ�����:	FKCW_RenderEx_CatmullRomSprite.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_RenderEx_Macros.h"
//-------------------------------------------------------------------------
// �ѿ�����ֵŤ������
// �þ�����Խ�һ��node��ͼƬ��������Ť����Ť����ʽ����ͨ��һϵ�еĿ��Ƶ����
// ע����Ϊ����һ�����ߣ�������contextSizeΪ0.���ǣ������ͨ����ȡ����Ƶ��б����������С
// ע�����ʹ��������Ӧ������������һ���������ء�TexturePacker֧�ָ�����(Extrude)ѡ�
class FKCW_RenderEx_CatmullRomSprite : public CCNodeRGBA, public CCBlendProtocol 
{
private:
	bool					m_bIsDirty;					// ���ʾ
	CCTextureAtlas*			m_pAtlas;					// ����
	FKCW_Base_PointList		m_tagControlPoints;			// ���߲ο���
	FKCW_Base_PointList		m_tagPoints;				// ���߶���
	float					m_fTension;					// ��������
	float					m_fPatternLength;			// ͼ����
	float					m_fPatternWidth;			// ͼ����
	vector<int>				m_vecSegmentPointIndices;	// Ƭ�ζ�������
	vector<int>				m_vecSegmentQuadIndices;	// Ƭ��UVֵ����
	map<int,bool>			m_mapSegmentVisibilities;	// Ƭ�ο��ӱ�ʾ�б�
	bool					m_bIsAllVisible;			// ȫƬ�ο�����
	CC_SYNTHESIZE_READONLY(CCSprite*, m_pSprite, PatternSprite);	// �ڲ�������
public:
	// ��������
	void					__UpdateAtlas();
	// ͨ�����Ƶ���Ϣ������ȫ������Ϣ
	void					__PopulatePoints( FKCW_Base_PointList& controlPoints, FKCW_Base_PointList& points);
	// ����һ������
	void					__PopulateQuad(const CCPoint& bl, const CCPoint& br, const CCPoint& tl, const CCPoint& tr,
		float texStartP, float texEndP, float verStartP, float verEndP);
public:
	FKCW_RenderEx_CatmullRomSprite(CCSprite* sprite);
	virtual ~FKCW_RenderEx_CatmullRomSprite();

	static FKCW_RenderEx_CatmullRomSprite* create(const char* fileImage);
	static FKCW_RenderEx_CatmullRomSprite* createWithTexture(CCTexture2D* tex);
	static FKCW_RenderEx_CatmullRomSprite* createWithSpriteFrameName(const char* name);
	static FKCW_RenderEx_CatmullRomSprite* createWithSpriteFrame(CCSpriteFrame* frame);
	static FKCW_RenderEx_CatmullRomSprite* createWithSprite(CCSprite* sprite);

	// ���ظ��ຯ��
	inline void			setBlendFunc(ccBlendFunc blendFunc) { m_pSprite->setBlendFunc(blendFunc); }
	inline ccBlendFunc	getBlendFunc(void) { return m_pSprite->getBlendFunc(); }
	virtual void		setOpacity(GLubyte opacity);
	virtual void		draw();

	// ���һ�����Ƶ�
	// ע���ò��������±�����ᱻ�ػ�
	void				AddControlPoint( const CCPoint& p );
	// ����һ���µĿ��Ƶ����
	// ע���ò��������±�����ᱻ�ػ�
	void				SetControlPoints( CCPointArray& pa );
	// ����ָ��Ƭ���Ƿ�ɼ�
	void				SetSegmentVisible(int sIndex, bool visible);
	// �ж�ָ��Ƭ���Ƿ�ɼ�
	bool				IsSegmentVisible(int sIndex);
	// ����ȫ��Ƭ�οɼ�
	void				ResetSegmentVisibility();
	// ����������������ֵԽ�����߻���Խ��
	void				SetTension(float t);

	// ��ȡ���Ƶ����
	int GetControlPointCount() { return m_tagControlPoints.GetCount(); }
	// ��ȡƬ�θ���
	int GetSegmentCount() { return MAX(0, GetControlPointCount() - 1); }
};