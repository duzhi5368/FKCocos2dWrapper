//*************************************************************************
//	��������:	2015-1-17
//	�ļ�����:	FKRenderObjModel.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../FKEngineCommonHead.h"
//-------------------------------------------------------------------------
// һ��RenderObjModel��Ӧһ���ļ�
class FKRenderObjModel : public CCObject
{
public:
	// �������
	struct SObjPart
	{
		string		m_strName;		// ������
		string		m_strFile;		// �����ļ���
		int			m_nDepth;		// �������
		SObjPart()
		{
			m_strName.clear();
			m_strFile.clear();
			m_nDepth = 0;
		}
	};
	// �󶨶���
	struct SObjLocator
	{
		string		m_strName;		// ������
		CCPoint		m_tagOffset;	// ƫ��ֵ
		SObjLocator()
		{
			m_strName.clear();
			m_tagOffset = CCPointZero;
		}
	};
	// ��Ч����
	struct SObjEffect
	{
		string		m_strName;		// ��Ч��
		string		m_strFileName;	// ��Ч�ļ���
		string		m_strLocator;	// ��Ч�󶨵Ľڵ���
		CCPoint		m_tagOffset;	// ƫ��ֵ
		CCPoint		m_tagScale;		// ����ֵ
		ccColor4B	m_tagColor;		// ��ɫֵ
		int			m_nDepth;		// ���
		SObjEffect()
		{
			m_strName.clear();
			m_strFileName.clear();
			m_strLocator.clear();
			m_tagOffset = CCPointZero;
			m_tagScale = ccp( 1.0f, 1.0f );
			m_tagColor = ccc4(255,255,255,255);
			m_nDepth = 0;
		}
	};

	typedef map<string, SObjPart>			ObjPartMap;
	typedef map<string, SObjLocator>		ObjLocatorMap;
	typedef map<string, SObjEffect>			ObjEffectMap;
public:
	FKRenderObjModel();
	~FKRenderObjModel();
private:
	string								m_strObjName;		// ������
	int									m_nVersion;			// �ļ��汾��
public:
	CCPoint								m_pOffset;			// ƫ����
	ObjPartMap							m_mapObjParts;		// �����б�
	ObjEffectMap						m_mapObjEffects;	// ��Ч�б�
	ObjLocatorMap						m_mapObjLocators;	// �󶨶����б�
public:
	// ����һ���ļ�
	virtual bool	LoadFromFKOFile( const string& strFKOFilePathName );
	// ���汾ģ�͵�һ���ļ���
	virtual bool	SaveToFKOFile( const string& strFKOFilePathName );

	// ���һ�����
	virtual bool	AddPart( const string& strName, const string& strFile, int nDepth );
	// �Ƴ�һ�����
	virtual void	RemovePart( const string& strName );

	// ���һ���ҽӶ���
	virtual bool	AddLocator( const string& strLocatorName, CCPoint& ptOffset );
	// ɾ��һ���ҽӶ���
	virtual void	RemoveLocator( const string& strLocatorName );

	// �����Ч�ڵ�
	virtual bool	AddEffect( const string& strEffectName, const string& strLocatorName, 
		const string& strEffectFileName, CCPoint& ptOffset, ccColor4B& color, CCPoint& scale, int nDepth );
	// ɾ����Ч�ڵ�
	virtual void	RemoveEffect( const string& strEffectName );

private:
	// ����10001�汾���ļ�
	virtual bool	__SaveToFKOFile_10001( const string& strFKOFilePathName );
};