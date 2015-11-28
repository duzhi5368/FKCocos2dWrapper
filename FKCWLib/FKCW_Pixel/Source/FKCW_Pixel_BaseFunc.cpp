//-------------------------------------------------------------------------
#include "../Include/FKCW_Pixel_BaseFunc.h"
//-------------------------------------------------------------------------
CCTexture2D* ScaleTexUsingRTT(CCTexture2D*texture,float scaleX,float scaleY)
{
	CCTexture2D*newTex=NULL;
	CCSprite*tSprite=CCSprite::createWithTexture(texture);
	// ��Ⱦ��������
	int w = static_cast<int>(tSprite->getContentSize().width*scaleX);
	int h = static_cast<int>(tSprite->getContentSize().height*scaleY);
	CCRenderTexture*renderTex=CCRenderTexture::create(
		w, 
		h);
	renderTex->begin();
	tSprite->setAnchorPoint(ccp(0,1));
	tSprite->setScaleY(-scaleY);
	tSprite->setScaleX(scaleX);
	tSprite->visit();
	renderTex->end();
	newTex = renderTex->getSprite()->getTexture();
	return newTex;
}
//-------------------------------------------------------------------------
// ��ȡһ������ͼƬ����ɫ����
vector<vector<ccColor4B> >	GetColorMatFromImage(CCImage *image)
{
	bool hasAlpha = image->hasAlpha();
	unsigned int width = image->getWidth();
	unsigned int height = image->getHeight();
	// ��ɫ����
	vector<vector<ccColor4B> > colorMat;
	colorMat.resize(height);
	for(unsigned int i=0;i<height;i++)
	{
		colorMat[i].resize(width);
	}
	// �����ɫ����
	if(hasAlpha)
	{
		unsigned int* inPixel32 = (unsigned int*)image->getData();

		for(unsigned int i=0;i<height;i++)
		{
			for(unsigned int j=0;j<width;j++)
			{
				colorMat[i][j].r=(int)((*inPixel32 >> 0) & 0xFF);
				colorMat[i][j].g=(int)((*inPixel32 >> 8) & 0xFF);
				colorMat[i][j].b=(int)((*inPixel32 >> 16) & 0xFF);
				colorMat[i][j].a=(int)((*inPixel32 >> 24) & 0xFF);
				inPixel32++;
			}
		}
	}
	else
	{
		// CCImageҪ�������ݱ�����RGBA8888�����������Alpha��˵���Ķ��д��ˡ�
		assert(false);
	}

	return colorMat;
}
//-------------------------------------------------------------------------