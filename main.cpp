#include "main.h"
int UID = 0;
int MID = 0;
int TID = 0;
stack<char> opt;
stack<float> val;
int main()
{
	User users[101];
	Good* goods = new Good;
	goods->next = NULL;
	Deal* deals = new Deal;
	deals->next = NULL;
	FILE* fp;
	if (exists_("user.txt"))
	{
		readuser(users);
	}
	if (exists_("commodity.txt"))
	{
		readgood(goods);
	}
	if (exists_("orser.txt"))
	{
		readdeal(deals);
	}
	while (true)
	{
		init();
		char choice1[101];
		cin >> choice1;
		if (strcmp(choice1,"1")==0)//选择管理员登录
		{
			admin you;
			bool ok = you.adminload();
			if (ok == true)//登录成功后进入管理员界面
			{
				
				while (true)
				{
					you.adminmeun();
					char choice2[100];
					cin>>choice2;
					char com[101];
					if (strcmp(choice2,"1")==0)//查看所有商品
					{
						strcpy(com, "SELECT * FROM commodity");
						sqladmin(com, goods, deals, users, you);
					}
					else if (strcmp(choice2, "2") == 0)//搜索商品
					{
						strcpy(com,returnfind());
						sqladmin(com, goods, deals, users, you);
					}
					else if (strcmp(choice2, "3") == 0)//下架商品
					{
						strcpy(com, returntakedown());
						sqladmin(com, goods, deals, users, you);
						writeingood(goods);
					}
					else if (strcmp(choice2, "4") == 0)//查看所有订单
					{
						strcpy(com, "SELECT * FROM order");
						sqladmin(com, goods, deals, users, you);
					}
					else if (strcmp(choice2, "5") == 0)//查看所有用户
					{
						strcpy(com, "SELECT * FROM user");
						sqladmin(com, goods, deals, users, you);
					}
					else if (strcmp(choice2, "6") == 0)//禁封用户
					{
						strcpy(com, returnkill());
						sqladmin(com, goods, deals, users, you);
						char com_[101];
						strcpy(com_, returnkillu(com));
						sqladmin(com_, goods, deals, users, you);
						writeinuser(users);
					}
					else if (strcmp(choice2, "7") == 0)//注销
					{
						break;
					}
					else
					{
						errorwa();
					}
				}
			}
			else//登录失败则返回主菜单，进入下一次循环
			{ }
		}
		else if (strcmp(choice1, "2") == 0)//注册用户
		{
			User you(users);
			users[UID-1] = you;
			writeinuser(users);
		}
		else if (strcmp(choice1, "3") == 0)//登录用户
		{
			User you;
			you=you.userload(users);
			if(you.exist==true)
			{ 
				while (true)
				{
					you.usermenu();
					char choice2[101];
					cin >> choice2;
					if (strcmp(choice2, "4") == 0)//注销
					{
						cout << "------即将返回主菜单------" << endl;
						cout << endl;
						cout << endl;
						break;
					}
					else if (strcmp(choice2, "1") == 0)//买家模式
					{
						while (true)
						{
							you.buyermenu();
							char choice3[101];
							cin >> choice3;
							char com[101];
							if (strcmp(choice3, "1") == 0)
							{
								strcpy(com, "SELECT * FROM commodity");
								sqlbuyer(com, goods, deals, users, you);
							}
							else if (strcmp(choice3, "2") == 0)
							{
								you.deal(deals, goods, users);
								writeindeal(deals);
								writeingood(goods);
								writeinuser(users);
							}
							else if (strcmp(choice3, "3") == 0)
							{
								strcpy(com, returnfind());
								sqlbuyer(com, goods, deals, users, you);
							}
							else if (strcmp(choice3, "4") == 0)
							{
								strcpy(com, "SELECT * FROM order");
								sqlbuyer(com, goods, deals, users, you);
							}
							else if (strcmp(choice3, "5") == 0)
							{
								strcpy(com, returncg());
								sqlbuyer(com, goods, deals, users, you);
							}
							else if (strcmp(choice3, "6") == 0)
							{
								break;
							}
							else
							{
								errorwa();
							}
						}
					}
					else if (strcmp(choice2, "2") == 0)//卖家模式
					{
						you.sellermenu();
						char choice3[101];
						cin >> choice3;
						char com[101];
						if(strcmp(choice3, "1") == 0)
						{ 
							Good* your_good=you.sell(goods);
							showagood(your_good);
							cout << "确认发布吗(y/n):";
							char yon[101];
							while (true)
							{
								cin >> yon;
								if (strcmp(yon, "y") == 0)
								{
									sellsuccess();
									writeingood(goods);
									break;
								}
								else if (strcmp(yon, "n") == 0)
								{
									your_good->state = 3;
									cout << "已为您下架" << endl;
									writeingood(goods);
									break;
								}
								else
								{
									errorwa();
								};
								
							}
						}
						else if(strcmp(choice3, "2") == 0)
						{ 
							strcpy(com, "SELECT * FROM commodity");
							sqlseller(com, goods, deals, users, you);
						}
						else if (strcmp(choice3, "3") == 0)
						{
							Good* regood=you.revise(goods);
							if (regood != NULL)
							{
								showagood(regood);
							}
						}
						else if (strcmp(choice3, "4") == 0)
						{
							strcpy(com,returntakedown());
							sqlseller(com, goods, deals, users, you);
							writeingood(goods);
						}
						else if (strcmp(choice3, "5") == 0)
						{
							strcpy(com, "SELECT * FROM order");
							sqlseller(com, goods, deals, users, you);
						}
						else if (strcmp(choice3, "6") == 0)
						{
							break;
						}
						else
						{
							errorwa();
						}
					}
					else if (strcmp(choice2, "3") == 0)//个人信息管理
					{ 
						you.usermessagemenu();
						char choice3[101];
						cin >> choice3;
						if(strcmp(choice3,"1")==0)//返回用户菜单
						{ 
							
						}
						else if(strcmp(choice3, "2") == 0)
						{ 
							you.changemessage(users);
							writeinuser(users);
						}
						else if (strcmp(choice3, "3") == 0)
						{
							you.self_message();
						}
						else if (strcmp(choice3, "4") == 0)
						{
							you.recharge(users);
							writeinuser(users);
						}
						else
						{
							errorwa();
						}
					}
					else
					{
						errorwa();
					}
				}
			}
			else
			{ }
		}
		else if (strcmp(choice1, "4")==0)
		{
			break;
		}
		else if (strcmp(choice1, "5")==0)
		{
		string s1;
		cin >> s1;
		string a = calculator(s1);
		cout << a;
		cout << endl;
 }
		else
		{
			errorwa();
		}

	}
	return 0;
}
