#include "MysqlOperate.h"

//查询的数据库分为两个表
//表1、广告播放记录表 每次播放广告之后会向里边插入广告 表名 ad
//表2、广告需求表  该表由广告投放者插入（插入方式待定），我们负责读取设定的播放次数  表名 requirements

//查询
std::vector<std::string> m_dat_data[100];
using namespace std;

MysqlOperate::MysqlOperate()
{

}

MysqlOperate::~MysqlOperate()
{

}

//连接数据库
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

////插入广告播放记录数据 公司名称 广告名称 开始时间 结束时间 播放次数
bool MysqlOperate::InsertRecordData(string company, string ad, string time_bg, string time_ed, int times)
{
	char query[1024];
	//stringstream buf1;
	//buf1 << "insert into ad values('" << company << "','测试','测试','测试','5')";
	sprintf(query, "insert into ad values( '%s', '%s' , '%s' , '%s' , '%d') ", company.c_str(), ad.c_str(),time_bg.c_str(), time_ed.c_str(),times);
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

//查询广告需求表
int MysqlOperate::QueryReqData(string company, std::string ad)
{
	char query[1024]; //查询语句
	sprintf(query, "SELECT 播放次数 from requirements where (公司名称='%s' and 广告名称='%s');", company.c_str(), ad.c_str());
	//返回0 查询成功，返回1查询失败  
	if (mysql_query(&mysql, query)) {        // 执行指定为一个空结尾的字符串的SQL查询。	
		printf("Query failed (%s)\n", mysql_error(&mysql));
		return false;
	}
	else {
		printf("query success\n");
	}
	//获取结果集  
	if (!(m_dat_res = mysql_store_result(&mysql)))    //获得sql语句结束后返回的结果集  
	{
		printf("Couldn't get result from %s\n", mysql_error(&mysql));
		return false;
	}
	int i = 0;
	//因为查询的这个数据每行只有1个
	while (m_dat_row = mysql_fetch_row(m_dat_res))//从结果集合中取得下一行
	{
		m_dat_data[i].push_back(m_dat_row[0]);
		m_dat_data[i++].push_back(m_dat_row[1]);
	}
	int temp = stoi(m_dat_data[0][0]);
	printf("result:%d\n", temp);
	return 0;
}

//导出Excel表格
void MysqlOperate::ExportAdExcel()
{
	char query[1024]; //查询语句
	sprintf(query, "select * into outfile 'd:/test.csv' FIELDS TERMINATED BY ','" 
		"from (select convert(('公司名称') using gbk),convert(('广告名称') using gbk),convert(('次数')using gbk),convert(('开始')using gbk),convert(('结束')using gbk)" 
		"union select convert((公司名称) using gbk),convert((广告名称) using gbk),convert((播放次数)using gbk),convert((开始播放时间)using gbk),convert((结束播放时间)using gbk) from ad) b;");
	if (mysql_query(&mysql, query)) {        // 执行指定为一个空结尾的字符串的SQL查询。	
		printf("Query failed (%s)\n", mysql_error(&mysql));
	}
	else {
		printf("query success\n");
	}
}


//在程序结束的时候请调用这个函数，释放资源
void MysqlOperate::FreeConnect()
{
	mysql_free_result(m_dat_res);  //释放一个结果集合使用的内存。
	mysql_close(&mysql);	 //关闭一个服务器连接
}

IMysqlOperate * GetFD()
{
	return new MysqlOperate();
}
