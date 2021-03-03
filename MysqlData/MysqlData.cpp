// MysqlData.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "MysqlOperate.h"

int main()
{
	IMysqlOperate* p = GetFD();
	p->ConnectDatabase();
	p->InsertRecordData("测试", "测试", "测试", "测试", 5);
}


