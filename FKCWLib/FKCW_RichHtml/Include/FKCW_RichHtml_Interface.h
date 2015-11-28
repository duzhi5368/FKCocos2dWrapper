//*************************************************************************
//	��������:	2015-1-3
//	�ļ�����:	FKCW_RichHtml_Interface.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_RichHtml_Macros.h"
#include "FKCW_RichHtml_BaseStruct.h"
#include "FKCW_RichHtml_HelpFunc.h"
//-------------------------------------------------------------------------
// RichHtmlԪ���б�
typedef std::vector<class FKCW_RichHtml_IRichElement*> element_list_t;
//-------------------------------------------------------------------------
// RichHtmlԪ��
class FKCW_RichHtml_IRichElement
{
public:
	virtual ~FKCW_RichHtml_IRichElement() {}

	//-----------------------
	// ����ӿ�
	// Parser�������ӿ�
	virtual bool parse(class FKCW_RichHtml_IRichParser* parser, const char** attr = NULL) = 0;
	// ������ӿ�
	virtual bool composit(class FKCW_RichHtml_IRichCompositor* compositor) = 0;
	// ��Ⱦ���ӿ�
	virtual void render(FKCW_RichHtml_Canvas canvas) = 0;
	//-----------------------
	// ��ջ����ӿ�
	virtual bool pushMetricsState() = 0;
	virtual bool pushRenderState() = 0;
	//-----------------------
	// λ�þ���ӿ�
	virtual FKCW_RichHtml_Pos getLocalPosition() const = 0;			// ��������
	virtual void setLocalPosition(FKCW_RichHtml_Pos pos) = 0;
	virtual void setLocalPositionX(short x) = 0;
	virtual void setLocalPositionY(short y) = 0;
	virtual FKCW_RichHtml_Pos getGlobalPosition() = 0;				// ȫ������
	virtual FKCW_RichHtml_Metrics* getMetrics() = 0;					// Ԫ�ؾ���
	virtual bool scaleToElementSize() = 0;				// �����������ţ���������ΪԪ�ش�С
	//-----------------------
	// ��Ⱦ���Խӿ�
	virtual FKCW_RichHtml_Texture* getTexture() = 0;
	virtual bool isBatchedDrawable() = 0;
	virtual unsigned int getColor() = 0;
	virtual const char* getFontAlias() = 0;
	//-----------------------
	// ��������Խӿ�
	virtual bool isCachedComposit() = 0;				// ��ӵ������У��ȴ�Flush
	virtual bool canLinewrap() = 0;
	virtual bool isNewlineBefore() = 0;
	virtual bool isNewlineFollow() = 0;
	virtual short getBaseline() = 0;					// �ױ���Yֵ����
	virtual bool needBaselineCorrect() = 0;
	virtual void onCachedCompositBegin(class FKCW_RichHtml_ICompositCache* cache, FKCW_RichHtml_Pos& pen) = 0;
	virtual void onCachedCompositEnd(class FKCW_RichHtml_ICompositCache* cache, FKCW_RichHtml_Pos& pen) = 0;
	//-----------------------
	// ���ӹ�ϵ�ӿ�
	virtual void addChildren(FKCW_RichHtml_IRichElement* child) = 0;
	virtual element_list_t* getChildren() = 0;
	virtual void removeAllChildren() = 0;
	virtual void setParent(FKCW_RichHtml_IRichElement* parent) = 0;
	virtual FKCW_RichHtml_IRichElement* getParent() = 0;
	virtual int	getID() = 0;
	virtual FKCW_RichHtml_IRichElement* findChildByID(int _id) = 0;
};
//-------------------------------------------------------------------------
// RichHtml ������
// �������ı���ע�⣺�ı������ļ�������UFT8��ʽ
class FKCW_RichHtml_IRichParser
{
public:
	virtual ~FKCW_RichHtml_IRichParser() {}

	// ����UTF8��ʽ�ַ���
	virtual element_list_t* parseString(const char* utf8_str) = 0;
	// ����һ��UTF8�ļ�
	virtual element_list_t* parseFile(const char* filename) = 0;
	// ��ȡRichNode����
	virtual class FKCW_RichHtml_IRichNode* getContainer() = 0;

	// �ж��Ƿ��ǽ��ͱ�ע�����ǣ����������
	virtual bool isPlainMode() = 0;
	virtual void setPlainMode(bool on) = 0;
};
//-------------------------------------------------------------------------
// �����
// ��RichHtmlԪ�ؽ������
class FKCW_RichHtml_IRichCompositor
{
public:
	virtual ~FKCW_RichHtml_IRichCompositor() {}

	virtual bool composit(FKCW_RichHtml_IRichElement* root) = 0;

	// ��ȡ��Χ����
	virtual const FKCW_RichHtml_Rect& getRect() const = 0;
	// ����ȫ��״̬�ͱ����������
	virtual void reset() = 0;

	// ��ȡ��ǰ�����״̬
	virtual FKCW_RichHtml_MetricsState* getMetricsState() = 0;
	virtual FKCW_RichHtml_MetricsState* pushMetricsState() = 0;
	virtual void popMetricsState() = 0;
	// ���ó�ʼ״̬
	virtual FKCW_RichHtml_MetricsState* initMetricsState(const FKCW_RichHtml_MetricsState* new_init_state = NULL) = 0;

	virtual FKCW_RichHtml_RenderState* getRenderState() = 0;
	virtual FKCW_RichHtml_RenderState* pushRenderState() = 0;
	virtual void popRenderState() = 0;
	virtual FKCW_RichHtml_RenderState* initRenderState(const FKCW_RichHtml_RenderState* new_init_state = NULL) = 0;

	// ��ȡ��ǰ����
	virtual class FKCW_Font_Catalog* getFont() = 0;
	// ��ȡRichNode����
	virtual class FKCW_RichHtml_IRichNode* getContainer() = 0;
	// ��ȡ������
	virtual class FKCW_RichHtml_ICompositCache* getRootCache() = 0;
};
//-------------------------------------------------------------------------
// ����Ԫ��
// �������������Ԫ��
class FKCW_RichHtml_ICompositCache
{
public:
	virtual ~FKCW_RichHtml_ICompositCache() {}

	virtual void appendElement(FKCW_RichHtml_IRichElement* ele) = 0;
	virtual FKCW_RichHtml_Rect flush(class FKCW_RichHtml_IRichCompositor* compositor) = 0;
	virtual void clear() = 0;

	virtual ENUM_Alignment getHAlign() = 0;
	virtual ENUM_Alignment getVAlign() = 0;
	virtual void setHAlign(ENUM_Alignment align) = 0;
	virtual void setVAlign(ENUM_Alignment align) = 0;
	virtual void setWrapline(bool wrap) = 0;
	virtual bool isWrapline() = 0;
	virtual short getSpacing() = 0;
	virtual short getPadding() = 0;
	virtual void setSpacing(short v) = 0;
	virtual void setPadding(short v) = 0;
};
//-------------------------------------------------------------------------
// BatchԪ�ؼ���Ⱦ
class FKCW_RichHtml_IRichAtlas
{
public:
	virtual ~FKCW_RichHtml_IRichAtlas() {}
	virtual void appendRichElement(FKCW_RichHtml_IRichElement* element) = 0;
	virtual void resetRichElements() = 0;
	virtual void updateRichRenderData() = 0;
};
//-------------------------------------------------------------------------
// Rich Node����
class FKCW_RichHtml_IRichNode
{
public:
	virtual ~FKCW_RichHtml_IRichNode() {}
	virtual FKCW_RichHtml_IRichParser* getParser() = 0;
	virtual FKCW_RichHtml_IRichCompositor* getCompositor() = 0;
	virtual FKCW_RichHtml_Size getActualSize() = 0;

	virtual FKCW_RichHtml_Size getPreferredSize() = 0;
	virtual void setPreferredSize(FKCW_RichHtml_Size size) = 0;

	virtual void setStringUTF8(const char* utf8_str) = 0;
	virtual void appendStringUTF8(const char* utf8_str) = 0;
	virtual const char* getStringUTF8() = 0;

	virtual void addOverlay(FKCW_RichHtml_IRichElement* overlay) = 0;
	virtual void addCCNode(class CCNode* node) = 0;
	virtual void removeCCNode(class CCNode* node) = 0;

	virtual FKCW_RichHtml_IRichAtlas* findAtlas(class CCTexture2D* texture, unsigned int color_rgba, int zorder = ZORDER_CONTEXT) = 0;
};
//-------------------------------------------------------------------------
// ������Ϣ�ص�
class FKCW_RichHtml_IRichEventHandler
{
public:
	virtual void onClick(FKCW_RichHtml_IRichNode* root, FKCW_RichHtml_IRichElement* ele, int _id) = 0;
	virtual void onMoved(FKCW_RichHtml_IRichNode* root, FKCW_RichHtml_IRichElement* ele, int _id, const CCPoint& location, const CCPoint& delta) = 0;
};
//-------------------------------------------------------------------------
template<typename T>
class FKCW_RichHtml_EvHandler : public FKCW_RichHtml_IRichEventHandler
{
public:
	typedef void (T::*mfunc_click_t)(FKCW_RichHtml_IRichNode* root, FKCW_RichHtml_IRichElement* ele, int _id);
	typedef void (T::*mfunc_moved_t)(FKCW_RichHtml_IRichNode* root, FKCW_RichHtml_IRichElement* ele, int _id, const CCPoint& location, const CCPoint& delta);

	FKCW_RichHtml_EvHandler(T* _t, mfunc_click_t _cf, mfunc_moved_t _mf) 
		: m_target(_t), m_clickfunc(_cf), m_movedfunc(_mf)
	{
	}
	FKCW_RichHtml_EvHandler(T* _t, mfunc_click_t _cf) 
		: m_target(_t), m_clickfunc(_cf), m_movedfunc(NULL)
	{
	}
	FKCW_RichHtml_EvHandler(T* _t, mfunc_moved_t _mf) 
		: m_target(_t), m_clickfunc(NULL), m_movedfunc(_mf)
	{
	}

	virtual void onClick(FKCW_RichHtml_IRichNode* root, FKCW_RichHtml_IRichElement* ele, int _id)
	{
		if ( m_target && m_clickfunc )
		{
			(m_target->*m_clickfunc)(root, ele, _id);
		}
	}

	virtual void onMoved(FKCW_RichHtml_IRichNode* root, FKCW_RichHtml_IRichElement* ele, int _id, const CCPoint& location, const CCPoint& delta)
	{
		if ( m_target && m_movedfunc )
		{
			(m_target->*m_movedfunc)(root, ele, _id, location, delta);
		}
	}

protected:
	T* m_target;
	mfunc_click_t m_clickfunc;
	mfunc_moved_t m_movedfunc;
};
//-------------------------------------------------------------------------