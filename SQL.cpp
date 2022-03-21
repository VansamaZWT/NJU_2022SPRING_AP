#include "main.h"
void sqladmin(char* commend,Good* goods,Deal* deals,User* users,admin you)
{
	time_t timep;
	time(&timep);
	char nowtime[30];
	strncpy(nowtime, ctime(&timep), 20);
	nowtime[20] = '\0';
	FILE* fp;
	fp=fopen("command.txt", "a");
	fprintf(fp, "%s:%s", nowtime, commend);
	fputc('\n', fp);
	fclose(fp);
	string com(commend);
	if (com[0] == 'S')
	{
		if (com.compare("SELECT * FROM commodity") == 0)
		{
			you.checkallgoods(goods);
			return;
		}
		else if (com.compare("SELECT * FROM order") == 0)
		{
			you.checkdeal(deals);
		}
		else if (com.compare("SELECT * FROM user") == 0)
		{
			you.checkusers(users);
		}
		else
		{
			string na = com.substr(53);
			char p[21];
			int i;
			for (i = 0; i < na.length(); i++)
				p[i] = na[i];
			p[i] = '\0';
			you.find(goods, p);
		}
	}
	else if (com[0] == 'U')
	{
		if (com[7] == 'c') {
			if (com[43] == 'c')
			{
				string mid = com.substr(57);
				char p[21];
				int i;
				for (i = 0; i < mid.length(); i++)
					p[i] = mid[i];
				p[i] = '\0';
				you.takedown(goods, p);
			}
			else if (com[43] == 's')
			{
				string id = com.substr(54);
				char p[21];
				int i;
				for (i = 0; i < id.length(); i++)
					p[i] = id[i];
				p[i] = '\0';
				you.kill(users, goods, p);
			}
		}
		else if (com[7] == 'u')
		{
			
		}
	}
}
void sqlbuyer(char* commend, Good* goods, Deal* deals, User* users, User you)
{
	time_t timep;
	time(&timep);
	char nowtime[30];
	strncpy(nowtime, ctime(&timep), 20);
	nowtime[20] = '\0';
	FILE* fp;
	fp = fopen("command.txt", "a");
	fprintf(fp, "%s:%s", nowtime, commend);
	fputc('\n', fp);
	fclose(fp);
	string com(commend);
	if (com[0] == 'S')
	{
		if (com.compare("SELECT * FROM commodity") == 0)
		{
			you.checkallgoods(goods);
			return;
		}
		else if (com.compare("SELECT * FROM order") == 0)
		{
			you.checkdeal_b(deals);
		}
		else if (com[39]=='N')
		{
			string na = com.substr(53);
			char p[21];
			int i;
			for (i = 0; i < na.length(); i++)
				p[i] = na[i];
			p[i] = '\0';
			you.find(goods, p);
		}
		else
		{
			string na = com.substr(51);
			char p[21];
			int i;
			for (i = 0; i < na.length(); i++)
				p[i] = na[i];
			p[i] = '\0';
			you.checkagood(goods, p);
		}
	}
	else if(com[0] == 'U')
	{
		you.extrasjk(deals, goods, users);
	}
}
void sqlseller(char* commend, Good* goods, Deal* deals, User* users, User you)
{
	time_t timep;
	time(&timep);
	char nowtime[30];
	strncpy(nowtime, ctime(&timep), 20);
	nowtime[20] = '\0';
	FILE* fp;
	fp = fopen("command.txt", "a");
	fprintf(fp, "%s:%s", nowtime, commend);
	fputc('\n', fp);
	fclose(fp);
	string com(commend);
	if (com[0] == 'S')
	{
		if (com.compare("SELECT * FROM commodity") == 0)
		{
			you.checkgoods(goods);
			return;
		}
		else if (com.compare("SELECT * FROM order") == 0)
		{
			you.checkdeal_s(deals);
		}
		else if (com[39] == 'N')
		{
			string na = com.substr(53);
			char p[21];
			int i;
			for (i = 0; i < na.length(); i++)
				p[i] = na[i];
			p[i] = '\0';
			you.find(goods, p);
		}
		else
		{
			string na = com.substr(51);
			char p[21];
			int i;
			for (i = 0; i < na.length(); i++)
				p[i] = na[i];
			p[i] = '\0';
			you.checkagood(goods, p);
		}
	}
	else if (com[0] == 'U')
	{
		if (com[7] == 'c')
		{
			if (com[43] == 'c')
			{
				string mid = com.substr(57);
				char p[21];
				int i;
				for (i = 0; i < mid.length(); i++)
					p[i] = mid[i];
				p[i] = '\0';
				you.takedown(goods, p);
			}
			else if (com[22] == 'p')
			{

			}
		}
		

	}
	else if (com[0] == 'I')
	{
		you.extrasjk(deals, goods, users);
	}
}
char* returnfind()
{
	cout << "**************************************" << endl;
	cout << "请输入搜索商品名称：";
	char ID[101];
	cin >> ID;
	char c[101];
	strcpy(c, "SELECT * FROM commodity WHERE commodityName CONTAINS ");
	strcat(c, ID);
	return c;
	
}
char* returntakedown()
{
	cout << "**************************************" << endl;
	cout << "请输入下架商品ID:";
	char ID[101];
	cin >> ID;
	char c[101];
	strcpy(c, "UPDATE commodity SET state = removed WHERE commodityID = ");
	strcat(c, ID);
	return c;
}
char* returnkill()
{
	cout << "**************************************" << endl;
	cout << "请输入注销用户ID：";
	char ID[101];
	cin >> ID;
	char c[101];
	strcpy(c, "UPDATE commodity SET state = removed WHERE sellerID = ");
	strcat(c, ID);
	return c;
}
char* returnkillu(char* comm)
{
	string com = comm;
	string id = com.substr(54);
	char p[21];
	int i;
	for (i = 0; i < id.length(); i++)
		p[i] = id[i];
	p[i] = '\0';
	char andsoon[101];
	strcpy(andsoon, "UPDATE user SET state = inactive WHERE userID = ");
	strcat(andsoon, p);
	return andsoon;
}
char* returncg()
{
	cout << "**************************************" << endl;
	cout << "请输入搜索商品ID：";
	char ID[101];
	cin >> ID;
	char c[101];
	strcpy(c, "SELECT * FROM commodity WHERE commodityID CONTAINS ");
	strcat(c, ID);
	return c;
}