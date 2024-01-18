#pragma once

#include <list>
#include <fstream>
#include <iostream>
#include <string>

#define _F_LOGIN "./login.ini"
#define _F_STOCK "./stock.txt"
#define _F_SAFETY "./safety.ini"
#define _F_SALES "./Sales_records.txt"
#define _F_PURCHASE "./Purchase_record.txt"
#define _F_LOGIN_STAFF "./login_ staff.ini"
#define _F_FIRM "./firm_stock.txt"

using namespace std;

struct msg
{
	int id;				//��Ʒid
	string name;		//��Ʒ����
	double out_price;		//��Ʒ���ۼ۸�
	double in_price;		//��Ʒ�����۸�
	int num;			//��Ʒ����
	int kind;			//��Ʒ����
	int firmID;			//��Ӧ�̱��
	string isPut;		//�Ƿ��ϼ�
};

struct safety
{
	string question;
	string answer;
};

struct staff
{
	int id; //Ա��ID
	string user; //Ա���û���
	string pwd; //Ա������
	string name; //Ա������
	string jurisdiction; //Ա��Ȩ��

};

struct firm
{
	string id; //���̱��
	string name; //��������
	string address; //���̵�ַ
	string phoneNumber; //���̵绰
	string fax; //���̴���
};

struct purchase
{
	int id; //������ƷID
	string name; //������Ʒ����
	double in_price;//���뵥��
	string date;//��������
	int num;//��������
	double cost;//���뻨��
};

struct sales
{
	int id; //������ƷID
	string name;//������Ʒ����
	string date;//��������
	double in_price;//����۸�
	double out_price;//���ۼ۸�
	int num;//��������
	double sale;//���۶�
	double income;//������
};

class CInfoFile
{
public:
	CInfoFile();
	~CInfoFile();

	//��ȡ���ܵ�½��Ϣ
	void ReadLogin(CString& name, CString& pwd);

	//д�����ܵ�½��Ϣ
	void WirteLogin(CString& name, CString& pwd);

	//��ȡԱ����½��Ϣ
	void ReadLogin();

	//д��Ա����½��Ϣ
	void WirteLogin();

	//��ȡ��ȫ��Ϣ
	void ReadSafety();

	//��ȫ��Ϣд���ļ�
	void WirteSafety();

	//�޸���������
	void WirtePwd(char* name, char* pwd);

	// ��ȡ��Ʒ����
	void ReadDocline();

	//��Ʒд���ļ�
	void WirteDocline();

	//��ȡ��Ӧ����Ϣ
	void ReadFirm();

	//д�빩Ӧ����Ϣ
	void WirteFirm();

	//��ȡ�����¼
	void ReadPurchaseRecord();

	//д�빺���¼
	void WirtePurchaseRecord();

	//��ȡ���ۼ�¼
	void ReadSalesRecord();

	//д����ۼ�¼
	void WirteSalesRecord();

	//�������Ʒ
	int Addline(CString name, 
		int num, 
		double out_price, 
		double in_price, 
		int kind, 
		int firmID);

	//�����ְԱ
	void Addline(CString user,
		CString pwd,
		CString name,
		CString jurisdiction);

	//����°�ȫ��Ϣ
	void Addline(CString question, CString answer);

	//����³���
	void Addline(string id,
		string name,
		string address,
		string phoneNumber,
		string fax);

	//��ӹ�����Ϣ
	void Addline(
		int id,
		string name,
		double in_price,
		string date,
		int num,
		double cost);

	//��ӳ�����Ϣ
	void Addline(int id,
		string name,
		string date,
		double in_price,
		double out_price,
		int num,
		double sale,
		double income);

	list<msg> ls;	//�洢��Ʒ����
	list<safety> qa; //�洢��ȫ����
	list<staff> st; //�洢Ա����Ϣ
	list<firm> fi; //�洢��Ӧ����Ϣ
	list<purchase> pu; //�洢�����¼
	list<sales> sa; //�洢���ۼ�¼
	int num;			//������¼��Ʒ����
};
