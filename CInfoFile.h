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
	int id;				//商品id
	string name;		//商品名称
	double out_price;		//商品零售价格
	double in_price;		//商品进货价格
	int num;			//商品个数
	int kind;			//商品类别号
	int firmID;			//供应商编号
	string isPut;		//是否上架
};

struct safety
{
	string question;
	string answer;
};

struct staff
{
	int id; //员工ID
	string user; //员工用户名
	string pwd; //员工密码
	string name; //员工名称
	string jurisdiction; //员工权限

};

struct firm
{
	string id; //厂商编号
	string name; //厂商名称
	string address; //厂商地址
	string phoneNumber; //厂商电话
	string fax; //厂商传真
};

struct purchase
{
	int id; //购入商品ID
	string name; //购入商品名称
	double in_price;//购入单价
	string date;//购入日期
	int num;//购入数量
	double cost;//购入花销
};

struct sales
{
	int id; //出售商品ID
	string name;//出售商品名称
	string date;//出售日期
	double in_price;//购入价格
	double out_price;//出售价格
	int num;//出售数量
	double sale;//销售额
	double income;//净收入
};

class CInfoFile
{
public:
	CInfoFile();
	~CInfoFile();

	//读取主管登陆信息
	void ReadLogin(CString& name, CString& pwd);

	//写入主管登陆信息
	void WirteLogin(CString& name, CString& pwd);

	//读取员工登陆信息
	void ReadLogin();

	//写入员工登陆信息
	void WirteLogin();

	//读取安全信息
	void ReadSafety();

	//安全信息写入文件
	void WirteSafety();

	//修改主管密码
	void WirtePwd(char* name, char* pwd);

	// 读取商品数据
	void ReadDocline();

	//商品写入文件
	void WirteDocline();

	//读取供应商信息
	void ReadFirm();

	//写入供应商信息
	void WirteFirm();

	//读取购买记录
	void ReadPurchaseRecord();

	//写入购买记录
	void WirtePurchaseRecord();

	//读取出售记录
	void ReadSalesRecord();

	//写入出售记录
	void WirteSalesRecord();

	//添加新商品
	int Addline(CString name, 
		int num, 
		double out_price, 
		double in_price, 
		int kind, 
		int firmID);

	//添加新职员
	void Addline(CString user,
		CString pwd,
		CString name,
		CString jurisdiction);

	//添加新安全信息
	void Addline(CString question, CString answer);

	//添加新厂商
	void Addline(string id,
		string name,
		string address,
		string phoneNumber,
		string fax);

	//添加购买信息
	void Addline(
		int id,
		string name,
		double in_price,
		string date,
		int num,
		double cost);

	//添加出售信息
	void Addline(int id,
		string name,
		string date,
		double in_price,
		double out_price,
		int num,
		double sale,
		double income);

	list<msg> ls;	//存储商品容器
	list<safety> qa; //存储安全问题
	list<staff> st; //存储员工信息
	list<firm> fi; //存储供应商信息
	list<purchase> pu; //存储购买记录
	list<sales> sa; //存储出售记录
	int num;			//用来记录商品个数
};
