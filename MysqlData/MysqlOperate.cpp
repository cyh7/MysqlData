#include "MysqlOperate.h"

//��ѯ���ݿ���Ҫ������

MysqlOperate::MysqlOperate()
{

}

MysqlOperate::~MysqlOperate()
{

}

bool MysqlOperate::ConnectDatabase()
{
	//��ʼ��mysql
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	const char host[] = "localhost";
	const char user[] = "root";
	const char psw[] = "1234";
	const char table[] = "test";
	const int port = 3306;
	//����false������ʧ�ܣ�����true�����ӳɹ�  
	if (!(mysql_real_connect(&mysql, host, user, psw, table, port, NULL, 0)))
		//�м�ֱ����������û��������룬���ݿ������˿ںţ�����дĬ��0����3306�ȣ���������д�ɲ����ٴ���ȥ  
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

IMysqlOperate * GetFD()
{
	return new MysqlOperate();
}
