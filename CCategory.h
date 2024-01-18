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
	//根据商品种类编号区分商品类型
	void SetCategory(int kind);

	//返回商品存放区域
	string Area();

	//返回商品小分类
	string SmallCategory();
};

