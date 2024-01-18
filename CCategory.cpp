#include "pch.h"
#include "CCategory.h"

void CCategory::SetCategory(int kind)
{
	if (kind > CATEGORY && kind < CATEGORY + 5) 
	{
		m_category.storage_area = "ϴ���ջ���";
		switch (kind)
		{
		case CATEGORY + 1:m_category.small_category = "��Ӫϴ����Ʒ";
			break;
		case CATEGORY + 2:m_category.small_category = "��ױƷ";
			break;
		case CATEGORY + 3:m_category.small_category = "�������Ƽ�";
			break;
		case CATEGORY + 4:m_category.small_category = "������Ʒ";
			break;
		default:
			break;
		}
	}
	else if(kind > CATEGORY + 4 && kind < CATEGORY + 9)
	{
		m_category.storage_area = "����ˮ����";
		switch (kind)
		{
		case CATEGORY + 5:m_category.small_category = "ˮ��Ʒ";
			break;
		case CATEGORY + 6:m_category.small_category = "���Ʒ";
			break;
		case CATEGORY + 7:m_category.small_category = "����";
			break;
		case CATEGORY + 8:m_category.small_category = "����ӹ�ʳƷ";
			break;
		default:
			break;
		}
	}
	else if(kind > CATEGORY + 8 && kind < CATEGORY + 13)
	{
		m_category.storage_area = "���аٻ���";
		switch (kind)
		{
		case CATEGORY + 9:m_category.small_category = "���Ӱٻ�";
			break;
		case CATEGORY + 10:m_category.small_category = "��ʳ";
			break;
		case CATEGORY + 11:m_category.small_category = "����ʳƷ";
			break;
		case CATEGORY + 12:m_category.small_category = "������Ʒ";
			break;
		default:
			break;
		}
	}
	else if (kind > CATEGORY + 12 && kind < CATEGORY + 16)
	{
		m_category.storage_area = "���аٻ���";
		switch (kind)
		{
		case CATEGORY + 13:m_category.small_category = "��Ӫ�ճ�����";
			break;
		case CATEGORY + 14:m_category.small_category = "��ˮ";
			break;
		case CATEGORY + 15:m_category.small_category = "����";
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
