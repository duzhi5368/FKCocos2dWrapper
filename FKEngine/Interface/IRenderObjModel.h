//*************************************************************************
//	��������:	2015-1-17
//	�ļ�����:	IRenderObjModel.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../../FKCWLib/FKCocos2dxWrapper.h"
//-------------------------------------------------------------------------
// һ����Ⱦ����ģ�Ͷ�Ӧһ���ļ�
class IRenderObjModel
{
public:
	// ����һ���ļ�
	virtual bool	LoadFromFKOFile( const string& strFKOFileName ) = 0;
	// ���汾ģ�͵�һ���ļ���
	virtual bool	SaveToFKOFile( const string& strFKOFileName ) = 0;

	// ���һ�����
	virtual bool	AddPart( const string& strName, const string& strFile, int nDepth ) = 0;
	// �Ƴ�һ�����
	virtual void	RemovePart( const string& strName ) = 0;

	// ���һ���ҽӶ���
	virtual bool	AddLocator( const string& strLocatorName, CCPoint& ptOffset ) = 0;
	// ɾ��һ���ҽӶ���
	virtual void	RemoveLocator( const string& strLocatorName ) = 0;

	// �����Ч�ڵ�
	virtual bool	AddEffect( const string& strEffectName, const string& strLocatorName, 
		const string& strEffectFileName, CCPoint& ptOffset, ccColor4B& color, CCPoint& scale, int nDepth ) = 0;
	// ɾ����Ч�ڵ�
	virtual void	RemoveEffect( const string& strEffectName ) = 0;
};