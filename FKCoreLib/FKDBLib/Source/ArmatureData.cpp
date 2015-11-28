//-------------------------------------------------------------------------
#include "../Include/ArmatureData.h"
#include <algorithm>
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
void CArmatureData::SortBoneDataList()
{
	if( m_vecBoneDataList.empty() )
		return;

	vector< std::pair<int, CBoneData*> >		vecTmp;	// ������ȱ�

	for( unsigned int i = 0; i < m_vecBoneDataList.size(); ++i )
	{
		CBoneData* pBoneData = m_vecBoneDataList[i];
		int nLevel = 0;								// ������Ȳ㼶
		CBoneData* pParentData = pBoneData;
		// �ݹ��Ҹ��ڵ�
		while( pParentData && !( pParentData->m_szParent.empty() ) )
		{
			nLevel++;
			pParentData = GetBoneDataByName( pParentData->m_szParent );
		}
		vecTmp.push_back( std::make_pair( nLevel, pBoneData ) );
	}

	// ����󣬸��ڵ�λ��vectorǰ�ˡ����Խ�ߵĽڵ�Խλ��β��
	std::sort( vecTmp.begin(), vecTmp.end(), SortBoneFunc );

	unsigned int i = vecTmp.size();
	while( i-- )
	{
		// �������Լ��� boneList ��
		m_vecBoneDataList[i] = vecTmp[i].second;
	}
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------