// MyPass_Demo.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "ctrl.h"
#define  OPTION int 
int main()
{
	PPASSWORD pPwd = nullptr;//密码数组
	int nCount = 0;          //当前密码个数
	g_nNum = 0;

	readInfo(&pPwd,&nCount); //从本地文件中读取密码，用于初始化密码本
	 
	while(true) 
	{
		printf("----------请输入你的选择-----------\n");
		printf("        1 查看所有密码：\n");
		printf("        2 新增密码：\n");
		printf("        3 删除密码：\n");
		printf("        4 修改密码：\n");
		printf("        5 查询密码：\n");
		printf("        6 生成文件：\n");
		printf("-----------------------------------\n");
		OPTION   op;
		scanf_s("%d",&op);
		switch (op)
		{
			case 查看所有:
				searchAllInfo(pPwd, nCount);
				break;
			case 新增:
				insertInfo(pPwd, &nCount);
				break;
			case 删除:
				deleteInfo(pPwd, &nCount);
				break;
			case 修改:
				alterInfo(pPwd, nCount);
				break;
			case 查询:
				searchInfo(pPwd, nCount);
				break;
			case 保存文本:
				SaveInfoA(pPwd, nCount);
				break;
		    default:
			    break;
		}
	}
    return 0;
}

