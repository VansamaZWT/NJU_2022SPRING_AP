#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<iomanip>
using namespace std;
struct Good
{
	int state;//1已上架2已售出3已下架
	char mid[5];
	char name[101];
	float price;
	int num;
	char discri[201];
	char time[21];
	char seller[7];
	Good* next;
};
struct Deal
{
	char tid[5] = {'T'};
	char good[5];
	float singleprice;
	int num;
	char time[21];
	char seller[5];
	char buyer[5];
	Deal* next;
};
struct Charge {
	int num;
	char ID[11];
	Charge* next;
};
class User
{
public:
	User() { exist = false; };
	User(User* users);
	void usermenu();
	User userload(User* users);
	void usermessagemenu();
	void recharge(User* users);
	void self_message();
	void changemessage(User* users);
	void sellermenu();
	Good* sell(Good* goods);
	void checkgoods(Good* goods);
	Good* revise(Good* goods);
	void takedown(Good* goods,char* id);
	void buyermenu();
	void checkallgoods(Good* goods);
	void find(Good* goods,char* name);
	void checkagood(Good* goods,char* ID);
	void deal(Deal* deals, Good* goods, User* users);
	void checkdeal_b(Deal* deals);
	void checkdeal_s(Deal* deals);
	void extrasjk(Deal* deals, Good* goods, User* users);
	bool exist;
	char uid[5] = { 'U' };
	char name[11];
	char phone[21];
	char address[41];
	char secret[21];
	float money = 0;
};
class admin
{
public:
	admin()
	{
		strcpy(ID, "admin");
		strcpy(secret, "123456");
	};
	bool adminload();
	void adminmeun();
	void checkusers(User* users);
	void checkallgoods(Good* goods);
	void find(Good* goods,char* name);
	void checkdeal(Deal* deals);
	void takedown(Good* goods,char* goodid);
	void kill(User* users,Good* goods, char* death);
private:
	char secret[15];
	char ID[15];
};