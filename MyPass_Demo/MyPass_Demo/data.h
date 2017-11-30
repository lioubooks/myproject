#pragma once
#define 查看所有    1
#define 新增        2
#define 删除        3
#define 修改        4
#define 查询        5
#define 保存文本    6
#define 保存二进制  7
//定义结构体，存储账号密码信息，包括站点、用户名、密码、备注信息 
typedef struct _PASSWORD {
	char website[100];     //站点名
	char userName[100];    //用户名
	char passWord[100];    //密码
	char note[100];        //备注
}PASSWORD, *PPASSWORD;

//全局变量 常量的声明
#define NUM 100            //初始密码本容量
extern  int g_nNum;           //当前密码本容量
