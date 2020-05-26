#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "keymng_msg.h"
#include "itcast_asn1_der.h"

//Teacher结构体编码
int TeacherEncode(Teacher *pTeacher, ITCAST_ANYBUF **outData)
{
	/* 
	typedef struct _Teacher
	{
		char name[64];
		int age;
		char *p;
		int plen;
	}Teacher;
	 */
	int					ret = 0;
	ITCAST_ANYBUF		*pTmp = NULL, *pHeadBuf = NULL;
	ITCAST_ANYBUF		*pTmpBuf = NULL;
	ITCAST_ANYBUF		*pOutData = NULL;
	unsigned char		*tmpout = NULL;
	int					tmpoutlen = 0;

	//编码name
	// 1 把Char 类型 转化成  ITCAST_ANYBUF
	ret = DER_ITCAST_String_To_AnyBuf(&pTmpBuf, pTeacher->name, strlen(pTeacher->name));
	if (ret != 0)
	{
		if(pTmpBuf != NULL){
			DER_ITCAST_FreeQueue(pTmpBuf);
		}
		printf("func  DER_ITCAST_String_To_AnyBuf() 转换teacher 为anyBuf 类型 err:%d \n", ret);
		return ret;
	}

	// 2 编码 name
	ret = DER_ItAsn1_WritePrintableString(pTmpBuf, &pHeadBuf);
	if (ret != 0)
	{
		if(pTmpBuf != NULL){
			DER_ITCAST_FreeQueue(pTmpBuf);
		}
		printf("func  DER_ITCAST_String_To_AnyBuf()  encode name err:%d \n", ret);
		return ret;
	}
	DER_ITCAST_FreeQueue(pTmpBuf);
	pTmp = pHeadBuf;

	//编码 age
	ret = DER_ItAsn1_WriteInteger(pTeacher->age, &(pTmp->next));
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHeadBuf); //释放链表 以免内存泄漏
		//在失败后，将pHeadBuf 指针释放，同时需要将pTmp 指针置空，防止野指针
		pTmp = NULL;
		printf("func DER_ItAsn1_WriteInteger() encode age err:%d \n", ret);
		return ret;
	}
	pTmp = pTmp->next;

	//编码 p
	ret = EncodeChar(pTeacher->p, pTeacher->plen, &(pTmp->next));
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHeadBuf); //释放链表 以免内存泄漏
		//在失败后，将pHeadBuf 指针释放，同时需要将pTmp 指针置空，防止野指针
		pTmp = NULL;
		printf("func EncodeChar() encode * P err:%d \n", ret);
		return ret;
	}
	pTmp = pTmp->next;

	//编码 plen
	ret = DER_ItAsn1_WriteInteger(pTeacher->plen, &(pTmp->next));
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHeadBuf); //释放链表 以免内存泄漏
		//在失败后，将pHeadBuf 指针释放，同时需要将pTmp 指针置空，防止野指针
		pTmp = NULL;
		printf("func DER_ItAsn1_WriteInteger() encode plen err:%d \n", ret);
		return ret;
	}

	//编码teacher 结构体
	ret = DER_ItAsn1_WriteSequence(pHeadBuf, &pOutData);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHeadBuf); //释放链表 以免内存泄漏
		//在失败后，将pHeadBuf 指针释放，同时需要将pTmp 指针置空，防止野指针
		pTmp = NULL;
		printf("func DER_ItAsn1_WriteSequence() encode  teacher stuct err:%d \n", ret);
		return ret;
	}

	*outData = pOutData; //老师结构体 大节点 传出来
	DER_ITCAST_FreeQueue(pHeadBuf); //释放链表 以免内存泄漏
	pTmp = NULL;

	/* 
	*out = (unsigned char *)malloc(pOutData->dataLen);
	if (*out == NULL)
	{
		ret = 2;
		DER_ITCAST_FreeQueue(pOutData);
		printf("func TeacherEncode() malloc err:%d \n", ret);
		return ret;
	}
	memcpy(*out, pOutData->pData, pOutData->dataLen); //把运算结果copy到新分配的内存块中
	*outlen = pOutData->dataLen;
	*/
	//DER_ITCAST_FreeQueue(pOutData);

	return ret;
}
//Teacher结构体解码
int TeacherDecode(unsigned char *inData, int inLen, Teacher **pStruct)
{
	int					ret = 0;
	ITCAST_ANYBUF		*pTmp = NULL, *pHead = NULL;
	ITCAST_ANYBUF		*pOutData = NULL;
	ITCAST_ANYBUF		*inAnyBuf = NULL;

	Teacher				*pTmpStru = NULL;

/*
	//把c语言buf 转化成 ITCAST_ANYBUF
	inAnyBuf = (ITCAST_ANYBUF *)malloc(sizeof(ITCAST_ANYBUF));
	if (inAnyBuf == NULL)
	{
		ret = 1;
		printf("func TeacherDecode malloc error: %d", ret);
		return ret;
	}
	memset(inAnyBuf, 0, sizeof(ITCAST_ANYBUF));

	inAnyBuf->pData = (unsigned char *)malloc(inLen);
	if (inAnyBuf->pData == NULL)
	{
		DER_ITCAST_FreeQueue(inAnyBuf);
		ret = 2;
		printf("func TeacherDecode malloc error: %d", ret);
		return ret;
	}
	memcpy(inAnyBuf->pData, indata, inLen);
	inAnyBuf->dataLen = inLen;
*/

	//将 ber 格式的字节流，转换成AnyBuf
	ret = DER_ITCAST_String_To_AnyBuf(&inAnyBuf, inData, inLen);
	if (ret != 0)
	{
		if(inAnyBuf != NULL) {
			DER_ITCAST_FreeQueue(inAnyBuf);
		}
		printf("func DER_ITCAST_String_To_AnyBuf error : %d", ret);
		return ret;
	}

	//解码 Teacher 结构体 得到4个节点
	ret = DER_ItAsn1_ReadSequence(inAnyBuf, &pHead);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(inAnyBuf);
		printf("func DER_ItAsn1_ReadSequence() err:%d \n", ret);
		return ret;
	}
	DER_ITCAST_FreeQueue(inAnyBuf);

		//把老师结构体给分配出来
	pTmpStru = (Teacher *)malloc(sizeof(Teacher));
	if (pTmpStru == NULL)
	{
		ret = 3;
		DER_ITCAST_FreeQueue(pHead); //释放链表
		printf("func malloc() err:%d \n", ret);
		return ret;
	}
	memset(pTmpStru, 0, sizeof(Teacher));

	pTmp = pHead;

	//解码 name
	ret = DER_ItAsn1_ReadPrintableString(pTmp, &pOutData);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHead); //释放链表
		pTmp = NULL; //防止野指针
		//解码结构体中的属性值失败，释放结构体空间，并返回
		TeacherDecode_Free(&pTmpStru);
		printf("func DER_ItAsn1_ReadPrintableString() err:%d \n", ret);
		return ret;
	}
	//给name变量赋值
	memcpy(pTmpStru->name, pOutData->pData, pOutData->dataLen);
	pTmp = pTmp->next; //跳到下一个节点
	DER_ITCAST_FreeQueue(pOutData);

	//解码age
	ret = DER_ItAsn1_ReadInteger(pTmp, &(pTmpStru->age));
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHead); //释放pHead 链表
		DER_ITCAST_FreeQueue(pTmp); //释放pTmp 链表，此处为什么还需要写pTmp的释放，因为此时的pTmp!= pHead了
		//解码结构体中的属性值失败，释放结构体空间，并返回
		TeacherDecode_Free(&pTmpStru);
		printf("func DER_ItAsn1_ReadInteger() err:%d \n", ret);
		return ret;
	}
	pTmp = pTmp->next; //跳到下一个节点

	//解码 p
	ret = DER_ItAsn1_ReadPrintableString(pTmp, &pOutData);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHead); //释放链表
		DER_ITCAST_FreeQueue(pTmp);
		//解码结构体中的属性值失败，释放结构体空间，并返回
		TeacherDecode_Free(&pTmpStru);
		printf("func DER_ItAsn1_ReadPrintableString() err:%d \n", ret);
		return ret;
	}
	pTmpStru->p = (char *)malloc(pOutData->dataLen + 1);
	if (pTmpStru->p == NULL)
	{
		ret = 4;
		printf("func malloc err:%d \n", ret);
		return ret;
	}
	memcpy(pTmpStru->p, pOutData->pData, pOutData->dataLen);
	pTmpStru->p[pOutData->dataLen] = '\0';

	pTmp = pTmp->next; //跳到下一个节点
	DER_ITCAST_FreeQueue(pOutData);

	//解码 plen
	ret = DER_ItAsn1_ReadInteger(pTmp, &(pTmpStru->plen));
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHead); //释放链表
		DER_ITCAST_FreeQueue(pTmp);
		//解码结构体中的属性值失败，释放结构体空间，并返回
		TeacherDecode_Free(&pTmpStru);
		printf("func DER_ItAsn1_ReadInteger() err:%d \n", ret);
		return ret;
	}
	DER_ITCAST_FreeQueue(pTmp);

	*pStruct = pTmpStru; //间接赋值

	return ret;
}
//Teacher结构体 释放内存
int TeacherDecode_Free(Teacher **pStruct)
{
	Teacher *tmp = NULL;
	if (pStruct == NULL)
	{
		return 0;
	}

	tmp = *pStruct;

	if (tmp != NULL)
	{
		free(tmp->p);
		free(tmp);
	}
	*pStruct = NULL; // 1 不但把指针所指向的内存给释放掉 2 同时把实参赋值 NULL 避免野指针
	return 0;
}

//MsgKey_Req 密钥请求报文 结构体 编码
int MsgKey_ReqEncode(MsgKey_Req *msgKey_Req , ITCAST_ANYBUF **outData){

	/*  请求报文格式
	typedef struct _MsgKey_Req
	{
		//1 密钥协商  	//2 密钥校验; 	//3 密钥注销
		int				cmdType;		//报文命令码 
		char			clientId[12];	//客户端编号
		char			AuthCode[16];	//认证码
		char			serverId[12];	//服务器端编号 
		char			r1[64];			//客户端随机数
	}MsgKey_Req;
	*/

	ITCAST_ANYBUF *pTmp=NULL, *pHeadBuf = NULL;
	ITCAST_ANYBUF *pTmpBuf=NULL;
	int ret=0;
	ITCAST_ANYBUF *pOutData=NULL;
	
	// 编码 cmdType
	ret = DER_ItAsn1_WriteInteger(msgKey_Req->cmdType, &pHeadBuf);
	if (ret != 0)
	{
		if(pHeadBuf != NULL) {
			DER_ITCAST_FreeQueue(pHeadBuf);
		}
		printf("DER_ItAsn1_WriteInteger 编码cmdType error: %d\n", ret);
		return ret;
	}
	pTmp = pHeadBuf; //保存头buf

	//编码客户端编号 clientId[12]
		//1 先将 char  类型的name 转换成 ITCAST_ANYBUF 类型
	ret = DER_ITCAST_String_To_AnyBuf(&pTmpBuf, msgKey_Req->clientId, strlen(msgKey_Req->clientId));
	if (ret != 0)
	{	
		if(pTmpBuf != NULL) {
			DER_ITCAST_FreeQueue(pTmpBuf);
		}
		printf("DER_ITCAST_String_To_AnyBuf  msgKey_Req->clientId 转为ITCAST_ANYBUF 类型 error: %d\n", ret);
		return ret;
	}
		// 2 clientId  --> TLV
	ret = DER_ItAsn1_WritePrintableString(pTmpBuf, &(pTmp->next));
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHeadBuf);
		pTmp = NULL;
		printf("DER_ItAsn1_WritePrintableString 将 clientId 编码 error: %d\n", ret);
		return ret;
	}
	pTmp = pTmp->next;

	//编码AuthCode[16] 认证码
		//1 先将 char  编码AuthCode 转换成 ITCAST_ANYBUF 类型 
	DER_ITCAST_FreeQueue(pTmpBuf); //先清空 pTmpBuf
	ret = DER_ITCAST_String_To_AnyBuf(&pTmpBuf, msgKey_Req->AuthCode, strlen(msgKey_Req->AuthCode));
	if (ret != 0)
	{
		if(pTmpBuf != NULL) {
			DER_ITCAST_FreeQueue(pTmpBuf);
		}
		printf("DER_ITCAST_String_To_AnyBuf  msgKey_Req->AuthCode 转为ITCAST_ANYBUF 类型 error: %d\n", ret);
		return ret;
	}
		// 2 AuthCode  --> TLV
	ret = DER_ItAsn1_WritePrintableString(pTmpBuf, &(pTmp->next));
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pTmp);
		DER_ITCAST_FreeQueue(pHeadBuf);
		printf("DER_ItAsn1_WritePrintableString 将 msgKey_Req->AuthCode 编码 error: %d\n", ret);
		return ret;
	}
	pTmp = pTmp->next;

	//编码serverId[12] 服务器端编号 
		//1 先将 char  编码serverId 转换成 ITCAST_ANYBUF 类型 
	DER_ITCAST_FreeQueue(pTmpBuf); //先清空 pTmpBuf
	ret = DER_ITCAST_String_To_AnyBuf(&pTmpBuf, msgKey_Req->serverId, strlen(msgKey_Req->serverId));
	if (ret != 0)
	{
		if(pTmpBuf != NULL) {
			DER_ITCAST_FreeQueue(pTmpBuf);
		}
		printf("DER_ITCAST_String_To_AnyBuf  msgKey_Req->serverId 转为ITCAST_ANYBUF 类型 error: %d\n", ret);
		return ret;
	}
		// 2 serverId  --> TLV
	ret = DER_ItAsn1_WritePrintableString(pTmpBuf, &(pTmp->next));
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pTmp);
		DER_ITCAST_FreeQueue(pHeadBuf);
		printf("DER_ItAsn1_WritePrintableString 将 msgKey_Req->serverId 编码 error: %d\n", ret);
		return ret;
	}
	pTmp = pTmp->next;

	//编码r1[64] 客户端随机数
		//1 先将 char  编码serverId 转换成 ITCAST_ANYBUF 类型 
	DER_ITCAST_FreeQueue(pTmpBuf); //先清空 pTmpBuf
	ret = DER_ITCAST_String_To_AnyBuf(&pTmpBuf, msgKey_Req->r1, strlen(msgKey_Req->r1));
	if (ret != 0)
	{
		if(pTmpBuf != NULL) {
			DER_ITCAST_FreeQueue(pTmpBuf);
		}
		printf("DER_ITCAST_String_To_AnyBuf  msgKey_Req->r1 转为ITCAST_ANYBUF 类型 error: %d\n", ret);
		return ret;
	}
		// 2 r1  --> TLV
	ret = DER_ItAsn1_WritePrintableString(pTmpBuf, &(pTmp->next));
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pTmp);
		DER_ITCAST_FreeQueue(pHeadBuf);
		printf("DER_ItAsn1_WritePrintableString 将 r1 编码 error: %d\n", ret);
		return ret;
	}
	pTmp = pTmp->next;
	//对MsgKey_Req 结构体进行编码
	ret = DER_ItAsn1_WriteSequence(pHeadBuf, &pOutData);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHeadBuf);
		DER_ITCAST_FreeQueue(pTmp);
		if(pOutData != NULL) {
			DER_ITCAST_FreeQueue(pOutData);
		}
		printf("DER_ItAsn1_WriteSequence error: %d\n", ret);
		return ret;
	}
	*outData = pOutData;
	DER_ITCAST_FreeQueue(pHeadBuf);
	DER_ITCAST_FreeQueue(pTmp);
	return 0;
}
//MsgKey_Req 密钥请求报文 结构体 解码
int MsgKey_ReqDecode(unsigned char *inData, int inLen, MsgKey_Req **msgKey_Req){
	ITCAST_ANYBUF *pHead=NULL , *pTmp=NULL;
	ITCAST_ANYBUF *tmpAnyBuf=NULL;
	ITCAST_ANYBUF *pOutData=NULL;
	int ret=0;
	MsgKey_Req *msgReq=NULL;
	/* 
	typedef struct _MsgKey_Req
	{
		//1 密钥协商  	//2 密钥校验; 	//3 密钥注销
		int				cmdType;		//报文命令码 
		char			clientId[12];	//客户端编号
		char			AuthCode[16];	//认证码
		char			serverId[12];	//服务器端编号 
		char			r1[64];			//客户端随机数
	}MsgKey_Req;
	 */
	//因传过来的是unsigned char *inData,int inLen,所以需要将其转换为buf类型
	// 转码 BER 报文 unsigned char * --> ITCAST_ANYBUF
	ret = DER_ITCAST_String_To_AnyBuf(&tmpAnyBuf, inData, inLen);
	if (ret != 0)
	{
		if (tmpAnyBuf != NULL)
			DER_ITCAST_FreeQueue(tmpAnyBuf);

		printf(" Decode DER_ITCAST_String_To_AnyBuf error: %d\n", ret);
		return ret;
	}

	// 解码大MsgKey_Req 结构体
	ret = DER_ItAsn1_ReadSequence(tmpAnyBuf, &pHead);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(tmpAnyBuf);
		if(pHead != NULL) {
			DER_ITCAST_FreeQueue(pHead);
		}
		printf(" Decode DER_ItAsn1_ReadSequence error: %d\n", ret);
		return ret;
	}
	DER_ITCAST_FreeQueue(tmpAnyBuf);
	// 给MsgKey_Req 结构体 malloc 空间。
	if (msgReq == NULL)
	{
		msgReq = (MsgKey_Req *)malloc(sizeof(MsgKey_Req));
		if (msgReq == NULL)
		{
			DER_ITCAST_FreeQueue(pHead);
			ret = -1;
			printf("MsgKey_Req malloc error: %d\n", ret);
			return ret;
		}
		memset(msgReq, 0, sizeof(MsgKey_Req));
	}
	pTmp = pHead;

	//解码 r1[64] 客户端随机数
	ret = DER_ItAsn1_ReadPrintableString(pTmp, &pOutData);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHead);
		pTmp = NULL;
		MsgKey_ReqDecode_Free(&msgReq);
		printf(" Decode DER_ItAsn1_ReadPrintableString msgReq error: %d\n", ret);
		return ret;
	}
	// ppPrintString -> pData; ---> msgReq
	memcpy(msgReq->r1, pOutData->pData, pOutData->dataLen);
	pTmp = pTmp->next;

	//serverId服务器端编号 
	ret = DER_ItAsn1_ReadPrintableString(pTmp, &pOutData);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pTmp);
		DER_ITCAST_FreeQueue(pHead);
		MsgKey_ReqDecode_Free(&msgReq);
		printf(" Decode DER_ItAsn1_ReadPrintableString serverId error: %d\n", ret);
		return ret;
	}
	// ppPrintString -> pData; ---> msgReq
	memcpy(msgReq->serverId, pOutData->pData, pOutData->dataLen);
	pTmp = pTmp->next;

	//AuthCode[16];	//认证码 解码
	ret = DER_ItAsn1_ReadPrintableString(pTmp, &pOutData);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHead);
		DER_ITCAST_FreeQueue(pTmp);
		MsgKey_ReqDecode_Free(&msgReq);
		printf(" Decode DER_ItAsn1_ReadPrintableString AuthCode error: %d\n", ret);
		return ret;
	}
	// ppPrintString -> pData; ---> msgReq
	memcpy(msgReq->AuthCode, pOutData->pData, pOutData->dataLen);
	pTmp = pTmp->next;

	//	char clientId[12];	//客户端编号
	ret = DER_ItAsn1_ReadPrintableString(pTmp, &pOutData);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHead);
		DER_ITCAST_FreeQueue(pTmp);
		MsgKey_ReqDecode_Free(&msgReq);
		printf(" Decode DER_ItAsn1_ReadPrintableString clientId error: %d\n", ret);
		return ret;
	}
	// ppPrintString -> pData; ---> msgReq
	memcpy(msgReq->clientId, pOutData->pData, pOutData->dataLen);
	pTmp = pTmp->next;

	//	int	cmdType;		//报文命令码  解码
	ret = DER_ItAsn1_ReadInteger(pTmp, &msgReq->cmdType);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHead);
		DER_ITCAST_FreeQueue(pTmp);
		MsgKey_ReqDecode_Free(&msgReq);
		printf(" Decode DER_ItAsn1_ReadInteger cmdType error: %d\n", ret);
		return ret;
	}
	*msgKey_Req = msgReq;
	DER_ITCAST_FreeQueue(pTmp);
	DER_ITCAST_FreeQueue(pHead);
	return 0;
}
//MsgKey_Req  密钥请求报文 结构体 释放内存
int MsgKey_ReqDecode_Free( MsgKey_Req **msgKey_Req){
{
	if (msgKey_Req == NULL)
	{
		return 0;
	}
	if(* msgKey_Req != NULL) {
		* msgKey_Req = NULL; 
	}
	return 0;
}
}

//MsgKey_Res 密钥应答报文 结构体 编码
int MsgKey_ResEncode(MsgKey_Res *msgKey_Res , ITCAST_ANYBUF **outData){
	/* 
	typedef struct  _MsgKey_Res
	{
	int					rv;				//返回值
	char				clientId[12];	//客户端编号
	char				serverId[12];	//服务器编号
	unsigned char		r2[64];			//服务器端随机数
	int					seckeyid;		//对称密钥编号 //modfy 2015.07.20
	}MsgKey_Res;
	 */
	ITCAST_ANYBUF *pTmp=NULL, *pHeadBuf = NULL;
	ITCAST_ANYBUF *pTmpBuf=NULL;
	int ret=0;
	ITCAST_ANYBUF *pOutData=NULL;
	
	// 编码 rv 返回值
	ret = DER_ItAsn1_WriteInteger(msgKey_Res->rv , &pHeadBuf);
	if (ret != 0)
	{
		if(pHeadBuf != NULL) {
			DER_ITCAST_FreeQueue(pHeadBuf);
		}
		printf("DER_ItAsn1_WriteInteger 编码rv error: %d\n", ret);
		return ret;
	}
	pTmp = pHeadBuf; //保存头buf

	//编码客户端编号 clientId[12]
		//1 先将 char  类型的name 转换成 ITCAST_ANYBUF 类型
	ret = DER_ITCAST_String_To_AnyBuf(&pTmpBuf, msgKey_Res->clientId, strlen(msgKey_Res->clientId));
	if (ret != 0)
	{
		if(pTmpBuf != NULL){
			DER_ITCAST_FreeQueue(pTmpBuf);
		}
		DER_ITCAST_FreeQueue(pHeadBuf);
		pTmp = NULL;
		printf("DER_ITCAST_String_To_AnyBuf  msgKey_Res->clientId 转为ITCAST_ANYBUF 类型 error: %d\n", ret);
		return ret;
	}
		// 2 clientId  --> TLV
	ret = DER_ItAsn1_WritePrintableString(pTmpBuf, &(pTmp->next));
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pTmp);
		pHeadBuf = NULL;
		DER_ITCAST_FreeQueue(pTmpBuf);
		printf("DER_ItAsn1_WritePrintableString 将 clientId 编码 error: %d\n", ret);
		return ret;
	}
	pTmp = pTmp->next;

	//编码serverId[12] 服务器端编号 
		//1 先将 char  编码serverId 转换成 ITCAST_ANYBUF 类型 
	DER_ITCAST_FreeQueue(pTmpBuf); //先清空 pTmpBuf
	ret = DER_ITCAST_String_To_AnyBuf(&pTmpBuf, msgKey_Res->serverId, strlen(msgKey_Res->serverId));
	if (ret != 0)
	{
		if(pTmpBuf != NULL) {
			DER_ITCAST_FreeQueue(pTmpBuf);
		}
		DER_ITCAST_FreeQueue(pTmp);
		DER_ITCAST_FreeQueue(pHeadBuf);
		printf("DER_ITCAST_String_To_AnyBuf  msgKey_Res->serverId 转为ITCAST_ANYBUF 类型 error: %d\n", ret);
		return ret;
	}
		// 2 serverId  --> TLV
	ret = DER_ItAsn1_WritePrintableString(pTmpBuf, &(pTmp->next));
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pTmpBuf);
		DER_ITCAST_FreeQueue(pHeadBuf);
		DER_ITCAST_FreeQueue(pTmp);
		printf("DER_ItAsn1_WritePrintableString 将 msgKey_Res->serverId 编码 error: %d\n", ret);
		return ret;
	}
	pTmp = pTmp->next;

	//编码r2[64] 客户端随机数
		//1 先将 char  编码r2转换成 ITCAST_ANYBUF 类型 
	DER_ITCAST_FreeQueue(pTmpBuf); //先清空 pTmpBuf
	ret = DER_ITCAST_String_To_AnyBuf(&pTmpBuf, msgKey_Res->r2, strlen(msgKey_Res->r2));
	if (ret != 0)
	{
		if(pTmpBuf != NULL) {
			DER_ITCAST_FreeQueue(pTmpBuf);
		}
		DER_ITCAST_FreeQueue(pTmp);
		DER_ITCAST_FreeQueue(pHeadBuf);
		printf("DER_ITCAST_String_To_AnyBuf  msgKey_Res->r2 转为ITCAST_ANYBUF 类型 error: %d\n", ret);
		return ret;
	}
		// 2 r1  --> TLV
	ret = DER_ItAsn1_WritePrintableString(pTmpBuf, &(pTmp->next));
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pTmpBuf);
		DER_ITCAST_FreeQueue(pTmp);
		DER_ITCAST_FreeQueue(pHeadBuf);
		printf("DER_ItAsn1_WritePrintableString 将 r2 编码 error: %d\n", ret);
		return ret;
	}
	pTmp = pTmp->next;

	//编码 int seckeyid;	对称密钥编号 //modfy 2015.07.20
	ret = DER_ItAsn1_WriteInteger(msgKey_Res->seckeyid , &pTmp);
	if (ret != 0)
	{
		printf("DER_ItAsn1_WriteInteger 编码seckeyid error: %d\n", ret);
		return ret;
	}
	//对MsgKey_Res 结构体进行编码
	ret = DER_ItAsn1_WriteSequence(pHeadBuf, &pOutData);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHeadBuf);
		printf("DER_ItAsn1_WriteSequence error: %d\n", ret);
		return ret;
	}
	*outData = pOutData;
	DER_ITCAST_FreeQueue(pHeadBuf);
	DER_ITCAST_FreeQueue(pTmp);
	return 0;

}
//MsgKey_Res 密钥应答报文 结构体 解码
int MsgKey_ResDecode(unsigned char *inData, int inLen, MsgKey_Res **msgKey_Res){
	/* 
	typedef struct  _MsgKey_Res
	{
		int					rv;				//返回值
		char				clientId[12];	//客户端编号
		char				serverId[12];	//服务器编号
		unsigned char		r2[64];			//服务器端随机数
		int					seckeyid;		//对称密钥编号 //modfy 2015.07.20
	}MsgKey_Res;
	 */
	ITCAST_ANYBUF *pHead=NULL , *pTmp=NULL;
	ITCAST_ANYBUF *tmpAnyBuf=NULL;
	ITCAST_ANYBUF *pOutData=NULL;
	int ret=0;
	MsgKey_Res *msgRes=NULL;
	
	//因传过来的是unsigned char *inData,int inLen,所以需要将其转换为buf类型
	// 转码 BER 报文 unsigned char * --> ITCAST_ANYBUF
	ret = DER_ITCAST_String_To_AnyBuf(&tmpAnyBuf, inData, inLen);
	if (ret != 0)
	{
		if (tmpAnyBuf != NULL)
			DER_ITCAST_FreeQueue(tmpAnyBuf);

		printf(" Decode DER_ITCAST_String_To_AnyBuf error: %d\n", ret);
		return ret;
	}

	// 解码大MsgKey_Res 结构体
	ret = DER_ItAsn1_ReadSequence(tmpAnyBuf, &pHead);
	if (ret != 0)
	{
		if (tmpAnyBuf != NULL)
			DER_ITCAST_FreeQueue(tmpAnyBuf);
		printf(" Decode DER_ItAsn1_ReadSequence error: %d\n", ret);
		return ret;
	}
	DER_ITCAST_FreeQueue(tmpAnyBuf);
	// 给MsgKey_Res 结构体 malloc 空间。
	if (msgRes == NULL)
	{
		msgRes = (MsgKey_Res *)malloc(sizeof(MsgKey_Res));
		if (msgRes == NULL)
		{
			DER_ITCAST_FreeQueue(pHead);
			ret = -1;
			printf("MsgKey_Req malloc error: %d\n", ret);
			return ret;
		}
		memset(msgRes, 0, sizeof(MsgKey_Res));
	}
	pTmp = pHead;
	
	// int seckeyid 对称密钥编号
	ret = DER_ItAsn1_ReadInteger(pTmp, &msgRes->seckeyid);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHead);
		pTmp = NULL;
		MsgKey_ResDecode_Free(&msgRes);
		printf(" Decode DER_ItAsn1_ReadPrintableString seckeyid error: %d\n", ret);
		return ret;
	}
	pTmp = pTmp->next;

	//解码 r2[64] 客户端随机数
	ret = DER_ItAsn1_ReadPrintableString(pTmp, &pOutData);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHead);
		DER_ITCAST_FreeQueue(pTmp);
		MsgKey_ResDecode_Free(&msgRes);
		printf(" Decode DER_ItAsn1_ReadPrintableString msgRes error: %d\n", ret);
		return ret;
	}
	// ppPrintString -> pData; ---> msgReq
	memcpy(msgRes->r2, pOutData->pData, pOutData->dataLen);
	pTmp = pTmp->next;

	//serverId服务器端编号 
	ret = DER_ItAsn1_ReadPrintableString(pTmp, &pOutData);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHead);
		DER_ITCAST_FreeQueue(pTmp);
		MsgKey_ResDecode_Free(&msgRes);
		printf(" Decode DER_ItAsn1_ReadPrintableString serverId error: %d\n", ret);
		return ret;
	}
	// ppPrintString -> pData; ---> msgReq
	memcpy(msgRes->serverId, pOutData->pData, pOutData->dataLen);
	pTmp = pTmp->next;

	//clientId[12];	//客户端编号
	ret = DER_ItAsn1_ReadPrintableString(pTmp, &pOutData);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHead);
		DER_ITCAST_FreeQueue(pTmp);
		MsgKey_ResDecode_Free(&msgRes);
		printf(" Decode DER_ItAsn1_ReadPrintableString AuthCode error: %d\n", ret);
		return ret;
	}
	// ppPrintString -> pData; ---> msgReq
	memcpy(msgRes->clientId, pOutData->pData, pOutData->dataLen);
	pTmp = pTmp->next;

	//	int	rv //返回值;
	ret = DER_ItAsn1_ReadInteger(pTmp, &msgRes->rv);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHead);
		DER_ITCAST_FreeQueue(pTmp);
		MsgKey_ResDecode_Free(&msgRes);
		printf(" Decode DER_ItAsn1_ReadInteger cmdType error: %d\n", ret);
		return ret;
	}
	*msgKey_Res = msgRes;
	DER_ITCAST_FreeQueue(pHead);
	DER_ITCAST_FreeQueue(pTmp);
	return 0;
}
//MsgKey_Res 密钥应答报文 结构体 释放内存
int MsgKey_ResDecode_Free( MsgKey_Res **msgKey_Res){
	if (msgKey_Res == NULL)
	{
		return 0;
	}
	if(* msgKey_Res != NULL) {
		* msgKey_Res = NULL; 
	}
	return 0;
}


// 对 type 和  结构体进行编码 封装。
int MsgEncode(
	void			*pStruct, /*in*/
	int				type,
	unsigned char	**outData, /*out*/
	int				*outLen)
{
	ITCAST_ANYBUF	*pHeadbuf = NULL, *pTemp = NULL;
	ITCAST_ANYBUF	*pOutData = NULL;
	int				ret = 0;

	if (pStruct == NULL && type < 0 || outData == NULL || outLen == NULL)
	{
		ret = KeyMng_ParamErr;
		printf("func MsgEncode() err:%d \n", ret);
		return ret;
	}

	//对参数中的 int type 编码
	ret = DER_ItAsn1_WriteInteger(type, &pHeadbuf);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHeadbuf);
		printf("func DER_ItAsn1_WriteInteger()　err:%d \n", ret);
		return ret;
	}
	pTemp = pHeadbuf;

	//根据传入的type类型，对不同的结构体进行编码 
	switch (type)
	{
	case ID_MsgKey_Teacher:
		//编码techer结构体
		ret=TeacherEncode(pStruct , &(pTemp->next));
		if(ret != 0 ){
			DER_ITCAST_FreeQueue(pHeadbuf);
			pTemp = NULL;
			printf("func TeacherEncode() encode teacher stuct　err:%d \n", ret);
			return ret;
		}
		break;

	case ID_MsgKey_Req:
		//密钥请求报文  编码
		ret = MsgKey_ReqEncode(pStruct , &(pTemp->next));
		if(ret != 0 ){
			DER_ITCAST_FreeQueue(pHeadbuf);
			pTemp = NULL;
			printf("func MsgKey_ReqEncode() encode Msg_Req stuct　err:%d \n", ret);
			return ret;
		}
		break;

	case ID_MsgKey_Res:
		//密钥应答报文 编码
		ret = MsgKey_ResEncode(pStruct , &(pTemp->next));
		if(ret != 0 ){
			DER_ITCAST_FreeQueue(pHeadbuf);
			pTemp = NULL;
			printf("func MsgKey_ResEncode() encode Msg_Res stuct　err:%d \n", ret);
			return ret;
		}
		break;

	default:
		ret = KeyMng_TypeErr;
		printf("类型输入失败()　itype:%d err:%d \n", type, ret);
		break;
	}

	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHeadbuf);
		printf("编码失败err:%d \n", ret);
		return ret;
	}

	//对type 和 结构体 再做一次 TLV
	ret = DER_ItAsn1_WriteSequence(pHeadbuf, &pOutData);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHeadbuf);
		pTemp != NULL;
		printf("func DER_ItAsn1_WriteSequence()　err:%d \n", ret);
		return ret;
	}

	*outData = (unsigned char *)malloc(pOutData->dataLen);
	if (*outData == NULL)
	{
		DER_ITCAST_FreeQueue(pOutData);
		DER_ITCAST_FreeQueue(pHeadbuf);
		ret = KeyMng_MallocErr;
		printf("malloc()　err:%d \n", ret);
		return ret;
	}
	memcpy(*outData, pOutData->pData, pOutData->dataLen);
	*outLen = pOutData->dataLen;
	DER_ITCAST_FreeQueue(pOutData);
	DER_ITCAST_FreeQueue(pHeadbuf);
	return ret;
}

int MsgDecode(
	unsigned char *inData,/*in*/
	int           inLen,
	void          **pStruct /*out*/,
	int           *type /*out*/)
{
	ITCAST_ANYBUF		*pHeadBuf = NULL, *inAnyBuf = NULL;
	int					ret = 0;
	unsigned long		itype = 0;

	//将 ber 格式的字节流，转换成 AnyBuf
	ret = DER_ITCAST_String_To_AnyBuf(&inAnyBuf, inData, inLen);
	if (ret != 0)
	{
		if(inAnyBuf != NULL){
			DER_ITCAST_FreeQueue(inAnyBuf);
		}
		printf("func DER_ITCAST_String_To_AnyBuf 解码 传入 大 anybuf 失败 error : %d", ret);
		return ret;
	}

	ret = DER_ItAsn1_ReadSequence(inAnyBuf, &pHeadBuf);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(inAnyBuf);
		printf("func DER_ItAsn1_ReadSequence() err:%d \n", ret);
		return ret;
	}
	DER_ITCAST_FreeQueue(inAnyBuf);

	//解析 type
	ret = DER_ItAsn1_ReadInteger(pHeadBuf, &itype);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHeadBuf); 
		printf("func DER_ItAsn1_ReadInteger() err:%d \n", ret);
		return ret;
	}

	switch (itype)
	{
	case ID_MsgKey_Teacher:
		//解码 老师结构体
		ret = TeacherDecode(pHeadBuf->next->pData, pHeadBuf->next->dataLen, (Teacher **)pStruct);
		break;
	case ID_MsgKey_Req:
		//解码 请求报文 
		ret = MsgKey_ReqDecode(pHeadBuf->next->pData, pHeadBuf->next->dataLen, (MsgKey_Req **)pStruct);
		break;
	case ID_MsgKey_Res:
		//解码 应答报文
		ret = MsgKey_ResDecode(pHeadBuf->next->pData, pHeadBuf->next->dataLen, (MsgKey_Res **)pStruct);
		break;
	default:
		ret = KeyMng_TypeErr;
		printf("itype:%d失败 :%d \n", itype, ret);
		break;
	}
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHeadBuf);
		return ret;
	}
	*type = itype;
	DER_ITCAST_FreeQueue(pHeadBuf);
	return ret;
}


int MsgMemFree(void **point, int type)
{
	if (point == NULL)
	{
		return 0;
	}

	if (type == 0) //释放 Encode编码以后的内存块
	{ 
		if (*point) free(*point);
		*point = NULL;
		return 0;
	}

	switch (type)
	{
	case ID_MsgKey_Teacher:
		TeacherDecode_Free((Teacher **)point);
		break;
	case ID_MsgKey_Req:
		MsgKey_ReqDecode_Free((MsgKey_Req **)point);
		break;
	case ID_MsgKey_Res:
		MsgKey_ResDecode_Free((MsgKey_Res **)point);
		break;
	default:
		break;
	}

	return 0;
}
