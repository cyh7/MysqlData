#include "MysqlOperate.h"

//查询数据库需要用数据

using namespace std;


char query[150]; //查询语句

MysqlOperate::MysqlOperate()
{

}

MysqlOperate::~MysqlOperate()
{

}

bool MysqlOperate::ConnectDatabase()
{
	//初始化mysql
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	const char host[] = "localhost";
	const char user[] = "root";
	const char psw[] = "1234";
	const char table[] = "test";
	const int port = 3306;
	//返回false则连接失败，返回true则连接成功  
	if (!(mysql_real_connect(&mysql, host, user, psw, table, port, NULL, 0)))
		//中间分别是主机，用户名，密码，数据库名，端口号（可以写默认0或者3306等），可以先写成参数再传进去  
	{
		//printf("Error connecting to database:%s\n", mysql_error(&mysql));
		return false;
	}
	else
	{
		printf("Connected...\n");
		return true;
	}
}

bool MysqlOperate::InsertRecordData(string company, string ad, string time_bg, string time_ed, int times)
{

	sprintf(query, "insert into ad values('%s', '%s', '%s', '%s', %d);", company, ad, time_bg, time_ed, times);
	if (mysql_query(&mysql, query))//执行SQL语句  
	{
		printf("Query failed (%s)\n", mysql_error(&mysql));
		return false;
	}
	else
	{
		printf("Insert success\n");
		return true;
	}
}

IMysqlOperate * GetFD()
{
	return new MysqlOperate();
}
