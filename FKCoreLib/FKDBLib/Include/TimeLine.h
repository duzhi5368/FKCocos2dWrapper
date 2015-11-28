//*************************************************************************
//	��������:	2014-8-11   15:12
//	�ļ�����:	TimeLine.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "BaseMacro.h"
#include <vector>
#include "Frame.h"
using std::vector;
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
// ʱ����
class CTimeLine
{
public:
	vector<CFrame*>		m_vecFrameList;			// ��ʱ�����ϵĹؼ�֡�б�
	f32					m_fDuration;			// ��ʱ������ʱ��
	f32					m_fScale;				// ���¼����ű�
public:
	CTimeLine()
		: m_fScale ( 1.0f )
		, m_fDuration( 0.0f )
	{
		m_vecFrameList.clear();
	}
	virtual ~CTimeLine()
	{
		Clear();
	}
public:
	virtual void Clear()
	{
		for( unsigned int i = 0; i < m_vecFrameList.size(); ++i )
		{
			m_vecFrameList[i]->Clear();
			delete m_vecFrameList[i];
		}
		m_vecFrameList.clear();
	}

	virtual void AddFrame( CFrame* p_pFrame )
	{
		if( p_pFrame == NULL )
			return;
		m_vecFrameList.push_back( p_pFrame );
	}
};
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------