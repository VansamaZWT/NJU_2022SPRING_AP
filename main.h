#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<math.h>
#include<string>
#include<time.h> 
#include <sstream>
#include < iomanip >
#include < stack >
#include "datestruct.h"
extern int UID;
extern int MID;
extern int TID;
void init();
char yourchoice();
void errorwa();
void showagood(Good* your_good);
void sellsuccess();
bool isFloat(const char* str);
bool isInt(const char* str);
void writeinuser(User* users);
void readuser(User* users);
void FGetStr(char* str, int size, FILE* file);
bool exists_(const std::string& name);
void writeingood(Good* goods);
void readgood(Good* goods);
void writeindeal(Deal* deals);
void readdeal(Deal* deals);
void sqladmin(char* commend, Good* goods, Deal* deals, User* users, admin you);
char* returnfind();
char* returntakedown();
char* returnkill();
char* returnkillu(char* comm);
void sqlbuyer(char* commend, Good* goods, Deal* deals, User* users, User you);
char* returncg();
void sqlseller(char* commend, Good* goods, Deal* deals, User* users, User you);
bool isOP(char c);
int level(char theOpt);
void change(string& before, string& after);
string cal(string& expr);
string calculator(string& ori);