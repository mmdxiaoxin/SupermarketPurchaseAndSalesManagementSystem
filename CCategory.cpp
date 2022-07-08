#include "pch.h"
#include "CCategory.h"

void CCategory::SetCategory(int kind)
{
	if (kind > CATEGORY && kind < CATEGORY + 5) 
	{
		m_category.storage_area = "洗漱日化区";
		switch (kind)
		{
		case CATEGORY + 1:m_category.small_category = "经营洗漱用品";
			break;
		case CATEGORY + 2:m_category.small_category = "化妆品";
			break;
		case CATEGORY + 3:m_category.small_category = "生活用制剂";
			break;
		case CATEGORY + 4:m_category.small_category = "日用杂品";
			break;
		default:
			break;
		}
	}
	else if(kind > CATEGORY + 4 && kind < CATEGORY + 9)
	{
		m_category.storage_area = "生鲜水果区";
		switch (kind)
		{
		case CATEGORY + 5:m_category.small_category = "水产品";
			break;
		case CATEGORY + 6:m_category.small_category = "畜产品";
			break;
		case CATEGORY + 7:m_category.small_category = "果蔬";
			break;
		case CATEGORY + 8:m_category.small_category = "日配加工食品";
			break;
		default:
			break;
		}
	}
	else if(kind > CATEGORY + 8 && kind < CATEGORY + 13)
	{
		m_category.storage_area = "休闲百货区";
		switch (kind)
		{
		case CATEGORY + 9:m_category.small_category = "日杂百货";
			break;
		case CATEGORY + 10:m_category.small_category = "零食";
			break;
		case CATEGORY + 11:m_category.small_category = "休闲食品";
			break;
		case CATEGORY + 12:m_category.small_category = "生活用品";
			break;
		default:
			break;
		}
	}
	else if (kind > CATEGORY + 12 && kind < CATEGORY + 16)
	{
		m_category.storage_area = "休闲百货区";
		switch (kind)
		{
		case CATEGORY + 13:m_category.small_category = "经营日常调料";
			break;
		case CATEGORY + 14:m_category.small_category = "酒水";
			break;
		case CATEGORY + 15:m_category.small_category = "饮料";
			break;
		default:
			break;
		}
	}
}

string CCategory::Area()
{
	return m_category.storage_area;
}

string CCategory::SmallCategory()
{
	return m_category.small_category;
}
