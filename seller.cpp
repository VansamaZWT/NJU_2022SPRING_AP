#include "user.h"
#include "main.h"
void User::sellermenu()
{
	cout << "===================================================================================" << endl;
	cout << "1.发布商品 2.查看发布商品 3.修改商品信息 4.下架商品 5.查看历史订单 6.返回用户主界面" << endl;
	cout << "===================================================================================" << endl;
	cout << endl;
	cout << endl;
	cout << "请输入选择：";
}
Good* User::sell(Good* goods)
{
	Good* p = goods;
	for (; p->next != NULL; p = p->next);
	cout << "请输入商品名称：";
	char good_name[101];
	cin>>good_name;
	strcpy(p->name, good_name);
	cout << "请输入商品金额：";
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
		cout << "******这是一个不合适的金额，请重新输入！******" << endl;
		cout << "请输入金额：";
	}
	cout << "请输入商品数目：";
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
		cout << "******这是一个不合适的数目，请重新输入！******" << endl;
		cout << "请输入数目：";
	}
	cout << "请输入商品描述：";
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
	cout << "请确认发布商品的信息无误！" << endl;
	cout << "*******************************" << endl;
	cout << "商品单号：" << your_good->mid<< endl;
	cout << "商品名称：" << your_good->name << endl;
	cout << "商品金额：" << setiosflags(ios::fixed) << setprecision(1)<< your_good->price<<endl;
	cout << "商品描述：" << your_good->discri << endl;
	cout << "*******************************" << endl;
	cout << endl;
}
void User::checkgoods(Good* goods)
{
	cout << "*******************************************************************************" << endl;
	cout << "商品ID     名称      价格       数目           上架时间            状态（1.已上架2.已售出3.已下架）" << endl;
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
	cout << "请输入修改商品ID：";
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
		cout << "未查找到该商品！" << endl;;
		return NULL;
	}
	else
	{
		cout << "请输入要修改的属性(1.价格 2.描述):";
		char c[101];
		cin >> c;
		if (strcmp(c,"1")==0)
		{
			cout << "请输入修改后的价格:";
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
				cout << "******这是一个不合适的金额，请重新输入！******" << endl;
				cout << "请输入您想要修改的价格：";
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
			cout << "修改成功！" << endl;
			p->price = m;
			return p;
		}
		else if (strcmp(c, "2") == 0)
		{
			cout << "请输入修改后的描述：";
			char dis[201];
			cin >> dis;
			strcpy(p->discri, dis);
			cout << "修改成功！" << endl;
			return p;
		}
		else
		{
			cout << "没有对应的商品属性，修改失败！" << endl;
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
		cout << "未查找到该商品！" << endl;
	}
	else
	{
		cout << "确认下架该商品吗？(y/n)" << endl;
		cout << "**********************************************************************************************************************" << endl;
		cout << "商品ID         名称          价格       数目            上架时间          卖家ID      状态（1.已上架2.已售出3.已下架）" << endl;
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
			cout << "-----非法操作！-----" << endl;
		};
		if (strcmp(yon, "y") == 0)
		{
			p->state = 3;
			cout << "已为您下架" << endl;
		}
		if (strcmp(yon, "n") == 0)
		{
			cout << "已取消下架" << endl;
		}
	}
}
void  User::checkdeal_s(Deal* deals)
{
	cout << "*******************************************************************************" << endl;
	cout << "ID       商品ID        单价           交易时间          数目         买家ID" << endl;
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