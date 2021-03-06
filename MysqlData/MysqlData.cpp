// MysqlData.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "MysqlOperate.h"
#include <string>

using namespace std;

int main()
{
	IMysqlOperate* p = GetFD();
	p->ConnectDatabase();
	string test = "测试";
	//p->InsertRecordData("2020-1-1",test, test, test, test, 5);
	//p->QueryReqData("a", "b");
	//p->ExportAdExcel();
	
}


