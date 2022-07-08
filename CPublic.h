#pragma once

#include <string>

class CPublic
{
public:
	CPublic();
	virtual ~CPublic();
	//设置登陆者权限
	static void SetJurisdiction(std::string jurisdiction);

	//获取登陆者权限
	static std::string GetJurisdiction();

	//传递员工信息
	static void SetStaffInf(int id,
		std::string user,
		std::string name);

	//传递厂商信息
	static void SetFirmName(std::string name);

	//获取厂商名称
	static std::string GetFirmName();

	//传递商品信息
	static void SetProductName(std::string name);

	//获取商品名称
	static std::string GetProductName();

	//获取员工信息
	static int GetStaffId();
	static std::string GetStaffUser();
	static std::string GetStaffName();
private:
	//全局变量
	static std::string public_jurisdiction;//登陆权限
	static int public_id; //员工ID
	static std::string public_user; //员工用户名
	static std::string public_name; //员工名称
	static std::string public_product_name; //商品名称
	static std::string public_firm_name; //厂商名称
};

