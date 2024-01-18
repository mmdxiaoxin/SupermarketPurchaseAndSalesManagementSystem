#include "pch.h"
#include "CInfoFile.h"

CInfoFile::CInfoFile()
{
}


CInfoFile::~CInfoFile()
{
}

//��ȡ���ܵ�½��Ϣ
void CInfoFile::ReadLogin(CString& name, CString& pwd)
{
	ifstream ifs; //�����ļ��������
	ifs.open(_F_LOGIN); //���ļ�

	char buf[1024] = { 0 };

	ifs.getline(buf, sizeof(buf)); //��ȡһ������
	name = CString(buf);			 //char *ת��ΪCString

	ifs.getline(buf, sizeof(buf));
	pwd = CString(buf);

	ifs.close(); //�ر��ļ�
}

//д�����ܵ�½��Ϣ
void CInfoFile::WirteLogin(CString& name, CString& pwd)
{
	ofstream ofs(_F_LOGIN);//�����ʽ���ļ�
	char* tmpName, *tmpPwd;
	//�˺�
	CStringA tmp1;
	tmp1 = name;
	tmpName = tmp1.GetBuffer();
	//����
	CStringA tmp2;
	tmp2 = pwd;
	tmpPwd = tmp2.GetBuffer();
	
	ofs << tmpName << endl; //nameд���ļ�
	ofs << tmpPwd << endl;	//pwdд���ļ�

	ofs.close();//�ر��ļ�
}

//��ȡԱ����½��Ϣ
void CInfoFile::ReadLogin()
{
	ifstream ifs(_F_LOGIN_STAFF); //���뷽ʽ���ļ�

	char buf[1024] = { 0 };
	st.clear();
	//ȡ����ͷ
	ifs.getline(buf, sizeof(buf));

	while (!ifs.eof()) //û���ļ���β
	{
		staff tmp;

		ifs.getline(buf, sizeof(buf)); //��ȡһ��

		char* sst = strtok(buf, "|"); //�ԡ�|���и�
		if (sst != NULL)
		{
			tmp.id = atoi(sst); //Ա��id
		}
		else
		{
			break;
		}

		sst = strtok(NULL, "|");
		tmp.user = sst;	//Ա���û���

		sst = strtok(NULL, "|");
		tmp.pwd = sst;	//Ա������

		sst = strtok(NULL, "|");
		tmp.name = sst;	//Ա������

		sst = strtok(NULL, "|");
		tmp.jurisdiction =sst;	//Ա������

		st.push_back(tmp); //��������ĺ���
	}

	ifs.close(); //�ر��ļ�
}

//д��Ա����½��Ϣ
void CInfoFile::WirteLogin()
{
	ofstream ofs(_F_LOGIN_STAFF);//�����ʽ���ļ�

	if (st.size() > 0)	//Ա����Ϣ���������ݲ�ִ��
	{
		ofs << "Ա��ID|�û���|����|Ա������|Ա��Ȩ��" << endl; //д���ͷ

		//ͨ��������ȡ���������ݣ�д���ļ����ԡ�|���ָ�����β�ӻ���
		for (list<staff>::iterator it = st.begin(); it != st.end(); it++)
		{
			ofs << it->id << "|";
			ofs << it->user << "|";
			ofs << it->pwd << "|";
			ofs << it->name << "|";
			ofs << it->jurisdiction << endl;
		}
	}
	ofs.close();//�ر��ļ�
}

//��ȡ��ȫ��Ϣ
void CInfoFile::ReadSafety()
{
	ifstream ifs(_F_SAFETY); //���뷽ʽ���ļ�

	char buf[1024] = { 0 };
	qa.clear();
	//ȡ����ͷ
	ifs.getline(buf, sizeof(buf));

	while (!ifs.eof()) //û���ļ���β
	{
		safety tmp;

		ifs.getline(buf, sizeof(buf)); //��ȡһ��

		char* sst = strtok(buf, "|"); //�ԡ�|���и�
		if (sst != NULL)
		{
			tmp.question = sst; //��ȫ����
		}
		else
		{
			break;
		}

		sst = strtok(NULL, "|");
		tmp.answer = sst;	//�ش�

		qa.push_back(tmp); //��������ĺ���
	}

	ifs.close(); //�ر��ļ�
}

//��ȫ��Ϣд���ļ�
void CInfoFile::WirteSafety()
{
	ofstream ofs(_F_SAFETY);//�����ʽ���ļ�

	if (qa.size() > 0)	//��ȫ�������������ݲ�ִ��
	{
		ofs << "��ȫ����|�ش�" << endl; //д���ͷ

		//ͨ��������ȡ���������ݣ�д���ļ����ԡ�|���ָ�����β�ӻ���
		for (list<safety>::iterator it = qa.begin(); it != qa.end(); it++)
		{
			ofs << it->question << "|";
			ofs << it->answer << endl;
		}
	}

	ofs.close();//�ر��ļ�
}

//�޸�����
void CInfoFile::WirtePwd(char* name, char* pwd)
{
	ofstream ofs;	 //�����ļ��������
	ofs.open(_F_LOGIN); //���ļ�

	ofs << name << endl; //nameд���ļ�
	ofs << pwd << endl;	//pwdд���ļ�

	ofs.close();	//�ر��ļ�
}

//��ȡ��Ʒ��Ϣ
void CInfoFile::ReadDocline()
{
	ifstream ifs(_F_STOCK); //���뷽ʽ���ļ�

	char buf[1024] = { 0 };
	ls.clear();
	//ȡ����ͷ
	ifs.getline(buf, sizeof(buf));

	while (!ifs.eof()) //û���ļ���β
	{
		msg tmp;

		ifs.getline(buf, sizeof(buf)); //��ȡһ��

		char* sst = strtok(buf, "|"); //�ԡ�|���и�
		if (sst != NULL)
		{
			tmp.id = atoi(sst); //��Ʒid
		}
		else
		{
			break;
		}

		sst = strtok(NULL, "|");
		tmp.name = sst;	//��Ʒ����

		sst = strtok(NULL, "|");
		tmp.out_price = atof(sst);	//��Ʒ���ۼ۸�

		sst = strtok(NULL, "|");
		tmp.in_price = atof(sst);	//��Ʒ�����۸�

		sst = strtok(NULL, "|");
		tmp.num = atoi(sst);	//��Ʒ��Ŀ

		sst = strtok(NULL, "|");
		tmp.kind = atoi(sst);	//��Ʒ����

		sst = strtok(NULL, "|");
		tmp.firmID = atoi(sst);	//��Ӧ�̱��

		sst = strtok(NULL, "|");
		tmp.isPut = sst;	//�Ƿ��ϼ�

		ls.push_back(tmp); //��������ĺ���
	}

	ifs.close(); //�ر��ļ�
}

//��Ʒд���ļ�
void CInfoFile::WirteDocline()
{
	ofstream ofs(_F_STOCK);//�����ʽ���ļ�

	if (ls.size() > 0)	//��Ʒ���������ݲ�ִ��
	{
		ofs << "��ƷID|��Ʒ����|��Ʒ���ۼ۸�|��Ʒ�����۸�|���|��Ʒ����|��Ӧ�̱��|�Ƿ��ϼ�" << endl; //д���ͷ

		//ͨ��������ȡ���������ݣ�д���ļ����ԡ�|���ָ�����β�ӻ���
		for (list<msg>::iterator it = ls.begin(); it != ls.end(); it++)
		{
			ofs << it->id << "|";
			ofs << it->name << "|";
			ofs << it->out_price << "|";
			ofs << it->in_price << "|";
			ofs << it->num << "|";
			ofs << it->kind << "|";
			ofs << it->firmID << "|";
			ofs << it->isPut << endl;
		}
	}

	ofs.close();//�ر��ļ�
}

void CInfoFile::ReadFirm()
{
	ifstream ifs(_F_FIRM); //���뷽ʽ���ļ�

	char buf[1024] = { 0 };
	fi.clear();
	//ȡ����ͷ
	ifs.getline(buf, sizeof(buf));

	while (!ifs.eof()) //û���ļ���β
	{
		firm tmp;

		ifs.getline(buf, sizeof(buf)); //��ȡһ��
		num++;	//Ա����Ŀ��һ

		char* sst = strtok(buf, "|"); //�ԡ�|���и�
		if (sst != NULL)
		{
			tmp.id = sst; //����id
		}
		else
		{
			break;
		}

		sst = strtok(NULL, "|");
		tmp.name = sst;	//��������

		sst = strtok(NULL, "|");
		tmp.address = sst;	//���̵�ַ

		sst = strtok(NULL, "|");
		tmp.phoneNumber = sst;	//���̵绰

		sst = strtok(NULL, "|");
		tmp.fax = sst;	//���̴���

		fi.push_back(tmp); //��������ĺ���
	}

	ifs.close(); //�ر��ļ�
}

void CInfoFile::WirteFirm()
{
	ofstream ofs(_F_FIRM);//�����ʽ���ļ�

	if (fi.size() > 0)	//������Ϣ���������ݲ�ִ��
	{
		ofs << "���̱��|��������|���̵�ַ|���̵绰|���̴���" << endl; //д���ͷ

		//ͨ��������ȡ���������ݣ�д���ļ����ԡ�|���ָ�����β�ӻ���
		for (list<firm>::iterator it = fi.begin(); it != fi.end(); it++)
		{
			ofs << it->id << "|";
			ofs << it->name << "|";
			ofs << it->address << "|";
			ofs << it->phoneNumber << "|";
			ofs << it->fax << endl;
		}
	}
	ofs.close();//�ر��ļ�
}

void CInfoFile::ReadPurchaseRecord()
{
	ifstream ifs(_F_PURCHASE); //���뷽ʽ���ļ�

	char buf[1024] = { 0 };
	pu.clear();
	//ȡ����ͷ
	ifs.getline(buf, sizeof(buf));

	while (!ifs.eof()) //û���ļ���β
	{
		purchase tmp;

		ifs.getline(buf, sizeof(buf)); //��ȡһ��

		char* sst = strtok(buf, "|"); //�ԡ�|���и�
		if (sst != NULL)
		{
			tmp.id = atoi(sst); //��Ʒid
		}
		else
		{
			break;
		}

		sst = strtok(NULL, "|");
		tmp.name = sst;	//��Ʒ����

		sst = strtok(NULL, "|");
		tmp.in_price = atof(sst);	//���뵥��

		sst = strtok(NULL, "|");
		tmp.date = sst;	//��������

		sst = strtok(NULL, "|");
		tmp.num = atoi(sst);	//��������

		sst = strtok(NULL, "|");
		tmp.cost = atof(sst);	//���뻨��

		pu.push_back(tmp); //��������ĺ���
	}

	ifs.close(); //�ر��ļ�
}

void CInfoFile::WirtePurchaseRecord()
{
	ofstream ofs(_F_PURCHASE);//�����ʽ���ļ�

	if (pu.size() > 0)	//�����ݲ�ִ��
	{
		ofs << "��ƷID|��Ʒ����|���뵥��|��������|��������|���뻨��" << endl; //д���ͷ

		//ͨ��������ȡ���������ݣ�д���ļ����ԡ�|���ָ�����β�ӻ���
		for (list<purchase>::iterator it = pu.begin(); it != pu.end(); it++)
		{
			ofs << it->id << "|";
			ofs << it->name << "|";
			ofs << it->in_price << "|";
			ofs << it->date << "|";
			ofs << it->num << "|";
			ofs << it->cost << endl;
		}
	}
	ofs.close();//�ر��ļ�
}

void CInfoFile::ReadSalesRecord()
{
	ifstream ifs(_F_SALES); //���뷽ʽ���ļ�

	char buf[1024] = { 0 };
	sa.clear();
	//ȡ����ͷ
	ifs.getline(buf, sizeof(buf));

	while (!ifs.eof()) //û���ļ���β
	{
		sales tmp;

		ifs.getline(buf, sizeof(buf)); //��ȡһ��

		char* sst = strtok(buf, "|"); //�ԡ�|���и�
		if (sst != NULL)
		{
			tmp.id = atoi(sst); //��Ʒid
		}
		else
		{
			break;
		}

		sst = strtok(NULL, "|");
		tmp.name = sst;	//��Ʒ����

		sst = strtok(NULL, "|");
		tmp.date = sst;	//��������

		sst = strtok(NULL, "|");
		tmp.in_price = atof(sst);	//���뵥��

		sst = strtok(NULL, "|");
		tmp.out_price = atof(sst);	//���۵���

		sst = strtok(NULL, "|");
		tmp.num = atoi(sst);	//��������

		sst = strtok(NULL, "|");
		tmp.sale = atof(sst);	//���۶�

		sst = strtok(NULL, "|");
		tmp.income = atof(sst);	//������

		sa.push_back(tmp); //��������ĺ���
	}

	ifs.close(); //�ر��ļ�
}

void CInfoFile::WirteSalesRecord()
{
	ofstream ofs(_F_SALES);//�����ʽ���ļ�

	if (sa.size() > 0)	//�����ݲ�ִ��
	{
		ofs << "��ƷID|��Ʒ����|��������|���뵥��|���۵���|��������|���۶�|������" << endl; //д���ͷ

		//ͨ��������ȡ���������ݣ�д���ļ����ԡ�|���ָ�����β�ӻ���
		for (list<sales>::iterator it = sa.begin(); it != sa.end(); it++)
		{
			ofs << it->id << "|";
			ofs << it->name << "|";
			ofs << it->date << "|";
			ofs << it->in_price << "|";
			ofs << it->out_price << "|";
			ofs << it->num << "|";
			ofs << it->sale << "|";
			ofs << it->income << endl;
		}
	}
	ofs.close();//�ر��ļ�
}

//�������Ʒ
//name:��Ʒ���ƣ�num����棬out_price����Ʒ���ۼ۸�
int CInfoFile::Addline(CString name, int num, double  out_price, double  in_price, int kind, int firmID)
{
	msg tmp;

	//��Ʒ���ƣ���棬�۸���Ч
	if (!name.IsEmpty() && num > 0 && out_price > 0 && in_price > 0)
	{
		tmp.id = ls.size() + 1;	//id�Զ���1
		CStringA str;
		str = name;	//CStringתCStirngA
		tmp.name = str.GetBuffer(); //CStirngAתchar *����Ʒ����
		tmp.num = num;	//���
		tmp.out_price = out_price;	//��Ʒ���ۼ۸�
		tmp.firmID = firmID;//��Ӧ�̱��
		tmp.in_price = in_price;//��Ʒ�����۸�
		tmp.kind = kind;//��Ʒ����
		tmp.isPut = "δ�ϼ�";//Ĭ�ϸ���ӵ���Ʒ���ϼ�

		ls.push_back(tmp);	//��������ĺ���
	}
	return tmp.id;
}

void CInfoFile::Addline(CString user, CString pwd, CString name, CString jurisdiction)
{
	staff tmp;

	//ְ����Ϣ��Ч
	if (!name.IsEmpty() && !user.IsEmpty() && !jurisdiction.IsEmpty() && !pwd.IsEmpty())
	{
		tmp.id = st.size() + 1;	//id�Զ���1
		CStringA str1;
		str1 = name;	//CStringתCStirngA
		tmp.name = str1.GetBuffer(); //CStirngAתchar *��

		CStringA str2;
		str2 = user;
		tmp.user = str2.GetBuffer();

		CStringA str3;
		str3 = pwd;
		tmp.pwd = str3.GetBuffer();

		CStringA str4;
		str4 = jurisdiction;
		tmp.jurisdiction = str4.GetBuffer();
		

		st.push_back(tmp);	//��������ĺ���
	}
}

void CInfoFile::Addline(CString question, CString answer)
{
	safety tmp;

	//��ȫ������Ч
	if (!question.IsEmpty() && !answer.IsEmpty())
	{
		CStringA str1;
		str1 = question;	//CStringתCStirngA
		tmp.question = str1.GetBuffer(); //CStirngAתchar *��

		CStringA str2;
		str2 = answer;
		tmp.answer = str2.GetBuffer();

		qa.push_back(tmp);	//��������ĺ���
	}
}

void CInfoFile::Addline(string id, string name, string address, string phoneNumber, string fax)
{
	firm tmp;

	if (name != "" && id != "" && address != "" && phoneNumber != "" && fax != "")
	{
		tmp.id = id;
		tmp.name = name;
		tmp.address = address;
		tmp.phoneNumber = phoneNumber;
		tmp.fax = fax;

		fi.push_back(tmp);
	}
}

void CInfoFile::Addline(int id, string name, double in_price, string date, int num, double cost)
{
	purchase tmp;

	if (name != "" && id != 0 && in_price > 0 && date != "" && num > 0 && cost > 0) 
	{
		tmp.id = id;
		tmp.name = name;
		tmp.in_price = in_price;
		tmp.date = date;
		tmp.num = num;
		tmp.cost = cost;

		pu.push_back(tmp);
	}
}

void CInfoFile::Addline(int id, string name, string date, double in_price, double out_price, int num, double sale, double income)
{
	sales tmp;

	if (name != "" && id != 0 && in_price > 0 && date != "" && num > 0 && in_price > 0 && out_price > 0 && sale > 0 && income > 0) 
	{
		tmp.id = id;
		tmp.name = name;
		tmp.in_price = in_price;
		tmp.date = date;
		tmp.num = num;
		tmp.out_price = out_price;
		tmp.sale = sale;
		tmp.income = income;

		sa.push_back(tmp);
	}
}
