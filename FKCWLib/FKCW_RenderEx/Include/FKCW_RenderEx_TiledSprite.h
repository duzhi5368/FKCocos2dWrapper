//*************************************************************************
//	��������:	2014-11-5
//	�ļ�����:	FKCW_RenderEx_TiledSprite.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_RenderEx_Macros.h"
//-------------------------------------------------------------------------
// һ���ܹ��ڴ�ֱ��ˮƽ�����Ͻ���ƽ������ľ���
// ע�������ʺ��������Ϸ��������Ϊ�����׽��ж�̬��С��������
// ע��ͨ��setContentSize()ָ����Ƭ�����������Զ�ƽ���������������������
// ע����ʹ��atlas�����ʱ��ע��Ӧ�������� 1�����ص����졣TexturePacker֧������ѡ�Extrude��
class FKCW_RenderEx_TiledSprite : public CCSprite
{
private:
	CCSprite*			m_pSprite;			// ��������
	bool				m_bDirty;			// ���ʾ
	CCTextureAtlas*		m_pAtlas;			// ������ͼ��
private:
	// ����������ͼ��
	void				__UpdateAtlas();
public:
	FKCW_RenderEx_TiledSprite(CCSprite* sprite);
	virtual ~FKCW_RenderEx_TiledSprite();

	static FKCW_RenderEx_TiledSprite* create(const char* fileImage);
	static FKCW_RenderEx_TiledSprite* createWithTexture(CCTexture2D* tex);
	static FKCW_RenderEx_TiledSprite* createWithSpriteFrameName(const char* name);
	static FKCW_RenderEx_TiledSprite* createWithSpriteFrame(CCSpriteFrame* frame);
	static FKCW_RenderEx_TiledSprite* createWithSprite(CCSprite* sprite);

	virtual bool initWithTexture(CCTexture2D* pTexture, const CCRect& rect, bool rotated);
	virtual void setOpacity(GLubyte opacity);
	virtual void setDisplayFrame(CCSpriteFrame *pNewFrame);
	virtual void draw();
	virtual void setContentSize(const CCSize& contentSize);

	virtual void setHeight(float h);
	virtual void setWidth(float w);
};