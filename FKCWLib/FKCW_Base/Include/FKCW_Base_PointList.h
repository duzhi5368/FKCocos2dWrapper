//*************************************************************************
//	��������:	2014-10-25
//	�ļ�����:	FKCW_Base_PointList.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	�������������б�
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_Base_Macro.h"
//--------------------------------------------------------------------
class FKCW_Base_PointList : public CCObject
{
private:
	CCPoint*		m_pBuffer;		// ������
	int				m_nCount;		// �����
	int				m_nCapacity;	// ��������ģ�����char�ģ�
public:
	FKCW_Base_PointList();
	virtual ~FKCW_Base_PointList();
	static FKCW_Base_PointList* Create();
public:
	// ���һ����
	void		AddPoint( float x, float y );
	void		AddPoint( CCPoint p ){ AddPoint( p.x, p.y ); }
	// ���һ������
	void		AddPoints( FKCW_Base_PointList& p_pList );
	// ��������ɾ��һ����
	void		DeletePointAt( int p_nIndex );
	// ��ȡ������
	CCPoint*	GetBuffer(){ return m_pBuffer; }
	// ��ȡ������
	int			GetCount(){ return m_nCount; }
	// ���ȫ����
	void		Clear();
	//  ��ȡָ������λ��һ����
	CCPoint		GetPointAt( int p_nIndex );
};