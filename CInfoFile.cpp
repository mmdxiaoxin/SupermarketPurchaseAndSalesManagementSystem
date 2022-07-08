#include "pch.h"
#include "CInfoFile.h"

CInfoFile::CInfoFile()
{
}


CInfoFile::~CInfoFile()
{
}

//读取主管登陆信息
void CInfoFile::ReadLogin(CString& name, CString& pwd)
{
	ifstream ifs; //创建文件输入对象
	ifs.open(_F_LOGIN); //打开文件

	char buf[1024] = { 0 };

	ifs.getline(buf, sizeof(buf)); //读取一行内容
	name = CString(buf);			 //char *转换为CString

	ifs.getline(buf, sizeof(buf));
	pwd = CString(buf);

	ifs.close(); //关闭文件
}

//写入主管登陆信息
void CInfoFile::WirteLogin(CString& name, CString& pwd)
{
	ofstream ofs(_F_LOGIN);//输出方式打开文件
	char* tmpName, *tmpPwd;
	//账号
	CStringA tmp1;
	tmp1 = name;
	tmpName = tmp1.GetBuffer();
	//密码
	CStringA tmp2;
	tmp2 = pwd;
	tmpPwd = tmp2.GetBuffer();
	
	ofs << tmpName << endl; //name写入文件
	ofs << tmpPwd << endl;	//pwd写入文件

	ofs.close();//关闭文件
}

//读取员工登陆信息
void CInfoFile::ReadLogin()
{
	ifstream ifs(_F_LOGIN_STAFF); //输入方式打开文件

	char buf[1024] = { 0 };
	st.clear();
	//取出表头
	ifs.getline(buf, sizeof(buf));

	while (!ifs.eof()) //没到文件结尾
	{
		staff tmp;

		ifs.getline(buf, sizeof(buf)); //读取一行

		char* sst = strtok(buf, "|"); //以“|”切割
		if (sst != NULL)
		{
			tmp.id = atoi(sst); //员工id
		}
		else
		{
			break;
		}

		sst = strtok(NULL, "|");
		tmp.user = sst;	//员工用户名

		sst = strtok(NULL, "|");
		tmp.pwd = sst;	//员工密码

		sst = strtok(NULL, "|");
		tmp.name = sst;	//员工名称

		sst = strtok(NULL, "|");
		tmp.jurisdiction =sst;	//员工名称

		st.push_back(tmp); //放在链表的后面
	}

	ifs.close(); //关闭文件
}

//写入员工登陆信息
void CInfoFile::WirteLogin()
{
	ofstream ofs(_F_LOGIN_STAFF);//输出方式打开文件

	if (st.size() > 0)	//员工信息链表有内容才执行
	{
		ofs << "员工ID|用户名|密码|员工名称|员工权限" << endl; //写入表头

		//通过迭代器取出链表内容，写入文件，以“|”分隔，结尾加换行
		for (list<staff>::iterator it = st.begin(); it != st.end(); it++)
		{
			ofs << it->id << "|";
			ofs << it->user << "|";
			ofs << it->pwd << "|";
			ofs << it->name << "|";
			ofs << it->jurisdiction << endl;
		}
	}
	ofs.close();//关闭文件
}

//读取安全信息
void CInfoFile::ReadSafety()
{
	ifstream ifs(_F_SAFETY); //输入方式打开文件

	char buf[1024] = { 0 };
	qa.clear();
	//取出表头
	ifs.getline(buf, sizeof(buf));

	while (!ifs.eof()) //没到文件结尾
	{
		safety tmp;

		ifs.getline(buf, sizeof(buf)); //读取一行

		char* sst = strtok(buf, "|"); //以“|”切割
		if (sst != NULL)
		{
			tmp.question = sst; //安全问题
		}
		else
		{
			break;
		}

		sst = strtok(NULL, "|");
		tmp.answer = sst;	//回答

		qa.push_back(tmp); //放在链表的后面
	}

	ifs.close(); //关闭文件
}

//安全信息写入文件
void CInfoFile::WirteSafety()
{
	ofstream ofs(_F_SAFETY);//输出方式打开文件

	if (qa.size() > 0)	//安全问题链表有内容才执行
	{
		ofs << "安全问题|回答" << endl; //写入表头

		//通过迭代器取出链表内容，写入文件，以“|”分隔，结尾加换行
		for (list<safety>::iterator it = qa.begin(); it != qa.end(); it++)
		{
			ofs << it->question << "|";
			ofs << it->answer << endl;
		}
	}

	ofs.close();//关闭文件
}

//修改密码
void CInfoFile::WirtePwd(char* name, char* pwd)
{
	ofstream ofs;	 //创建文件输出对象
	ofs.open(_F_LOGIN); //打开文件

	ofs << name << endl; //name写入文件
	ofs << pwd << endl;	//pwd写入文件

	ofs.close();	//关闭文件
}

//读取商品信息
void CInfoFile::ReadDocline()
{
	ifstream ifs(_F_STOCK); //输入方式打开文件

	char buf[1024] = { 0 };
	ls.clear();
	//取出表头
	ifs.getline(buf, sizeof(buf));

	while (!ifs.eof()) //没到文件结尾
	{
		msg tmp;

		ifs.getline(buf, sizeof(buf)); //读取一行

		char* sst = strtok(buf, "|"); //以“|”切割
		if (sst != NULL)
		{
			tmp.id = atoi(sst); //商品id
		}
		else
		{
			break;
		}

		sst = strtok(NULL, "|");
		tmp.name = sst;	//商品名称

		sst = strtok(NULL, "|");
		tmp.out_price = atof(sst);	//商品零售价格

		sst = strtok(NULL, "|");
		tmp.in_price = atof(sst);	//商品进货价格

		sst = strtok(NULL, "|");
		tmp.num = atoi(sst);	//商品数目

		sst = strtok(NULL, "|");
		tmp.kind = atoi(sst);	//商品类别号

		sst = strtok(NULL, "|");
		tmp.firmID = atoi(sst);	//供应商编号

		sst = strtok(NULL, "|");
		tmp.isPut = sst;	//是否上架

		ls.push_back(tmp); //放在链表的后面
	}

	ifs.close(); //关闭文件
}

//商品写入文件
void CInfoFile::WirteDocline()
{
	ofstream ofs(_F_STOCK);//输出方式打开文件

	if (ls.size() > 0)	//商品链表有内容才执行
	{
		ofs << "商品ID|商品名称|商品零售价格|商品进货价格|库存|商品类别号|供应商编号|是否上架" << endl; //写入表头

		//通过迭代器取出链表内容，写入文件，以“|”分隔，结尾加换行
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

	ofs.close();//关闭文件
}

void CInfoFile::ReadFirm()
{
	ifstream ifs(_F_FIRM); //输入方式打开文件

	char buf[1024] = { 0 };
	fi.clear();
	//取出表头
	ifs.getline(buf, sizeof(buf));

	while (!ifs.eof()) //没到文件结尾
	{
		firm tmp;

		ifs.getline(buf, sizeof(buf)); //读取一行
		num++;	//员工数目加一

		char* sst = strtok(buf, "|"); //以“|”切割
		if (sst != NULL)
		{
			tmp.id = sst; //厂商id
		}
		else
		{
			break;
		}

		sst = strtok(NULL, "|");
		tmp.name = sst;	//厂商名称

		sst = strtok(NULL, "|");
		tmp.address = sst;	//厂商地址

		sst = strtok(NULL, "|");
		tmp.phoneNumber = sst;	//厂商电话

		sst = strtok(NULL, "|");
		tmp.fax = sst;	//厂商传真

		fi.push_back(tmp); //放在链表的后面
	}

	ifs.close(); //关闭文件
}

void CInfoFile::WirteFirm()
{
	ofstream ofs(_F_FIRM);//输出方式打开文件

	if (fi.size() > 0)	//厂商信息链表有内容才执行
	{
		ofs << "厂商编号|厂商名称|厂商地址|厂商电话|厂商传真" << endl; //写入表头

		//通过迭代器取出链表内容，写入文件，以“|”分隔，结尾加换行
		for (list<firm>::iterator it = fi.begin(); it != fi.end(); it++)
		{
			ofs << it->id << "|";
			ofs << it->name << "|";
			ofs << it->address << "|";
			ofs << it->phoneNumber << "|";
			ofs << it->fax << endl;
		}
	}
	ofs.close();//关闭文件
}

void CInfoFile::ReadPurchaseRecord()
{
	ifstream ifs(_F_PURCHASE); //输入方式打开文件

	char buf[1024] = { 0 };
	pu.clear();
	//取出表头
	ifs.getline(buf, sizeof(buf));

	while (!ifs.eof()) //没到文件结尾
	{
		purchase tmp;

		ifs.getline(buf, sizeof(buf)); //读取一行

		char* sst = strtok(buf, "|"); //以“|”切割
		if (sst != NULL)
		{
			tmp.id = atoi(sst); //商品id
		}
		else
		{
			break;
		}

		sst = strtok(NULL, "|");
		tmp.name = sst;	//商品名称

		sst = strtok(NULL, "|");
		tmp.in_price = atof(sst);	//购入单价

		sst = strtok(NULL, "|");
		tmp.date = sst;	//购入日期

		sst = strtok(NULL, "|");
		tmp.num = atoi(sst);	//购入数量

		sst = strtok(NULL, "|");
		tmp.cost = atof(sst);	//购入花销

		pu.push_back(tmp); //放在链表的后面
	}

	ifs.close(); //关闭文件
}

void CInfoFile::WirtePurchaseRecord()
{
	ofstream ofs(_F_PURCHASE);//输出方式打开文件

	if (pu.size() > 0)	//有内容才执行
	{
		ofs << "商品ID|商品名称|购入单价|购入日期|购入数量|购入花销" << endl; //写入表头

		//通过迭代器取出链表内容，写入文件，以“|”分隔，结尾加换行
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
	ofs.close();//关闭文件
}

void CInfoFile::ReadSalesRecord()
{
	ifstream ifs(_F_SALES); //输入方式打开文件

	char buf[1024] = { 0 };
	sa.clear();
	//取出表头
	ifs.getline(buf, sizeof(buf));

	while (!ifs.eof()) //没到文件结尾
	{
		sales tmp;

		ifs.getline(buf, sizeof(buf)); //读取一行

		char* sst = strtok(buf, "|"); //以“|”切割
		if (sst != NULL)
		{
			tmp.id = atoi(sst); //商品id
		}
		else
		{
			break;
		}

		sst = strtok(NULL, "|");
		tmp.name = sst;	//商品名称

		sst = strtok(NULL, "|");
		tmp.date = sst;	//出售日期

		sst = strtok(NULL, "|");
		tmp.in_price = atof(sst);	//购入单价

		sst = strtok(NULL, "|");
		tmp.out_price = atof(sst);	//零售单价

		sst = strtok(NULL, "|");
		tmp.num = atoi(sst);	//出售数量

		sst = strtok(NULL, "|");
		tmp.sale = atof(sst);	//销售额

		sst = strtok(NULL, "|");
		tmp.income = atof(sst);	//净收入

		sa.push_back(tmp); //放在链表的后面
	}

	ifs.close(); //关闭文件
}

void CInfoFile::WirteSalesRecord()
{
	ofstream ofs(_F_SALES);//输出方式打开文件

	if (sa.size() > 0)	//有内容才执行
	{
		ofs << "商品ID|商品名称|出售日期|购入单价|零售单价|出售数量|销售额|净收入" << endl; //写入表头

		//通过迭代器取出链表内容，写入文件，以“|”分隔，结尾加换行
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
	ofs.close();//关闭文件
}

//添加新商品
//name:商品名称，num：库存，out_price：商品零售价格
int CInfoFile::Addline(CString name, int num, double  out_price, double  in_price, int kind, int firmID)
{
	msg tmp;

	//商品名称，库存，价格有效
	if (!name.IsEmpty() && num > 0 && out_price > 0 && in_price > 0)
	{
		tmp.id = ls.size() + 1;	//id自动加1
		CStringA str;
		str = name;	//CString转CStirngA
		tmp.name = str.GetBuffer(); //CStirngA转char *，商品名称
		tmp.num = num;	//库存
		tmp.out_price = out_price;	//商品零售价格
		tmp.firmID = firmID;//供应商编号
		tmp.in_price = in_price;//商品进货价格
		tmp.kind = kind;//商品类别号
		tmp.isPut = "未上架";//默认刚添加的商品不上架

		ls.push_back(tmp);	//放在链表的后面
	}
	return tmp.id;
}

void CInfoFile::Addline(CString user, CString pwd, CString name, CString jurisdiction)
{
	staff tmp;

	//职工信息有效
	if (!name.IsEmpty() && !user.IsEmpty() && !jurisdiction.IsEmpty() && !pwd.IsEmpty())
	{
		tmp.id = st.size() + 1;	//id自动加1
		CStringA str1;
		str1 = name;	//CString转CStirngA
		tmp.name = str1.GetBuffer(); //CStirngA转char *，

		CStringA str2;
		str2 = user;
		tmp.user = str2.GetBuffer();

		CStringA str3;
		str3 = pwd;
		tmp.pwd = str3.GetBuffer();

		CStringA str4;
		str4 = jurisdiction;
		tmp.jurisdiction = str4.GetBuffer();
		

		st.push_back(tmp);	//放在链表的后面
	}
}

void CInfoFile::Addline(CString question, CString answer)
{
	safety tmp;

	//安全问题有效
	if (!question.IsEmpty() && !answer.IsEmpty())
	{
		CStringA str1;
		str1 = question;	//CString转CStirngA
		tmp.question = str1.GetBuffer(); //CStirngA转char *，

		CStringA str2;
		str2 = answer;
		tmp.answer = str2.GetBuffer();

		qa.push_back(tmp);	//放在链表的后面
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
