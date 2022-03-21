#include "admin.h"
bool admin::adminload()
{
	char your_id[15];
	char your_secret[15];
	cout << "请输入管理员姓名：";
	cin >> your_id;
	cout << "请输入密码：";
	cin >> your_secret;
	if (strcmp(your_id, ID)==0 && strcmp(your_secret, secret)==0)
	{
		cout << endl;
		cout << "----登录成功----";
		cout << endl;
		cout << endl;
		return true;
	}
	else
	{
		cout << endl;
		cout << "----登陆失败，自己反思一下！----";
		cout << endl;
		cout << endl;
		return false;
	}
}void admin::adminmeun()
{
	cout << "=====================================================================================" << endl;
	cout << "1.查看所有商品 2.搜索商品 3.下架商品 4.查看所有订单 5.查看所有用户 6.禁封用户 7.注销" << endl;
	cout << "=====================================================================================" << endl;
	cout << endl;
	cout << "请输入操作：";
}
void admin::checkusers(User* users)
{
	cout << "*******************************************************************" << endl;
	cout << "用户ID    用户名      联系方式       地址        余额     生存状态" << endl;
	for (int i=0;i<UID;i++)
	{
		cout << users[i].uid << "       " << users[i].name << "         " << users[i].phone <<
			"       " << users[i].address << "        " <<setiosflags(ios::fixed) << setprecision(2)
			<< users[i].money << "     "<< users[i].exist<<endl;
	}
	cout << "*******************************************************************" << endl;
	cout << endl;
	cout << endl;
}
void admin::checkallgoods(Good* goods)
{
	Good* p = goods;
	cout << "*******************************************************************************" << endl;
	cout << "商品ID     名称      价格       数目           上架时间            状态（1.已上架2.已售出3.已下架）" << endl;
	for (; p->next != NULL; p = p->next)
	{
		cout << p->mid << "      " << p->name << "     " << setiosflags(ios::fixed) << setprecision(1) << p->price << "      " << p->num << "       " <<
			p->time << "        " << p->state << endl;
	}
	cout << "*******************************************************************************" << endl;
	cout << endl;
	cout << endl;
}
void admin::find(Good* goods,char* name)
{
	string str1(name);
	cout << "************************************************************************************" << endl;
	cout << "商品ID        名称          价格          上架时间             卖家ID           状态" << endl;
	for (Good* p = goods; p->next != NULL; p = p->next)
	{
		string str2(p->name);
		int i = str2.find(str1);
		if (i != -1)
		{
			cout << p->mid << "        " << p->name << "          " << p->price << "      " << p->time 
				<< "      " << p->seller <<"           "<<p->state<< endl;
		}
	}
	cout << "************************************************************************************" << endl;
	cout << endl;
	cout << endl;
}
void  admin::checkdeal(Deal* deals)
{
	cout << "*******************************************************************************" << endl;
	cout << "ID       商品ID        单价           交易时间          数目    买家ID    卖家ID" << endl;
	for (Deal* p = deals; p->next != NULL; p = p->next)
	{
		if (true)
		{
			cout << p->tid << "      " << p->good << "         " << p->singleprice << "       "
				<< p->time << "        " << p->num << "    " << p->buyer << "    "<<p->seller<<endl;
		}
	}
	cout << "*******************************************************************************" << endl;
}
void admin::takedown(Good* goods,char* goodid)
{
	Good* p = goods;
	goodid[1];
	for (; p != NULL; p = p->next)
	{
		int i = strcmp(p->mid,goodid);
		if (i== 0)
		{
			break;
		}
	}
	if (p == NULL)
	{
		cout << "未查找到该商品！" << endl;
	}
	else
	{
		cout << "确认下架该商品吗？(y/n)" << endl;
		cout << "**********************************************************************************************************************" << endl;
		cout << "商品ID         名称          价格       数目            上架时间          卖家ID      状态（1.已上架2.已售出3.已下架）" << endl;
		cout << p->mid << "            " << p->name << "       " << setiosflags(ios::fixed) << setprecision(1)
			<< p->price << "      " << p->num << "       " <<
			p->time << "        " << p->seller << "      " << p->state << endl;
		cout << "**********************************************************************************************************************" << endl;
		char yon[101];
		while (true)
		{
			cin >> yon;
			if (strcmp(yon, "y") == 0)
			{
				p->state=3;
				cout << "已为您下架" << endl;
				break;
			}
			else if (strcmp(yon, "n") == 0)
			{
				cout << "已取消下架" << endl;
				break;
			}
			else
			{
				cout << endl;
				cout << "----非法操作，请重新输入！----";
				cout << endl;
			};

		}
		
	}
	cout << endl;
}
void admin::kill(User* users,Good* goods,char* death)
{
	int i = 0;
	for (; i < UID; i++)
	{
		if (strcmp(users[i].uid, death)==0)
		{
			break;
		}
	}
	if (i < UID)
	{
		cout << "确定禁封该用户吗？" << endl;
		cout << "*******************************************************************" << endl;
		cout << "用户ID    用户名      联系方式       地址        余额     生存状态" << endl;
		cout << users[i].uid << "       " << users[i].name << "          " << users[i].phone <<
			"       " << users[i].address << "        " << setiosflags(ios::fixed) << setprecision(2)
			<< users[i].money << "     " << users[i].exist << endl;
		cout << "*******************************************************************" << endl;
		cout << "请选择（y/n）：";
		char yon[101];
		while (true)
		{
			cin >> yon;
			if (strcmp(yon, "y") == 0)
			{
				users[i].exist= false;
				cout << "禁封成功" << endl;
				cout << endl;
				for (Good* p = goods; p->next != NULL; p = p->next)
				{
					if (strcmp(p->seller, users[i].uid) == 0)
					{
						p->state = 3;
					}
				}
				break;
			}
			else if (strcmp(yon, "n") == 0)
			{
				cout << "已取消禁封！" << endl;
				break;
			}
			else
			{
				cout << endl;
				cout << "----非法操作，请重新输入！----";
				cout << endl;
			}
		}
	}
	else
	{
		cout << "******查无此人!******" << endl;
		cout << endl;
	}
}