//*************************************************************************
//	��������:	2014-8-12   9:31
//	�ļ�����:	ArmatureData.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "BaseMacro.h"
#include "BoneData.h"
#include "SkinData.h"
#include "AnimationData.h"
#include <vector>
using std::vector;
//-------------------------------------------------------------------------
// ����һ���Ǽ���������������Ϣ
class CArmatureData
{
public:
	string					m_szName;				// ���Ǽܵ�����
	vector<CBoneData*>		m_vecBoneDataList;		// ���Ǽ��������Ĺ������ݣ�Ҳ����Flash�е�ͼ���ˣ�
	vector<CSkinData*>		m_vecSkinDataList;		// ���Ǽ���������skin��Ϣ������skin�е�slot���Ӧ���͹������ݣ�ͼ�㣩һһ��Ӧ
	vector<CAnimationData*>	m_vecAnimationDataList; // ���Ǽ��������Ķ�����
public:
	CArmatureData()
	{
		m_szName.clear();
	}

	virtual ~CArmatureData()
	{
		Clear();
	}
public:
	virtual void Clear()
	{
		for( unsigned int i = 0; i < m_vecBoneDataList.size(); ++i )
		{
			m_vecBoneDataList[i]->Clear();
			delete m_vecBoneDataList[i];
		}
		for( unsigned int i = 0; i < m_vecSkinDataList.size(); ++i )
		{
			m_vecSkinDataList[i]->Clear();
			delete m_vecSkinDataList[i];
		}
		for( unsigned int i = 0; i < m_vecAnimationDataList.size(); ++i )
		{
			m_vecAnimationDataList[i]->Clear();
			delete m_vecAnimationDataList[i];
		}
		m_vecAnimationDataList.clear();
		m_vecBoneDataList.clear();
		m_vecSkinDataList.clear();
	}

	CBoneData* GetBoneDataByName( const string& p_szBoneName )
	{
		for( unsigned int i = 0; i < m_vecBoneDataList.size(); ++i )
		{
			if( m_vecBoneDataList[i]->m_szName == p_szBoneName )
			{
				return m_vecBoneDataList[i];
			}
		}
		return NULL;
	}

	CSkinData* GetFirstSkinData()
	{
		if( m_vecSkinDataList.empty() )
			return NULL;
		return m_vecSkinDataList[0];
	}

	CSkinData* GetSkinDataByName( const string& p_szSkinName )
	{
		for( unsigned int i = 0; i < m_vecSkinDataList.size(); ++i )
		{
			if( m_vecSkinDataList[i]->m_szName == p_szSkinName )
			{
				return m_vecSkinDataList[i];
			}
		}
		return NULL;
	}

	CAnimationData* GetAnimationDataByName( const string& p_szAnimationName )
	{
		for( unsigned int i = 0; i < m_vecAnimationDataList.size(); ++i )
		{
			if( m_vecAnimationDataList[i]->m_szName == p_szAnimationName )
			{
				return m_vecAnimationDataList[i];
			}
		}
		return NULL;
	}

	void AddBoneData( CBoneData* p_pBoneData )
	{
		if( p_pBoneData == NULL )
			return;
		m_vecBoneDataList.push_back( p_pBoneData );
	}

	void AddSkinData( CSkinData* p_pSkinData )
	{
		if( p_pSkinData == NULL )
			return;
		m_vecSkinDataList.push_back( p_pSkinData );
	}

	void AddAnimationData( CAnimationData* p_pAnimationData )
	{
		if( p_pAnimationData == NULL )
			return;
		m_vecAnimationDataList.push_back( p_pAnimationData );
	}

	static bool SortBoneFunc( const std::pair<int, CBoneData*>&a, const std::pair<int, CBoneData*>&b )
	{
		return a.first < b.first;
	}

	void SortBoneDataList();
};

//-------------------------------------------------------------------------

//-------------------------------------------------------------------------