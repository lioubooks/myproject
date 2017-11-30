#include"stdafx.h"
#include "ctrl.h"
#include <stdlib.h>

void searchAllInfo(PASSWORD pwd[],int nCount) {
	printf("====共计： %3d条记录====================\n",nCount);
	for (size_t i = 0; i < nCount;i++) {
		printf("---ID: %3d---------------------\n",i);
		printf("目  标： %s  \n", pwd[i].website);
		printf("用户名： %s  \n", pwd[i].userName);
		printf("密  码： %s  \n", pwd[i].passWord);
		printf("备  注： %s  \n", pwd[i].note);
	}
	printf("\n");
	system("pause");
	system("CLS");
}
void insertInfo(PASSWORD pwd[],int * pnCount) {
	int i = *pnCount;
	if (i<0||i>=NUM) {
		printf("插入位置异常：%d",i);
		return;
	}
	printf("请输入<目标站点>\n");
	scanf_s("%s", pwd[i].website, 100);
	printf("请输入<用户名>\n");
	scanf_s("%s", pwd[i].userName, 100);
	printf("请输入<密码>\n");
	scanf_s("%s", pwd[i].passWord, 100);
	printf("请输入<备注信息>\n");
	scanf_s("%s", pwd[i].note, 100);

	(*pnCount)++;

	SaveInfoB(pwd, *pnCount);

	printf("\n");
	system("pause");
	system("CLS");
}

void  deleteInfo(PASSWORD pwd[],int * pnCount) {
	int i ;
	printf("请输入待删除项<密码ID>");
	scanf_s("%d", &i);
	if (i < 0||i>=NUM) {
		printf("删除位置异常:%d\n",i);
		return ;
	}
	for (size_t j = i; j < *pnCount-1;j++) {
		pwd[j] = pwd[j+1];
	}
	(*pnCount)--;
	SaveInfoB(pwd, *pnCount);
	printf("\n");
	system("pause");
	system("CLS");
}

void alterInfo(PASSWORD pwd[], int nCount) {
	int i = -1;
	printf("请输入待修改项<密码ID>");
	scanf_s("%d", &i);
	if (i < 0 || i >= NUM) {
		printf("修改位置异常:%d\n", i);
		return;
	}
	else {
		printf("---ID: %3d----------------\n", i);
		printf("目  标： %s  \n", pwd[i].website);
		printf("用户名： %s  \n", pwd[i].userName);
		printf("密  码： %s  \n", pwd[i].passWord);
		printf("备  注： %s  \n", pwd[i].note);
		printf("~修改~\n");
		printf("请输入<目标站点>\n");
		scanf_s("%s", pwd[i].website, 100);
		printf("请输入<用户名>\n");
		scanf_s("%s", pwd[i].userName, 100);
		printf("请输入<密码>\n");
		scanf_s("%s", pwd[i].passWord, 100);
		printf("请输入<备注信息>\n");
		scanf_s("%s", pwd[i].note, 100);
	}
	SaveInfoB(pwd, nCount);
	printf("\n");
	system("pause");
	system("CLS");
}
void searchInfo(PASSWORD pwd[], int nCount) {
	char key[100] = {0};
	printf("请输入查找密码的关键字：\n");
	scanf_s("%s", key, 100);

	int findPwd[100] = {0};
	int nfindCount = 0;
	for (size_t i = 0; i < nCount; i++) {
		if (strstr(pwd[i].website, key)) {
			findPwd[nfindCount++] = i;
			continue;
		}
		if (strstr(pwd[i].userName, key)) {
			findPwd[nfindCount++] = i;
			continue;
		}
		if (strstr(pwd[i].passWord, key)) {
			findPwd[nfindCount++] = i;
			continue;
		}
	}

		printf("===共计匹配：%d条记录============\n",nfindCount);
		for (size_t i = 0; i < nfindCount; i++) {
			int pos = findPwd[i];
			printf("---ID: %3d----------------\n", pos);
			printf("目  标： %s  \n", pwd[pos].website);
			printf("用户名： %s  \n", pwd[pos].userName);
			printf("密  码： %s  \n", pwd[pos].passWord);
			printf("备  注： %s  \n", pwd[pos].note);
		}
		printf("\n");
		system("pause");
		system("CLS");
}

void SaveInfoA(PASSWORD pwd[], int nCount) {
	FILE * pFile;
	errno_t err = fopen_s(&pFile, "E:\\VS2017\\15PB\\mydata.txt", "w");
	if (err!=0) {
		return;
	}
	fprintf(pFile, "====共计: %d条记录==========\n", nCount);
	for (size_t i = 0; i < nCount;i++) {
		fprintf(pFile,"--ID: %3d--------------\n",i);
		fprintf(pFile, "目  标：%s \n", pwd[i].website);
		fprintf(pFile, "用户名：%s \n", pwd[i].userName);
		fprintf(pFile, "密  码：%s \n", pwd[i].passWord);
		fprintf(pFile, "备  注：%s \n", pwd[i].note);
	}
	fclose(pFile);

	printf("保存文本密码生成成功，使用后尽快删除！！\n");
	system("pause");
	system("CLS");
}

void SaveInfoB(PASSWORD pwd[], int nCount) {
	FILE *pFile;
	errno_t err = fopen_s(&pFile, "E:\\VS2017\\15PB\\mydata.i", "wb");
	if (err != 0) {
		return;
	}
	fwrite(&nCount,sizeof(nCount),1,pFile);
	fwrite(&g_nNum, sizeof(g_nNum), 1, pFile);

	int byteSize = sizeof(PASSWORD)*g_nNum;
	char *buf = (char*)malloc(byteSize);
	memcpy_s(buf, byteSize, pwd, byteSize);
	for (size_t i = 0; i < byteSize;i++) {
		buf[i] ^= (i + nCount + g_nNum);
	}
	size_t rlen = fwrite(buf,sizeof(PASSWORD),g_nNum,pFile);
	if (rlen != g_nNum) {
		printf("写入密码文件错误！\n");
	}
	else {
		printf("成功!\n");
	}
	fclose(pFile);
	free(buf);
}

void readInfo(PPASSWORD * ppPwd, int * pnCount) {
	FILE *pFile;
	errno_t err = fopen_s(&pFile, "data.i", "rb");
	if (err!=0) {
		*ppPwd = (PPASSWORD)malloc(sizeof(PASSWORD)*NUM);
		g_nNum = NUM;
		return;
	}
	fread(pnCount,sizeof(int),1,pFile);
	fread(&g_nNum, sizeof(g_nNum), 1, pFile);
	*ppPwd = (PPASSWORD)malloc(sizeof(PASSWORD)*g_nNum);
	memset(*ppPwd, 0, sizeof(PASSWORD)*g_nNum);
	size_t rlen = fread(*ppPwd,sizeof(PASSWORD),g_nNum,pFile);
	if (rlen != g_nNum) {
		printf("读取密码文件错误！\n");
		fclose(pFile);
		return;
	}
	int byteSize = sizeof(PASSWORD)*g_nNum;
	char *buf = (char*)*ppPwd;
	for (size_t i = 0; i < byteSize; i++) {
		buf[i] ^= (i + *pnCount + g_nNum);
	}
	fclose(pFile);
}