//*************************************************************************
//	��������:	2014-10-28
//	�ļ�����:	FKCW_Base_ResourceLoaderListener.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	��Դ���ؽ��ȼ�����
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_Base_Macro.h"
//-------------------------------------------------------------------------
class FKCW_Base_ResourceLoaderListener
{
public:
	// ����Դ�ڼ���ʱ��֪ͨ����
	// ������p_fProgress ��ǰ���ȡ�ֵ��0-100֮��
	// ������p_fDelta ���ϴε��ø�֪ͨ���� ֮��ļ��ʱ��
	virtual void		OnResourceLoadingProgress( float p_fProgress, float p_fDelta ) = 0;
	// ����Դ�������ʱ��֪ͨ
	virtual void		OnResourceLoadingDone() = 0;
};