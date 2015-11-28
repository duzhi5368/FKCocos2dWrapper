//*************************************************************************
//	��������:	2014-11-26
//	�ļ�����:	SceneMacro.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
// ����ѡ�����������
const static unsigned int TEST_MENU_LINE_SPACE	= 40;
//-------------------------------------------------------------------------
// ���Գ�������
enum ENUM_TEST_SCENE_TYPE
{
	eTestSceneType_Default	= 0,

	eTestSceneType_GR_Examples,

	eTestSceneType_Font_Test,

	eTestSceneType_Database_Database,

	eTestSceneType_SimpleNet_NetObj,

	eTestSceneType_Json_Json,

	eTestSceneType_SceneEx_UISceneEx,

	eTestSceneType_3D_FKSimpleModel,

	eTestSceneType_RichHtml_HtmlLabel,

	eTestSceneType_Story_StoryLayer,

	eTestSceneType_Pixel_Demo,

	eTestSceneType_Shader_Demo1,
	eTestSceneType_Shader_Demo2,

	eTestSceneType_Network_FileDownLoader,
	eTestSceneType_Network_HttpGet,
	eTestSceneType_Network_TCP,
	eTestSceneType_Network_UDP,

	eTestSceneType_UI_AutoRenderMenuItemSprite,
	eTestSceneType_UI_MenuItemColor,
	eTestSceneType_UI_ToastLayer,
	eTestSceneType_UI_SimpleRookieGuider,
	eTestSceneType_UI_DynamicNumLabel,
	eTestSceneType_UI_MenuItemProgressTimer,
	eTestSceneType_UI_ProgressIndicator,
	eTestSceneType_UI_ScrollableLayer,
	eTestSceneType_UI_Table,
	
	eTestSceneType_Action_Blur,
	eTestSceneType_Action_ClipIn,
	eTestSceneType_Action_Count,
	eTestSceneType_Action_Flash,
	eTestSceneType_Action_Missile,
	eTestSceneType_Action_Shake,
	eTestSceneType_Action_Shine,
	eTestSceneType_Action_TreeFadeIn,
	eTestSceneType_Action_TreeFadeOut,
	eTestSceneType_Action_TrailMoveTo,
	eTestSceneType_Action_CallFuncT,
	eTestSceneType_Action_Curl,
	eTestSceneType_Action_Suck,

	eTestSceneType_UIWidget_DrawZOrder,
	eTestSceneType_UIWidget_Button,
	eTestSceneType_UIWidget_CheckBox,
	eTestSceneType_UIWidget_ColorView,
	eTestSceneType_UIWidget_ControlView,
	eTestSceneType_UIWidget_ExpandableListView,
	eTestSceneType_UIWidget_GradientView,
	eTestSceneType_UIWidget_ImageView,
	eTestSceneType_UIWidget_GridPageView,
	eTestSceneType_UIWidget_GridView,
	eTestSceneType_UIWidget_Label,
	eTestSceneType_UIWidget_Layout,
	eTestSceneType_UIWidget_ProgressBar,
	eTestSceneType_UIWidget_ScrollView,
	eTestSceneType_UIWidget_ToggleView,
	eTestSceneType_UIWidget_ListView,
	eTestSceneType_UIWidget_Slider,
	eTestSceneType_UIWidget_TextRich,
	eTestSceneType_UIWidget_LabelAtlas,
	eTestSceneType_UIWidget_PageView,
	eTestSceneType_UIWidget_TableView,

	eTestSceneType_Base_AStar,
	eTestSceneType_Base_UtilsI,
	eTestSceneType_Base_Encode,
	eTestSceneType_Base_DrawingPrimitives,
	eTestSceneType_Base_CVSLoader,
	eTestSceneType_Base_DecodeHtml,
	eTestSceneType_Base_Localization,
	eTestSceneType_Base_Memory,
	eTestSceneType_Base_PinYin,
	eTestSceneType_Base_ResourceLoader,
	eTestSceneType_Base_SecureUserDefault,
	eTestSceneType_Base_FileZip,

	eTestSceneType_RenderEx_GradientSprite,
	eTestSceneType_RenderEx_TiledSprite,
	eTestSceneType_RenderEx_LaserSprite,
	eTestSceneType_RenderEx_TurnCardSprite,
	eTestSceneType_RenderEx_EraserSprite,
	eTestSceneType_RenderEx_ScrollingBackgroundNode,
	eTestSceneType_RenderEx_JoystickNode,
	eTestSceneType_RenderEx_NumberCountNode,
	eTestSceneType_RenderEx_SimpleShaderColorPainter,
	eTestSceneType_RenderEx_CatmullRomSprite,
	eTestSceneType_RenderEx_SwayNode,
	eTestSceneType_RenderEx_BlurTextureFilter,
	eTestSceneType_RenderEx_SpotLightSprite,

	eTestSceneType_EffectNode_2DSoftShadow,
	eTestSceneType_EffectNode_BreakSprite,
	eTestSceneType_EffectNode_ColorAdjustSprite,
	eTestSceneType_EffectNode_GhostLikeSprite,
	eTestSceneType_EffectNode_Laser,
	eTestSceneType_EffectNode_LightingBolt,
	eTestSceneType_EffectNode_NormalMapped,
	eTestSceneType_EffectNode_RippleSprite,
	eTestSceneType_EffectNode_Ripple2DSprite,
	eTestSceneType_EffectNode_ShatterSprite,
	eTestSceneType_EffectNode_TailSprite,
	eTestSceneType_EffectNode_TinyWindTerrain,

	eTestSceneType_TMX_Isometric,
	eTestSceneType_TMX_Hexagonal,
	eTestSceneType_TMX_Orthogonal,
	eTestSceneType_TMX_Flip,
	// to do add...
	eTestSceneType_Max,
};
const std::string g_aTestNames[eTestSceneType_Max] = {
	"��������",

	"FKCW_GR_GestureRecognizer - ����ʶ��",

	"FKCW_Font_Test - ��������",

	"FKCW_Database_Database - ���ݿ�",

	"FKCW_SimpleNet_NetObject - TCP���ӷ�װ",

	"FKCW_Json_Parser - Json�ļ�����",

	"FKCW_SceneEx_UISceneEx - �����������",

	"FKCW_3D_FKSimpleModel - 3D��Ⱦ�����Լ�FKSimpleModel�ļ�֧�ֲ���",

	"FKCW_RichHtml_HtmlLabel - ����HTML����Ⱦ���ı�",

	"FKCW_Story_StoryLayer - AVG���°�ű�����",

	"FKCW_Pixel_Demo - ����֧�ֿ�Demo����",

	"FKCW_Shader_Demo1 - ShaderЧ������1",
	"FKCW_Shader_Demo2 - ShaderЧ������2",

	"FKCW_Network_FileDownLoader - �ļ�������",
	"FKCW_Network_HttpGet - Http��Get��������",
	"FKCW_Network_TCP - TCP����",
	"FKCW_Network_UDP - UDP����",

	"FKCW_UI_AutoRenderMenuItemSprite - �������˵�ѡ���",
	"FKCW_UI_MenuItemColor - ��ɫѡ���",
	"FKCW_UI_ToastLayer - ����Tip��",
	"FKCW_UI_SimpleRookieGuiderLayer - ����������",
	"FKCW_UI_DynamicNumLabel - ��̬���ֱ�ǩ",
	"FKCW_UI_MenuItemProgressTimer - ������ʱ��Ĳ˵�ѡ��",
	"FKCW_UI_ProgressIndicator - ������ʾ��",
	"FKCW_UI_ScrollableLayer - ������ǩ��",
	"FKCW_UI_Table - ��Table�ؼ�",
	
	"FKCW_Action_Blur - ģ������",
	"FKCW_Action_ClipIn - ���뽥������",
	"FKCW_Action_Count - ���ַ�ת����",
	"FKCW_Action_Flash - ���⶯��",
	"FKCW_Action_Missile - ��������",
	"FKCW_Action_Shake - �𶯶���",
	"FKCW_Action_Shine - ���߶���",
	"FKCW_Action_TreeFadeIn - ���Զ���",
	"FKCW_Action_TreeFadeOut - ��������",
	"FKCW_Action_TrailMoveTo - ��β�ƶ�����",
	"FKCW_Action_CallFuncT - ģ������ص�����",
	"FKCW_Action_Curl - ������ת����",
	"FKCW_Action_Suck - �ڶ����붯��",

	"FKCW_UIWidget_DrawZOrder - ����UIWidget�ؼ�����˳��",
	"FKCW_UIWidget_Button - ��ť",
	"FKCW_UIWidget_CheckBox - ѡ���",
	"FKCW_UIWidget_ColorView - ��ɫ��View",
	"FKCW_UIWidget_ControlView - ҡ�˿ؼ�",
	"FKCW_UIWidget_ExpandableListView - ����չ�б�",
	"FKCW_UIWidget_GradientView - ����ؼ�",
	"FKCW_UIWidget_ImageView - ͼƬ�ؼ�",
	"FKCW_UIWidget_GridPageView - ���������ؼ�(����)",
	"FKCW_UIWidget_GridView - ���������ؼ�(����)",
	"FKCW_UIWidget_Label - ��̬���ֱ�ǩ",
	"FKCW_UIWidget_Layout - ����������",
	"FKCW_UIWidget_ProgressBar - ������",
	"FKCW_UIWidget_ScrollView - ��������",
	"FKCW_UIWidget_ToggleView - ����View",
	"FKCW_UIWidget_ListView - ����������",
	"FKCW_UIWidget_Slider - ����",
	"FKCW_UIWidget_TextRich - ���ı�",
	"FKCW_UIWidget_LabelAtlas - ��̬��ǩ��",
	"FKCW_UIWidget_PageView - ҳ�滬��������",
	"FKCW_UIWidget_TableView - ����������",

	"FKCW_Base_AStar - A*Ѱ·��ʾ",
	"FKCW_Base_Utils - ������",
	"FKCW_Base_MD5_Base64_SHA1 - ���ܽ�����",
	"FKCW_Base_DrawingPrimitives - ��������Ԫ��",
	"FKCW_Base_CVSLoader - CVS��ʽ������",
	"FKCW_Base_DecodeHtml - HTML��ʽ����������",
	"FKCW_Base_Localization - ����Ӧ������Ա�",
	"FKCW_Base_Memroy - �ڴ�й¶���",
	"FKCW_Base_PinYin - ƴ����",
	"FKCW_Base_ResourceLoader - �����߳���Դ����",
	"FKCW_Base_SecureUserDefault - ���ܱ�׼�û������ļ�",
	"FKCW_Base_FileZip - �ļ�ѹ����ѹ��",

	"FKCW_RenderEx_GradientSprite - �ὥ��Ч���ľ���",
	"FKCW_RenderEx_TiledSprite - ��侫��",
	"FKCW_RenderEx_LaserSprite - ���伤�⾫��",
	"FKCW_RenderEx_TurnCardSprite - ���ƣ���ҳ������",
	"FKCW_RenderEx_EraserSprite - ��Ƥ����������",
	"FKCW_RenderEx_ScrollingBackgroundNode - ���޾������Ľڵ�",
	"FKCW_RenderEx_JoystickNode - ����ҡ�˽ڵ�",
	"FKCW_RenderEx_NumberCountNode - �ɱ��ٷ��������־���",
	"FKCW_RenderEx_SimpleShaderColorPainter - �򵥵�node��ɫ����Ϳɫ��",
	"FKCW_RenderEx_CatmullRomSprite - �ѿ�����ֵŤ������",
	"FKCW_RenderEx_SwayNode - ���ϲ�ҡҷ�ľ���ڵ�",
	"FKCW_RenderEx_BlurTextureFilter - ����ģ��������",
	"FKCW_RenderEx_SpotLightSprite - �۹��Ч������",

	"FKCW_EffectNode_2DSoftShadow - 2D����Ӱ�ڵ�",
	"FKCW_EffectNode_BreakSprite - ������侫��",
	"FKCW_EffectNode_ColorAdjustSprite - hsvɫ�ʵ�������",
	"FKCW_EffectNode_GhostLikeSprite - ���龫��",
	"FKCW_EffectNode_Laser - ��������",
	"FKCW_EffectNode_LightingBolt - ���羫��",
	"FKCW_EffectNode_NormalMapped - ���߾���",
	"FKCW_EffectNode_RippleSprite - ������������",
	"FKCW_EffectNode_Ripple2DSprite - 2D������������",
	"FKCW_EffectNode_ShatterSprite - �������龫��",
	"FKCW_EffectNode_TailSprite - ��β��Ӱ����",
	"FKCW_EffectNode_TinyWindTerrain - ��ϷTinyWind���Ƶĵ���",

	"FKCW_TMX_Map[Isometric] - б45�ȵ�ͼ����",
	"FKCW_TMX_Map[Hexagonal] - �����ε�ͼ����",
	"FKCW_TMX_Map[Orthogonal] - ���ֱ�ǵ�ͼ����",
	"FKCW_TMX_Map[Flip] - ��Ԫ�����ͼ����",
	// to do add...
};
//--------------------------------------------------------