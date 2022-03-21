#include "user.h"
#include "main.h"
void User::buyermenu()
{
	cout << "=========================================================================" << endl;
	cout << "1.�鿴��Ʒ�б� 2.������Ʒ 3.������Ʒ 4.�鿴��ʷ���� 5.�鿴��Ʒ���� 6.����" << endl;
	cout << "=========================================================================" << endl;
	cout << endl;
	cout << endl;
	cout << "������ѡ��";
}
void User::checkallgoods(Good* goods)
{
	Good* p = goods;
	cout << "*******************************************************************" << endl;
	cout << "��ƷID     ����      �۸�       ��Ŀ           �ϼ�ʱ��            " << endl;
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
	cout << "��ƷID        ����          �۸�          �ϼ�ʱ��               ����ID" << endl;
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
			cout << "��Ʒ���ţ�" << p->mid << endl;
			cout << "��Ʒ���ƣ�" << p->name << endl;
			cout << "��Ʒ��" << p->price << endl;
			cout << "��Ʒ������" << p->discri << endl;
			cout << "��Ʒ������" << p->num << endl;
			cout << "�ϼ�ʱ�䣺" << p->time << endl;
			cout << "����ID��" << p->seller << endl;
			cout << "*******************************" << endl;
			flag = true;
		}
	}
	if (flag == false)
	{
		cout << "��Ǹ��δ�ҵ�����Ʒ��" << endl;
	}
	cout << endl;
	cout << endl;
}
void User::deal(Deal* deals, Good* goods, User* users)
{
	cout << "��������ƷID��";
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
		cout << "����Ʒ�����ڣ�" << endl;
	}
	else
	{
		if (p->state == 1)
		{
			int yournum;
			cout << "������������";
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
				cout << "******����һ�������ʵ���Ŀ�����������룡******" << endl;
				cout << "��������Ŀ��";
			}
			if (yournum <= p->num)
			{
				if (money >= p->price*yournum)
				{
					cout << "****************************" << endl;
					cout << "�������ѣ�" << endl;
					time_t timep;
					time(&timep);
					char nowtime[30];
					strncpy(nowtime, ctime(&timep), 20);
					nowtime[20] = '\0';
					cout << "����ʱ�䣺" << nowtime << endl;
					cout << "���׽�" << p->price << endl;
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
					cout << "������" << money << endl;
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
					cout << "���㣡" << endl;
				}
			}
			else
			{
				cout << "����Ʒ��Ŀ���㣡" << endl;
			}
		}
	}
}
void  User::checkdeal_b(Deal* deals)
{
	cout << "*******************************************************************************" << endl;
	cout << "ID       ��ƷID        ����           ����ʱ��          ��Ŀ         ����ID" << endl;
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