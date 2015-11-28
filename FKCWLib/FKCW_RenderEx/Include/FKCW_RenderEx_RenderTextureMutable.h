//*************************************************************************
//	��������:	2014-11-13
//	�ļ�����:	FKCW_RenderEx_RenderTextureMutable.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_RenderEx_Macros.h"
#include "FKCW_RenderEx_Texture2DMutable.h"
//-------------------------------------------------------------------------
class FKCW_RenderEX_RenderTextureMutable : public CCNode 
{
	CC_PROPERTY(CCSprite*, m_pSprite, Sprite)
public:
	FKCW_RenderEX_RenderTextureMutable();
	virtual ~FKCW_RenderEX_RenderTextureMutable();

	// ����һ����Ⱦ�������
	// ע����֧��RGB��RGBA
    static FKCW_RenderEX_RenderTextureMutable* Create(int w, int h, CCTexture2DPixelFormat eFormat);
	// ����һ��RGBA8888����Ⱦ�������
    static FKCW_RenderEX_RenderTextureMutable* Create(int w, int h);
    bool initWithWidthAndHeight(int w, int h, CCTexture2DPixelFormat eFormat);

    // ��ʼץȡ
	void begin();
	// ��ʼ��Ⱦ��������֮ǰ�����������һ������
	// ע����������Ч�ķ�ʽ���ȵ���clear�ڵ���beginץȡ��
    void beginWithClear(float r, float g, float b, float a);
	// ץȡ����
	// para bIsTOCacheTexture       the parameter is only used for android to cache the texture
	void end(bool bIsTOCacheTexture = true);
    // �õ�ɫ�������
    void clear(float r, float g, float b, float a);

	// ���浱ǰ����һ���ļ���
	// ������szFilePath ���浽���ļ�·�� x,y �������������½����꣬nWidth��nHeight ���
	bool saveBuffer(const char *szFilePath, int x = 0, int y = 0, int nWidth = 0, int nHeight = 0);
	// ������format �����ͼƬ��ʽ��֧��kCCImageFormatPNG ��kCCImageFormatJPG
	bool saveBuffer(int format, const char *name, int x = 0, int y = 0, int nWidth = 0, int nHeight = 0);

	FKCW_RenderEx_Texture2DMutable* getTexture() const;

	// �������������ݱ��浽CCImage��
	// ע��ֻ�ܱ���һ��RGBA8888��ʽ��Image
	bool getUIImageFromBuffer(CCImage *pImage, int x = 0, int y = 0, int nWidth = 0, int nHeight = 0);

protected:
	GLuint							m_uFBO;
	GLint							m_nOldFBO;
	FKCW_RenderEx_Texture2DMutable*	m_pTexture;
	CCImage*						m_pUITextureImage;
    GLenum							m_ePixelFormat;
};