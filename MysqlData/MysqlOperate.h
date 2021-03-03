#pragma once
#include <stdio.h>  
#include <WinSock.h>  //一定要包含这个
#include "mysql.h"
#include <Windows.h> 
#include <vector>
#include <string>
//包含附加依赖项，也可以在工程--属性里面设置  
#pragma comment(lib,"wsock32.lib") 
#pragma comment(lib,"libmysql.lib")

//默认虚函数类
class IMysqlOperate
{
public:
	virtual bool ConnectDatabase() = 0;
	virtual bool InsertRecordData(std::string company, std::string ad, std::string time_bg, std::string time_ed, int times) = 0;
};


class MysqlOperate : public IMysqlOperate
{
public:
	MysqlOperate();
    ~MysqlOperate();

	//继承的实现
	//连接数据库
	bool ConnectDatabase();
	//插入数据
	bool InsertRecordData(std::string company, std::string ad, std::string time_bg, std::string time_ed, int times);
//MySql使用的变量
public:
	MYSQL mysql; //mysql连接 
	MYSQL_RES *m_dat_res; //这个结构代表返回行的一个查询结果集
	MYSQL_ROW m_dat_row; //一个行数据的类型安全(type-safe)的表示，表示数据行的列

private:
	

};

//工厂函数
IMysqlOperate * GetFD();
