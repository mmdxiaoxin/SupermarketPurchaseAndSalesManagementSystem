#pragma once

#include <string>

using namespace std;

#define CATEGORY 120000

struct category
{
	string storage_area;
	string small_category;
};

class CCategory
{
private:
	category m_category;
public:
	//������Ʒ������������Ʒ����
	void SetCategory(int kind);

	//������Ʒ�������
	string Area();

	//������ƷС����
	string SmallCategory();
};

