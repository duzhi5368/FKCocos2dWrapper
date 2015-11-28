//*************************************************************************
//	��������:	2014-10-25
//	�ļ�����:	FKCW_Base_Utils.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_Base_Macro.h"
#include "FKCW_Base_Types.h"
//-------------------------------------------------------------------------
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include <jni.h>
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#import <UIKit/UIKit.h>
#endif
//-------------------------------------------------------------------------
enum ENUM_ConsolTextColor
{
	eConsolTextColor_Blue			= 0x09,		// ����
	eConsolTextColor_Green			= 0x0A,		// ����
	eConsolTextColor_Ching			= 0x0B,		// ����
	eConsolTextColor_Red			= 0x0C,		// ����
	eConsolTextColor_Pink			= 0x0D,		// Ʒ����
	eConsolTextColor_Yellow			= 0x0E,		// ����
};
enum ENUM_ConsolBKColor
{
	eConsolBKColor_Blue				= 0x10,		// ����
	eConsolBKColor_Green			= 0x20,		// �̵�
	eConsolBKColor_Ching			= 0x30,		// ���
	eConsolBKColor_Red				= 0x40,		// ���
	eConsolBKColor_Pink				= 0x50,		// Ʒ���
	eConsolBKColor_Yellow			= 0x60,		// �Ƶ�
	eConsolBKColor_Gray				= 0x80,		// �ҵ�
};
//-------------------------------------------------------------------------
#define FKFULLLOG(format, ...)						FKCW_Base_Utils::FKConsoleLog("%s [L]%d -"format, __FILE__,__LINE__, ##__VA_ARGS__)
#define FKFULLCOLORLOG(color,format, ...)			FKCW_Base_Utils::FKConsoleLogColor(color, "%s [L]%d -"format, __FILE__,__LINE__,##__VA_ARGS__)
#define FKLOG(format, ...)							FKCW_Base_Utils::FKConsoleLog(format, ##__VA_ARGS__)
#define FKCOLORLOG(color,format, ...)				FKCW_Base_Utils::FKConsoleLogColor(color, format, ##__VA_ARGS__)
//-------------------------------------------------------------------------
class FKCW_Base_Utils
{
private:
	static StringList		s_TmpStringList;
	static CCArray			s_TmpArray;
public:
	// ����consoleLog
	static void				FKConsoleLog(const char * pszFormat, ...);
	// ��ɫ�������£��� + ���
	/*
	FOREGROUND_BLUE			������ɫ����	1
	FOREGROUND_GREEN		������ɫ����	2
	FOREGROUND_RED			������ɫ����	4
	FOREGROUND_INTENSITY	ǰ��ɫ������ʾ	8
	BACKGROUND_BLUE			������ɫ����	16
	BACKGROUND_GREEN		������ɫ����	32
	BACKGROUND_RED			������ɫ����	64
	BACKGROUND_INTENSITY	����ɫ������ʾ	128
	*/
	static void				FKConsoleLogColor( short p_sColor, const char * pszFormat, ... );
	// д��Log
	static void				FKFileLog( const char* p_szMsg );

	// intת��Ϊstring
	static string			ItoA(int p_nNum);
	// stringת��Ϊint
	static int				AtoI(const char* str);
	static int				AtoI(string str);
	// floatת��Ϊstring
	static string			FtoA(float p_fNum,int p_nPrecision = 2);
	// stringת��Ϊfloat
	static double			AtoF(const char* str);
	static double			AtoF(string str);
	// HexStringת��Ϊint
	static int				Hex2I(const char* str);
	// �ַ�ת��Ϊ16������ʽ ����Aת��Ϊ"41"
	static string			Char2hex( char dec );
	// �ַ���ת��
	static string			Bin2Hex(const unsigned char * input, size_t length);
	// �ж�һ���ַ����Ƿ������ִ�
	static bool				IsDigital( const string& str );
	// �ж�һ���ַ����Ƿ���ʮ�����Ƶ����ִ�
	static bool				IsDigitalHex( const string& str );
	// �ַ���ת��Ϊint
	// ������nBase��ָ���ף�����10������10,16������16
	static bool				AtoI( const string& str, int nBase, int& nOutNum );

	// ��ȡһ���ַ�����Hashֵ
	static unsigned int		HashString( const char* p_szSrc );
	// ����һ���ַ���
	// ����ֵ����������ַ�����ע�⣬������Ӧ�������ͷŸ��ַ����ڴ�
	static const char*		Copy( const char* p_szSrc );
	// ����һ���ַ�����ָ������
	// ����ֵ����������ַ�����ע�⣬������Ӧ�������ͷŸ��ַ����ڴ�
	static const char*		Copy( const char* p_szSrc, int p_nStart, size_t p_unLen );
	// �ж�һ���ַ��Ƿ��ǿո��ַ�
	static bool				IsSpace( const char a );
	// ȥ���ַ������հ�
	static void				LeftTrim( string& str );
	// ȥ���ַ����Ҳ�հ�
	static void				RightTrim( string& str );
	// �ո�ָ��ַ���(ȥ�ո�ͷβ)
	static string			Trim( const string& s );
	// �����Ž����ַ����ָȡ����ǰ���������в�(��ȥ�����ű���)�����ź�
	static void				TrimWithBrackets( const string& s, string& head, string& in, string& tail );
	// ת���ַ���ΪСд
	static void				ToLowerCase( string& s );
	// �ж�һ���ַ���(s)�ײ��ַ����Ƿ����ƶ��ַ���(sub)ƥ��
	static bool				IsStartWith( const string& s, const string& sub );
	// �ж�һ���ַ���(s)β���ַ����Ƿ����ƶ��ַ���(sub)ƥ��
	static bool				IsEndWith( const string& s, const string& sub );
	// ����һ���ַ����е������ַ�Ϊָ���ַ�
	static void				ReplaceChar( string& s, char p_cOld, char p_cNew );
	// ����һ���ַ����е������ַ�Ϊָ���ַ���
	static string			Replace( string& s, const string& p_strOld, const string& p_strNew );
	// ��һ���ַ������Ƴ�һ���ַ�
	static void				RemoveChar( string& s, char c );
	// ����һ���ָ��������ַ����ָ�( ������Ͳ�ͬ���ֱ�Ϊstring, int, float, bool )
	// ע������ֵ����Ҫ�ⲿ�ͷţ���ע�ⷵ��ֵ����Ϊ�������飬��ú������̿���������ò����ڴ潫�����������ظ�ʹ��
	static CCArray&			ComponentOfString( const string& s, const char p_cSeparator );
	static CCArray&			IntComponentOfString( const string& s, const char p_cSeparator );
	static CCArray&			FloatComponentOfString( const string& s, const char p_cSeparator );
	static CCArray&			BoolComponentOfString( const string& s, const char p_cSeparator );
	// ͨ���ָ�������������һ���ַ�������һϵ�к���������
	static string			JoinString( const CCArray& a, const char p_cSeparator );
	static string			JoinInt( const CCArray& a, const char p_cSeparator );
	static string			JoinFloat( const CCArray& a, const char p_cSeparator );
	static string			JoinBool( const CCArray& a, const char p_cSeparator );
	// ���ַ���ת��Ϊ����ֵ
	/* ����
	* {3.2} ==> ccp(3.2, 0)
	* {,3.4} ==> ccp(0, 3.4)
	* {3.2 ==> ccp(3.2, 0)
	* {,3.4 ==> ccp(0, 3.4)
	* {2,3,4} ==> ccp(2, 3)
	* {[2,3}]) ==> ccp(2,3)
	* {,} ==> ccp(0, 0)
	*/
	// ע��������ʧ�ܣ��򷵻�ccPointZero
	static CCPoint			CcpFromString( const string& s );
	// ���ַ���ת��ΪCCSzie��С
	/* ����
	* {3.2} ==> ccp(3.2, 0)
	* {,3.4} ==> ccp(0, 3.4)
	* {3.2 ==> ccp(3.2, 0)
	* {,3.4 ==> ccp(0, 3.4)
	* {2,3,4} ==> ccp(2, 3)
	* {[2,3}]) ==> ccp(2,3)
	* {,} ==> ccp(0, 0)
	*/
	// ע��������ʧ�ܣ��򷵻�ccSizeZero
	static CCSize			CcsFromString(const string& s);
	// ���ַ���ת��ΪCCRect����
	/* ����
	* {x,y,w,h} ==> ccRectMake( x, y, w,h );
	*/
	// ע��������ʧ�ܣ��򷵻�ccRectZero
	static CCRect			CcrFromString(const string& s);
	// ���ַ���ת��Ϊ����
	/* ����
	* {a1,a2,a3,...}
	*/
	// ע1�����ڲ�Ԫ���е����ţ�����˫���Ű������򷵻ص���string���顣���򷵻ص���float���顣
	// ע2������ֵ����Ҫ�ⲿ�ͷţ���ע�ⷵ��ֵ����Ϊ�������飬��ú������̿���������ò����ڴ潫�����������ظ�ʹ��
	static CCArray&			ArrayFromString( const string& s );
	// ������ת��Ϊ�ַ���
	// �൱�� ArrayFromString ������
	static string			ArrayToString( const CCArray& arr );

	// floatת��string
	static string			FloatToString( float f );
	// intת��string
	static string			IntToString( int n );
	// ����һ��UTF-8�ַ�ռ�ö����ֽ�
	static int				GetUTF8Btyes( unsigned char c );
	// ����һ��UTF-8�ַ�������
	static int				GetUTF8StrLen( const char* p );
	// ����һ��UTF-8�ַ������ж��ٸ�UTF-8�ַ�
	static int				GetUTF8CharCount( const char* p_szUTF8 );
	// ��ȡһ��UTF-8�ַ������ַ���
	static char*			SubUTF8String( const char* p_str, unsigned int start, unsigned int end );
	// תUrl����Ϊʵ�ʱ���
	static string			UrlEncode( const string& s );
	// ����HTMLʵ���ַ���
	static string			DecodeHtmlEntities( const string& p_strSrc );
	// ��һ�������ַ���ת��Ϊƴ���ַ���
	// ע����ǰ��֧�� utf-8 �ַ�����GBK �ַ�����ʱ��֧��
	static string			GetPinyin( const string& s );

	// ��ȡһ���ַ����������ļ��зָ���'\\'λ��
	// ����ֵ����û���ļ��зָ������򷵻�-1
	static int				LastSlashIndex( string p_strPath );
	// ��ȡһ���ַ��������ĵ��'.'λ��
	// ����ֵ����û�е�ţ��򷵻�-1
	static int				LastDotIndex( const string& p_strPath );
	// ��ȡһ��·���ַ�������Ƭ�Σ����ļ��зָ����ж�'\\'��
	static string			LastPathOfComponent( const string& p_strPath );
	// ɾ��һ��·���ַ�������Ƭ��
	/* ��: ����					���
	* "/tmp/scratch.tiff"		"/tmp"
	* "/tmp/scratch"			"/tmp"
	* "/tmp/"					"/tmp"
	* "scratch"					""
	* "/" 						"/"
	*/
	static string			DeleteLastPathOfComponment( const string& p_strPath );
	// Ϊһ��·�����һ��βƬ��
	/* ��������					���
	* "/tmp", "/scratch.tiff"	"/tmp/scratch.tiff"
	* "/tmp//", "/scratch"		"/tmp/scratch"
	* "/tmp", "/"				"/tmp"
	* "/", "tmp/" 				"/tmp"
	*/
	static string			AppendLastPathOfComponment( const string& p_strPath, const string& p_strComponent );
	// ɾ���ļ���׺��
	static string			DeletePathExtension( const string& p_strPath );
	// ��ȡ�ļ���׺��
	// ע������ֵ�� . ��š�����".exe"".jpg"
	static string			GetPathExtension( const string& p_strPath );
	// ��ȡһ��·���ĸ�·��
	static string			GetParentPath( const string& p_strPath );
	// ��ȡ·������·��
	// ����·���Ǿ���·������ʲôҲ����
	// ��iOS�У�����·��ǰ����� ~/Documents
	// ��Android�У�����·��ǰ����� �ڲ��洢�ļ���·��
	// windows�У���ʲôҲ����
	static string			Externalize(const string& path);
	// ����ļ�·���ַ���
	// ��һ��·��strFilePathName����������� ·���� �ļ������Լ��ļ���׺
	static bool				ParseFilePathName( const std::string& strFilePathName,
		std::string& strPathName, std::string& strFileName, std::string& strFileExtName );
	// �ж�һ��·���Ƿ��Ǿ���·��
	static bool				IsAbsolutePath( const string& strFilePathName );

	// ��ȡһ�����ֵ�λ��������0,1,2����1λ��12,38����2λ��9821����4λ
	// ע�����Ǹ����������Ӹ���
	static int				GetNumDigits( int p_nNum );
	// �Ը���������һ�����ȵ��������� 123.54 -> 123.50
	static double			Round( double x, int p_nPrecision );
	static float			Round( float f );
	// �Ը���������һ�����ȵ����� 123.54 -> 123.0
	static double			Floor( double x, int p_nPrecision );
	// �Ը���������һ�����ȵ���������λ 123.54 -> 124.0
	static double			Ceil( double x, int p_nPrecision );
	// �����ڲ�
	static float			Lerp( float a, float b, float p );
	// ��ƽ��ֵ
	static float			Pow2(float x);
	// �����0-1��֮��ĸ�����
	static float			Random01();
	// ���һ����Χ�ڵĸ�����
	static float			RandomInRange(float min,float max);
	// ��һ��������תһ���Ƕ�
	static CCPoint			RotateVector2(const CCPoint&vec,float A);
	static CCPoint			RotateVector2(const CCPoint&vec,float cosA,float sinA);
	// �ж������Ƿ���ͬ
	static bool				IsPointEqual(const CCPoint&point1,const CCPoint&point2,float eps);
	static bool				IsPointEqual(const CCPoint&p1,const CCPoint&p2);
	// ͨ��sin.cosֵ������Ƕ�ֵ
	static float			CalculateAngleFromCosAndSin(float cosA,float sinA);
	// ����Vec1��Vec2�ĽǶȵ�sin,cosֵ����������ֱ�����ΪCCPoint��y,x����
	static CCPoint			CalculateCosASinAOfVec1ToVec2(const CCPoint&vec1,const CCPoint&vec2);
	// ����a��N�η�
	static float			Pow(float a,int n);
	// �� ��һ���ߵľ���
	// ע�����Ǵ�start��end�����ӳ��ߡ��㵽���ߵľ������䴹�߾���
	// ������ֵΪ��������ζ�����ߵ��󷽡�������ֵΪ��������ζ�ŵ����ߵ��ҷ���
	static float			PointDisToLine(const CCPoint&point,const CCPoint&start,const CCPoint&end);
	// ��ȡ�����ߵĽ���
	// ��ƽ�У����� CCPoint(INFINITY,INFINITY);
	static CCPoint			GetIntersectPointOfTwoLine(const CCPoint&p1,const CCPoint&dir1,
							const CCPoint&p2,const CCPoint&dir2);
	// ��������������Բ�뾶ƽ��
	static float			CalculateIncircleR2(const CCPoint&v0,const CCPoint&v1,const CCPoint&v2);
	// ����һ����С��������
	// ˵�������ص���������v0v1��p0p1֮��ľ���Ϊd, v1v2��p1p2֮��ľ���Ϊd, v2v0��p2p0֮��ľ���Ϊd
	// ����ֵӦ����������p0, p1, p2����Ҳ����p0p1p2������һ���㣬�򷵻�ֵΪһ��Ԫ�ص�
	static vector<CCPoint>	MakeTriangleSmaller(CCPoint v0,CCPoint v1,CCPoint v2,float d);
	// ��ȡ�����߻��ⷨ��
	static CCPoint			GetRightNormal(const CCPoint&dir);
	// ��ȡ�Ҳ�������������
	// ע�⣺û�б�׼����
	static CCPoint			GetRightVector(const CCPoint&p1,const CCPoint&p2);
	// �������������
	static float			CalculateTriangleArea(const CCPoint&v0,const CCPoint&v1,const CCPoint&v2);
	// ����㵽ָ��Բ������
	// ����ֵ�����ȷ�������е㣬�ڶ���ֵ�����Ҳ��е㡣
	// ע�⣺������Բ�ڣ��򷵻ؿ�������������Բ�ϣ��򷵻ص�������λ����ͬ��
	static vector<CCPoint>	CalculateTangentPointsOfPointToCircle(const CCPoint &center, float r,const CCPoint &point);
	// ͨ��ָ���߳���������N����
	static vector<CCPoint>	MakeRegularPolygon(int r,int n);
	// ͨ�����㣬���������ζ�������
	static vector<CCPoint>	MakeRectPolygon(float rx,float ry);

	// �ж�һ�������Ƿ��ڰ�Χ����
	static bool				TestSegmentAABB( CCPoint p_pPoint0, CCPoint p_pPoint1, SAABB p_Box );
	// �ϲ���������
	static CCRect			Combine( const CCRect& p_r1, const CCRect& p_r2 );

	// ��һ��int������ж��ֲ���
	static int				BinarySearch( int* p_pA, unsigned int p_unLen, int p_nKey );
	// ��������
	static void				QuickSort(int* p_pA, unsigned int p_unLen );


	// ��ȡ�ڵ�Դ�㣨��Ը��ڵ㣩
	static CCPoint			GetOrigin( CCNode* p_pNode );
	// ��ȡ�ڵ����ģ���Ը��ڵ㣩
	static CCPoint			GetCenter( CCNode* p_pNode );
	// ��ȡ�ڵ㱾������
	static CCPoint			GetLocalCenter( CCNode* p_pNode );
	// ��ȡ�ڵ�λ�ã���Ը��ڵ㣩
	static CCPoint			GetPoint( CCNode* p_pNode, float p_fXPercent, float p_fYPercent );
	// ��ȡ�ڵ�λ�ã���Ը��ڵ㣩
	// ������p_tagAnchor ê��
	static CCPoint			GetPoint( CCNode* p_pNode, CCPoint p_tagAnchor );
	// ��ȡ�ڵ�λ�ã���Ա�node�ڵ㣩
	static CCPoint			GetLocalPoint( CCNode* p_pNode, float p_fXPercent, float p_fYPercent );
	// ��ȡ�ڵ�λ�ã���Ա�node�ڵ㣩
	static CCPoint			GetLocalPoint( CCNode* p_pNode, CCPoint p_tagAnchor );
	// ��ȡ������ռ��еİ�Χ��
	static CCRect			GetBoundingBoxInWorldSpace( CCNode* p_pNode );
	// ��ȡһ���ɱ�ͼƬ��������ľ���
	static CCRect			GetCenterRect( const string& p_strFrameName );
	// ��ȡһ���ɱ�ͼƬ��������ľ���
	static CCRect			GetCenterRect( CCSpriteFrame* p_pFrame );
	// ��ȡ�ڵ����ڳ�������
	static CCScene*			GetScene( CCNode* p_pNode );
	// �ݹ�����һ���ڵ��Լ���ȫ���ӽڵ� alpha ֵ
	static void				SetOpacityRecursively( CCNode* p_pNode, int p_nOpacity );


	// ��1970-1-1�����ڵ�����
	static int64_t			GetStaticCurrentTimeSeconds();
	// ��ȡ��ǰ��׼ʱ��
	static string			GetUTCDataString();
	// ��ȡ�����ѹ�ʱ�䣨��ȷ�����룩
	static bool				GetTimeOfDay( timeval_t* tv, void* tz );
	// ��ȡ�����ѹ�ʱ�䣨��ȷ���룩
	static double			GetTimeSeconds();
	// ��ȡ�Ӳ���ϵͳ��������ǰ�ѹ�ʱ�䣨��ȷ�����룩
	static unsigned int		GetTimeTickCount();
	// ��Ļ�����������ļ�
	// ע1���ļ�֧��jpg,jpeg,png��������ʽ����Ϊjpg���档
	// ע2���ļ���Сһ���봰�ڴ�Сһ��
	// ����1������ͼ�ĸ��ڵ㣬�����Ϳ��Խ����ػ���Ļ�ϲ��ֽڵ㡣������ͼƬ��С��Ȼ�Ǵ��ڴ�С������ֵΪNULL�������������Ļ��
	// ����2�������ͼ��·���������ļ������ļ���׺����Ӧ�������·������ios��android��Ӧ����һ������Ŀ¼��
	// ����3���������Ҫʹ��һ��ģ���ļ������ֵ��Ϊtrue
	static string			ScreenShot( CCNode* p_pRoot, const string& p_strPath, bool p_bIsNeedStencil = false );
	// DNS����
	static string			Domain2IP( const char* p_szDomain );
	// ����windows����̨
	static void				CreateWinConsole();
	// ϵͳSleep
	static void				SystemSleep( unsigned int millisec );
	// ϵͳ�ͷ�
	static void				SystemYield();

	// �ļ�ѹ��
	static int				CompressFile( const char* p_szSrcFile, const char* p_szDstFile, int nLevel = -1 );
	// �ļ���ѹ��
	static int				DecompressFile( const char* p_szSrcFile, const char* p_szDstFile, 
		double* p_pNow = NULL, double* p_pTotal = NULL );
	// �����ļ�����Ȩ��
	static bool				Access( const char* p_szPath, int p_nMode );
	// ����Ŀ¼
	static bool				MakeDir( const char* p_szPath );
	// ����Ŀ¼·��
	static bool				BuildDir( const char* p_szPath );
	// �ļ�������
	static bool				Rename( const char* p_szFrom, const char* p_szTo );
	// ɾ���ļ� 
	static bool				Remove( const char* p_szPath );
};
//-------------------------------------------------------------------------