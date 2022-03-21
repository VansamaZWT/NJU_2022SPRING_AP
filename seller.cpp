#include "user.h"
#include "main.h"
void User::sellermenu()
{
	cout << "===================================================================================" << endl;
	cout << "1.������Ʒ 2.�鿴������Ʒ 3.�޸���Ʒ��Ϣ 4.�¼���Ʒ 5.�鿴��ʷ���� 6.�����û�������" << endl;
	cout << "===================================================================================" << endl;
	cout << endl;
	cout << endl;
	cout << "������ѡ��";
}
Good* User::sell(Good* goods)
{
	Good* p = goods;
	for (; p->next != NULL; p = p->next);
	cout << "��������Ʒ���ƣ�";
	char good_name[101];
	cin>>good_name;
	strcpy(p->name, good_name);
	cout << "��������Ʒ��";
	while (true)
	{
		char mon[101];
		cin >> mon;
		if (isFloat(mon))
		{
			float the_mon;
			sscanf(mon, "%f", &the_mon);
			if (the_mon <= 1000000)
			{
				p->price=the_mon;
				break;
			}
			else {
			}
		}
		cout << "******����һ�������ʵĽ����������룡******" << endl;
		cout << "�������";
	}
	cout << "��������Ʒ��Ŀ��";
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
				p->num = the_mon;
				break;
			}
			else {
			}
		}
		cout << "******����һ�������ʵ���Ŀ�����������룡******" << endl;
		cout << "��������Ŀ��";
	}
	cout << "��������Ʒ������";
	char discri[201];
	cin>>discri;
	strcpy(p->discri, discri);
	time_t timep;
	time(&timep);
	char nowtime[30];
	strcpy(nowtime, ctime(&timep));
	strncpy(p->time, nowtime, 20);
	nowtime[20] = '\0';
	p->time[20] = '\0';
	p->mid[0] = 'M';
	strcpy(p->seller, uid);
	for (int i = 3; i >= 1; i--)
	{
		int num = MID;
		for (int j = 1; j < 4 - i; j++)
		{
			num = num / 10;
		}
		p->mid[i] = '0' + num % 10;
	}
	p->mid[4] = '\0';
	MID++;
	p->state = 1;
	FILE* fp;
	fp = fopen("command.txt", "a");
	char com[101];
	strcpy(com, "INSERT INTO commodity VALUES (");
	fprintf(fp, "%s:%s", nowtime,com);
	fprintf(fp, "%s,%f,%d,%s", p->name, p->price, p->num, p->discri);
	fputc(')', fp);
	fputc('\n', fp);
	fclose(fp);
	p->next = new Good;
	p->next->next = NULL;

	return p;
}
void showagood(Good* your_good)
{
	cout << "��ȷ�Ϸ�����Ʒ����Ϣ����" << endl;
	cout << "*******************************" << endl;
	cout << "��Ʒ���ţ�" << your_good->mid<< endl;
	cout << "��Ʒ���ƣ�" << your_good->name << endl;
	cout << "��Ʒ��" << setiosflags(ios::fixed) << setprecision(1)<< your_good->price<<endl;
	cout << "��Ʒ������" << your_good->discri << endl;
	cout << "*******************************" << endl;
	cout << endl;
}
void User::checkgoods(Good* goods)
{
	cout << "*******************************************************************************" << endl;
	cout << "��ƷID     ����      �۸�       ��Ŀ           �ϼ�ʱ��            ״̬��1.���ϼ�2.���۳�3.���¼ܣ�" << endl;
	for (Good* p = goods; p->next != NULL; p = p->next)
	{
		if (strcmp(p->seller, uid) == 0)
		{
			cout << p->mid << "       " << p->name << "     "<<setiosflags(ios::fixed) <<setprecision(1)<< p->price <<"      " << p->num << "       " <<
				p->time << "        " <<p->state << endl;
		}
	}
	cout << "*******************************************************************************" << endl;
	cout << endl;
	cout << endl;
}
Good* User::revise(Good* goods)
{
	Good* p = goods;
	cout << "**************************************" << endl;
	cout << "�������޸���ƷID��";
	char ID[101];
	cin >> ID;
	for (; p != NULL; p = p->next)
	{
		if (strcmp(p->mid, ID) == 0 && strcmp(uid, p->seller) == 0)
		{
			break;
		}
	}
	if (p == NULL)
	{
		cout << "δ���ҵ�����Ʒ��" << endl;;
		return NULL;
	}
	else
	{
		cout << "������Ҫ�޸ĵ�����(1.�۸� 2.����):";
		char c[101];
		cin >> c;
		if (strcmp(c,"1")==0)
		{
			cout << "�������޸ĺ�ļ۸�:";
			float m=0;
			char mon[101];
			while (true)
			{
				cin >> mon;
				if (isFloat(mon))
				{
					sscanf(mon, "%f", &m);
					break;
				}
				cout << "******����һ�������ʵĽ����������룡******" << endl;
				cout << "����������Ҫ�޸ĵļ۸�";
			}
			char com[101];
			strcpy(com, "UPDATE commodity SET price = ");
			char pri[20];
			sprintf(pri, "%f", m);
			int i = 0;
			for (; pri[i] != '.'; i++);
			i += 2;
			pri[i] = '\0';
			strcat(com, pri);
			strcat(com, " WHERE commodityID = ");
			strcat(com, p->mid);
			time_t timep;
			time(&timep);
			char nowtime[30];
			strncpy(nowtime, ctime(&timep), 20);
			nowtime[20] = '\0';
			FILE* fp;
			fp = fopen("command.txt", "a+");
			fprintf(fp, "%s:%s", nowtime, com);
			fputc('\n', fp);
			fclose(fp);
			cout << "�޸ĳɹ���" << endl;
			p->price = m;
			return p;
		}
		else if (strcmp(c, "2") == 0)
		{
			cout << "�������޸ĺ��������";
			char dis[201];
			cin >> dis;
			strcpy(p->discri, dis);
			cout << "�޸ĳɹ���" << endl;
			return p;
		}
		else
		{
			cout << "û�ж�Ӧ����Ʒ���ԣ��޸�ʧ�ܣ�" << endl;
			return NULL;
		}
	}
}
void User::takedown(Good* goods,char*ID)
{
	Good* p = goods;
	for (; p != NULL; p = p->next)
	{
		if (strcmp(p->mid, ID) == 0 && strcmp(uid, p->seller) == 0)
		{
			break;
		}
	}
	if (p == NULL)
	{
		cout << "δ���ҵ�����Ʒ��" << endl;
	}
	else
	{
		cout << "ȷ���¼ܸ���Ʒ��(y/n)" << endl;
		cout << "**********************************************************************************************************************" << endl;
		cout << "��ƷID         ����          �۸�       ��Ŀ            �ϼ�ʱ��          ����ID      ״̬��1.���ϼ�2.���۳�3.���¼ܣ�" << endl;
		cout << p->mid << "           " << p->name << "       " << setiosflags(ios::fixed) << setprecision(1) 
			<< p->price << "      " << p->num << "       " <<
			p->time << "        " <<p->seller<<"      " <<p->state << endl;
		cout << "**********************************************************************************************************************" << endl;
		char yon[101];
		while (true)
		{
			cin >> yon;
			if (strcmp(yon, "y") == 0 || strcmp(yon, "n") == 0)
			{
				break;
			}
			cout << "-----�Ƿ�������-----" << endl;
		};
		if (strcmp(yon, "y") == 0)
		{
			p->state = 3;
			cout << "��Ϊ���¼�" << endl;
		}
		if (strcmp(yon, "n") == 0)
		{
			cout << "��ȡ���¼�" << endl;
		}
	}
}
void  User::checkdeal_s(Deal* deals)
{
	cout << "*******************************************************************************" << endl;
	cout << "ID       ��ƷID        ����           ����ʱ��          ��Ŀ         ���ID" << endl;
	for (Deal* p = deals; p->next != NULL; p = p->next)
	{
		if (strcmp(p->seller, uid) == 0)
		{
			cout << p->tid << "      " << p->good << "         " << p->singleprice << "       "
				<< p->time << "        " << p->num << "        " << p->buyer << endl;
		}
	}
	cout << "*******************************************************************************" << endl;
}