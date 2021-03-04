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
	virtual void FreeConnect() = 0;
	virtual int QueryReqData(std::string company, std::string ad) = 0;
	virtual void ExportAdExcel() = 0;
};


class MysqlOperate : public IMysqlOperate
{
public:
	MysqlOperate();
    ~MysqlOperate();

	//继承的实现
	//连接数据库
	bool ConnectDatabase();
	//插入广告播放记录数据 公司名称 广告名称 开始时间 结束时间 播放次数
	bool InsertRecordData(std::string company, std::string ad, std::string time_bg, std::string time_ed, int times);
	//在程序结束的时候请调用这个函数，释放资源
	void FreeConnect();
	//查询播放需求记录中的播放次数 参数为所要查询的公司名称以及参数名称
	int QueryReqData(std::string company, std::string ad);
	//在指定位置导出播放历史表格
	void ExportAdExcel();

public:
	MYSQL mysql; //mysql连接 
	MYSQL_RES *m_dat_res; //这个结构代表返回行的一个查询结果集
	MYSQL_ROW m_dat_row; //一个行数据的类型安全(type-safe)的表示，表示数据行的列

private:
	

};

//工厂函数
IMysqlOperate * GetFD();
