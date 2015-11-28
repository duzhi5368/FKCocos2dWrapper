/********************************************************************
	created:	2014/10/31
	file base:	FKCW_Base_ByteBuffer
	author:		FreeKnight
	
	purpose:	
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include "FKCW_Base_Macro.h"
#include "FKCW_Base_Memory.h"
//--------------------------------------------------------------------
class FKCW_Base_ByteBuffer : public CCObject
{
private:
	static const int		DEFAULT_INCREASE_SIZE = 200;		// Ĭ������ֵ
protected:
	uint8*			m_pBuffer;			// ������ָ��
	size_t			m_unReadPos;		// ��λ��
	size_t			m_unWritePos;		// дλ��
	size_t			m_unBufferSize;		// ��������С
	bool			m_bExternal;		// �Ƿ�ʹ���ⲿģʽ
protected:
	// ����һ���ƶ���С���ڴ�
	void			_Reserve( size_t p_unRes );
	// ȷ���������㹻���ܹ�дָ���ֽڴ�С������
	void			_EnsureCanWrite( size_t p_unSize );
public:
	FKCW_Base_ByteBuffer();
	FKCW_Base_ByteBuffer( size_t p_unRes );
	FKCW_Base_ByteBuffer( const FKCW_Base_ByteBuffer& p_Other );
	// ��������һ���ⲿ���ݣ��������Լ��ڷ��ڴ�
	// ������p_szBuffer ������ p_unBufSize ��������С p_unDataLen �ڻ������еĿ�������
	FKCW_Base_ByteBuffer( const char* p_szBuffer, size_t p_unBufSize, size_t p_unDataLen );
	virtual ~FKCW_Base_ByteBuffer();

	// ����һ��Ĭ�ϴ�С�� FKCW_Base_ByteBuffer
	static FKCW_Base_ByteBuffer*		Create();
	// ����һ��ָ����С�� FKCW_Base_ByteBuffer��
	static FKCW_Base_ByteBuffer*		Create( size_t p_unRes );
	// ���ö�дָ��λ��
	void			Clear();
	// ���ػ�����ָ��
	const uint8*	GetBuffer();
	// ��ȡ�ɶ������С
	size_t			GetAvailable();
	// ��ǰ�ƶ���ָ��
	void			Skip( size_t p_unLen );
	// ����ƶ���ָ��
	void			Revoke( size_t p_unLen );
	// �ƶ���ǰ���ݵ��������ײ�
	void			Compact();

	// �ӻ�������ȡָ����С�����ݣ�����ȡLen�����˻�������С������������������ֽ�
	// ����ֵ������ʵ�ʶ�ȡ���ֽ���
	size_t			Read( uint8* p_pBuffer, size_t p_unLen );
	// ��ȡһ��string
	void			Read( string& p_strDest );
	// ��ȡһ��C string
	void			ReadCString( string& p_strDest );
	// ��ȡһ��pascal �ַ�������ǰ�����ֽڱ������ַ�������
	void			ReadPascalString( string& p_strDest );
	// ��ȡһ���ַ��������ǵ������л��ߵ��˽�β�Ż�ֹͣ
	void			ReadLine( string& p_strDest );

	// д��ָ��������
	void			Write( const uint8* p_pData, size_t p_unSize );
	// д��һ��string
	void			Write( const string& p_strData );
	// д��һ��C string
	void			WriteCString( const string& p_strData );
	// д��һ��pascal �ַ�������ǰ�����ֽڱ������ַ������ȣ���ע�⣬�ַ�������β����0
	void			WritePascalString( const string& p_strData );
	// д��һ��string������
	void			WriteLine( const string& p_strData );

	// ��ȡ��ָ��λ��
	size_t			GetReadPos();
	// ���ö�ָ��
	void			SetReadPos( size_t p_unPos );
	// ����дָ��
	void			SetWritePos( size_t p_unPos );


	// �ӻ����ж�ȡ sizeof(T) ��С������
	template< typename T > T Read()
	{
		if(m_unReadPos + sizeof(T) > m_unWritePos)
			return (T)0;
		T ret = *(T*)&m_pBuffer[m_unReadPos];
		m_unReadPos += sizeof(T);
		return ret;
	}
	// �򻺳�����дһЩ����
	template<typename T> void Write(const T& data) 
	{
		size_t new_size = m_unWritePos + sizeof(T);
		if(new_size > m_unBufferSize) 
		{
			new_size = (new_size / DEFAULT_INCREASE_SIZE + 1) * DEFAULT_INCREASE_SIZE;
			_Reserve(new_size);
		}

		*(T*)&m_pBuffer[m_unWritePos] = data;
		m_unWritePos += sizeof(T);
	}
	// �򻺳���д��һ��vector
	template<typename T> size_t WriteVector(const vector<T>& v) 
	{
		for(typename vector<T>::const_iterator i = v.begin(); i != v.end(); i++) 
		{
			Write<T>(*i);
		}
		return v.size();
	}
	// �ӻ�������ȡһ��vector
	template<typename T> size_t ReadVector(size_t vsize, vector<T>& v) 
	{
		v.clear();
		while(vsize--) 
		{
			T t = Read<T>();
			v.push_back(t);
		}
		return v.size();
	}
	// �򻺳���д��һ��list
	template<typename T> size_t WriteList(const list<T>& v) 
	{
		for(typename list<T>::const_iterator i = v.begin(); i != v.end(); i++) 
		{
			Write<T>(*i);
		}
		return v.size();
	}
	// �ӻ�������ȡһ��vector
	template<typename T> size_t ReadList(size_t vsize, list<T>& v) 
	{
		v.clear();
		while(vsize--) 
		{
			T t = Read<T>();
			v.push_back(t);
		}
		return v.size();
	}
	// �򻺳���д��һ��map
	template <typename K, typename V> size_t WriteMap(const map<K, V>& m) 
	{
		for(typename map<K, V>::const_iterator i = m.begin(); i != m.end(); i++) 
		{
			Write<K>(i->first);
			Write<V>(i->second);
		}
		return m.size();
	}
	// �ӻ�������ȡһ��map
	template <typename K, typename V> size_t readMap(size_t msize, map<K, V>& m) 
	{
		m.clear();
		while(msize--) {
			K k = Read<K>();
			V v = Read<V>();
			m.insert(make_pair(k, v));
		}
		return m.size();
	}
};