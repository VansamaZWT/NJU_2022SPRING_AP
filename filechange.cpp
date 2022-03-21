#include "main.h"
bool exists_(const std::string& name) {
	if (FILE* file = fopen(name.c_str(), "r")) {
		fclose(file);
		return true;
	}
	else {
		return false;
	}
}
void FGetStr(char* str, int size, FILE* file)
{
	int i = 0;
	char c;
	while (c = fgetc(file), c != '\n' && c != EOF && i < size - 1)
	{
		str[i] = c;
		++i;
	}
	if (c != '\n')
	{
		ungetc(c, stdin);
	}
	str[i] = '\0';
}
void writeinuser(User* users)
{
	FILE* fp;
	fp = fopen("user.txt", "w");
	fputs("userID,username,password,phoneNumber,address,balance,userState\n", fp);
	for (int i = 0; i < UID; i++)
	{
		fprintf(fp, "%s,%s,%s,%s,%s,%.1f", users[i].uid, users[i].name, users[i].secret, users[i].phone, users[i].address, users[i].money);
		if (users[i].exist)
		{
			fprintf(fp, ",%s", "active\n");
		}
		else
		{
			fprintf(fp, ",%s", "inactive\n");
		}
	}
	fclose(fp);
}
void readuser(User* users)
{
	FILE* fp;
	fp = fopen("user.txt", "r");
	fseek(fp, 64, SEEK_SET);
	while(fread(&users[UID].uid[0], 1, 1, fp))
	{		
		int i = 0;
		i++;
		for (; users[UID].uid[i - 1] != ','; i++)
		{
			fread(&users[UID].uid[i], 1, 1, fp);
		}
		users[UID].uid[i - 1] = '\0';
		i = 0;
		fread(&users[UID].name[i], 1, 1, fp);
		i++;
		for (; users[UID].name[i - 1] != ','; i++)
		{
			fread(&users[UID].name[i], 1, 1, fp);
		}
		users[UID].name[i - 1] = '\0';
		i = 0;
		fread(&users[UID].secret[i], 1, 1, fp);
		i++;
		for (; users[UID].secret[i - 1] != ','; i++)
		{
			fread(&users[UID].secret[i], 1, 1, fp);
		}
		users[UID].secret[i - 1] = '\0';
		i = 0;
		fread(&users[UID].phone[i], 1, 1, fp);
		i++;
		for (; users[UID].phone[i - 1] != ','; i++)
		{
			fread(&users[UID].phone[i], 1, 1, fp);
		}
		users[UID].phone[i - 1] = '\0';
		i = 0;
		fread(&users[UID].address[i], 1, 1, fp);
		i++;
		for (; users[UID].address[i - 1] != ','; i++)
		{
			fread(&users[UID].address[i], 1, 1, fp);
		}
		users[UID].address[i - 1] = '\0';
		fscanf(fp, "%f", &users[UID].money);
		fseek(fp, 1, SEEK_CUR);
		char alive[10];
		FGetStr(alive, 9, fp);
		if (strcmp(alive, "active") == 0)
		{
			users[UID].exist = true;
		}
		else
		{
			users[UID].exist = false;
		}
		UID++;
	}
	fclose(fp);
}
void writeingood(Good* goods)
{
	FILE* fp;
	fp = fopen("commodity.txt", "w");
	fputs("commodityID,commodityName,price,number,description,sellerID,addedDate,state\n", fp);
	for (Good* p = goods;p->next!=NULL; p=p->next)
	{
		fprintf(fp, "%s,%s,%.1f,%d,%s,%s,%s", p->mid, p->name,p->price,p->num,p->discri,p->seller,p->time);
		if (p->state==1)
		{
			fprintf(fp, ",%s", "onSale\n");
		}
		else if(p->state==2)
		{
			fprintf(fp, ",%s", "sold\n");
		}
		else
		{
			fprintf(fp, ",%s", "removed\n");
		}
	}
	fclose(fp);
}
void readgood(Good* goods)
{
	FILE* fp;
	Good* p=goods;
	fp = fopen("commodity.txt", "r");
	fseek(fp, 77, SEEK_SET);
	while (fread(&p->mid[0], 1, 1, fp))
	{
		int i = 0;
		i++;
		for (; p->mid[i - 1] != ','; i++)
		{
			fread(&p->mid[i], 1, 1, fp);
		}
		p->mid[i - 1] = '\0';
		i = 0;
		fread(&p->name[i], 1, 1, fp);
		i++;
		for (; p->name[i - 1] != ','; i++)
		{
			fread(&p->name[i], 1, 1, fp);
		}
		p->name[i - 1] = '\0';
		fscanf(fp, "%f", &p->price);
		fseek(fp, 1, SEEK_CUR);
		fscanf(fp, "%d", &p->num);
		fseek(fp, 1, SEEK_CUR);
		i = 0;
		fread(&p->discri[i], 1, 1, fp);
		i++;
		for (; p->discri[i - 1] != ','; i++)
		{
			fread(&p->discri[i], 1, 1, fp);
		}
		p->discri[i - 1] = '\0';
		i = 0;
		fread(&p->seller[i], 1, 1, fp);
		i++;
		for (; p->seller[i - 1] != ','; i++)
		{
			fread(&p->seller[i], 1, 1, fp);
		}
		p->seller[i - 1] = '\0';
		i = 0;
		fread(&p->time[i], 1, 1, fp);
		i++;
		for (; p->time[i - 1] != ','; i++)
		{
			fread(&p->time[i], 1, 1, fp);
		}
		p->time[i - 1] = '\0';
		char alive[10];
		FGetStr(alive, 9, fp);
		if (strcmp(alive, "onSale") == 0)
		{
			p->state = 1;
		}
		else if (strcmp(alive, "sold") == 0)
		{
			p->state = 2;
		}
		else
		{
			p->state = 3;
		}
		p->next = new Good;
		p->next->next = NULL;
		p = p->next;
		MID++;
	}
	fclose(fp);
}
void writeindeal(Deal* deals)
{
	FILE* fp;
	fp = fopen("order.txt", "w");
	fputs("orderID,commodityID,unitPrice,number,date,sellerID,buyerID\n", fp);
	for (Deal* p = deals; p->next != NULL; p = p->next)
	{
		fprintf(fp, "%s,%s,%.1f,%d,%s,%s,%s", p->tid, p->good, p->singleprice, p->num, p->time, p->seller, p->buyer);
	}
	fclose(fp);
}
void readdeal(Deal* deals)
{
	FILE* fp;
	Deal* p = deals;
	fp = fopen("order.txt", "r");
	fseek(fp, 60, SEEK_SET);
	while (fread(&p->tid[0], 1, 1, fp))
	{
		int i = 0;
		i++;
		for (; p->tid[i - 1] != ','; i++)
		{
			fread(&p->tid[i], 1, 1, fp);
		}
		p->tid[i - 1] = '\0';
		i = 0;
		fread(&p->good[i], 1, 1, fp);
		i++;
		for (; p->good[i - 1] != ','; i++)
		{
			fread(&p->good[i], 1, 1, fp);
		}
		p->good[i - 1] = '\0';
		fscanf(fp, "%f", &p->singleprice);
		fseek(fp, 1, SEEK_CUR);
		fscanf(fp, "%d", &p->num);
		fseek(fp, 1, SEEK_CUR);
		i = 0;
		fread(&p->time[i], 1, 1, fp);
		i++;
		for (; p->time[i - 1] != ','; i++)
		{
			fread(&p->time[i], 1, 1, fp);
		}
		p->time[i - 1] = '\0';
		i = 0;
		fread(&p->seller[i], 1, 1, fp);
		i++;
		for (; p->seller[i - 1] != ','; i++)
		{
			fread(&p->seller[i], 1, 1, fp);
		}
		p->seller[i - 1] = '\0';
		i = 0;
		fread(&p->buyer[i], 1, 1, fp);
		i++;
		for (; p->buyer[i - 1] != ','; i++)
		{
			fread(&p->buyer[i], 1, 1, fp);
		}
		p->buyer[i - 1] = '\0';
		p->next = new Deal;
		p->next->next = NULL;
		p = p->next;
		TID++;
	}
	fclose(fp);
}