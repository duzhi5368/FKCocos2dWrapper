//*************************************************************************
//	��������:	2015-1-8
//	�ļ�����:	Test_Shader_Demo2.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../resource.h"
#include "../TestScene.h"
#include "../../../FKCWLib/FKCocos2dxWrapper.h"
//-------------------------------------------------------------------------
class CTest_Shader_Demo2Layer : public CCLayer
{
public:
	virtual bool init()
	{
		do 
		{
			CC_BREAK_IF( !CCLayer::init() );

			m_fPassedTime = 0;

			// ���������ֳ�ʼ������
			for( unsigned int i = 0; i < 6; ++i )
			{
				for( unsigned int j = 0; j < 3; ++j )
				{
					CreateSprite( i,j );
				}
			}

			return true;
		} while ( 0 );
		return false;
	}

	virtual void onEnter()
	{
		CCLayer::onEnter();
		this->scheduleUpdate();
	}
	virtual void onExit()
	{
		this->unscheduleUpdate();
		CCLayer::onExit();
	}
public:
	void CreateSprite( int i, int j )
	{
		CCSprite* p = CCSprite::create( s_szMidCocosLogoPicPath );
		p->setPosition( ccp(i * 180 + 28 + 75, 180 * j + 75 + 40) );

		int nType = i + j * 6;
		if( nType == 0 )
		{
			// ԭ�ļ���donothing
			CCLabelTTF* pLabel = CCLabelTTF::create(A2U("ԭ�ļ�").c_str(),"Arial", 26);
			pLabel->setPosition( ccp(75, -15));
			p->addChild( pLabel );
		}
		else if( nType == 1 )
		{
			p->setShaderProgram(FKCW_Shader_ShaderManager::ProgramForKey( KeyShaderSmallBlur ));
			FKCW_Shader_ShaderManager::SetSmallBlur( p->getContentSize() );

			CCLabelTTF* pLabel = CCLabelTTF::create(A2U("���ģ��").c_str(),"Arial", 26);
			pLabel->setPosition( ccp(75, -15));
			p->addChild( pLabel );
		}
		else if( nType == 2 )
		{
			p->setShaderProgram(FKCW_Shader_ShaderManager::ProgramForKey( KeyShaderBigBlur ));
			FKCW_Shader_ShaderManager::SetBigBlur( p->getContentSize() );

			CCLabelTTF* pLabel = CCLabelTTF::create(A2U("�ض�ģ��").c_str(),"Arial", 26);
			pLabel->setPosition( ccp(75, -15));
			p->addChild( pLabel );
		}
		else if( nType == 3 )
		{
			p->setShaderProgram(FKCW_Shader_ShaderManager::ProgramForKey( KeyShaderSmallSharpen ));
			FKCW_Shader_ShaderManager::SetSmallSharpen(  p->getContentSize() );

			CCLabelTTF* pLabel = CCLabelTTF::create(A2U("���ĥɰ").c_str(),"Arial", 26);
			pLabel->setPosition( ccp(75, -15));
			p->addChild( pLabel );
		}
		else if( nType == 4 )
		{
			p->setShaderProgram(FKCW_Shader_ShaderManager::ProgramForKey( KeyShaderBigSharpen ));
			FKCW_Shader_ShaderManager::SetBigSharpen( p->getContentSize() );

			CCLabelTTF* pLabel = CCLabelTTF::create(A2U("�ض�ĥɰ[bug]").c_str(),"Arial", 26);
			pLabel->setPosition( ccp(75, -15));
			p->addChild( pLabel );
		}
		else if( nType == 5 )
		{
			p->setShaderProgram(FKCW_Shader_ShaderManager::ProgramForKey( KeyShaderSimpleSharpen ));
			FKCW_Shader_ShaderManager::SetSimpleSharpen( p->getContentSize() );

			CCLabelTTF* pLabel = CCLabelTTF::create(A2U("����ĥɰ").c_str(),"Arial", 26);
			pLabel->setPosition( ccp(75, -15));
			p->addChild( pLabel );
		}
		else if( nType == 6 )
		{
			p->setShaderProgram(FKCW_Shader_ShaderManager::ProgramForKey( KeyShaderDilate ));
			FKCW_Shader_ShaderManager::SetDilate( p->getContentSize() );

			CCLabelTTF* pLabel = CCLabelTTF::create(A2U("����Ч��").c_str(),"Arial", 26);
			pLabel->setPosition( ccp(75, -15));
			p->addChild( pLabel );
		}
		else if( nType == 7 )
		{
			p->setShaderProgram(FKCW_Shader_ShaderManager::ProgramForKey( KeyShaderErode ));
			FKCW_Shader_ShaderManager::SetErode( p->getContentSize() );

			CCLabelTTF* pLabel = CCLabelTTF::create(A2U("��ʴЧ��").c_str(),"Arial", 26);
			pLabel->setPosition( ccp(75, -15));
			p->addChild( pLabel );
		}
		else if( nType == 8 )
		{
			p->setShaderProgram(FKCW_Shader_ShaderManager::ProgramForKey( KeyShaderLaplacian ));
			FKCW_Shader_ShaderManager::SetLaplacian( p->getContentSize() );

			CCLabelTTF* pLabel = CCLabelTTF::create(A2U("Laplacian���").c_str(),"Arial", 26);
			pLabel->setPosition( ccp(75, -15));
			p->addChild( pLabel );
		}
		else if( nType == 9 )
		{
			//��shader�ڰ�׿�»ᱨ��.�����Ѽ�¼
#if CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID

			p->setShaderProgram(FKCW_Shader_ShaderManager::ProgramForKey( KeyShaderSobel ));
			FKCW_Shader_ShaderManager::SetSobel( p->getContentSize() );
			CCLabelTTF* pLabel = CCLabelTTF::create(A2U("Sobel���").c_str(),"Arial", 26);
#else
			CCLabelTTF* pLabel = CCLabelTTF::create(A2U("Sobel-BUG").c_str(),"Arial", 26);
#endif
			
			pLabel->setPosition( ccp(75, -15));
			p->addChild( pLabel );

			
		}
		else if( nType == 10 )
		{
			//��shader�ڰ�׿�»ᱨ��.�����Ѽ�¼
#if CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID

			p->setShaderProgram(FKCW_Shader_ShaderManager::ProgramForKey( KeyShaderPrewitt ));
			FKCW_Shader_ShaderManager::SetPrewitt( p->getContentSize() );
			CCLabelTTF* pLabel = CCLabelTTF::create(A2U("Prewitt���").c_str(),"Arial", 26);
#else
			CCLabelTTF* pLabel = CCLabelTTF::create(A2U("Prewitt-BUG").c_str(),"Arial", 26);
#endif
			
			pLabel->setPosition( ccp(75, -15));
			p->addChild( pLabel );

			
		}
		else if( nType == 11 )
		{
			p->setShaderProgram(FKCW_Shader_ShaderManager::ProgramForKey( KeyShaderMotionBlur ));
			FKCW_Shader_ShaderManager::SetMotionBlur( p->getContentSize() );

			CCLabelTTF* pLabel = CCLabelTTF::create(A2U("�˶�ģ��").c_str(),"Arial", 26);
			pLabel->setPosition( ccp(75, -15));
			p->addChild( pLabel );
		}
		else if( nType == 12 )
		{
			p->setShaderProgram(FKCW_Shader_ShaderManager::ProgramForKey( KeyShaderBigEmboss ));

			CCLabelTTF* pLabel = CCLabelTTF::create(A2U("��̬����").c_str(),"Arial", 26);
			pLabel->setPosition( ccp(75, -15));
			p->addChild( pLabel );
		}
		else if( nType == 13 )
		{
			p->setShaderProgram(FKCW_Shader_ShaderManager::ProgramForKey( KeyShaderColorRamp ));
			FKCW_Shader_ShaderManager::SetColorRamp();

			CCLabelTTF* pLabel = CCLabelTTF::create(A2U("��ƬЧ��").c_str(),"Arial", 26);
			pLabel->setPosition( ccp(75, -15));
			p->addChild( pLabel );
		}
		else if( nType == 14 )
		{
			CCLabelTTF* pLabel = CCLabelTTF::create(A2U("Todo").c_str(),"Arial", 26);
			pLabel->setPosition( ccp(75, -15));
			p->addChild( pLabel );
		}
		else if( nType == 15 )
		{
			CCLabelTTF* pLabel = CCLabelTTF::create(A2U("Todo").c_str(),"Arial", 26);
			pLabel->setPosition( ccp(75, -15));
			p->addChild( pLabel );
		}
		else if( nType == 16 )
		{
			CCLabelTTF* pLabel = CCLabelTTF::create(A2U("Todo").c_str(),"Arial", 26);
			pLabel->setPosition( ccp(75, -15));
			p->addChild( pLabel );
		}
		else if( nType == 17 )
		{
			CCLabelTTF* pLabel = CCLabelTTF::create(A2U("Todo").c_str(),"Arial", 26);
			pLabel->setPosition( ccp(75, -15));
			p->addChild( pLabel );
		}

		addChild( p );
	}

	void update( float p_fDetla )
	{
		m_fPassedTime += p_fDetla;

		FKCW_Shader_ShaderManager::SetBigEmboss( m_fPassedTime );
	}

public:
	CREATE_FUNC( CTest_Shader_Demo2Layer );
private:
	float m_fPassedTime;
};
//-------------------------------------------------------------------------
CREATE_TEST_SCENE_CLASS(Shader, Demo2, ShaderЧ������2��)
	//-------------------------------------------------------------------------