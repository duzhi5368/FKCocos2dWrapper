//*************************************************************************
//	创建日期:	2014-11-27
//	文件名称:	FKCW_Pixel.h
//  创 建 人:   王宏张 FreeKnight	
//	版权所有:	MIT
//	说    明:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
/* 
====================================
模块说明：	
====================================
	 cocos2dx的像素支持扩展。可以简便的创建和绘制静态像素对象和动态（可破坏）像素对象。
	优点：	1：资源便于进行预处理。
			2：资源很小。
			3：可以进行高效的碰撞测试。
			4：容易进行动态破坏。
====================================
内部文件功能说明：
====================================
	
====================================
依赖项目/库：
====================================
====================================
todo:
====================================
*/ 
//-------------------------------------------------------------------------
#include "Include/FKCW_Pixel_DynamicPixelActor.h"

#include "Include/FKCW_Pixel_StaticPixelSprite.h"
#include "Include/FKCW_Pixel_DynamicPixelActor.h"
#include "Include/FKCW_Pixel_DynamicPixelModel.h"