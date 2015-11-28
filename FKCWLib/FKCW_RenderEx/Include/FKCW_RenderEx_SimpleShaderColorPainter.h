//*************************************************************************
//	��������:	2014-11-28
//	�ļ�����:	FKCW_RenderEx_SimpleShaderColorPainter.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_RenderEx_Macros.h"
//-------------------------------------------------------------------------
const GLchar* const szColorChangeSource =
				"#ifdef GL_ES													  \n \
				precision mediump float;										  \n \
				#endif															  \n \
				uniform sampler2D u_texture;									  \n \
				varying vec2 v_texCoord;										  \n \
				varying vec4 v_fragmentColor;									  \n \
				uniform mat4 matrixEffect;										  \n \
				void main(void)													  \n \
				{																  \n \
					gl_FragColor = texture2D(u_texture, v_texCoord)*matrixEffect*v_fragmentColor; \n \
				}";
//-------------------------------------------------------------------------
enum EffectSelect
{
	ES_NONE              = 0,  //û����Ч
	ES_BLACK_AND_WHITE   = 1,  //�ڰ׻�
	ES_OLD_PHOTOS        = 2,  //����Ƭ
	ES_INVERT            = 3,  //����
	ES_BURNS			 = 4,  //���ˣ�ƫ�죩
	ES_POISONING		 = 5,  //�ж���ƫ�̣�
	ES_COLD			     = 6,  //���䣨ƫ����

	ES_USER_DEFINED //�Զ������Ч������Ŵ����￪ʼ
};
//-------------------------------------------------------------------------
struct Matrix44
{
	GLfloat _matrix[16];
};
//-------------------------------------------------------------------------
struct EffectListNode
{
	CCNode* _pNode;
	GLint   _uniformMatrix;
	int		_effectSelect;
};
//-------------------------------------------------------------------------
/**
 * ����ģʽ�ļ򵥵�Ƭ����ȾЧ����
 * �ȵ��� addEffectNode ������Ҫ��Ⱦ��Ч�Ľڵ�
 * Ȼ����Ե��� setEffect ������Ч�� getEffectSelect�ĵ���Чѡ��
 */
class FKCW_RenderEx_SimpleShaderColorPainter
{
public:
	static FKCW_RenderEx_SimpleShaderColorPainter* getInstance();
	static void destroy();

	/**
	 * �����Զ������Ч����
	 *@param matrix ��Ч����
	 *@return ���ؽڵ��� m_nodeList �����,ʧ���򷵻�-1
	 */
	int addEffectMatrix(const Matrix44& matrix);

	/**
	 * ���ýڵ����Ч����������Ƚϸ�Ч
	 *@param nodeIndex �ڵ���ţ���addEffectNode�����ķ���ֵ
	 *@param sel ��Ч��ѡ��
	 */
	bool setEffect(unsigned int nodeIndex,unsigned int sel);

	/**
	 * ���ýڵ����Ч������ʹ�ø��Ӹ�Ч�� bool setEffect(int nodeIndex,int sel)
	 * �����ȵ��� addEffectNode ����Ҫ��Ⱦ��Ч�Ľڵ�ӵ�������
	 *@param pNode �ڵ�ָ��
	 *@param sel ��Ч��ѡ��
	 */
	bool setEffect(CCNode* pNode,unsigned int sel);
	// ������Ҫ��Ⱦ��Ч�Ľڵ�
	int  addEffectNode(CCNode* pNode);
	// �õ��ڵ����Чѡ����û�д˽ڵ��򷵻�-1����������Ƚϸ�Ч
	int  getEffectSelect(unsigned int nodeInde);
	// �õ��ڵ����Чѡ����û�д˽ڵ��򷵻�-1������ʹ�ø��Ӹ�Ч�� int getEffectSelect(int nodeInde)
	int  getEffectSelect(CCNode* pNode);
	
private:
	static FKCW_RenderEx_SimpleShaderColorPainter* s_instance;

	FKCW_RenderEx_SimpleShaderColorPainter();
	~FKCW_RenderEx_SimpleShaderColorPainter(){}

	std::vector<Matrix44>		m_matrices;
	std::vector<EffectListNode> m_nodeList;
};