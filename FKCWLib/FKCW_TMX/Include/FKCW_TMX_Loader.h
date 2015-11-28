//*************************************************************************
//	��������:	2014-12-29
//	�ļ�����:	FKCW_TMX_Loader.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_TMX_Macros.h"
//-------------------------------------------------------------------------
class FKCW_TMX_MapInfo;
//-------------------------------------------------------------------------
class FKCW_TMX_Loader : public CCObject, public CCSAXDelegator
{
private:
	// tmx�ļ���ǩ
	enum TMXTag{
		UNKNOWN,
		MAP,
		TILESET,
		TILE,
		IMAGE,
		LAYER,
		DATA,
		PROPERTIES,
		PROPERTY,
		OBJECTGROUP,
		OBJECT,
		POLYLINE,
		POLYGON
	};

	// TMX�ļ���ǩ����
	enum TMXAttr{
		ATTR_UNKNOWN,
		ATTR_VERSION,
		ATTR_ORIENTATION,
		ATTR_WIDTH,
		ATTR_HEIGHT,
		ATTR_TILEWIDTH,
		ATTR_TILEHEIGHT,
		ATTR_NAME,
		ATTR_FIRSTGID,
		ATTR_SPACING,
		ATTR_MARGIN,
		ATTR_VISIBLE,
		ATTR_OPACITY,
		ATTR_X,
		ATTR_Y,
		ATTR_TYPE,
		ATTR_COLOR,
		ATTR_POINTS
	};

private:
	string m_tmxDir;			// tmxĿ¼
	FKCW_TMX_MapInfo* m_map;	// ��ͼ����
	vector<TMXTag> m_tags;		// ��ǩ��
	int m_lastGid;				// ����GridID
	bool m_compressed;			// �Ƿ�ѹ��

private:
	// �ļ���ȡ
	// ��ʧ�ܷ��� false
	bool load(const char* data, int length);

	// ��ǩ����
	void pushTag(TMXTag tag);
	void popTag();
	TMXTag topTag();
	TMXTag parentTag();
	TMXTag grandpaTag();
	TMXTag getTag(const char* name);
	TMXAttr getAttr(const char* name);

	// ����һ������ֵ
	const char* valueForKey(const char** atts, const char* name);

protected:
	FKCW_TMX_Loader();

public:
	virtual ~FKCW_TMX_Loader();
	static FKCW_TMX_Loader* create();

	virtual void startElement(void* ctx, const char* name, const char** atts);
	virtual void endElement(void* ctx, const char* name);
	virtual void textHandler(void* ctx, const char* s, int len);

	// ����һ�� tmx �ļ�
	// ������tmx���·��
	FKCW_TMX_MapInfo* load(const string& tmxFile);
	// ����һ�� tmx ���ݡ�����Ҫ�����߸����ļ�·�� 
	FKCW_TMX_MapInfo* load(const char* tmxData, int length, const string& resourcePath);
};