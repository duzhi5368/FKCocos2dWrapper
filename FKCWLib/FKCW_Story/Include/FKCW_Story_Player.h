//*************************************************************************
//	��������:	2015-1-3
//	�ļ�����:	FKCW_Story_Player.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_Story_Macros.h"
#include <cocos-ext.h>
//-------------------------------------------------------------------------
class FKCW_Story_Layer;
class FKCW_Story_Command;
class FKCW_Story_Player : public CCObject
{
private:
	CCPoint m_oldDesignSize;					// ֮ǰ����ƴ�С
	bool m_needRestoreDesignSize;				// �Ƿ���Ҫ����֮ǰ����ƴ�С

private:
	// ��ȡ��һ������
	void fetchNextCommand();
	// ִ��һ������
	void executeCurrentCommand();
	// ��ȡһ����ɫ�ڵ�
	CCNode* getRole(const char* name);
	// ��ȡһ��������ɫ����
	cocos2d::extension::CCArmature* getArmatureRole(const char* name);	
	// ĳ����ִ����ϵĻص�����
	void onArmatureAnimationDone(cocos2d::extension::CCArmature* armature, 
		cocos2d::extension::MovementEventType e, const char* name);

public:
	FKCW_Story_Player();
	virtual ~FKCW_Story_Player();
	static FKCW_Story_Player* create(FKCW_Story_Layer* owner);

	/// init
	virtual bool initWithOwner(FKCW_Story_Layer* owner);

	// ����һ���ļ�����
	int ParserStoryScriptString(const char* szStr );
	// ��ʼ����
	void start();
	// һ����Ϣ�������
	void onMessageDone();
	// �յ������Ϣ
	void onClickDone();
	// �Ƿ��д���
	bool hasError() { return !m_error.empty(); }

	CC_SYNTHESIZE(FKCW_Story_Layer*, m_owner, Owner);
	CC_SYNTHESIZE(FKCW_Story_Command*, m_curCmd, CurrentCommand);
	CC_SYNTHESIZE(int, m_curCmdIndex, CurrentCommandIndex);
	CC_SYNTHESIZE_READONLY_BOOL(m_done, Done);
	CC_SYNTHESIZE_READONLY_PASS_BY_REF(CCDictionary, m_roleMap, RoleMap);

	// ȫ������
	CC_SYNTHESIZE(float, m_msgSize, MessageSize);
	CC_SYNTHESIZE(int, m_msgColor, MessageColor);
	CC_SYNTHESIZE(CCPoint, m_msgPos, MessagePos);
	CC_SYNTHESIZE(CCPoint, m_msgAnchor, MessageAnchor);
	CC_SYNTHESIZE_PASS_BY_REF(string, m_msgFont, MessageFont);
	CC_SYNTHESIZE_PASS_BY_REF(string, m_nameFont, NameFont);
	CC_SYNTHESIZE_PASS_BY_REF(string, m_labelFont, LabelFont);
	CC_SYNTHESIZE(float, m_nameSize, NameSize);
	CC_SYNTHESIZE(int, m_nameColor, NameColor);
	CC_SYNTHESIZE(CCPoint, m_labelAnchor, LabelAnchor);
	CC_SYNTHESIZE(float, m_labelSize, LabelSize);
	CC_SYNTHESIZE(int, m_labelColor, LabelColor);
	CC_SYNTHESIZE(CCPoint, m_namePos, NamePos);
	CC_SYNTHESIZE(CCPoint, m_nameAnchor, NameAnchor);
	CC_SYNTHESIZE(CCPoint, m_bgPos, BgPos);
	CC_SYNTHESIZE(CCPoint, m_requiredDesignSize, RequiredDesignSize);
	CC_SYNTHESIZE(ResolutionPolicy, m_requiredPolicy, RequiredPolicy);
	CC_SYNTHESIZE(CCSize, m_msgConstraints, MessageConstraints);
	CC_SYNTHESIZE(CCTextAlignment, m_msgAlignment, MessageAlignment);
	CC_SYNTHESIZE(CCSize, m_labelConstraints, LabelConstraints);
	CC_SYNTHESIZE(CCTextAlignment, m_labelAlignment, LabelAlignment);

	CC_SYNTHESIZE_PASS_BY_REF_SETTER(string, m_error, Error);
};
