#include "user.h"
#include "main.h"
void User::buyermenu()
{
	cout << "=========================================================================" << endl;
	cout << "1.查看商品列表 2.购买商品 3.搜索商品 4.查看历史订单 5.查看商品详情 6.返回" << endl;
	cout << "=========================================================================" << endl;
	cout << endl;
	cout << endl;
	cout << "请输入选择：";
}
void User::checkallgoods(Good* goods)
{
	Good* p = goods;
	cout << "*******************************************************************" << endl;
	cout << "商品ID     名称      价格       数目           上架时间            " << endl;
	for (; p->next != NULL; p = p->next)
	{
		if (p->state == 1)
		{
			cout << p->mid << "      " << p->name << "       " << setiosflags(ios::fixed) << setprecision(1) << p->price << "      " << p->num << "       " <<
				p->time << endl;
		}
	}
	cout << "*******************************************************************" << endl;
	cout << endl;
	cout << endl;
}
void User::find(Good* goods,char* name)
{
	string str1(name);
	cout << "***********************************************************************" << endl;
	cout << "商品ID        名称          价格          上架时间               卖家ID" << endl;
	for (Good* p = goods; p->next != NULL; p = p->next)
	{
		string str2(p->name);
		int i = str2.find(str1);
		if (i != -1&&p->state==1)
		{
			cout << p->mid << "        " << p->name << "          " << p->price <<"      "<<p->time<<"      "<<p->seller<<endl;
		}
	}
	cout << "***********************************************************************" << endl;
	cout << endl;
	cout << endl;
}
void User::checkagood(Good* goods,char* ID)
{
	bool flag = false;
	for (Good* p = goods; p->next != NULL; p = p->next)
	{
		if (strcmp(p->mid, ID) == 0)
		{
			cout << "*******************************" << endl;
			cout << "商品单号：" << p->mid << endl;
			cout << "商品名称：" << p->name << endl;
			cout << "商品金额：" << p->price << endl;
			cout << "商品描述：" << p->discri << endl;
			cout << "商品数量：" << p->num << endl;
			cout << "上架时间：" << p->time << endl;
			cout << "卖家ID：" << p->seller << endl;
			cout << "*******************************" << endl;
			flag = true;
		}
	}
	if (flag == false)
	{
		cout << "抱歉，未找到该商品！" << endl;
	}
	cout << endl;
	cout << endl;
}
void User::deal(Deal* deals, Good* goods, User* users)
{
	cout << "请输入商品ID：";
	char mID[15];
	cin >> mID;
	Good* p = goods;
	for (; p->next != NULL; p = p->next)
	{
		if (strcmp(p->mid, mID) == 0)
		{
			break;
		}
	}
	if (p->next == NULL)
	{
		cout << "该商品不存在！" << endl;
	}
	else
	{
		if (p->state == 1)
		{
			int yournum;
			cout << "请输入数量：";
			while (true)
			{
				char mon[101];
				cin >> mon;
				if (isInt(mon))
				{
					int the_mon;
					sscanf(mon, "%d", &the_mon);
					if (the_mon <= 1000000)
					{
						yournum = the_mon;
						break;
					}
					else {
					}
				}
				cout << "******这是一个不合适的数目，请重新输入！******" << endl;
				cout << "请输入数目：";
			}
			if (yournum <= p->num)
			{
				if (money >= p->price*yournum)
				{
					cout << "****************************" << endl;
					cout << "交易提醒！" << endl;
					time_t timep;
					time(&timep);
					char nowtime[30];
					strncpy(nowtime, ctime(&timep), 20);
					nowtime[20] = '\0';
					cout << "交易时间：" << nowtime << endl;
					cout << "交易金额：" << p->price << endl;
					money -= p->price*yournum;
					int n = uid[4] - '0' + (uid[3] - '0') * 10;
					users[n].money -= p->price * yournum;
					for (int i=0;i<UID; i++)
					{
						if (strcmp(users[i].uid, p->seller) == 0)
						{
							users[i].money += p->price*yournum;
						}
					}
					p->num -= yournum;
					cout << "您的余额：" << money << endl;
					cout << "****************************" << endl;
					int i = uid[4] - '0' + (uid[3] - '0') * 10;;
					users[i] = *this;
					Deal* o = deals;
					for (; o->next != NULL; o = o->next);
					strcpy(o->buyer, uid);
					strcpy(o->good, p->mid);
					strcpy(o->seller, p->seller);
					o->singleprice = p->price;
					o->num =yournum;
					strcpy(o->time, nowtime);
					for (int i = 3; i >= 1; i--)
					{
						int num = TID;
						for (int j = 1; j < 4 - i; j++)
						{
							num = num / 10;
						}
						o->tid[i] = '0' + num % 10;
					}
					o->tid[4] = '\0';
					TID++;
					FILE* fp;
					fp = fopen("command.txt", "a+");
					char com[101];
					strcpy(com, "INSERT INTO order VALUES (");
					fprintf(fp, "%s:%s", nowtime, com);
					fprintf(fp, "%s,%s,%f,%d,%s,%s,%s", o->tid, o->good,o->singleprice, o->num, o->time,o->buyer,o->seller);
					fputc(')', fp);
					fputc('\n', fp);
					fclose(fp);
					char com1[101];
					strcpy(com1, "UPDATE commodity SET number =");
					char com2[5];
					sprintf(com2, "%d", p->num);
					strcat(com1, com2);
					strcat(com1, " WHERE commodityID = ");
					strcat(com1, p->mid);
					fp = fopen("command.txt", "a");
					fprintf(fp, "%s:%s", nowtime, com1);
					fputc('\n', fp);
					fclose(fp);
					if (p->num == 0)
					{
						char c[101];
						strcpy(c, "UPDATE commodity SET state = removed WHERE commodityID = ");
						strcat(c, p->mid);
						admin a;
						sqladmin(c, goods, deals, users, a);
					}
					o->next = new Deal;
					o->next->next = NULL;
				}
				else
				{
					cout << "余额不足！" << endl;
				}
			}
			else
			{
				cout << "该商品数目不足！" << endl;
			}
		}
	}
}
void  User::checkdeal_b(Deal* deals)
{
	cout << "*******************************************************************************" << endl;
	cout << "ID       商品ID        单价           交易时间          数目         卖家ID" << endl;
	for (Deal* p = deals; p->next != NULL; p = p->next)
	{
		if (strcmp(p->buyer, uid) == 0)
		{
			cout << p->tid << "      " << p->good<< "         " << p->singleprice << "       " 
				<< p->time << "        " << p->num << "        " << p->seller << endl;
		}
	}
	cout << "*******************************************************************************" << endl;
}