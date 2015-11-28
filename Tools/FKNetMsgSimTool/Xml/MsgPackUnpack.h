#ifndef _MSG_PARSER_H_
#define _MSG_PARSER_H_

//-------------------------------------------------------------------------
#include "XmlParser.h"
#include "FKCWLib/FKCocos2dxWrapper.h"
//-------------------------------------------------------------------------

class MsgPackUnpack : public cocos2d::CCObject
{
public:
	//��������紫�����
	//buffer�� ������Buffer����
	//msgPace: �������MsgPack��
	static void pack(FKCW_SimpleNet_Buffer &buffer, MsgPack msgPace);
	
	//�����MsgPack�ṹ��
	//magPack: ����󴢴�MsgPack������
	//xmlParser: XML��������ָ��
	//buffer�� �������BufferԴ����
	static void unPack(MsgPack& magPack, XmlParser* xmlParser, FKCW_SimpleNet_Buffer* buffer);
	
	//�ַ��������MsgPack�ṹ��
	//magPack: ����󴢴�MsgPack������
	//xmlParser: XML��������ָ��
	//stream: �ַ�����
	//lenght: �ַ���������
	static void unPackStringStream(MsgPack& magPack, XmlParser* xmlParser, char* stream, int lenght);
};

#endif	//_MSG_PARSER_H_