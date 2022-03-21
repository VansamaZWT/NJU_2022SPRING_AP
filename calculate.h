#pragma once
#include "main.h"
char ops[10] = "+-*/()=.";
bool isOP(char c);
int level(char theOpt);
void change(string& before, string& after);
string cal(string& expr);
string calculator(string& ori);
extern stack<char> opt;
extern stack<float> val;