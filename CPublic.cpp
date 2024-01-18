#include "pch.h"
#include "CPublic.h"


CPublic::CPublic()
{
}

CPublic::~CPublic()
{
}

std::string CPublic::public_jurisdiction = "Ö÷¹Ü";
std::string CPublic::public_user = "";
std::string CPublic::public_name = "";
std::string CPublic::public_product_name = "";
std::string CPublic::public_firm_name = "";
int CPublic::public_id = 0;

void CPublic::SetJurisdiction(std::string jurisdiction)
{
	public_jurisdiction = jurisdiction;
}

void CPublic::SetStaffInf(int id, std::string user, std::string name)
{
	public_id = id;
	public_name = name;
	public_user = user;
}

void CPublic::SetFirmName(std::string name)
{
	public_firm_name = name;
}

std::string CPublic::GetFirmName()
{
	return public_firm_name;
}

void CPublic::SetProductName(std::string name)
{
	public_product_name = name;
}

std::string CPublic::GetProductName()
{
	return	public_product_name;
}

int CPublic::GetStaffId()
{
	return public_id;
}

std::string CPublic::GetStaffUser()
{
	return public_user;
}

std::string CPublic::GetStaffName()
{
	return public_name;
}

std::string CPublic::GetJurisdiction()
{
	return public_jurisdiction;
}

