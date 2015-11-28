//*************************************************************************
//	��������:	2014-8-12   11:25
//	�ļ�����:	SkeletonData.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "BaseMacro.h"
#include "ArmatureData.h"
#include "Point.h"
#include <string>
#include <vector>
#include <map>
using std::string;
using std::vector;
using std::map;
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
// ����ʵ��һ������xml�ļ��������ˣ�������һ���Ǽܻ���һ��Bones��������Ϣ
class CSkeletonData
{
public:
	string						m_szName;
	map< string, CPoint >		m_mapSubTexturePivots;		// ���������ĵ�λ�ñ�
	vector< CArmatureData* >	m_vecArmatureDataList;		// ����������xml�ļ�������¼����Armature�б�
public:
	CSkeletonData()
	{
		m_szName.clear();
		m_vecArmatureDataList.clear();
		m_mapSubTexturePivots.clear();
	}
	virtual ~CSkeletonData()
	{
		Clear();
	}
public:
	vector<string>		GetArmatureNameList()
	{
		vector<string>		vecNameList;
		vecNameList.clear();
		for( unsigned int i = 0; i < m_vecArmatureDataList.size(); ++i )
		{
			vecNameList.push_back( m_vecArmatureDataList[i]->m_szName );
		}
		return vecNameList;
	}

	virtual void Clear()
	{
		for( unsigned int i = 0; i < m_vecArmatureDataList.size(); ++i )
		{
			m_vecArmatureDataList[i]->Clear();
			delete m_vecArmatureDataList[i];
		}
		m_vecArmatureDataList.clear();
		m_mapSubTexturePivots.clear();
	}

	CArmatureData* GetArmatureDataByName( const string& p_szArmatureName )
	{
		for( unsigned int i = 0; i < m_vecArmatureDataList.size(); ++i )
		{
			if( m_vecArmatureDataList[i]->m_szName == p_szArmatureName )
			{
				return m_vecArmatureDataList[i];
			}
		}
		return NULL;
	}

	void AddArmatureData( CArmatureData* p_pArmatureData )
	{
		if( p_pArmatureData == NULL )
			return;
		m_vecArmatureDataList.push_back( p_pArmatureData );
	}

	void RemoveArmatureData( CArmatureData* p_pArmatureData )
	{
		if( p_pArmatureData == NULL )
			return;
		if( p_pArmatureData->m_szName.empty() )
			return;
		RemoveArmatureDataByName( p_pArmatureData->m_szName );
	}

	void RemoveArmatureDataByName( const string& p_szArmatureName )
	{
		for( unsigned int i = 0; i < m_vecArmatureDataList.size(); ++i )
		{
			if( m_vecArmatureDataList[i]->m_szName == p_szArmatureName )
			{
				vector<CArmatureData*>::iterator Ite = m_vecArmatureDataList.begin() + i;
				delete *Ite;
				m_vecArmatureDataList.erase( m_vecArmatureDataList.begin() + i );
				return;
			}
		}
	}

	CPoint* GetSubTexturePivot( const string& p_szSubTextureName )
	{
		map<string, CPoint>::iterator Ite = m_mapSubTexturePivots.find( p_szSubTextureName );
		if( Ite == m_mapSubTexturePivots.end() )
			return NULL;
		return &(Ite->second);
	}

	CPoint	AddSubTexturePivot( f32 p_fX, f32 p_fY, const string& p_szSubTextureName )
	{
		map< string, CPoint >::iterator Ite = m_mapSubTexturePivots.find( p_szSubTextureName );
		if( Ite != m_mapSubTexturePivots.end() )
		{
			// ���Ѵ��ڣ������λ��
			Ite->second.m_fX = p_fX;
			Ite->second.m_fY = p_fY;
			return Ite->second;
		}

		CPoint& pt = m_mapSubTexturePivots[p_szSubTextureName];
		pt.m_fX = p_fX;
		pt.m_fY = p_fY;
		return pt;
	}

	void RemoveSubTexturePivot( const string& p_szSubTextureName )
	{
		map< string, CPoint >::iterator Ite = m_mapSubTexturePivots.find( p_szSubTextureName );
		if( Ite == m_mapSubTexturePivots.end() )
			return;
		m_mapSubTexturePivots.erase( Ite );
	}

	void RemoveAllSubTexturePivots()
	{
		m_mapSubTexturePivots.clear();
	}
};

//-------------------------------------------------------------------------

//-------------------------------------------------------------------------