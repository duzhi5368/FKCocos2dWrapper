//*************************************************************************
//	��������:	2014-8-19   16:44
//	�ļ�����:	CommonHead.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************
 /*
                     _ooOoo_
                    o8888888o
                    88" . "88
                    (| -_- |)
                    O\  =  /O
                 ____/`---'\____
               .'  \\|     |//  `.
              /  \\|||  :  |||//  \
             /  _||||| -:- |||||-  \
             |   | \\\  -  /// |   |
             | \_|  ''\---/''  |   |
             \  .-\__  `-`  ___/-. /
           ___`. .'  /--.--\  `. . __
        ."" '<  `.___\_<|>_/___.'  >'"".
       | | :  `- \`.;`\ _ /`;.`/ - ` : | |
       \  \ `-.   \_ __\ /__ _/   .-` /  /
  ======`-.____`-.___\_____/___.-`____.-'======
                     `=---='
  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
          ���汣��    ����BUG    �����޸�
 */
#pragma once

//-------------------------------------------------------------------------
#pragma warning ( disable : 4251 )
//-------------------------------------------------------------------------
#include "../../FKDBLib/Include/BaseMacro.h"
#include "../../FKDBLib/Include/BaseMath.h"
#include "../../FKDBLib/Include/Armature.h"
#include "../../FKDBLib/Include/Animation.h"
#include "../../FKDBLib/Include/BaseFactory.h"
#include "../../FKDBLib/Include/Slot.h"
#include "../../FKDBLib/Include/Bone.h"
#include "../../FKDBLib/Include/DargonBonesXMLParser.h"
#include "../../FKDBLib/Include/AnimationState.h"
#include "../../FKDBLib/Include/AnimationEvent.h"
#include "../../FKDBLib/Include/FrameEvent.h"
#include "../../FKDBLib/Include/SoundEvent.h"
#include "../../FKDBLib/Include/ConstString.h"

#include "../../FKDBLib/Interface/ITextureAtlas.h"
#include "../../FKDBLib/Interface/IDisplayBridge.h"
#include "../../FKDBLib/Interface/IAnimation.h"

#include "../../FKDBLib/Include/TinyXML2.h"


#include "cocos2d.h"
//-------------------------------------------------------------------------
// �Ƿ�����cocos2dx��BatchNode������Ⱦ��������Ⱦ���Σ�
// 1 ��ʾ����������ֵ��ʾ�ر�
#define  USE_BATCH_NODE		1
//-------------------------------------------------------------------------