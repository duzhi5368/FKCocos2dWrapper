//*************************************************************************
//	��������:	2015-1-3
//	�ļ�����:	FKCW_RichHtml.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
/* 
====================================
ģ��˵����	
====================================
	֧��HTML��ʽ������������Ⱦ��RichLabel
	// ��׼HTML��ǩ֧��
	//	- <p>		: id; style="white-space:nowrap; color; font; text-align:left|center|right; margin; padding; line-height(no use)"
	//	- <br>		: id; 
	//	- <hr>		: id; width; size; style="color"
	//	- <font>	: id; face; color
	//	- <u>		: id; 
	//	- <table>	: id; width; align; cellspadding; cellsspacing; border; bgcolor; bordercolor; frame; rules
	//	- <tr>		: id; align; valign
	//	- <td>		: id; width; height; align; valign; padding; spacing; nowrap; bgcolor; bg-image; bg-rect
	//	- <img>		: id; src; alt(no use); texture-rect="<TOP>px <LEFT>px <BOTTOM>px <LEFT>px"
	//	- <a>		: id; name; href; bgcolor
	//	- <button>	: id; name; value; bgcolor
	//
	//	����֧��ccbi��ʽ��ǩ
	//	- <ccb>		: id; src; play="auto"; anim;
====================================
�ڲ��ļ�����˵����
====================================
	
====================================
������Ŀ/�⣺
====================================
	FKCW_Base
	FKCW_Font
====================================
todo:
====================================
*/ 
//-------------------------------------------------------------------------
#include "Include/FKCW_RichHtml_Macros.h"
#include "Include/FKCW_RichHtml_HelpFunc.h"
#include "Include/FKCW_RichHtml_BaseStruct.h"
#include "Include/FKCW_RichHtml_Interface.h"

#include "Include/FKCW_RichHtml_RichHtmlAltas.h"
#include "Include/FKCW_RichHtml_RichHtmlCache.h"
#include "Include/FKCW_RichHtml_RichHtmlCompositor.h"
#include "Include/FKCW_RichHtml_RichHtmlElement.h"
#include "Include/FKCW_RichHtml_RichHtmlNode.h"
#include "Include/FKCW_RichHtml_RichHtmlOverlay.h"
#include "Include/FKCW_RichHtml_RichHtmlParser.h"

#include "Include/FKCW_RichHtml_RichHtmlLabel.h"