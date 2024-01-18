#pragma once

#include <string>

class CPublic
{
public:
	CPublic();
	virtual ~CPublic();
	//���õ�½��Ȩ��
	static void SetJurisdiction(std::string jurisdiction);

	//��ȡ��½��Ȩ��
	static std::string GetJurisdiction();

	//����Ա����Ϣ
	static void SetStaffInf(int id,
		std::string user,
		std::string name);

	//���ݳ�����Ϣ
	static void SetFirmName(std::string name);

	//��ȡ��������
	static std::string GetFirmName();

	//������Ʒ��Ϣ
	static void SetProductName(std::string name);

	//��ȡ��Ʒ����
	static std::string GetProductName();

	//��ȡԱ����Ϣ
	static int GetStaffId();
	static std::string GetStaffUser();
	static std::string GetStaffName();
private:
	//ȫ�ֱ���
	static std::string public_jurisdiction;//��½Ȩ��
	static int public_id; //Ա��ID
	static std::string public_user; //Ա���û���
	static std::string public_name; //Ա������
	static std::string public_product_name; //��Ʒ����
	static std::string public_firm_name; //��������
};

