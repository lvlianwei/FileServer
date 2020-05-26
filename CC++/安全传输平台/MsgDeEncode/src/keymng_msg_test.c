
#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "keymng_msg.h"

int main(void)
{
	/*
	int					ret = 0;
	Teacher				t1;
	unsigned char		*myOut = NULL;
	int					myOutlen;
	Teacher				*myStruct = NULL;
	int					iType = 0;
	memset(&t1, 0, sizeof(Teacher));
	strcpy(t1.name, "name1");
	t1.age = 100;
	t1.p = (char *)malloc(100);
	strcpy(t1.p, "aaaaabbbbb"); 
	t1.plen = strlen(t1.p);

	ret = MsgEncode(&t1, ID_MsgKey_Teacher, &myOut, &myOutlen);
	if (ret != 0)
	{
		printf("func MsgEncode() err:%d \n", ret);
		return ret;
	}
	printf("--------------------MsgEncode finish\n");
	ret = MsgDecode(myOut, myOutlen, &myStruct, &iType);
	if (ret != 0)
	{
		printf("func MsgDecode() err:%d \n", ret);
		return ret;
	}
	printf("====================MsgDecode finish\n");
	if (strcmp(t1.name, myStruct->name) == 0 &&
		memcmp(t1.p, myStruct->p, myStruct->plen) == 0)
	{
		printf("编码 == 解码  scuess\n");
	}
	else
	{
		printf("编码 != 解码  fail\n");
	}

	//释放内存块
	MsgMemFree((void **)&myOut, 0);
	MsgMemFree((void **)&myStruct, iType);
	*/

	int					ret = 0;
	MsgKey_Req			msg_Req;
	unsigned char		*myOut = NULL;
	int					myOutlen;
	MsgKey_Req			*myStruct = NULL;
	int					iType = 60;
	memset(&msg_Req, 0, sizeof(MsgKey_Req));
	msg_Req.cmdType = 10;
	strcpy(msg_Req.clientId, "clientId");
	strcpy(msg_Req.AuthCode, "AuthCode");
	strcpy(msg_Req.serverId, "serverId");
	strcpy(msg_Req.r1, "r1");

	ret = MsgEncode(&msg_Req, ID_MsgKey_Req, &myOut, &myOutlen);
	if (ret != 0)
	{
		printf("func MsgEncode() err:%d \n", ret);
		return ret;
	}
	printf("--------------------MsgEncode finish\n");
	ret = MsgDecode(myOut, myOutlen, &myStruct, &iType);
	if (ret != 0)
	{
		printf("func MsgDecode() err:%d \n", ret);
		return ret;
	}
	printf("====================MsgDecode finish\n");
	if (strcmp(msg_Req.AuthCode, myStruct->AuthCode) == 0 &&
		memcmp(msg_Req.r1, myStruct->r1, strlen(myStruct->r1)) == 0)
	{
		printf("编码 == 解码  scuess\n");
	}
	else
	{
		printf("编码 != 解码  fail\n");
	}

	//释放内存块
	MsgMemFree((void **)&myOut, 0);
	MsgMemFree((void **)&myStruct, iType);
	printf("hello...\n");
	system("pause");

	return 0;
}
