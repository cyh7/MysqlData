#pragma once
#include <stdio.h>  
#include <WinSock.h>  //һ��Ҫ�������
#include "mysql.h"
#include <Windows.h> 
#include <vector>
#include <string>
//�������������Ҳ�����ڹ���--������������  
#pragma comment(lib,"wsock32.lib") 
#pragma comment(lib,"libmysql.lib")

//Ĭ���麯����
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

	//�̳е�ʵ��
	//�������ݿ�
	bool ConnectDatabase();
	//�����沥�ż�¼���� ��˾���� ������� ��ʼʱ�� ����ʱ�� ���Ŵ���
	bool InsertRecordData(std::string company, std::string ad, std::string time_bg, std::string time_ed, int times);
	//�ڳ��������ʱ�����������������ͷ���Դ
	void FreeConnect();
	//��ѯ���������¼�еĲ��Ŵ��� ����Ϊ��Ҫ��ѯ�Ĺ�˾�����Լ���������
	int QueryReqData(std::string company, std::string ad);
	//��ָ��λ�õ���������ʷ���
	void ExportAdExcel();

public:
	MYSQL mysql; //mysql���� 
	MYSQL_RES *m_dat_res; //����ṹ�������е�һ����ѯ�����
	MYSQL_ROW m_dat_row; //һ�������ݵ����Ͱ�ȫ(type-safe)�ı�ʾ����ʾ�����е���

private:
	

};

//��������
IMysqlOperate * GetFD();
