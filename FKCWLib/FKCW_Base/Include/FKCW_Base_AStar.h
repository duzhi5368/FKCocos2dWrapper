//*************************************************************************
//	��������:	2014-11-28
//	�ļ�����:	FKCW_Base_AStar.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_Base_Macro.h"
//-------------------------------------------------------------------------
struct SCoord
{
	int _x;
	int _y;

	SCoord()
	{
	}
	
	SCoord(int x,int y):
		_x(x),
		_y(y)
	{
	}

	inline bool operator == (const SCoord& coord)const
	{
		return this->_x == coord._x && this->_y == coord._y;
	}

	inline bool operator != (const SCoord& coord)const
	{
		return this->_x != coord._x || this->_y != coord._y;
	}

	inline void operator += (const SCoord& coord)
	{
		this->_x += coord._x ;
		this->_y += coord._y;
	}
};
//-------------------------------------------------------------------------
struct SStepData
{
	int _h;//H ��ʾ��ָ���ķ����ƶ����յ� B ��Ԥ�ƺķ� (H �кܶ���㷽��, ���������趨ֻ�������������ƶ�).
	int _g;//G ��ʾ����� A �ƶ���������ָ��������ƶ��ķ� (����б�����ƶ�).

	SCoord _coord;
	SCoord _parentCoord;

	SStepData()
	{
	}

	SStepData(const SCoord& coord):
		_coord(coord)
	{
	}
};
//-------------------------------------------------------------------------
/**
 * A* Ѱ·�㷨
 * �����ȵ���SetMapSize���õ�ͼ��С
 */
class FKCW_Base_AStar
{
public:
	FKCW_Base_AStar();

	///���õ�ͼ�Ĵ�С,������һ��ʼ����
	bool SetMapSize(int row,int col);
	 
	/**
	 * ����·��
	 * @return true - �д���㵽�յ��·��,����GetRoute�������·��; false - �Ҳ�������㵽�յ��·�� 
	 */
	bool ComputeRoute();
	// ��ô���㵽�յ��·��
	bool GetRoute(std::vector<SCoord>* list);
	// �����ϰ���
	void SetObstacle(const SCoord& coord);
	// ȡ���ϰ���
	void CancleObstacle(const SCoord& coord);
	// ��������ϰ���
	void ClearObstacles();
	// �ж�������������û���ϰ���
	bool IsObstacle(const SCoord& coord);
	// ���ÿɲ������߶Խ���
	void SetDiagonalEnable(bool bEnable){m_numSurround = bEnable?8:4;}
	// ��ǰ�Ƿ�����߶Խ���
	bool IsDiagonalEnable(){ return (m_numSurround == 8); }
	int  GetRow()						{return m_row;}
	int  GetCol()						{return m_col;}
	void SetStart(const SCoord& coord)  {m_start  = coord;}
	void SetTarget(const SCoord& coord) {m_target = coord;}
	const SCoord& GetStart()            {return m_start;}
	const SCoord& GetTarget()           {return m_target;}
private:
	unsigned char*			m_map;
	int						m_row;
	int						m_col;
	SCoord					m_target;
	SCoord					m_start;

	//�ڼ������ܷ����ʱ��ʹ��
	int						m_numSurround;
	int						m_gAdd[8];
	SCoord					m_surround[8];
	
	std::list<SStepData>	m_openList;
	std::list<SStepData>	m_closeList;
	
	bool		__PopBestStep(SStepData* pSD); 
	bool		__IsInList(std::list<SStepData>& list, const SCoord& coord);
	bool		__JudgeSurround(const SCoord& coord,const SCoord& parentCoord, int G);
	SStepData*	__FindFromList(std::list<SStepData>& list, const SCoord& coord);
	int			__ComputeH(const SCoord& coord) {return abs(m_target._x-coord._x)*10 + abs(m_target._y-coord._y)*10;}
};
//-------------------------------------------------------------------------