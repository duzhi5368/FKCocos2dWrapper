//*************************************************************************
//	��������:	2014-12-15
//	�ļ�����:	Test_Base_UtilsI.h
//  �� �� ��:   WilhanTIan
//	��Ȩ����:	MIT
//	˵    ��:	������
//  ���Խ��:		
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../resource.h"
#include "../TestScene.h"
#include "../../../FKCWLib/FKCocos2dxWrapper.h"
//-------------------------------------------------------------------------
#define CREATE_TEST_BASE_UTILS_I_BUTTON(_TEST_FUNC_NAME_, _LABEL_)\
	FKCW_UIWidget_Button* button##_TEST_FUNC_NAME_  =  FKCW_UIWidget_Button::createWith9Sprite(CCSize(210, 30),\
	s_szSprite9Btn1Path, s_szSprite9Btn2Path );\
	button##_TEST_FUNC_NAME_->initText(FKCW_Base_StringConvert::a2u(#_LABEL_).c_str(), "", 14);\
	button##_TEST_FUNC_NAME_->setPosition(CCPoint(210/2, 15+2));\
	button##_TEST_FUNC_NAME_->setOnClickListener(this, fkcw_uiwidget_click_selector(CTest_Base_UtilsILayer::onButton##_TEST_FUNC_NAME_##Click));\
	FKCW_UIWidget_Layout* pLayout##_TEST_FUNC_NAME_ = FKCW_UIWidget_Layout::create();\
	pLayout##_TEST_FUNC_NAME_->setContentSize(CCSize(210, 32));\
	m_pButtonListView->insertNodeAtLast(pLayout##_TEST_FUNC_NAME_);\
	pLayout##_TEST_FUNC_NAME_->addChild(button##_TEST_FUNC_NAME_);\
	m_pButtonListView->reloadData()
//-------------------------------------------------------------------------
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
#define FOREGROUND_BLUE      0x0001 // text color contains blue.
#define FOREGROUND_GREEN     0x0002 // text color contains green.
#define FOREGROUND_RED       0x0004 // text color contains red.
#define FOREGROUND_INTENSITY 0x0008 // text color is intensified.
#define BACKGROUND_BLUE      0x0010 // background color contains blue.
#define BACKGROUND_GREEN     0x0020 // background color contains green.
#define BACKGROUND_RED       0x0040 // background color contains red.
#define BACKGROUND_INTENSITY 0x0080 // background color is intensified.
#endif
//-------------------------------------------------------------------------
class CTest_Base_UtilsILayer : public CCLayer
{
public:
	bool init()
	{
		//������������
		m_pWindow = FKCW_UIWidget_WidgetWindow::create( );
		m_pWindow->setMultiTouchEnabled(true);
		this->addChild(m_pWindow);
		
		m_pListView = FKCW_UIWidget_ListView::create(CCSize(640, 500));
		m_pListView->setPosition(SCREEN_CENTER_POS + CCPoint(-120, 0));
		m_pListView->setBackgroundColor(cc4BLACK);
		m_pListView->setDirection(eScrollViewDirectionVertical);
		m_pWindow->addChild(m_pListView);

		m_pButtonListView = FKCW_UIWidget_ListView::create(CCSize(210, 500));
		m_pButtonListView->setPosition(SCREEN_CENTER_POS + CCPoint(330, 0));
		m_pButtonListView->setDirection(eScrollViewDirectionVertical);
		m_pWindow->addChild(m_pButtonListView);

		CREATE_TEST_BASE_UTILS_I_BUTTON(ConsoleLog, �ڿ���̨�����ͨ���);
		CREATE_TEST_BASE_UTILS_I_BUTTON(ConsoleLogColor, �ڿ���̨�������ɫ�����);
		CREATE_TEST_BASE_UTILS_I_BUTTON(FKFileLog, �ں�̨��¼Log���);
		CREATE_TEST_BASE_UTILS_I_BUTTON(GetUTCDataString, ��ʾ��ǰʱ��);
		CREATE_TEST_BASE_UTILS_I_BUTTON(GetCurrentTimeMillis, ��1970-1-1�����ڵ�����);
		CREATE_TEST_BASE_UTILS_I_BUTTON(ScreenShot, �����������ļ�);
		CREATE_TEST_BASE_UTILS_I_BUTTON(Domain2IP, DNS����);
		CREATE_TEST_BASE_UTILS_I_BUTTON(Random01, ȡ0-1֮������������);
		CREATE_TEST_BASE_UTILS_I_BUTTON(RandomInRange, ���һ����Χ�ڵĸ�����);
		CREATE_TEST_BASE_UTILS_I_BUTTON(Pow2, ��ƽ��ֵ);
		CREATE_TEST_BASE_UTILS_I_BUTTON(Lerp, �����ڲ�);
		CREATE_TEST_BASE_UTILS_I_BUTTON(Ceil, ������һ�����ȵ���������λ);
		CREATE_TEST_BASE_UTILS_I_BUTTON(Floor, �Ը���������һ�����ȵ�����);
		CREATE_TEST_BASE_UTILS_I_BUTTON(Round, ��������һ�����ȵ���������);
		CREATE_TEST_BASE_UTILS_I_BUTTON(BinarySearch, ��int������ж��ֲ���);
		CREATE_TEST_BASE_UTILS_I_BUTTON(GetPathExtension, ��ȡ�ļ���׺��);
		CREATE_TEST_BASE_UTILS_I_BUTTON(DeletePathExtension, ɾ���ļ���׺��);
		CREATE_TEST_BASE_UTILS_I_BUTTON(AppendLastPathOfComponment, Ϊ·�����βƬ��);
		CREATE_TEST_BASE_UTILS_I_BUTTON(DeleteLastPathOfComponment, ɾ��·���ַ�������Ƭ��);
		CREATE_TEST_BASE_UTILS_I_BUTTON(LastPathOfComponent, ��ȡһ��·���ַ�������Ƭ��);
		CREATE_TEST_BASE_UTILS_I_BUTTON(LastDotIndex, ��ȡ�ַ���������'.'λ��);
		CREATE_TEST_BASE_UTILS_I_BUTTON(LastSlashIndex, ��ȡ�ַ���������'\\'λ��);
		CREATE_TEST_BASE_UTILS_I_BUTTON(RemoveChar, ��һ���ַ������Ƴ�һ���ַ�);
		CREATE_TEST_BASE_UTILS_I_BUTTON(Replace, �滻�ַ����е��ַ�������);
		CREATE_TEST_BASE_UTILS_I_BUTTON(ReplaceChar, �滻�ַ����е������ַ�Ϊ);
		CREATE_TEST_BASE_UTILS_I_BUTTON(IsEndWith, �ж��ַ���β���Ƿ�ƥ��);
		CREATE_TEST_BASE_UTILS_I_BUTTON(IsStartWith, �ж��ַ���ͷ���Ƿ�ƥ��);
		CREATE_TEST_BASE_UTILS_I_BUTTON(ToLowerCase, ת���ַ���ΪСд);
		CREATE_TEST_BASE_UTILS_I_BUTTON(Trim, ȥ�ո�ͷβ);
		CREATE_TEST_BASE_UTILS_I_BUTTON(GetNumDigits, ��ȡһ�����ֵ�λ��);
		CREATE_TEST_BASE_UTILS_I_BUTTON(CalculateIncircleR2, ��ȡ����������Բ�뾶);

		m_pButtonSlider = FKCW_UIWidget_Slider::create();
		m_pButtonSlider->setSliderImage(s_szSliderPath);
		m_pButtonSlider->setProgressImage(s_szProgressVPath);
		m_pButtonSlider->setBackgroundImage(s_szProgressVBGPath);
		m_pButtonSlider->setPosition(SCREEN_CENTER_POS+CCPoint(450, 0));
		m_pButtonSlider->setMaxValue( (int)(m_pButtonListView->getContainer()->getContentSize().height - m_pButtonListView->getContentSize().height) );
		m_pButtonSlider->setMinValue(0);
		m_pButtonSlider->setValue(0);
		m_pButtonSlider->setDirection(eProgressBarDirectionTopToBottom);
		m_pButtonSlider->setOnValueChangedListener(this, fkcw_uiwidget_valuechanged_selector(CTest_Base_UtilsILayer::onButtonValueChanged));
		m_pWindow->addChild(m_pButtonSlider);

		return true;
	}
public:
	void onButtonValueChanged(CCObject* pSender, int nValue)
	{
		m_pButtonListView->setContentOffset(CCPoint( 0, (float)(-nValue) ));
	}
	void onInfoValueChanged(CCObject* pSender, int nValue)
	{
		m_pListView->setContentOffset(CCPoint( 0, (float)(-nValue) ));
	}
public:
	void onButtonConsoleLogClick(CCObject* pSender)
	{
		FKCW_Base_Utils::FKConsoleLog("����һ���������");
		addStringInListView(m_pListView, ">>FKCW_Base_Utils::FKConsoleLog(\"����һ���������\");  �Ѿ�ִ�У���ע�����̨��־��");
	}
	void onButtonConsoleLogColorClick(CCObject* pSender)
	{
		int randA = (int)FKCW_Base_Utils::RandomInRange(0, 3);
		int randB = (int)FKCW_Base_Utils::RandomInRange(0, 3);
		int randC = (int)FKCW_Base_Utils::RandomInRange(0, 3);

		short color = 0;

		switch (randA)
		{
		case 0:
			color = color + FOREGROUND_BLUE;
			break;
		case 1:
			color = color + FOREGROUND_GREEN;
			break;
		case 2:
			color = color + FOREGROUND_RED;
			break;
		default:
			color = color + FOREGROUND_BLUE;
			break;
		}

		switch (randB)
		{
		case 0:
			color = color + BACKGROUND_BLUE;
			break;
		case 1:
			color = color + BACKGROUND_GREEN;
			break;
		case 2:
			color = color + BACKGROUND_RED;
			break;
		default:
			color = color + BACKGROUND_BLUE;
			break;
		}

		switch (randC)
		{
		case 0:
			color = color + FOREGROUND_INTENSITY;
			break;
		case 1:
			color = color + BACKGROUND_INTENSITY;
			break;
		}

		FKCW_Base_Utils::FKConsoleLogColor(color, "�ڿ���̨�������ɫ�����");
		addStringInListView(m_pListView, ">>FKCW_Base_Utils::FKConsoleLogColor(color, \"�ڿ���̨�������ɫ�����\");  �Ѿ�ִ�У���ע�����̨��־��");
	}
	void onButtonFKFileLogClick(CCObject* pSender)
	{
		FKCW_Base_Utils::FKFileLog("����һ����̨����Log");
		addStringInListView(m_pListView, ">>FKCW_Base_Utils::FKFileLog(\"����һ���������Log\");  �뵽��exe�����ļ��в��ҵ���log�ļ�ȷ�ϲ��Գɹ���");
	}
	void onButtonGetUTCDataStringClick(CCObject* pSender)
	{
		std::string str = ">>FKCW_Base_Utils::GetUTCDataString();  reutrn > ";
		str = str + FKCW_Base_Utils::GetUTCDataString();
		addStringInListView(m_pListView, str.c_str());
	}
	void onButtonGetCurrentTimeMillisClick(CCObject* pSender)
	{
		int64_t t = FKCW_Base_Utils::GetStaticCurrentTimeSeconds();
		char buff[1024];
		sprintf(buff, ">>GetCurrentTimeMillis(); ��ִ�С� return > %I64d", t);
		addStringInListView(m_pListView, buff);
	}
	void onButtonScreenShotClick(CCObject* pSender)
	{
		std::string fileName = FKCW_Base_Utils::ScreenShot(NULL, "ScreenShot.png");
#if _DEBUG
		fileName = ">>FKCW_Base_Utils::ScreenShot(NULL, \"ScreenShot.png\"); ��ͼ�Ѿ����浽:./Debug.win32/ScreenShot.png";
#else
		fileName = ">>FKCW_Base_Utils::ScreenShot(NULL, \"ScreenShot.png\"); ��ͼ�Ѿ����浽:./Release.win32/ScreenShot.png";
#endif
		addStringInListView(m_pListView, fileName.c_str());
	}
	void onButtonDomain2IPClick(CCObject* pSender)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) 
		WSADATA wsa; 
		WORD wVersionRequested; 
		wVersionRequested = MAKEWORD( 2, 0 );  
		if (WSAStartup(wVersionRequested , &wsa)!=0) 
		{
			FKLOG("��ʼ��WSAʧ��,����������Ȼʧ��...");
		}; 
		std::string ip = ">>FKCW_Base_Utils::Domain2IP(\"www.google.com\"); ��ִ�С� return > " + FKCW_Base_Utils::Domain2IP("www.google.com");
		addStringInListView(m_pListView, ip.c_str());
#endif
		
	}
	void onButtonCalculateIncircleR2Click(CCObject* pSender)
	{
		CCPoint points[3];
		points[0].x = 200; points[0].y = 200;
		points[1].x = 500; points[1].y = 200;
		points[2].x = FKCW_Base_Utils::RandomInRange(0, 1000); points[2].y = FKCW_Base_Utils::RandomInRange(0, 1000);

		char str[512];
		memset( str, 0, 512 );
		sprintf( str, ">>FKCW_Base_Utils::CalculateIncircleR2( x1 = %.2f, y1 = %.2f, x2 = %.2f, y2 = %.2f, \n x3 = %.2f, y3 = %.2f, ); ��ִ�С�return > %.5f",
			points[0].x, points[0].y, points[1].x, points[1].y, points[2].x, points[2].y, sqrtf(FKCW_Base_Utils::CalculateIncircleR2(points[0], points[1], points[2])));
		addStringInListView(m_pListView, str);
	}
	void onButtonRandom01Click(CCObject* pSender)
	{
		char buff[20];
		sprintf(buff, "%f", FKCW_Base_Utils::Random01());
		std::string str = ">>FKCW_Base_Utils::Random01(); ��ִ�С� return > ";
		str = str + buff;
		addStringInListView(m_pListView, str.c_str());
	}
	void onButtonRandomInRangeClick(CCObject* pSender)
	{
		char buff[20];
		sprintf(buff, "%f", FKCW_Base_Utils::RandomInRange(10, 20));
		std::string str = ">>FKCW_Base_Utils::RandomInRange(10, 20); ��ִ�С� return > ";
		str = str + buff;
		addStringInListView(m_pListView, str.c_str());
	}
	void onButtonPow2Click(CCObject* pSender)
	{
		float y = FKCW_Base_Utils::RandomInRange(5, 20);

		char buff[20];
		sprintf(buff, "%f", y);
		std::string str = ">>FKCW_Base_Utils::Pow2(";
		str = str + buff + "); ��ִ�С� return > ";

		char math[20];
		sprintf(math, "%f", FKCW_Base_Utils::Pow2(y));
		str = str + math;

		addStringInListView(m_pListView, str.c_str());
	}
	void onButtonLerpClick(CCObject* pSender)
	{
  		float a = FKCW_Base_Utils::RandomInRange(0, 20);
		float b = FKCW_Base_Utils::RandomInRange(0, 20);
		float c = FKCW_Base_Utils::RandomInRange(0, 20);

		float d = FKCW_Base_Utils::Lerp(a, b, c);

		char cA[20];
		char cB[20];
		char cC[20];
		char cD[20];

		sprintf(cA, "%.2f", a);
		sprintf(cB, "%.2f", b);
		sprintf(cC, "%.2f", c);
		sprintf(cD, "%f", d);

		std::string str = ">>FKCW_Base_Utils::Lerp(";
		str = str + cA + ", " + cB + ", " + cC + "); ��ִ�С�  return > " + cD;
		addStringInListView(m_pListView, str.c_str());
	}
	void onButtonCeilClick(CCObject* pSender)
	{
		double a	= FKCW_Base_Utils::RandomInRange(0, 100);
		int b		= static_cast<int>(FKCW_Base_Utils::RandomInRange(0, 5));
		double c	= FKCW_Base_Utils::Ceil(a, b);

		char cA[20];
		char cB[20];
		char cC[20];

		sprintf(cA, "%lf", a);
		sprintf(cB, "%d", b);
		sprintf(cC, "%lf", c);

		std::string str = ">>FKCW_Base_Utils::Ceil(";
		str = str + cA + ", " + cB + "); ��ִ�С� return > " + cC;
		addStringInListView(m_pListView, str.c_str());
	}
	void onButtonFloorClick(CCObject* pSender)
	{
		double a = FKCW_Base_Utils::RandomInRange(0, 100);
		int b	= static_cast<int>(FKCW_Base_Utils::RandomInRange(0, 5));
		double c = FKCW_Base_Utils::Floor(a, b);

		char cA[20];
		char cB[20];
		char cC[20];

		sprintf(cA, "%lf", a);
		sprintf(cB, "%d", b);
		sprintf(cC, "%lf", c);

		std::string str = ">>FKCW_Base_Utils::Floor(";
		str = str + cA + ", " + cB + "); ��ִ�С� return > " + cC;
		addStringInListView(m_pListView, str.c_str());
	}
	void onButtonRoundClick(CCObject* pSender)
	{
		double a = FKCW_Base_Utils::RandomInRange(0, 100);
		int b = static_cast<int>(FKCW_Base_Utils::RandomInRange(0, 5));
		double c = FKCW_Base_Utils::Round(a, b);

		char cA[20];
		char cB[20];
		char cC[20];

		sprintf(cA, "%lf", a);
		sprintf(cB, "%d", b);
		sprintf(cC, "%lf", c);

		std::string str = ">>FKCW_Base_Utils::Round(";
		str = str + cA + ", " + cB + "); ��ִ�С� return > " + cC;
		addStringInListView(m_pListView, str.c_str());
	}
	void onButtonBinarySearchClick(CCObject* pSender)
	{
		int map[10];
		std::string sMap;
		for(int i=0; i<10; i++)
		{
			map[i] = static_cast<int>(FKCW_Base_Utils::RandomInRange(0, 10000));
			char buff[8];
			sprintf(buff, "%d, ", map[i]);
			sMap = sMap + buff;
		}
		sMap = ">>����int���飬Ԫ��10����"+sMap;
		addStringInListView(m_pListView, sMap.c_str());

		int index = static_cast<int>(FKCW_Base_Utils::RandomInRange(0, 9));
		index = map[index];

		// ����
		sMap.clear();
		FKCW_Base_Utils::QuickSort(map, 10);
		for(int i = 0; i < 10; ++i)
		{
			char buff[8];
			sprintf(buff, "%d, ", map[i]);
			sMap = sMap + buff;
		}
		sMap = "    >�����"+sMap;
		addStringInListView(m_pListView, sMap.c_str());

		int out = FKCW_Base_Utils::BinarySearch(map, 10, index);
		char str[512]; 
		memset( str, 0, 512 );
		sprintf(str, "    >FKCW_Base_Utils::BinarySearch(int����, 10, %d); ����ִ�С� return > %d", index, out);
		addStringInListView(m_pListView, str);
	}
	void onButtonGetPathExtensionClick(CCObject* pSender)
	{
		int i = static_cast<int>(FKCW_Base_Utils::RandomInRange(0, 4));
		if(i == 0)
		{
			std::string str = ">>FKCW_Base_Utils::GetPathExtension(\"Qwe.png\"); ��ִ�� return > " + FKCW_Base_Utils::GetPathExtension("Qwe.png");
			addStringInListView(m_pListView, str.c_str());
		}
		else if(i == 1)
		{
			 std::string str = ">>FKCW_Base_Utils::GetPathExtension(\"./321.exe\"); ��ִ�� return > " + FKCW_Base_Utils::GetPathExtension("./321.exe");
			 addStringInListView(m_pListView, str.c_str());
		}
		else if(i == 2)
		{
			std::string str = ">>FKCW_Base_Utils::GetPathExtension(\"..\\Qwe.text\"); ��ִ�� return > " + FKCW_Base_Utils::GetPathExtension("..\\Qwe.text");
			addStringInListView(m_pListView, str.c_str());
		}
		else if(i == 3)
		{
			std::string str = ">>FKCW_Base_Utils::GetPathExtension(\"E:/asd/_temp.data\"); ��ִ�� return > " + FKCW_Base_Utils::GetPathExtension("E:/asd/_temp.data");
			addStringInListView(m_pListView, str.c_str());
		}
	}
	void onButtonDeletePathExtensionClick(CCObject* pSender)
	{
		int i = static_cast<int>(FKCW_Base_Utils::RandomInRange(0, 4));
		if(i == 0)
		{
			std::string str = ">>FKCW_Base_Utils::DeletePathExtension(\"Qwe.png\"); ��ִ�� return > " + FKCW_Base_Utils::DeletePathExtension("Qwe.png");
			addStringInListView(m_pListView, str.c_str());
		}
		else if(i == 1)
		{
			std::string str = ">>FKCW_Base_Utils::DeletePathExtension(\"./321.exe\"); ��ִ�� return > " + FKCW_Base_Utils::DeletePathExtension("./321.exe");
			addStringInListView(m_pListView, str.c_str());
		}
		else if(i == 2)
		{
			std::string str = ">>FKCW_Base_Utils::DeletePathExtension(\"..\\Qwe.text\"); ��ִ�� return > " + FKCW_Base_Utils::DeletePathExtension("..\\Qwe.text");
			addStringInListView(m_pListView, str.c_str());
		}
		else if(i == 3)
		{
			std::string str = ">>FKCW_Base_Utils::DeletePathExtension(\"E:/asd/_temp.data\"); ��ִ�� return > " + FKCW_Base_Utils::DeletePathExtension("E:/asd/_temp.data");
			addStringInListView(m_pListView, str.c_str());
		}
	}
	void onButtonAppendLastPathOfComponmentClick(CCObject* pSender)
	{
		int i = static_cast<int>(FKCW_Base_Utils::RandomInRange(0, 4));
		if(i == 0)
		{
			std::string str = ">>FKCW_Base_Utils::AppendLastPathOfComponment(\"/tmp\", \"/scratch.tiff\"); \n    >��ִ�� return > " + FKCW_Base_Utils::AppendLastPathOfComponment("/tmp", "/scratch.tiff");
			addStringInListView(m_pListView, str.c_str());
		}
		else if(i == 1)
		{
			std::string str = ">>FKCW_Base_Utils::AppendLastPathOfComponment(\"/tmp//\", \"/scratch\"); \n    ��ִ�� return > " + FKCW_Base_Utils::AppendLastPathOfComponment("/tmp//", "/scratch");
			addStringInListView(m_pListView, str.c_str());
		}
		else if(i == 2)
		{
			std::string str = ">>FKCW_Base_Utils::AppendLastPathOfComponment(\"/tmp\", \"/\"); ��ִ�� return > " + FKCW_Base_Utils::AppendLastPathOfComponment("/tmp", "/");
			addStringInListView(m_pListView, str.c_str());
		}
		else if(i == 3)
		{
			std::string str = ">>FKCW_Base_Utils::AppendLastPathOfComponment(\"/\", \"tmp/\"); ��ִ�� return > " + FKCW_Base_Utils::AppendLastPathOfComponment("/", "tmp/");
			addStringInListView(m_pListView, str.c_str());
		}
	}
	void onButtonDeleteLastPathOfComponmentClick(CCObject* pSender)
	{
		int i = static_cast<int>(FKCW_Base_Utils::RandomInRange(0, 5));
		if(i == 0)
		{
			std::string str = ">>FKCW_Base_Utils::DeleteLastPathOfComponment(\"/tmp/scratch.tiff\"); \n    >��ִ�� return > " + FKCW_Base_Utils::DeleteLastPathOfComponment("/tmp/scratch.tiff");
			addStringInListView(m_pListView, str.c_str());
		}
		else if(i == 1)
		{
			std::string str = ">>FKCW_Base_Utils::DeleteLastPathOfComponment(\"/tmp/scratch\"); \n    ��ִ�� return > " + FKCW_Base_Utils::DeleteLastPathOfComponment("/tmp/scratch");
			addStringInListView(m_pListView, str.c_str());
		}
		else if(i == 2)
		{
			std::string str = ">>FKCW_Base_Utils::DeleteLastPathOfComponment(\"/tmp/\"); \n    ��ִ�� return > " + FKCW_Base_Utils::DeleteLastPathOfComponment("/tmp/");
			addStringInListView(m_pListView, str.c_str());
		}
		else if(i == 3)
		{
			std::string str = ">>FKCW_Base_Utils::DeleteLastPathOfComponment(\"scratch\"); \n    ��ִ�� return > " + FKCW_Base_Utils::DeleteLastPathOfComponment("scratch");
			addStringInListView(m_pListView, str.c_str());
		}
		else if(i == 4)
		{
			std::string str = ">>FKCW_Base_Utils::DeleteLastPathOfComponment(\"/\"); \n    ��ִ�� return > " + FKCW_Base_Utils::DeleteLastPathOfComponment("/");
			addStringInListView(m_pListView, str.c_str());
		}
	}
	void onButtonLastPathOfComponentClick(CCObject* pSender)
	{
		int i = static_cast<int>(FKCW_Base_Utils::RandomInRange(0, 4));
		if(i == 0)
		{
			std::string str = ">>FKCW_Base_Utils::LastPathOfComponent(\"/tmp\\\\scratch.tiff\"); \n    >��ִ�� return > " + FKCW_Base_Utils::LastPathOfComponent("/tmp\\\\scratch.tiff");
			addStringInListView(m_pListView, str.c_str());
		}
		else if(i == 1)
		{
			std::string str = ">>FKCW_Base_Utils::LastPathOfComponent(\"\\\\tmp\\\\scratch\"); \n    ��ִ�� return > " + FKCW_Base_Utils::LastPathOfComponent("\\\\tmp\\\\scratch");
			addStringInListView(m_pListView, str.c_str());
		}
		else if(i == 2)
		{
			std::string str = ">>FKCW_Base_Utils::LastPathOfComponent(\"E:\\\\a/b.png\"); \n    ��ִ�� return > " + FKCW_Base_Utils::LastPathOfComponent("E:\\\\a/b.png");
			addStringInListView(m_pListView, str.c_str());
		}
		else if(i == 3)
		{
			std::string str = ">>FKCW_Base_Utils::LastPathOfComponent(\"\\\\scratch\"); \n    ��ִ�� return > " + FKCW_Base_Utils::LastPathOfComponent("\\\\scratch");
			addStringInListView(m_pListView, str.c_str());
		}
	}
	void onButtonLastDotIndexClick(CCObject* pSender)
	{
		int i = static_cast<int>(FKCW_Base_Utils::RandomInRange(0, 4));
		if(i == 0)
		{
			int index = FKCW_Base_Utils::LastDotIndex("/tmp/scratch.tiff");
			char buff[10];
			sprintf(buff, "%d", index);

			std::string str = ">>FKCW_Base_Utils::LastDotIndex(\"/tmp/scratch.tiff\"); \n    >��ִ�� return > ";
			str = str + buff;
			addStringInListView(m_pListView, str.c_str());
		}
		else if(i == 1)
		{
			int index = FKCW_Base_Utils::LastDotIndex("qwe.aswd.qwe.qqqqq.q");
			char buff[10];
			sprintf(buff, "%d", index);

			std::string str = ">>FKCW_Base_Utils::LastDotIndex(\"qwe.aswd.qwe.qqqqq.q\"); \n    >��ִ�� return > ";
			str = str + buff;
			addStringInListView(m_pListView, str.c_str());
		}
		else if(i == 2)
		{
			int index = FKCW_Base_Utils::LastDotIndex("....");
			char buff[10];
			sprintf(buff, "%d", index);

			std::string str = ">>FKCW_Base_Utils::LastDotIndex(\"....\"); \n    >��ִ�� return > ";
			str = str + buff;
			addStringInListView(m_pListView, str.c_str());
		}
		else if(i == 3)
		{
			int index = FKCW_Base_Utils::LastDotIndex(".aaaa.");
			char buff[10];
			sprintf(buff, "%d", index);

			std::string str = ">>FKCW_Base_Utils::LastDotIndex(\".aaaa.\"); \n    >��ִ�� return > ";
			str = str + buff;
			addStringInListView(m_pListView, str.c_str());
		}
	}
	void onButtonLastSlashIndexClick(CCObject* pSender)
	{
		int i = static_cast<int>(FKCW_Base_Utils::RandomInRange(0, 4));
		if(i == 0)
		{
			int index = FKCW_Base_Utils::LastSlashIndex("\\\\");
			char buff[10];
			sprintf(buff, "%d", index);

			std::string str = ">>FKCW_Base_Utils::LastSlashIndex(\"\\\\\"); \n    >��ִ�� return > ";
			str = str + buff;
			addStringInListView(m_pListView, str.c_str());
		}
		else if(i == 1)
		{
			int index = FKCW_Base_Utils::LastSlashIndex("12345\\");
			char buff[10];
			sprintf(buff, "%d", index);

			std::string str = ">>FKCW_Base_Utils::LastSlashIndex(\"12345\\\"); \n    >��ִ�� return > ";
			str = str + buff;
			addStringInListView(m_pListView, str.c_str());
		}
		else if(i == 2)
		{
			int index = FKCW_Base_Utils::LastSlashIndex("\\123\\\\aaa");
			char buff[10];
			sprintf(buff, "%d", index);

			std::string str = ">>FKCW_Base_Utils::LastSlashIndex(\"\\123\\\\aaa\"); \n    >��ִ�� return > ";
			str = str + buff;
			addStringInListView(m_pListView, str.c_str());
		}
		else if(i == 3)
		{
			int index = FKCW_Base_Utils::LastSlashIndex("aaa\\aaa.png");
			char buff[10];
			sprintf(buff, "%d", index);

			std::string str = ">>FKCW_Base_Utils::LastSlashIndex(\"aaa\\\\aaa.png\"); \n    >��ִ�� return > ";
			str = str + buff;
			addStringInListView(m_pListView, str.c_str());
		}
	}
	void onButtonRemoveCharClick(CCObject* pSender)
	{
		std::string str = "this is a food~";
		FKCW_Base_Utils::RemoveChar( str, 'i');

		std::string out = ">>string str = this is a food\n    >FKCW_Base_Utils::RemoveChar(str, \"'i'\"); \n    >��ִ�� return > str���Ϊ" + str;
		addStringInListView(m_pListView, out.c_str());
	}
	void onButtonReplaceClick(CCObject* pSender)
	{
		std::string str = "this is a food!";
		str = FKCW_Base_Utils::Replace( str, "food", "pig");

		std::string out = ">>string str = this is a food!\n    >FKCW_Base_Utils::Replace(str, \"food\", \"pig\"); \n    >��ִ�� return > \"" + str + "\"";
		addStringInListView(m_pListView, out.c_str());
	}
	void onButtonReplaceCharClick(CCObject* pSender)
	{
		std::string str = "this is a food!";
		FKCW_Base_Utils::ReplaceChar( str, 's', 'z');

		std::string out = ">>string str = this is a food!\n    >FKCW_Base_Utils::ReplaceChar(str, 's', 'z'); \n    >��ִ�� return > str���Ϊ:\"" + str + "\"";
		addStringInListView(m_pListView, out.c_str());
	}
	void onButtonIsEndWithClick(CCObject* pSender)
	{
		std::string str = "this is a food!";
		bool tag = FKCW_Base_Utils::IsEndWith(str, "ood");
		if (tag)
		{
			std::string out = ">>string str = this is a food!\n    >FKCW_Base_Utils::IsEndWith(str, \"ood\"); \n    >��ִ�� return > true";
			addStringInListView(m_pListView, out.c_str());
		}
		else
		{
			std::string out = ">>string str = this is a food!\n    >FKCW_Base_Utils::IsEndWith(str, \"ood\"); \n    >��ִ�� return > false";
			addStringInListView(m_pListView, out.c_str());
		}
	}
	void onButtonIsStartWithClick(CCObject* pSender)
	{
		std::string str = "this is a food!";
		bool tag = FKCW_Base_Utils::IsStartWith(str, "tha");
		if (tag)
		{
			std::string out = ">>string str = this is a food!\n    >FKCW_Base_Utils::IsStartWith(str, \"th\"); \n    >��ִ�� return > true";
			addStringInListView(m_pListView, out.c_str());
		}
		else
		{
			std::string out = ">>string str = this is a food!\n    >FKCW_Base_Utils::IsStartWith(str, \"th\"); \n    >��ִ�� return > false";
			addStringInListView(m_pListView, out.c_str());
		}
	}
	void onButtonToLowerCaseClick(CCObject* pSender)
	{
		std::string str = "This Is A Food!";
		FKCW_Base_Utils::ToLowerCase(str);
		std::string out = ">>string str = This Is A Food!\n    >FKCW_Base_Utils::ToLowerCase(str); \n    >��ִ�� return > str���Ϊ" + str;
		addStringInListView(m_pListView, out.c_str());
	}
	void onButtonTrimClick(CCObject* pSender)
	{
		std::string str = "    this is a Food!    ";
		str = FKCW_Base_Utils::Trim(str);
		std::string out = ">>string str = \"    this is a Food!    \"\n    >FKCW_Base_Utils::Trim(str); \n    >��ִ�� return > str���\"" + str + "\"";
		addStringInListView(m_pListView, out.c_str());
	}
	void onButtonGetNumDigitsClick(CCObject* pSender)
	{
		int i = static_cast<int>(FKCW_Base_Utils::RandomInRange(-1000, 10000));
		int len = FKCW_Base_Utils::GetNumDigits(i);

		char math[20];
		sprintf(math, "%d", i);
		char lenC[8];
		sprintf(lenC, "%d", len);

		std::string str;
		str = str + ">>FKCW_Base_Utils::GetNumDigits(" + math + "); ��ִ�С� return > " + lenC;
		addStringInListView(m_pListView, str.c_str());
	}


	void exitProgress()
	{
		FKCW_UI_ProgressIndicator::Hide();
	}
public:
	CREATE_FUNC( CTest_Base_UtilsILayer );
protected:
	void addStringInListView(FKCW_UIWidget_ListView* listView, const char* contextString)
	{
		FKCW_UIWidget_Layout* pLayout = FKCW_UIWidget_Layout::create();

		CCLabelTTF* label = CCLabelTTF::create(FKCW_Base_StringConvert::a2u(contextString).c_str(), "", 12);
		label->setPositionX(label->getContentSize().width/2.0f + 10);
		label->setHorizontalAlignment(CCTextAlignment::kCCTextAlignmentLeft);
		pLayout->setContentSize(label->getContentSize() + CCSize(0, 6));
		pLayout->addChild(label);

		listView->insertNodeAtLast(pLayout);

		if(listView->getNodeCount() > 100)
			listView->removeFrontNode();

		listView->reloadData();
		listView->setContentOffsetToBottom();
	}
protected:
	FKCW_UIWidget_WidgetWindow*		m_pWindow;
	FKCW_UIWidget_ListView*			m_pListView;
	FKCW_UIWidget_Slider*			m_pButtonSlider;
	FKCW_UIWidget_ListView*			m_pButtonListView;
};
//-------------------------------------------------------------------------
CREATE_TEST_SCENE_CLASS(Base, UtilsI, ������)
//-------------------------------------------------------------------------