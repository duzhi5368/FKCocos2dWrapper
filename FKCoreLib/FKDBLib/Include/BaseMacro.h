//*************************************************************************
//	��������:	2014-8-11   10:25
//	�ļ�����:	BaseMacro.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include <vector>
//-------------------------------------------------------------------------
// ���ݸ�ʽ����
//-------------------------------------------------------------------------
typedef float			f32;
typedef unsigned int	uint;
typedef unsigned char	uc8;
typedef char			c8;
//-------------------------------------------------------------------------
// ���ú�
#ifndef SAFE_DELETE
#define SAFE_DELETE(p)            do { if(p) { delete (p); (p) = 0; } } while(0)
#endif
//-------------------------------------------------------------------------
// ��ʾ������ ����Ŀ�Ĳ���
#ifndef FK_OUT
#define FK_OUT
#endif
//-------------------------------------------------------------------------
#ifndef FK_INLINE

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#define FK_INLINE	inline
#else
#define FK_INLINE	__forceinline
#endif

#endif
//-------------------------------------------------------------------------
// float����ֵ�ȽϷ�ֵ
#ifndef FK_EPSILON
#define FK_EPSILON     1.192092896e-07F
#endif
//-------------------------------------------------------------------------
template< typename T >
int GetVectorItemIndex( std::vector<T>& vec, const T& value )
{
	for( unsigned int i = 0; i < vec.size(); ++i )
	{
		if( vec[i] == value )
		{
			return static_cast<int>(i);
		}
	}
	return -1;
}
//-------------------------------------------------------------------------