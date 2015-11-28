//*************************************************************************
//	��������:	2015-1-3
//	�ļ�����:	FKCW_RichHtml_RichHtmlElement.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_RichHtml_Macros.h"
#include "FKCW_RichHtml_BaseStruct.h"
#include "FKCW_RichHtml_HelpFunc.h"
#include "FKCW_RichHtml_Interface.h"
#include "FKCW_RichHtml_RichHtmlCache.h"
//-------------------------------------------------------------------------
// ����RichHtmlԪ��
class FKCW_RichHtml_EleBase : public FKCW_RichHtml_IRichElement
{
public:
	typedef std::map<std::string, std::string> attrs_t;

public:
	static attrs_t*		parseAttributes(const char** attrs);
	static bool			hasAttribute(attrs_t* attrs, const char* attr);

	CCNode* createDrawSolidPolygonNode(FKCW_RichHtml_Canvas canvas);

public:
	virtual bool parse(class FKCW_RichHtml_IRichParser* parser, const char** attr = NULL);
	virtual bool composit(class FKCW_RichHtml_IRichCompositor* compositor);
	virtual void render(FKCW_RichHtml_Canvas canvas);

	virtual bool pushMetricsState() { return false; }
	virtual bool pushRenderState() { return false; }

	virtual element_list_t* getChildren();
	virtual void addChildren(FKCW_RichHtml_IRichElement* child);
	virtual void removeAllChildren();
	virtual FKCW_RichHtml_IRichElement* getParent();
	virtual void setParent(FKCW_RichHtml_IRichElement* parent);

	virtual int	getID();
	virtual FKCW_RichHtml_IRichElement* findChildByID(int _id);

	virtual FKCW_RichHtml_Pos getLocalPosition() const { return m_rPos; }
	virtual void setLocalPosition(FKCW_RichHtml_Pos pos) { m_rPos = pos;}
	virtual void setLocalPositionX(short x) { m_rPos.x = x;}
	virtual void setLocalPositionY(short y) { m_rPos.y = y; }
	virtual FKCW_RichHtml_Pos getGlobalPosition() { return m_rGlobalPos; }
	
	virtual FKCW_RichHtml_Metrics* getMetrics() { return &m_rMetrics; }
	
	virtual FKCW_RichHtml_Texture* getTexture() { return &m_rTexture; }
	virtual bool scaleToElementSize() { return false; }
	virtual void setRColor(unsigned int color) { m_rColor = color; }
	virtual unsigned int getColor() { return m_rColor; }
	virtual const char* getFontAlias() { return NULL; }
	virtual bool isBatchedDrawable() { return false; }

	virtual bool canLinewrap() { return true; }
	virtual bool isNewlineBefore() { return false; }
	virtual bool isNewlineFollow() { return false;}
	virtual bool isCachedComposit() { return false;}
	virtual short getBaseline() { return 0; }
	virtual bool needBaselineCorrect() { return false;}

	virtual void onCachedCompositBegin(class FKCW_RichHtml_ICompositCache* cache, FKCW_RichHtml_Pos& pen){}
	virtual void onCachedCompositEnd(class FKCW_RichHtml_ICompositCache* cache, FKCW_RichHtml_Pos& pen){}

	FKCW_RichHtml_EleBase();
	virtual ~FKCW_RichHtml_EleBase();

protected:
	// ��������
	virtual bool onParseAttributes(class FKCW_RichHtml_IRichParser* parser, attrs_t* attrs ){ return true; }

	// ���ñ���λ�ú����
	virtual void onCompositStart(class FKCW_RichHtml_IRichCompositor* compositor) {}
	// Push״̬֮�����
	virtual void onCompositStatePushed(class FKCW_RichHtml_IRichCompositor* compositor) {}
	// ����������������
	virtual void onCompositChildrenEnd(class FKCW_RichHtml_IRichCompositor* compositor) {}
	// ״̬������Ϻ���ã���ʱԪ����Ҫ�����
	virtual bool onCompositFinish(class FKCW_RichHtml_IRichCompositor* compositor) { return false; }

	// ����ʵ�ֵ���Ⱦ�¼�
	virtual void onRenderPrev(FKCW_RichHtml_Canvas canvas) {}
	virtual void onRenderPost(FKCW_RichHtml_Canvas canvas) {}

	int m_rID;

	element_list_t* m_rChildren;
	FKCW_RichHtml_IRichElement* m_rParent;

	FKCW_RichHtml_Pos m_rPos;
	FKCW_RichHtml_Pos m_rGlobalPos;
	FKCW_RichHtml_Metrics m_rMetrics;
	FKCW_RichHtml_Texture m_rTexture;

	unsigned int m_rColor;
	bool m_rDirty;
};
//-------------------------------------------------------------------------
// ʵ�Ķ����Ԫ��
class FKCW_RichHtml_EleSolidPolygon : public FKCW_RichHtml_EleBase
{
public:
	CCNode* createDrawNode(FKCW_RichHtml_Canvas canvas);
};
//-------------------------------------------------------------------------
// Batch������ȾԪ�أ�ʹ���ظ�������
class FKCW_RichHtml_EleBatchedDrawable : public FKCW_RichHtml_EleBase
{
public:
	virtual bool isBatchedDrawable() { return true; }
	virtual bool isCachedComposit() { return true; }

	FKCW_RichHtml_EleBatchedDrawable();

protected:
	virtual bool onCompositFinish(class FKCW_RichHtml_IRichCompositor* compositor);
	virtual void onRenderPrev(FKCW_RichHtml_Canvas canvas);
};
//-------------------------------------------------------------------------
class FKCW_RichHtml_AtlasHelper : public FKCW_RichHtml_EleBatchedDrawable
{
public:
	virtual bool scaleToElementSize() { return true; }

	virtual void onRenderPrev(FKCW_RichHtml_Canvas canvas);
	virtual bool isDirty() { return m_rDirty; }
	virtual void setDirty(bool b) { m_rDirty = b; }

	virtual void setGlobalPosition(FKCW_RichHtml_Pos pos) { m_rGlobalPos = pos; }
};

// ����Ԫ��
class FKCW_RichHtml_EleGlyph : public FKCW_RichHtml_EleBatchedDrawable
{
public:
	virtual bool canLinewrap() { return true; }
	virtual short getBaseline() { return m_rMetrics.rect.min_y(); }
	virtual const char* getFontAlias() { return m_font_alias.c_str(); }

	FKCW_RichHtml_EleGlyph(unsigned int charcode);
	virtual ~FKCW_RichHtml_EleGlyph();

protected:
	virtual void onCompositStart(class FKCW_RichHtml_IRichCompositor* compositor);

private:
	unsigned int m_charcode;
	struct SGlyphSlot* m_slot;
	std::string m_font_alias;
};
//-------------------------------------------------------------------------
// HTML�ڵ�Ԫ��
class FKCW_RichHtml_EleHTMLNode : public FKCW_RichHtml_EleBase
{
public:
	static attrs_t*		parseStyle(const std::string& style_str);
	static FKCW_RichHtml_Margin		parseMargin(const std::string& str);
	static unsigned int parseColor(const std::string& color_str);
	static FKCW_RichHtml_OptSize		parseOptSize(const std::string& str);
	static short		parsePixel(const std::string& str);
	static float		parsePercent(const std::string& str);
	static bool			parseAlignment(const std::string& str, ENUM_Alignment& align);
};
//-------------------------------------------------------------------------
// HTML��<p>Ԫ��
//  - ֧�ּ򵥵�CSS����
//		- �հ׸�: nowrap
//		- ��ɫ:#rrggbb[aa]
//		- ����:(font alias)
//		- �������:left|center|right
//		- �и�: Npx					
//		- ��Ե��ע: Npx				
//		- ���: Npx					
//-------------------------------------------------------------------------
class FKCW_RichHtml_EleHTMLP : public FKCW_RichHtml_EleHTMLNode
{
public:
	virtual bool pushMetricsState() { return true; }
	virtual bool pushRenderState() { return true; }
	virtual bool isCachedComposit() { return true; }
	virtual bool isNewlineBefore() { return true; }
	virtual bool isNewlineFollow() { return true; }

protected:
	virtual bool onParseAttributes(class FKCW_RichHtml_IRichParser* parser, attrs_t* attrs );
	virtual void onCompositStatePushed(class FKCW_RichHtml_IRichCompositor* compositor);
	virtual void onCompositChildrenEnd(class FKCW_RichHtml_IRichCompositor* compositor);
	virtual bool onCompositFinish(class FKCW_RichHtml_IRichCompositor* compositor);

private:
	FKCW_RichHtml_LineCache m_FKCW_RichHtml_LineCache;
	std::string m_rFontAlias;
};
//-------------------------------------------------------------------------
// HTML��Ԫ��
class FKCW_RichHtml_EleHTMLRoot : public FKCW_RichHtml_EleHTMLNode
{
public:
	virtual bool pushMetricsState() { return true; }
	virtual bool isCachedComposit() { return true; }
	virtual bool isNewlineBefore() { return true; }
	virtual bool isNewlineFollow() { return true; }

protected:
	virtual bool onCompositFinish(class FKCW_RichHtml_IRichCompositor* compositor) { return true; }
};
//-------------------------------------------------------------------------
class FKCW_RichHtml_EleHTMLNotSupport : public FKCW_RichHtml_EleHTMLNode
{
};
//-------------------------------------------------------------------------
// HTML<br>����Ԫ��
class FKCW_RichHtml_EleHTMLBR : public FKCW_RichHtml_EleHTMLNode
{
public:
	virtual bool isCachedComposit() { return true; }
	virtual bool isNewlineFollow() { return true; }
	virtual bool needBaselineCorrect() { return true; }

protected:
	virtual bool onCompositFinish(class FKCW_RichHtml_IRichCompositor* compositor);
};
//-------------------------------------------------------------------------
// HTMl<font>����Ԫ��
// ���� face=<font alias>
//		color=#rrggbb[aa]
class FKCW_RichHtml_EleHTMLFont : public FKCW_RichHtml_EleHTMLNode
{
public:
	virtual bool pushRenderState() { return true; }
	FKCW_RichHtml_EleHTMLFont();

protected:
	virtual bool onParseAttributes(class FKCW_RichHtml_IRichParser* parser, attrs_t* attrs );
	virtual void onCompositStatePushed(class FKCW_RichHtml_IRichCompositor* compositor);

private:
	std::string m_rFont;
	unsigned int m_rColor;
};
//-------------------------------------------------------------------------
// HTML<span>��ǩ
// �ַ�����ɫ���»���
class FKCW_RichHtml_EleHTMLSpans : public FKCW_RichHtml_EleHTMLNode
{
public:
	virtual bool pushRenderState() { return true; }

	virtual bool isDrawUnderline() { return m_rDrawUnderline; }
	virtual void setDrawUnderline(bool b) { m_rDrawUnderline = b; }

	virtual bool isDrawBackground() { return m_rDrawBackground; }
	virtual void setDrawBackground(bool b) { m_rDrawBackground = b; }
	virtual unsigned int getBGColor() { return m_rBGColor; }

	FKCW_RichHtml_EleHTMLSpans();
	virtual ~FKCW_RichHtml_EleHTMLSpans();

protected:
	virtual void onRenderPost(FKCW_RichHtml_Canvas canvas);

private:
	void travesalChildrenSpans(
		element_list_t* eles, const char*& font, short& start_span_x, short& span_y, short& underline_thickness, 
		short& end_span_x, short& min_span_y, short& max_span_y, unsigned int& color, bool is_root);
	void clearAllSpans();

protected:
	bool m_rDrawUnderline;
	bool m_rDrawBackground;
	unsigned int m_rBGColor;
	std::vector<FKCW_RichHtml_EleSolidPolygon*> m_rUnderlineDrawables;
	std::vector<FKCW_RichHtml_EleSolidPolygon*> m_rBackgroudDrawables;
	std::list<FKCW_RichHtml_Rect> m_rSpans; // spans
};
//-------------------------------------------------------------------------
// HTML<u>�»���Ԫ��
class FKCW_RichHtml_EleHTMLU : public FKCW_RichHtml_EleHTMLSpans
{
public:
	FKCW_RichHtml_EleHTMLU();
};
//-------------------------------------------------------------------------
// HTML<hr/>ˮƽ��Ԫ��
// ���ԣ�width=w%|w			- ˮƽ�߿�
//		 size=n				- ˮƽ�ߺ��
// CSS֧��
//		 color:#rrggbb[aa]	- ˮƽ����ɫ
class FKCW_RichHtml_EleHTMLHR : public FKCW_RichHtml_EleBase
{
public:
	virtual bool isNewlineBefore() { return true; }
	virtual bool isNewlineFollow() { return true; }
	virtual bool isCachedComposit() { return true; }

	virtual void onCachedCompositBegin(class FKCW_RichHtml_ICompositCache* cache, FKCW_RichHtml_Pos& pen);
	virtual void onCachedCompositEnd(class FKCW_RichHtml_ICompositCache* cache, FKCW_RichHtml_Pos& pen);
	FKCW_RichHtml_EleHTMLHR();

protected:
	virtual bool onParseAttributes(class FKCW_RichHtml_IRichParser* parser, attrs_t* attrs );
	virtual void onCompositStart(class FKCW_RichHtml_IRichCompositor* compositor);
	virtual bool onCompositFinish(class FKCW_RichHtml_IRichCompositor* compositor);
	virtual void onRenderPost(FKCW_RichHtml_Canvas canvas);

	short m_rSize;
	FKCW_RichHtml_OptSize m_rWidth;
	short m_rTempPadding;
};
//-------------------------------------------------------------------------
// HTML <td> ��Ԫ����֧��
//	- ����: width=<n>%|<n>
//	- ����: height=<n>%|<n>
//	- ����: align=left|right|center	
//	- ����: valign=top|bottom|middle
//	- ����: padding=<n>				
//	- ����: spacing=<n>				
//	- ����: nowrap=nowrap			
//	- ����: bgcolor=#rrggbb[aa]
//	- ����: bg-image="image file path"
//	- ����: bg-rect="<TOP>px <RIGHT>px <BOTTOM>px <LEFT>px"
class FKCW_RichHtml_EleHTMLCell : public FKCW_RichHtml_EleHTMLNode
{
	friend class FKCW_RichHtml_TableCache;
public:
	virtual bool pushMetricsState() { return true; }
	virtual void onRenderPrev(FKCW_RichHtml_Canvas canvas);
	void setIndex(int index) { m_rIndexNumber = index; }
	bool isWidthSet() { return !m_rWidth.isZero(); }

	FKCW_RichHtml_EleHTMLCell(class FKCW_RichHtml_EleHTMLRow* row);
	virtual ~FKCW_RichHtml_EleHTMLCell();

protected:
	virtual bool onParseAttributes(class FKCW_RichHtml_IRichParser* parser, attrs_t* attrs );
	virtual void onCompositStatePushed(class FKCW_RichHtml_IRichCompositor* compositor);
	virtual void onCompositChildrenEnd(class FKCW_RichHtml_IRichCompositor* compositor);

private:
	class FKCW_RichHtml_EleHTMLRow* m_rRow;
	FKCW_RichHtml_LineCache m_FKCW_RichHtml_LineCache;

	bool m_rHAlignSpecified;
	bool m_rVAlignSpecified;
	int m_rIndexNumber;
	ENUM_Alignment m_rHAlignment;
	ENUM_Alignment m_rVAlignment;
	FKCW_RichHtml_OptSize m_rWidth;
	FKCW_RichHtml_OptSize m_rHeight;
	FKCW_RichHtml_Rect m_rContentSize;
	FKCW_RichHtml_AtlasHelper m_rBGTexture;
};
//-------------------------------------------------------------------------
// HTML<tr>�����֧��
//	- ����: align=left|right|center	- content halignment
//	- ����: valign=top|bottom|middle- content valignment
class FKCW_RichHtml_EleHTMLRow : public FKCW_RichHtml_EleHTMLNode
{
	friend class FKCW_RichHtml_TableCache;
public:
	virtual bool pushMetricsState() { return true; }
	virtual bool isCachedComposit() { return true; }

	virtual std::vector<class FKCW_RichHtml_EleHTMLCell*>& getCells();
	class FKCW_RichHtml_EleHTMLTable* getTable();
	short getCellWidth(int index, FKCW_RichHtml_OptSize width);

	virtual void addChildren(FKCW_RichHtml_IRichElement* child);

	FKCW_RichHtml_EleHTMLRow(class FKCW_RichHtml_EleHTMLTable* table);

protected:
	virtual bool onParseAttributes(class FKCW_RichHtml_IRichParser* parser, attrs_t* attrs );
	virtual void onCompositStatePushed(class FKCW_RichHtml_IRichCompositor* compositor);
	virtual bool onCompositFinish(class FKCW_RichHtml_IRichCompositor* compositor) { return true; }

private:
	class FKCW_RichHtml_EleHTMLTable* m_rTable;
	std::vector<class FKCW_RichHtml_EleHTMLCell*> m_rCells;

	bool m_rHAlignSpecified;
	bool m_rVAlignSpecified;
	ENUM_Alignment m_rHAlignment;
	ENUM_Alignment m_rVAlignment;
	short m_rLeftWidth;
};
//-------------------------------------------------------------------------
// HTML<table>��������֧��
//	- ����: width=<n>%|<n>
//	- ����: align=left|right|center	- table halignment relative to other elements
//	- ����: cellspadding=<n>		- cell content padding
//	- ����: cellsspacing=<n>		- cell content spacing
//	- ����: border=<n>				- border thickness
//	- ����: bgcolor=#rrggbb[aa]		- background color
//	- ����: bordercolor=#rrggbb[aa]	- border color
//	- ����: frame=<frame>			- draw outer frame, see EFrame
//	- ����: rules=<rules>			- draw inner frame, see ERules
class FKCW_RichHtml_EleHTMLTable : public FKCW_RichHtml_EleHTMLNode
{
	friend class FKCW_RichHtml_TableCache;
public:
	enum EFrame
	{
		e_void,
		e_above,
		e_below,
		e_hsides,
		e_lhs,
		e_rhs,
		e_vsides,
		e_box,
		e_border,
	};
	enum ERules
	{
		e_none,
		e_groups,
		e_rows,
		e_cols,
		e_all,
	};

	virtual bool pushMetricsState() { return true; }
	virtual bool isCachedComposit() { return true; }
	virtual bool isNewlineBefore() { return true; }
	virtual bool isNewlineFollow()	{ return true; }

	virtual short getZoneWidth() { return m_rZoneWidth; }

	virtual void onCachedCompositBegin(class FKCW_RichHtml_ICompositCache* cache, FKCW_RichHtml_Pos& pen);
	virtual void onCachedCompositEnd(class FKCW_RichHtml_ICompositCache* cache, FKCW_RichHtml_Pos& pen);

	virtual void addChildren(FKCW_RichHtml_IRichElement* child);
	FKCW_RichHtml_EleHTMLTable();

protected:
	virtual bool onParseAttributes(class FKCW_RichHtml_IRichParser* parser, attrs_t* attrs );
	virtual void onCompositStatePushed(class FKCW_RichHtml_IRichCompositor* compositor);
	virtual void onCompositChildrenEnd(class FKCW_RichHtml_IRichCompositor* compositor);
	virtual bool onCompositFinish(class FKCW_RichHtml_IRichCompositor* compositor);
	virtual void onRenderPrev(FKCW_RichHtml_Canvas canvas);
	virtual void drawThicknessLine(short left, short top, short right, short bottom, const ccColor4F& color);
	
private:
	void createTicknessLineNode(FKCW_RichHtml_Canvas canvas, short left, short top, short right, short bottom, const ccColor4F& color);

	static EFrame parseFrame(const std::string& str);
	static ERules parseRules(const std::string& str);

	FKCW_RichHtml_TableCache m_rTableCache;
	std::vector<class FKCW_RichHtml_EleHTMLRow*> m_rRows;

	FKCW_RichHtml_OptSize m_rWidth;
	short m_rBorder;
	unsigned int m_rBorderColor;
	EFrame m_rFrame;
	ERules m_rRules;

	bool m_rHAlignSpecified;
	ENUM_Alignment m_rHAlign;
	ENUM_Alignment m_rTempAlign;
	short m_rZoneWidth;
};
//-------------------------------------------------------------------------
// HTML<img>��̬ͼƬ֧��
//	- ����: src=<resource-path>
//	- ����: alt=<string>		- ��δ֧��
//	- ����: texture-rect="<TOP>px <RIGHT>px <BOTTOM>px <LEFT>px"
class FKCW_RichHtml_EleHTMLImg : public FKCW_RichHtml_EleBatchedDrawable
{
public:
	virtual bool needBaselineCorrect() { return true; }

protected:
	virtual bool onParseAttributes(class FKCW_RichHtml_IRichParser* parser, attrs_t* attrs );
	virtual void onCompositStart(class FKCW_RichHtml_IRichCompositor* compositor);

private:
	std::string m_filename;
	std::string m_alt;
};
//-------------------------------------------------------------------------
// HTML ����֧��
class FKCW_RichHtml_EleHTMLTouchable : public FKCW_RichHtml_EleHTMLSpans
{
public:
	virtual void setEnabled(bool b) { m_rEnabled = b;}
	virtual bool isEnabled() { return m_rEnabled; }

	virtual const std::string& getName() const = 0;
	virtual const std::string& getValue() const = 0;

	virtual bool isLocationInside(CCPoint location);

	virtual bool onTouchBegan(CCNode* container, CCTouch *touch, CCEvent *evt);
	virtual void onTouchMoved(CCNode* container, CCTouch *touch, CCEvent *evt);
	virtual void onTouchEnded(CCNode* container, CCTouch *touch, CCEvent *evt);
	virtual void onTouchCancelled(CCNode* container, CCTouch *touch, CCEvent *evt);

	FKCW_RichHtml_EleHTMLTouchable();

protected:
	virtual void onCompositStart(class FKCW_RichHtml_IRichCompositor* compositor);

	bool m_rEnabled;
};
//-------------------------------------------------------------------------
// HTML<button>��ť֧��
//	- ����: name=<name string>		- button name
//	- ����: value=<value string>	- button value
//	- ����: bgcolor=#rrggbb[aa]		- back ground color
class FKCW_RichHtml_EleHTMLButton : public FKCW_RichHtml_EleHTMLTouchable
{
public:
	virtual void setName(const std::string& name) { m_rName = name; }
	virtual const std::string& getName() const { return m_rName; }
	virtual void setValue(const std::string& value) { m_rValue = value; }
	virtual const std::string& getValue() const { return m_rValue; }

protected:
	virtual void onTouchEnded(CCNode* container, CCTouch *touch, CCEvent *evt);
	virtual bool onParseAttributes(class FKCW_RichHtml_IRichParser* parser, attrs_t* attrs );

	std::string m_rName;
	std::string m_rValue;
};
//-------------------------------------------------------------------------
// HTML<A>������
//	- ����: name=<name string>		- name
//	- ����: href=<target string>	- target
//	- ����: bgcolor=#rrggbb[aa]		- back ground color
class FKCW_RichHtml_EleHTMLAnchor : public FKCW_RichHtml_EleHTMLTouchable
{
public:
	virtual void setName(const std::string& name) { m_rName = name; }
	virtual const std::string& getName() const { return m_rName; }
	virtual const std::string& getValue() const { return m_rHref; }
	virtual void setHerf(const std::string& value) { m_rHref = value; }
	virtual const std::string& getHref() const { return m_rHref; }

protected:
	virtual bool onParseAttributes(class FKCW_RichHtml_IRichParser* parser, attrs_t* attrs );

	std::string m_rName;
	std::string m_rHref;
};
//-------------------------------------------------------------------------
// CCBNode�ڵ�Ԫ��
//	- CCB: <ccb> - ����cocosBuilder��"ccbi"�ļ�����������ӵ�����
//	- ����: src=<file>		- ccbi file name
//	- ����: play="auto"		- auto play after load
//	- ����: anim=<sequence> - auto play sequence name
class FKCW_RichHtml_EleCCBNode : public FKCW_RichHtml_EleBase
{
public:
	typedef class CCNode* (*ccb_reader_t)(const char* ccbi_file);
	static void registerCCBReader(ccb_reader_t reader);

	virtual bool isCachedComposit() { return true; }
	virtual bool canLinewrap() { return true; }
	virtual bool needBaselineCorrect() { return true;  }

	FKCW_RichHtml_EleCCBNode();
	virtual ~FKCW_RichHtml_EleCCBNode();

protected:
	virtual bool onParseAttributes(class FKCW_RichHtml_IRichParser* parser, attrs_t* attrs );
	virtual bool onCompositFinish(class FKCW_RichHtml_IRichCompositor* compositor);
	virtual void onRenderPost(FKCW_RichHtml_Canvas canvas);

private:
	std::string m_filename;
	std::string m_sequence;
	CCNode* m_ccbNode;
	bool m_dirty;
};
//-------------------------------------------------------------------------