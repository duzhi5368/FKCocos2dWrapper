//*************************************************************************
//	��������:	2015-1-22
//	�ļ�����:	FKAnimateExResMgr.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../FKEngineCommonHead.h"
//-------------------------------------------------------------------------
class FKAnimateExRes;
class FKAnimateExResMgr
{
protected:
	FKAnimateExResMgr();
	~FKAnimateExResMgr();
public:
	static FKAnimateExResMgr& GetInstance()
	{
		static FKAnimateExResMgr s_Inst;
		return s_Inst;
	}
public:
	// ����������Դ
	// ������szAnimationExResName ������Դ�ļ���
	// ע��������Դ�Ѿ����ڣ���ֱ�ӷ���ԭ��Դָ��
	FKAnimateExRes*		GetAnimateExRes( const char* szAnimationExResName );
	// ɾ��������Դ
	void				ReleaseAnimationExRes( FKAnimateExRes* pAniRes );
	// �ͷ�ȫ����Դ
	void				ReleaseAllResource();
	// �ͷ�û���ͷŵ���Դ
	void				ReleaseUnusedResource();
private:
	typedef map<string, FKAnimateExRes*>	AnimationExResMap;
	AnimationExResMap				m_mapAnimationExRes;	// ������Դ�б�
};