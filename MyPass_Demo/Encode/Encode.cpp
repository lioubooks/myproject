// Encode.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<string.h>
#include<stdio.h>
int main()
{
	FILE *mydata=nullptr;
	errno_t err;
	err = fopen_s(&mydata, "E:\\VS2017\\15PB\\text0.i", "wb");
	char  mytext[] = "这是一个爱奇艺的账号密码：aiqiyi2017zqq";
	int len = strlen(mytext);
	//加密
	for (int i = 0; i < len;i++) {
		mytext[i] ^= 0xfefe;
	}
	printf("密文：");
	puts(mytext);
	if (err!=0)
	{
		printf("打开文件失败！\n");
	}
	else {
		fputs(mytext, mydata);
		fclose(mydata);
	}
	//解密
	for (int i = 0; i < len; i++) {
		mytext[i] ^= 0xfefe;
	}
	printf("\n明文：");
	puts(mytext);

    return 0;
}

