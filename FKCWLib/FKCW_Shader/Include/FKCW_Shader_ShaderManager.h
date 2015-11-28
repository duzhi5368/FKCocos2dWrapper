/********************************************************************
	created:	2014/10/29
	file base:	FKCW_Shader_ShaderManager
	author:		FreeKnight
	
	purpose:	
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include "FKCW_Shader_Macros.h"
//--------------------------------------------------------------------
// shader Key ö��
#define KeyShaderFlash					"ShaderFlash"
#define KeyShaderBlur					"ShaderBlur"
#define KeyShaderLaser					"ShaderLaser"
#define KeyShaderLighting				"ShaderLighting"
#define KeyShaderMatrix					"ShaderMatrix"
#define KeyShaderShine					"ShaderShine"
#define KeyShaderBloom					"ShaderBloom"
#define KeyShaderCelShading				"ShaderCelShading"
#define KeyShaderEdgeDetection			"ShaderEdgeDetection"
#define KeyShaderOldPhoto				"ShaderOldPhoto"
#define KeyShaderNegative				"ShaderNegative"
#define KeyShaderBrightness				"ShaderBrightness"
#define KeyShaderContrast				"ShaderContrast"
#define KeyShaderSaturation				"ShaderSaturation"
#define KeyShaderBlackWhite				"ShaderBlackWhite"
#define KeyShaderSimpleEdgeDetection	"ShaderSimpleEdgeDetection"
#define KeyShaderEmboss					"ShaderEmboss"
#define KeyShaderSmallBlur				"ShaderSmallBlur"
#define KeyShaderBigBlur				"ShaderBigBlur"
#define KeyShaderSmallSharpen			"ShaderSmallSharpen"
#define KeyShaderBigSharpen				"ShaderBigSharpen"
#define KeyShaderSimpleSharpen			"ShaderSimpleSharpen"
#define KeyShaderDilate					"ShaderDilate"
#define KeyShaderErode					"ShaderErode"
#define KeyShaderLaplacian				"ShaderLaplacian"
#define KeyShaderSobel					"ShaderSobel"
#define KeyShaderPrewitt				"ShaderPrewitt"
#define KeyShaderMotionBlur				"ShaderMotionBlur"
#define KeyShaderBigEmboss				"ShaderBigEmboss"
#define KeyShaderColorRamp				"ShaderColorRamp"
//--------------------------------------------------------------------
class FKCW_Shader_ShaderManager
{
private:
	// ����Key����һ���Ѷ���shader
	static void				LoadCustomShader( const string& p_strKey );
public:
	// ��ȡָ��Key��CCGLProgram
	static CCGLProgram*		ProgramForKey( const string& p_strKey );
private:
	static void genTexCoordOffsets(GLuint width,
		GLuint height, GLfloat* pOutTexCoordOff, GLfloat step = 1.0f );
public:
	// ��������Ч��
	static void		SetFlash( float r, float g, float b, float t );
	// ����ģ��Ч��
	static void		SetBlur( CCSize p_tagNodeSize, CCSize p_tagBlurSize, 
		ccColor4F p_tagBlurSubtract = cc4fTRANSPARENT );
	// ���ù���Ч��
	static void		SetLighting( ccColor4B p_Mul, ccColor3B p_Add );
	// ������ɫ��������
	static void		SetColorMatrix( const kmMat4& p_Mat4 );
	// ���û�ɫͼ
	static void		SetGray();
	// ���ù���Ч��
	// ������	p_fWidth �ڵ���
	//			p_tagLB ģ������λ��
	//			p_tagRT ģ������λ��
	//			p_tagColor �仯ɫ1,2,3
	//			p_tagGradientPositions ���߱仯λ�ã�ȡֵΪ[0,1]֮�䡣ͨ����������߷ֶν���ɫ�ʱ仯
	//			p_fTime ʱ��[0,1]
	static void		SetShine( float p_fWidth, CCPoint p_tagLB, CCPoint p_tagRT,
		ccColor4B p_tagColor1, ccColor4B p_tagColor2, ccColor4B p_tagColor3,
		ccVertex3F p_tagGradientPositions, float p_fTime );
	// ����bloomЧ��
	static void		SetBloom();
	// ���ÿ�ͨЧ��
	static void		SetCelShading( CCSize p_tagNodeSize );
	// ���ñ�Ե���
	static void		SetEdgeDetectionSize( CCSize p_tagNodeSize );
	// ��������ƬЧ��
	static void		SetOldPhoto();
	// ���ø�ɫЧ��
	static void		SetNegative();
	// ���ø߹�
	static void		SetBrightness();
	// ���öԱ�Ч��
	static void		SetContrast();
	// ���ñ���
	static void		SetSaturation();
	// ���úڰ׻�
	static void		SetBlackWhite();
	// ���ü��ױ�ԵЧ��
	static void		SetSimpleEdgeDetection();
	// ���ø���Ч��
	static void		SetEmboss();
	// ���ģ��Ч��
	static void		SetSmallBlur( CCSize p_tagNodeSize );
	// �ض�ģ��Ч��
	static void		SetBigBlur( CCSize p_tagNodeSize );
	// ���ĥɰ
	static void		SetSmallSharpen( CCSize p_tagNodeSize );
	// �ض�ĥɰ
	static void		SetBigSharpen( CCSize p_tagNodeSize );
	// ����ĥɰ
	static void		SetSimpleSharpen( CCSize p_tagNodeSize );
	// ����
	static void		SetDilate( CCSize p_tagNodeSize );
	// ��ʴЧ��
	static void		SetErode( CCSize p_tagNodeSize );
	// Laplacian���
	static void		SetLaplacian( CCSize p_tagNodeSize );
	// Sobel��Ե���
	static void		SetSobel( CCSize p_tagNodeSize );
	// Prewitt��Ե���
	static void		SetPrewitt( CCSize p_tagNodeSize );
	// �˶�ģ��
	static void		SetMotionBlur( CCSize p_tagNodeSize );
	// ��ϸ����
	static void		SetBigEmboss( float t );
	// ��ƬЧ��
	static void		SetColorRamp();
};