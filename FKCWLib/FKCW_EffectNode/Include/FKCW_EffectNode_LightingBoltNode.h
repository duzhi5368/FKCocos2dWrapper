//*************************************************************************
//	��������:	2014-11-17
//	�ļ�����:	FKCW_EffectNode_LightingBoltNode.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	���羫��ڵ�
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_EffectNode_Mesh.h"
#include "FKCW_EffectNode_IndexVBO.h"
#include "FKCW_EffectNode_GLProgramWithUnifos.h"
//-------------------------------------------------------------------------
class FKCW_EffectNode_LightingSeg
{
public:
	CCPoint									startPoint;
	CCPoint									endPoint;
	CCPoint									branchEndPoint;			// ֻ�����Ӷβű����ֵ
	int										branchID;				// ���������ķ�֧ID������ֵΪ0�����ʾ�ҽ�������֧��
	int										branchStartGenerationID;// ����������֧����ʼ����ID
	int										generationID;			// ���ε���ʼ����ID,Դ�ε���ʼ����IDΪ0
	FKCW_EffectNode_LightingSeg*			father;
	vector<FKCW_EffectNode_LightingSeg*>	childList;
	bool									needReGenerate;			// ����֧��������Ϊ���Σ��Ƿ�Ҫ�������¼�����ʼ����ID
public:
	FKCW_EffectNode_LightingSeg();
	FKCW_EffectNode_LightingSeg(CCPoint start,CCPoint end);
	virtual~FKCW_EffectNode_LightingSeg();

	void	init(CCPoint start,CCPoint end);
	bool	addChildRef(FKCW_EffectNode_LightingSeg*child);
	bool	removeChildRef(FKCW_EffectNode_LightingSeg*child);
	float	getLen()const;
	CCPoint getDir()const;
	CCPoint getVec()const;
	CCPoint getRightNormal()const;
	CCPoint getMidPoint()const;
protected:
	void	_InitParameter();
};
//-------------------------------------------------------------------------
class FKCW_EffectNode_LightingBoltSprite:public CCSprite
{
public:
	FKCW_EffectNode_LightingBoltSprite();
	virtual ~FKCW_EffectNode_LightingBoltSprite();

	void									updateNGeneration();
	void									draw();
	bool									init();
	void									setStartAndEnd(CCPoint start,CCPoint end);
	void									genLighting();
	void									doJitter();
	bool									getIsDrawDebug()const{return m_isDrawDebug;}
	void									setIsDrawDebug(bool value){m_isDrawDebug=value;}
protected:
	void									initProgram();
	void									genSeges();
	void									genMesh();
	vector<FKCW_EffectNode_LightingSeg*>	genSegesFromBranchSeg(FKCW_EffectNode_LightingSeg* branchSeg,int nGeneration);
	vector<FKCW_EffectNode_LightingSeg*>	splitSeg(FKCW_EffectNode_LightingSeg* seg,int generationID);
	void									releaseNeedReGenBranch(vector<FKCW_EffectNode_LightingSeg*>& branchList,vector<FKCW_EffectNode_LightingSeg*>& segList);
	void									releaseNeedReGenBranch_inn(FKCW_EffectNode_LightingSeg* seg,vector<FKCW_EffectNode_LightingSeg*>& segList);
	void									debugDraw_segWireFrame(float lineWidth);
	void									debugDraw_segLineAndDot(float lineWidth,float pointSize);
protected:
	FKCW_EffectNode_GLProgramWithUnifos*	m_program;
	CCPoint									m_startPoint_parentSpace;	// ���ռ���ʼ��
	CCPoint									m_endPoint_parentSpace;		// ���ռ���ֹ��
	CCPoint									m_startPoint;				// ���ؿռ���ʼ��
	CCPoint									m_endPoint;					// ���ؿռ���ֹ��
	vector<FKCW_EffectNode_LightingSeg*>	m_segList;					// �����б�
	int										m_nGeneration;				// �ָ���ٸ���֧��
	FKCW_EffectNode_LightingSeg*			m_headSeg;					// ����������ͷ����
	FKCW_EffectNode_LightingSeg*			m_tailSeg;					// ����������β����
	FKCW_EffectNode_Mesh*					m_mesh;
	FKCW_EffectNode_IndexVBO*				m_indexVBO;
	float									m_k_offset;
	float									m_mainSegLen;
	float									m_percentageOfJitterBranch;
	float									m_opacityZoom;
	bool									m_isDrawDebug;
};
//-------------------------------------------------------------------------
class FKCW_Action_FlashAction;
class FKCW_EffectNode_LightingBoltNode:public CCNode
{
public:
    friend class FKCW_Action_FlashAction;
public:
    FKCW_EffectNode_LightingBoltNode(){
        m_lbSprite=NULL;
        m_lbSprite2=NULL;
		m_isDrawDebug=false;
    }
    virtual~FKCW_EffectNode_LightingBoltNode(){}
    bool init(const CCPoint&start,const CCPoint&end);
    void setStartAndEnd(const CCPoint&start,const CCPoint&end){
        m_start=start;
        m_end=end;
        m_lbSprite->setStartAndEnd(m_start, m_end);
        m_lbSprite2->setStartAndEnd(m_start, m_end);
    }
    CCPoint getStart()const{return m_start;}
    CCPoint getEnd()const{return m_end;}
	bool getIsDrawDebug()const{
		assert(m_lbSprite->getIsDrawDebug()==m_isDrawDebug);
		assert(m_lbSprite2->getIsDrawDebug()==m_isDrawDebug);
		return m_isDrawDebug;
	}
	void setIsDrawDebug(bool value){
		m_isDrawDebug=value;
		m_lbSprite->setIsDrawDebug(value);
		m_lbSprite2->setIsDrawDebug(value);
	}
protected:
    CCPoint m_start;				// ���ؼ���ʼ�ڵ�
    CCPoint m_end;					// ���ؼ���ֹ�ڵ�
    FKCW_EffectNode_LightingBoltSprite*m_lbSprite;
    FKCW_EffectNode_LightingBoltSprite*m_lbSprite2;
	bool m_isDrawDebug;
};
//-------------------------------------------------------------------------
class FKCW_Action_FlashAction : public CCActionInterval
{
public:
	FKCW_Action_FlashAction();
	virtual~FKCW_Action_FlashAction();

	// ������fDuration -1��ʾ�޾�ѭ��
	static FKCW_Action_FlashAction* create(float fDuration,float oneFlashTime);
	// ������fDuration -1��ʾ�޾�ѭ��
	bool			initWithDuration(float fDuration,float oneFlashTime);
	virtual void	stop();
	virtual void	startWithTarget(CCNode *pTarget);
	virtual void	update(float time);
	virtual bool	isDone();
protected:
	void			_StartAnimation(CCNode* pTarget);
	void			_StopAnimation(CCNode* pTarget);
	void			_CallBack_flashForever(CCNode* sender);
	void			_CallBack_genLightning(CCNode* sender);
	void			_CallBack_jitter(CCNode* sender);
	void			_CallBack_resetOpacity(CCNode* sender);
	void			_InitMembers();
protected:
	float			m_timeFoe;
	float			m_timeCur;
	float			m_oneFlashTime;
	float			m_jitterTimeOfOneFlash;
	float			m_jitterInterval;
	bool			m_isDoJitter;
	GLubyte			m_startOpacity;	// �������⿪ʼ��͸����
	GLubyte			m_endOpacity;	// ����������ֹ��͸����
};
//-------------------------------------------------------------------------