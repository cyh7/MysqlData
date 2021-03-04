#include "MysqlOperate.h"

//��ѯ�����ݿ��Ϊ������
//��1����沥�ż�¼�� ÿ�β��Ź��֮�������߲����� ���� ad
//��2����������  �ñ��ɹ��Ͷ���߲��루���뷽ʽ�����������Ǹ����ȡ�趨�Ĳ��Ŵ���  ���� requirements

//��ѯ
std::vector<std::string> m_dat_data[100];
using namespace std;

MysqlOperate::MysqlOperate()
{

}

MysqlOperate::~MysqlOperate()
{

}

//�������ݿ�
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

////�����沥�ż�¼���� ��˾���� ������� ��ʼʱ�� ����ʱ�� ���Ŵ���
bool MysqlOperate::InsertRecordData(string company, string ad, string time_bg, string time_ed, int times)
{
	char query[1024];
	//stringstream buf1;
	//buf1 << "insert into ad values('" << company << "','����','����','����','5')";
	sprintf(query, "insert into ad values( '%s', '%s' , '%s' , '%s' , '%d') ", company.c_str(), ad.c_str(),time_bg.c_str(), time_ed.c_str(),times);
	if (mysql_query(&mysql, query))//ִ��SQL���  
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

//��ѯ��������
int MysqlOperate::QueryReqData(string company, std::string ad)
{
	char query[1024]; //��ѯ���
	sprintf(query, "SELECT ���Ŵ��� from requirements where (��˾����='%s' and �������='%s');", company.c_str(), ad.c_str());
	//����0 ��ѯ�ɹ�������1��ѯʧ��  
	if (mysql_query(&mysql, query)) {        // ִ��ָ��Ϊһ���ս�β���ַ�����SQL��ѯ��	
		printf("Query failed (%s)\n", mysql_error(&mysql));
		return false;
	}
	else {
		printf("query success\n");
	}
	//��ȡ�����  
	if (!(m_dat_res = mysql_store_result(&mysql)))    //���sql�������󷵻صĽ����  
	{
		printf("Couldn't get result from %s\n", mysql_error(&mysql));
		return false;
	}
	int i = 0;
	//��Ϊ��ѯ���������ÿ��ֻ��1��
	while (m_dat_row = mysql_fetch_row(m_dat_res))//�ӽ��������ȡ����һ��
	{
		m_dat_data[i].push_back(m_dat_row[0]);
		m_dat_data[i++].push_back(m_dat_row[1]);
	}
	int temp = stoi(m_dat_data[0][0]);
	printf("result:%d\n", temp);
	return 0;
}

//����Excel���
void MysqlOperate::ExportAdExcel()
{
	char query[1024]; //��ѯ���
	sprintf(query, "select * into outfile 'd:/test.csv' FIELDS TERMINATED BY ','" 
		"from (select convert(('��˾����') using gbk),convert(('�������') using gbk),convert(('����')using gbk),convert(('��ʼ')using gbk),convert(('����')using gbk)" 
		"union select convert((��˾����) using gbk),convert((�������) using gbk),convert((���Ŵ���)using gbk),convert((��ʼ����ʱ��)using gbk),convert((��������ʱ��)using gbk) from ad) b;");
	if (mysql_query(&mysql, query)) {        // ִ��ָ��Ϊһ���ս�β���ַ�����SQL��ѯ��	
		printf("Query failed (%s)\n", mysql_error(&mysql));
	}
	else {
		printf("query success\n");
	}
}


//�ڳ��������ʱ�����������������ͷ���Դ
void MysqlOperate::FreeConnect()
{
	mysql_free_result(m_dat_res);  //�ͷ�һ���������ʹ�õ��ڴ档
	mysql_close(&mysql);	 //�ر�һ������������
}

IMysqlOperate * GetFD()
{
	return new MysqlOperate();
}
