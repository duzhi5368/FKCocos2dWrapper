//*************************************************************************
//	��������:	2015-1-3
//	�ļ�����:	FKCW_Story_CommandSet.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_Story_Macros.h"
//-------------------------------------------------------------------------
// ȫ�ֵĹ�����������
extern CCArray gStoryCommandSet;

// �ṩ���༭��
#if FKCW_STORY_DESIGNER_TOOL
extern vector<string> gUsedSpriteFrameNames;
extern vector<string> gUsedImageNames;
extern vector<string> gUsedArmatureNames;
#endif
//-------------------------------------------------------------------------
// ������ע����ű��ĺ���
//-------------------------------------------------------------------------
/**
 * �趨��Ϸ�Ļ�����С, ������趨, ��������Ϸ�ĵ�ǰ��С�趨. �ھ��鲥����ɺ��
 * �ָ�ԭ���Ĵ�С
 *
 * \note
 * һ������²���Ҫ���ô˷���
 *
 * @param w ���
 * @param h �߶�
 */
extern void winsize(float w, float h);

/**
 * �趨��Ϸ������ģʽ, ������趨, ��������Ϸ�ĵ�ǰ��С�趨.
 *
 * \note
 * ����cocos2d-x���������, �ھ��鲥����ɺ��޷��ָ�ԭ��������ģʽ.
 *
 * \note
 * һ������²���Ҫ���ô˷���
 * 
 * @param p ����ģʽ����
 */
extern void policy(ResolutionPolicy p);

/**
 * ��ʾһ������Ի�, ����Ի���������һ���ı�, ��������һ��һ��������ʾ��.
 * ����Ի�����ɫ, �����С, λ��, ê�㶼��ר�ŵ�������п���. ����Ҫ�ǿ��ǵ�
 * ��Щ����һ�㲻��, ����ͳһ���ƿ��Լ���msg����Ĳ�������
 *
 * @param name ˵���˵�����, ����Ҳ��һ��������ı�, ��ר�ŵ��������������ɫ, �����С, ê���λ��.
 * @param s �Ի�������
 * @param wait �Ի�ȫ����ʾ��Ϻ�ȴ���ʱ��, С��0��ʾ�ȴ��û��������ʧ
 */
extern void msg(string name, string s, float wait = 1);

/**
 * ���þ���Ի�����Ĵ�С, ���ھ���ű���˳��ִ�е�, ����������Ӱ������֮ǰ�ĶԻ�����
 * 
 * @param size �����С
 */
extern void msgsize(float size);

/**
 * ���þ���Ի�����ɫ, ���ھ���ű���˳��ִ�е�, ����������Ӱ������֮ǰ�ĶԻ���ɫ
 * 
 * @param c ��ʽΪargb8888
 */
extern void msgcolor(unsigned int c);

/**
 * ����Ի�������, ���ھ���ű���˳��ִ�е�, ����������Ӱ������֮ǰ�ĶԻ�����
 * 
 * @param x x����
 * @param y y����
 */
extern void msgpos(float x, float y);

/**
 * ����Ի��ڵ��ê��, ȱʡ�����������. ���ھ���ű���˳��ִ�е�, ����������Ӱ������֮ǰ�ĶԻ�ê��.
 * ê��ʹ�����ֵ��ʾ��, ��0��ʾ��߻��±�, 1��ʾ�ұ߻��ϱ�.
 * 
 * @param x xê��
 * @param y yê��
 */
extern void msganchor(float x, float y);

/**
 * ���þ���Ի��ڵ������п�, ȱʡ�ǲ�����(Ҳ���ǵ���, ����ǿ�ƻ���), ���ھ���ű���˳��ִ��
 * ��, ����������Ӱ������֮ǰ�ĶԻ��п�.
 *
 * @param w �п�
 */
extern void msgwidth(float w);

/**
 * ���þ���Ի��ڵ���ı�ˮƽ���뷽ʽ, ȱʡ�Ǿ���, ���ھ���ű���˳��ִ��
 * ��, ����������Ӱ������֮ǰ�ĶԻ�����.
 *
 * @param a ����Ϊleft, center, right
 */
extern void msgalign(CCTextAlignment a);

/**
 * ���þ���Ի��ڵ������, ���ھ���ű���˳��ִ��
 * ��, ����������Ӱ������֮ǰ�ĶԻ�����
 *
 * @param fontName ��������
 */
extern void msgfont(string fontName);

/**
 * ���Ƶ�����, ���ھ���ű���˳��ִ�е�, ����������Ӱ������֮ǰ����������
 *
 * @param x x����
 * @param y y����
 */
extern void namepos(float x, float y);

/**
 * �������Ƶ���ɫ, ���ھ���ű���˳��ִ�е�, ����������Ӱ������֮ǰ��������ɫ
 *
 * @param c ��ʽΪargb8888
 */
extern void namecolor(unsigned int c);

/**
 * ������������Ĵ�С, ���ھ���ű���˳��ִ�е�, ����������Ӱ������֮ǰ����������
 *
 * @param size �����С
 */
extern void namesize(float size);

/**
 * ���ƽڵ��ê��, ȱʡ�����������. ���ھ���ű���˳��ִ�е�, ����������Ӱ������֮ǰ������ê��.
 * ê��ʹ�����ֵ��ʾ��, ��0��ʾ��߻��±�, 1��ʾ�ұ߻��ϱ�.
 *
 * @param x xê��
 * @param y yê��
 */
extern void nameanchor(float x, float y);

/**
 * �������ƽڵ������, ���ھ���ű���˳��ִ��
 * ��, ����������Ӱ������֮ǰ����������
 *
 * @param fontName ��������
 */
extern void namefont(string fontName);

/**
 * ���ñ�ǩ����ɫ, ���ھ���ű���˳��ִ�е�, ����������Ӱ������֮ǰ�ı�ǩ��ɫ.
 * ���˾���Ի�������֮����ı�, ͳһ��һЩ����������ǵ���ɫ, �����С�����.
 *
 * @param c ��ʽΪargb8888
 */
extern void labelcolor(unsigned int c);

/**
 * ���ñ�ǩ����Ĵ�С, ���ھ���ű���˳��ִ�е�, ����������Ӱ������֮ǰ�ı�ǩ����.
 * ��ǩ��ָ���˾���Ի�������֮��������ı�
 *
 * @param size �����С
 */
extern void labelsize(float size);

/**
 * ���ñ�ǩ�ڵ������, ���ھ���ű���˳��ִ��
 * ��, ����������Ӱ������֮ǰ�ı�ǩ����
 *
 * @param fontName ��������
 */
extern void labelfont(string fontName);

/**
 * ��ǩ�ڵ��ê��, ȱʡ�����������. ���ھ���ű���˳��ִ�е�, ����������Ӱ������֮ǰ�ı�ǩê��.
 * ê��ʹ�����ֵ��ʾ��, ��0��ʾ��߻��±�, 1��ʾ�ұ߻��ϱ�. ��ǩ��ָ���˾���Ի�������֮��������ı�
 *
 * @param x xê��
 * @param y yê��
 */
extern void labelanchor(float x, float y);

/**
 * ���ñ�ǩ�ڵ������п�, ȱʡ�ǲ�����(Ҳ���ǵ���, ����ǿ�ƻ���), ���ھ���ű���˳��ִ��
 * ��, ����������Ӱ������֮ǰ�ı�ǩ�п�.
 *
 * @param w �п�
 */
extern void labelwidth(float w);

/**
 * ���ñ�ǩ�ڵ���ı�ˮƽ���뷽ʽ, ȱʡ�Ǿ���, ���ھ���ű���˳��ִ��
 * ��, ����������Ӱ������֮ǰ�ı�ǩ����.
 *
 * @param a ����Ϊleft, center, right
 */
extern void labelalign(CCTextAlignment a);

/**
 * ��ĳ����ɫִ��һ���ƶ�����
 * 
 * @param name ��ɫ������
 * @param x Ҫ�ƶ�����xλ��
 * @param y Ҫ�ƶ�����yλ��
 * @param time �ƶ���ɵ�ʱ��
 */
extern void move(string name, float x, float y, float time);

/**
 * �ȴ��������ټ���ִ�о���
 * 
 * @param time �ȴ�ʱ��
 */
extern void wait(float time);

/**
 * �ȴ�ĳ������������һ��, ����������һ�����������armplay, �������ʾ����.
 */
extern void waitarm();

/**
 * �ȴ��û��������λ��, �ټ���ִ�о���
 */
extern void waitclick();

/**
 * ��ĳ����ɫִ�е���Ч��
 *
 * @param name ��ɫ����
 * @param time �������ʱ��
 */
extern void fadein(string name, float time);

/**
 * ��ĳ����ɫִ�е���Ч��
 *
 * @param name ��ɫ����
 * @param time �������ʱ��
 */
extern void fadeout(string name, float time);

/**
 * ��ĳ����ɫִ������Ч��
 *
 * @param name ��ɫ����
 * @param color ������ɫ
 * @param times �������
 * @param time ����ʱ��
 */
extern void flash(string name, unsigned int color, float times, float time);

/**
 * ��ĳ����ɫִ����˸Ч��
 *
 * @param name ��ɫ����
 * @param times ��˸����
 * @param time ��˸ʱ��
 */
extern void blink(string name, float times, float time);

/**
 * ��ĳ����ɫִ�ж���Ч��
 * 
 * @param name ��ɫ����
 * @param apmlitude �����ķ���
 * @param time ����ʱ��
 */
extern void shake(string name, float amplitude, float time);

/**
 * ��ĳ����ɫִ�����Ŷ���
 *
 * @param name ��ɫ����
 * @param to ���ŵ����ٱ�, 1��ʾԭ��С, 2��ʾ2��
 * @param time ����ʱ��
 */
extern void scaleto(string name, float to, float time);

/**
 * ����һ��ͼƬ��ɫ, �������ɫ(Sprite), �ý�ɫ��ͼƬ����������ĳ�Ŵ�ͼ(һ����TexturePacker����), 
 * Ҳ��������ĳ��ͼƬ�ļ�. �����ȳ���ʹ�ô�ͼ, ����Ҳ���֡, ��᳢����Ѱ�ļ�
 *
 * \note
 * �����ɫ��������һ��CCSprite��, ��ɫ������һ������, �����������ͨ���������������ɫ.
 *
 * @param name ��ɫ����
 * @param frameName ��ɫͼƬ��֡��, ���֡������, ��᳢����Ѱ�ļ�
 * @param x ��ɫ�ĳ�ʼxλ��
 * @param y ��ɫ�ĳ�ʼyλ��
 */
extern void img(string name, string frameName, float x, float y);

/**
 * ����һ����ǩ��ɫ, �������Ǵ�����һ��CCRichLabelTTF����. ��ǩ����ɫ, �����С, ê�㶼��ר������
 * ��ͳһ����, ����Ϊ�˼���ÿ�δ�����ǩʱ��Ҫ�ṩ�Ĳ���. 
 * 
 * @param name ��ɫ����
 * @param text ��ǩ����, ������CCRichLabelTTF֧�ֵĸ��ı���ʽ
 * @param x ��ʼxλ��
 * @param y ��ʼyλ��
 */
extern void label(string name, string text, float x, float y);

/**
 * ����һ��������ɫ, �������Ǵ�����һ��CBArmature����. �����Ķ�����ɫȱʡ�������κζ���,
 * һ��Ҫ��һ��armplay���������Ŷ���.
 *
 * @param name ��ɫ����
 * @param armName ���������ļ�����(��ExportJson��չ��)
 * @param x ��ʼxλ��
 * @param y ��ʼyλ��
 */
extern void arm(string name, string armName, float x, float y);

/**
 * ��ĳ��������ɫ���Ŷ���
 *
 * @param name ��ɫ����
 * @param animName ��������
 */
extern void armplay(string name, string animName);

/**
 * �ı�ĳ����ɫ����ת�Ƕ�
 *
 * @param name ��ɫ����
 * @param degree �Ƕ�, ��ֵ��ʾ˳ʱ��, ��ֵ��ʾ��ʱ��
 */
extern void angle(string name, float degree);

/**
 * ��ĳ����ɫִ����ת����
 *
 * @param name ��ɫ����
 * @param delta Ҫ��ת�ĽǶ�
 * @param time ����ʱ��
 */
extern void rotateby(string name, float delta, float time);

/**
 * ���ñ���������, ������һ�������ͼƬ��ɫ, ����û������, ��ʾ��������. ������ê�����м�, Ŀǰ���ܸ���.
 * ��������ô�����, ������λ�þ�������Ļ�м�.
 * 
 * @param x ����λ��
 * @param y ����λ��
 */
extern void bgpos(float x, float y);

/**
 * ָ������ͼƬ, ͼƬ��������ĳ����ͼ(ͨ����TexturePacker����)
 * 
 * @param frameName ͼƬ֡��
 */
extern void bg(string frameName);

/**
 * ָ��������ɫ, ������ɫ�����ȼ����ڱ���ͼƬ, ���ͬʱ�����˱���ͼƬ�ͱ�����ɫ, �ұ�����ɫ��͸����,
 * �򱳾�ͼƬ�����ɼ�.
 *
 * @param c argb8888��ʽ
 */
extern void bgcolor(unsigned int c);

/**
 * �趨ĳ����ɫ����Ⱦ˳��, ���߽�z orderֵ, ֵ���߽���ʾ��ֵС�ߵ�����
 *
 * @param name ��ɫ����
 * @param zOrder ��Ⱦ˳��
 */
extern void z(string name, int zOrder);

/**
 * ���ű�������, �����ǰ�б�������, ��ֹͣ��ǰ�ı�������
 *
 * \note
 * �ļ�·���ᱻ����ӳ�䵽�ⲿ�洢��, ����������ٶ�λ���ڲ�, ��������֧�����ظ��µ����.
 *
 * @param musicFile ���������ļ�·��
 */
extern void bgm(string musicFile);

/**
 * ������Ч
 *
 * \note
 * �ļ�·���ᱻ����ӳ�䵽�ⲿ�洢��, ����������ٶ�λ���ڲ�, ��������֧�����ظ��µ����.
 *
 * @param soundFile ��Ч�ļ�·��
 */
extern void sound(string soundFile);

/**
 * ɾ��һ����ɫ
 *
 * @param name ��ɫ����
 */
extern void remove(string name);

/**
 * ��ʾĳ����ɫ
 *
 * @param name ��ɫ����
 */
extern void show(string name);

/**
 * ����ĳ����ɫ
 *
 * @param name ��ɫ����
 */
extern void hide(string name);

/**
 * ˮƽ��תĳ����ɫ
 *
 * @param name ��ɫ����
 */
extern void flipx(string name);

/**
 * ��ֱ��תĳ����ɫ
 *
 * @param name ��ɫ����
 */
extern void flipy(string name);

/**
 * ���ý�ɫ��λ��
 *
 * @param name ��ɫ����
 * @param x xλ��
 * @param y yλ��
 */
extern void pos(string name, float x, float y);

/**
 * ���ý�ɫ��λ��, ��λ����ĳ���ڵ�Ϊ�ο��õ�(��Ϊ�ο���ɫ), ����ο���ɫ��(1, 1), ����ʾ
 * ����ɫ��λ�����óɲο���ɫ�����Ͻ�λ��.
 *
 * @param name ��ɫ����
 * @param refName �ο���ɫ����
 * @param relativeX �ο���ɫ�����xλ��
 * @param relativeY �ο���ɫ�����yλ��
 */
extern void npos(string name, string refName, float relativeX, float relativeY);

/**
 * ���ý�ɫ��λ��, ��λ������ĻΪ�ο��õ�(ʵ�����ǿɼ�����), ����(1, 1)��ʾ��Ļ�����Ͻ�
 *
 * @param name ��ɫ����
 * @param relativeX ��Ļ�����xλ��
 * @param relativeY ��Ļ�����yλ��
 */
extern void spos(string name, float relativeX, float relativeY);

/**
 * ���ý�ɫ��ê��
 *
 * @param name ��ɫ����
 * @param x xê��
 * @param y yê��
 */
extern void anchor(string name, float x, float y);

/**
 * ���ý�ɫ����ɫ
 * 
 * @param name ��ɫ����
 * @param c argb8888��ʽ
 */
extern void color(string name, unsigned int c);

/**
 * ���ý�ɫ������
 * 
 * @param name ��ɫ����
 * @param x x��������
 * @param y y��������
 */
extern void scale(string name, float x, float y);

/**
 * �������ƻ��һ������, �������������ַ���.
 *
 * @param key ������ֵ
 * @return ����ֵ. ��������������򷵻ؿ��ַ���
 */
extern string p(string key);
//-------------------------------------------------------------------------
class FKCW_Story_Command : public CCObject 
{
public:
	// �������
    enum Type
	{
        UNKNOWN			= 0,
        WIN_SIZE,
        POLICY,
        MSG,
        MSG_SIZE,
        MSG_COLOR,
        MSG_POS,
        MSG_ANCHOR,
        MSG_WIDTH,
        MSG_ALIGN,
        MSG_FONT,
        NAME_POS,
        NAME_COLOR,
        NAME_SIZE,
        NAME_ANCHOR,
        NAME_FONT,
        LABEL_COLOR,
        LABEL_SIZE,
        LABEL_FONT,
        LABEL_ANCHOR,
        LABEL_WIDTH,
        LABEL_ALIGN,
        MOVE,
        WAIT,
        WAIT_ARM,
        WAIT_CLICK,
        FADE_IN,
        FADE_OUT,
        FLASH,
        BLINK,
        SHAKE,
        SCALE_TO,
        IMG,
        LABEL,
        ARM,
        ARM_PLAY,
        ANGLE,
        ROTATE_BY,
        BG_POS,
        BG,
        BG_COLOR,
        Z,
        BGM,
        SOUND,
        REMOVE,
        SHOW,
        HIDE,
        FLIP_X,
        FLIP_Y,
        POS,
        NODE_POS,
        SCREEN_POS,
        ANCHOR,
        COLOR,
        SCALE,

		eType_MAX,
    };
public:
	const static int s_nKeyLen = eType_MAX;
public:
    // �������
    union {
        struct {
            float w;
            float h;
        } winsize;
        
        struct {
            ResolutionPolicy p;
        } policy;
        
        struct {
            const char* name;
            const char* s;
            float wait;
        } msg;
        
        struct {
            float size;
        } msgsize;
        
        struct {
            unsigned int c;
        } msgcolor;
        
        struct {
            float x;
            float y;
        } msgpos;
        
        struct {
            float x;
            float y;
        } msganchor;
        
        struct {
            float w;
        } msgwidth;
        
        struct {
            CCTextAlignment a;
        } msgalign;
        
        struct {
            const char* fontName;
        } msgfont;
        
        struct {
            float size;
        } namesize;
        
        struct {
            unsigned int c;
        } namecolor;
        
        struct {
            float x;
            float y;
        } namepos;
        
        struct {
            float x;
            float y;
        } nameanchor;
        
        struct {
            const char* fontName;
        } namefont;
        
        struct {
            unsigned int c;
        } labelcolor;
        
        struct {
            float size;
        } labelsize;
        
        struct {
            const char* fontName;
        } labelfont;
        
        struct {
            float x;
            float y;
        } labelanchor;
        
        struct {
            float w;
        } labelwidth;
        
        struct {
            CCTextAlignment a;
        } labelalign;
        
        struct {
            const char* name;
            float x;
            float y;
            float time;
        } move;
        
        struct {
            float time;
        } wait;
        
        struct {
            const char* name;
            unsigned int c;
            float times;
            float time;
        } flash;
        
        struct {
            const char* name;
            float times;
            float time;
        } blink;
        
        struct {
            const char* name;
            float amplitude;
            float time;
        } shake;
        
        struct {
            const char* name;
            float delta;
            float time;
        } rotateby;
        
        struct {
            const char* name;
            float to;
            float time;
        } scaleto;
        
        struct {
            const char* name;
            float time;
        } fadein;
        
        struct {
            const char* name;
            float time;
        } fadeout;
        
        struct {
            float x;
            float y;
            const char* name;
            const char* frameName;
        } img;
        
        struct {
            float x;
            float y;
            const char* name;
            const char* text;
        } label;
        
        struct {
            float x;
            float y;
            const char* name;
            const char* armName;
        } arm;
        
        struct {
            const char* name;
            const char* animName;
        } armplay;
        
        struct {
            const char* name;
            float degree;
        } angle;
        
        struct {
            float x;
            float y;
        } bgpos;
        
        struct {
            const char* frameName;
        } bg;
        
        struct {
            unsigned int c;
        } bgcolor;
        
        struct {
            const char* musicFile;
        } bgm;
        
        struct {
            const char* soundFile;
        } sound;
        
        struct {
            const char* name;
            int z;
        } z;
        
        struct {
            const char* name;
        } remove;
        
        struct {
            const char* name;
        } show;
        
        struct {
            const char* name;
        } hide;
        
        struct {
            const char* name;
        } flipx;
        
        struct {
            const char* name;
        } flipy;
        
        struct {
            float x;
            float y;
            const char* name;
        } pos;
        
        struct {
            float x;
            float y;
            const char* name;
            const char* refName;
        } npos;
        
        struct {
            float x;
            float y;
            const char* name;
        } spos;
        
        struct {
            float x;
            float y;
            const char* name;
        } anchor;
        
        struct {
            unsigned int c;
            const char* name;
        } color;
        
        struct {
            const char* name;
            float x;
            float y;
        } scale;
    } m_param;
    
public:
    FKCW_Story_Command();
    virtual ~FKCW_Story_Command();
    static FKCW_Story_Command* create(Type type);
    
    virtual bool initWithCommand(Type type);
    
    CC_SYNTHESIZE(Type, m_type, Type);
};
//-------------------------------------------------------------------------
const string s_CommandKey[FKCW_Story_Command::s_nKeyLen-1] = { 
	"���ڴ�С",
	"����ģʽ",
	"��ʾ�Ի�",
	"�Ի������С",
	"�Ի�������ɫ",
	"�Ի���������",
	"�Ի��ڵ�ê��",
	"�Ի������п�",
	"�Ի����ֶ��뷽ʽ",
	"�Ի�������",
	"������������",
	"����������ɫ",
	"���������С",
	"���ƽڵ�ê��",
	"����������",
	"��ǩ������ɫ",
	"��ǩ�����С",
	"��ǩ������",
	"��ǩ�ڵ�ê��",
	"��ǩ�����п�",
	"��ǩ���ֶ��뷽ʽ",
	"��ɫ�ƶ�",
	"�ȴ�����",
	"�ȴ������������",
	"�ȴ��û����",
	"�����붯��",
	"���󵭳�����",
	"�������⶯��",
	"������˸����",
	"���󶶶�����",
	"�������Ŷ���",
	"����ͼƬ����",
	"������ǩ����",
	"������������",
	"���Ŷ���",
	"��ת����",
	"������ת����",
	"���ñ���λ��",
	"���ñ���",
	"���ñ�����ɫ",
	"���Ķ���Zֵ",
	"���ű�������",
	"������Ч",
	"ɾ��һ������",
	"��ʾһ������",
	"����һ������",
	"ˮƽ��ת����",
	"��ֱ��ת����",
	"���ö������λ��",
	"���ö���ο�λ��",
	"���ö������λ��",
	"���ö���ê��",
	"���ö�����ɫ",
	"���ö�������"
};
//-------------------------------------------------------------------------