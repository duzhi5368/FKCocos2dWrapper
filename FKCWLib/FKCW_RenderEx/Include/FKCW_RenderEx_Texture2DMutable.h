//*************************************************************************
//	��������:	2014-11-13
//	�ļ�����:	FKCW_RenderEx_Texture2DMutable.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	��ǿ�����������ʵ�ֺ�����Ⱦ��������ȡ��ĳ�����ɫ������ĳЩ�����ɫ��
/*
���ӣ�ʵ�ּ򵥵ĻҶ�ͼ
	FKCW_RenderEx_Texture2DMutable* texture = mRenderLayer->getTexture(); 
	int width = texture->getContentSize().width; 
	int height = texture->getContentSize().height; 

	unsigned int* data = texture->getDataRGBA(); 
	assert(data); 
	// �����ش���
	for(int y = 0; y < height; ++y) 
	{ 
		for(int x = 0; x < width; ++x)
		{ 
			uint32 color =  data[y * texture->getPixelsWide() + x]; 
			uint8 r = COLOR_GETR_RGBA(color); 
			uint8 g = COLOR_GETG_RGBA(color); 
			uint8 b = COLOR_GETB_RGBA(color); 
			uint8 a = COLOR_GETA_RGBA(color); 

			if(a == 0)	// ���͸���򲻴���
			continue; 

			uint8 avg = 0.3 * r + 0.59 * g + 0.11 * b; 
			data[y * texture->getPixelsWide() + x] = COLOR_RGBA(avg, avg, avg, a); 
		} 
	} 
	texture->putDataRGBA();		// �����޸ĺ������
*/
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_RenderEx_Macros.h"
//-------------------------------------------------------------------------
// �Ƿ񱣴�Դ�ļ�
#define FKCW_MUTABLE_TEXTURE_SAVE_ORIGINAL_DATA 0
//-------------------------------------------------------------------------
class FKCW_RenderEx_Texture2DMutable : public CCTexture2D
{
#if FKCW_MUTABLE_TEXTURE_SAVE_ORIGINAL_DATA
	CC_PROPERTY_READONLY(void*, m_pOriginalData, OriginalTexData);
#endif
	CC_PROPERTY(void*, m_pTexData, TexData);
	unsigned int		m_unBytesPerPixel;
	bool				m_bIsDirty;
public:
	FKCW_RenderEx_Texture2DMutable();
	~FKCW_RenderEx_Texture2DMutable(void);
	// ͨ��һ��texture2d���г�ʼ��
	bool	initWithData(const void* data, CCTexture2DPixelFormat pixelFormat, 
		unsigned int pixelsWide, unsigned int pixelsHigh, const CCSize& contentSize);
	bool initWithString(const char *text, const char *fontName, float fontSize);
	bool initWithImage(CCImage *uiImage);
	bool initPremultipliedATextureWithImage(CCImage *image, unsigned int width, unsigned int height);

	// ��Texture���ؼ�����Դ����
	void			updateData();
	// ��FBO�����¼�����Դ����
	void			updateData(unsigned int fbo, unsigned int oldfbo);

	// �����ɱ������ܽӿ�
	void			releaseData(void *data);
	void*			keepData(void *data, unsigned int length);
	void			restore();

	// ��ȡ/��� RGBA8888 ��ɫ����
	// ������pt �Ǵ����Ͻ���Ϊ 0,0 ��
	ccColor4B		pixelAt(const CCPoint& pt);
	unsigned int	pixelAt(int x, int y);
	bool			setPixelAt(int x, int y, unsigned int c);
	bool			setPixelAt(const CCPoint& pt, const ccColor4B& c);

	// ��ȡ�����������ݣ���RGBA8888��ʽ
	unsigned int*	getDataRGBA();
	void			putDataRGBA();
	// ʵ��ʹ��������ӵ������ݽ����������
	void			apply();

	// ��һ���������ָ����ɫ
	void			fillRect(const CCRect& rect, unsigned int c);
	void			fillRect(const CCRect& rect, const ccColor4B& c);
	// �����ɫ����������
	void			fill(const ccColor4B& c);

	CCTexture2D*	copyMutable(bool isMutable);
	FKCW_RenderEx_Texture2DMutable* copy();
	void			copy(FKCW_RenderEx_Texture2DMutable* textureToCopy, const CCPoint& offset);
};