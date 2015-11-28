//-------------------------------------------------------------------------
#include "FKRenderTextMgr.h"
//-------------------------------------------------------------------------
FKRenderTextMgr::FKRenderTextMgr()
{

}
//-------------------------------------------------------------------------
FKRenderTextMgr::~FKRenderTextMgr()
{

}
//-------------------------------------------------------------------------
// ������Ⱦ����
// ������szString ����
// ������szFontName ��������
// ������nFontSize �����С
// ������tagDimentions ����ߴ�
// ������bIsBmpFont �Ƿ���BMP����
IRenderText* FKRenderTextMgr::CreateRenderText( const char* szString, const char* szFontName, 
								 int nFontSize,  CCSize tagDimentions, bool bIsBMPFont )
{
	static RENDER_OBJ_ID s_RenderTextID = 0;
	if( ++s_RenderTextID == 0 )
		s_RenderTextID++;

	FKRenderText* pRenderText = new FKRenderText( s_RenderTextID );
	if( pRenderText == NULL )
		return NULL;

	if( bIsBMPFont )
		pRenderText->CreateByBMP( szString, szFontName, nFontSize, tagDimentions );
	if( !bIsBMPFont )
		pRenderText->Create( szString, szFontName, nFontSize, tagDimentions );

	m_mapRenderText[s_RenderTextID] = ( IRenderText* )pRenderText;

	return pRenderText;
}
//-------------------------------------------------------------------------
// ɾ����Ⱦ����
// ������pRenderText ��Ҫɾ������Ⱦ����
bool FKRenderTextMgr::RemoveRenderText( IRenderText* pRenderText )
{
	if( pRenderText == NULL )
		return false;
	RENDER_OBJ_ID id = ((FKRenderText*)pRenderText)->GetID();
	RenderTextMap::iterator Ite = m_mapRenderText.find( id );
	if( Ite == m_mapRenderText.end() )
		return false;
	m_mapRenderText.erase( id );

	pRenderText->Release();
	return true;
}
//-------------------------------------------------------------------------
// ɾ����Ⱦ����
// ������id ΨһID
bool FKRenderTextMgr::RemoveRenderTextByID( RENDER_OBJ_ID id )
{
	if( id == 0 )
		return false;
	RenderTextMap::iterator Ite = m_mapRenderText.find( id );
	if( Ite == m_mapRenderText.end() )
		return false;
	IRenderText* pRenderText = Ite->second;
	m_mapRenderText.erase( id );

	pRenderText->Release();
	return true;
}
//-------------------------------------------------------------------------