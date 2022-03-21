#define _CRT_SECURE_NO_WARNINGS
#include "calculate.h"
#include <iostream>
#include<stack>
using namespace std;
bool isOP(char c)
{
	for (int i = 0; i < 9; i++)
	{
		if (c == ops[i])
		{
			return true;
		}
	}
	return false;
}
int level(char theOpt)
{
	switch (theOpt) {
	case '(':
		return 0;
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	case ')':
		return 3;
	}
}
void change(string& before, string& after)//中缀转后缀
{
	int state = 1;//引入state来处理小数，如是1则在数字外，0则是数字内
	char c;
	for (int i = 0; i < before.length(); i++)
	{
		c = before[i];
		if (isdigit(c))
		{
			after = after + c;
			state = 0;
		}
		else
		{
			if (state == 0 && c == '.') {
				after = after + '.';
				continue;
			}
			if (state == 0 && c != '.') {
				after += ' ';
			}
			if (c == '(')
			{
				opt.push(c);
			}
			else if (c == ')') {
				while (!opt.empty() && opt.top() != '(') {
					after += opt.top();
					after += ' ';
					opt.pop();
				}
				opt.pop();
			}
			else
			{
				while (true)
				{
					if (opt.empty() || opt.top() == '(')
					{
						opt.push(c);
					}
					else if (level(c) > level(opt.top()))
					{
						opt.push(c);
					}
					else
					{
						after += opt.top();
						opt.pop();
						after += ' ';
						continue;
					}
					break;
				}
			}
			state = 1;
		}
	}
	while (!opt.empty()) {
		after += opt.top();
		after += ' ';
		opt.pop();
	}
}
string cal(string& expr)//计算后缀表达式
{
	int prenum = 0;
	bool dot = false;
	int state = 1;
	float count = 1;
	bool jogi = false;
	for (size_t i = 0; i < expr.length(); i++)
	{
		char c = expr[i];
		if (!isdigit(c) && c != '.')
		{
			jogi = true;
		}
	}
	if (!jogi)
	{
		return expr;
	}
	for (size_t i = 0; i < expr.length(); i++)
	{
		char c = expr[i];
		if (isdigit(c) || c == '.') {
			if (isdigit(c)) {
				prenum *= 10;
				prenum += c - '0';
				state = 0;
				if (dot == true)
					count *= 10.0;
			}
			if (c == '.') {
				dot = true;
				continue;
			}
		}
		else
		{
			dot = false;
			float num = prenum / count;
			count = 1;
			if (state == 0)
			{
				val.push(num);
				prenum = 0;
			}
			float x, y;
			if (c != ' ')
			{
				x = val.top();
				val.pop();
				y = val.top();
				val.pop();
				switch (c)
				{
				case '+':val.push(x + y); break;
				case '-':val.push(y - x); break;
				case '*':val.push(x * y); break;
				case '/':if (x != 0) { val.push(y / x); break; }
						else { return "除零错误"; }
				}
			}
			state = 1;
		}
	}
	char res[20];
	sprintf(res, "%f", val.top());
	for (int i = 0; i < strlen(res); i++)
	{
		if (res[i] == '.')
		{
			if (res[i + 1] == '0')
			{
				res[i] = '\0';
				break;
			}
			res[i + 2] = '\0';
			break;
		}
	}
	string resul = res;
	return resul;
}
string calculator(string& ori)
{//先处理空格
	string pre;
	//记录上一个有效元素,1数字2点3操作符
	int state = 0;
	for (int i = 0; i < ori.length(); i++)
	{
		char c = ori[i];
		if ((c < '0' || c>'9') && !isOP(c) && c != '\0' && c != ' ')
		{
			return "非法的数值";
		}
		if (c != ' ')
		{
			pre += c;
			if (isdigit(c))
			{
				state = 1;
			}
			else if (c == '.')
			{
				state = 2;
			}
			else if (isOP(c))
			{
				state = 3;
			}
		}
		else
		{
			if (state == 2)
			{
				return "空格错误";
			}
			else if (state == 1)
			{
				if (isdigit(ori[i + 1]))
				{
					return "空格错误";
				}
			}
		}
	}
	//再处理掉负号
	for (size_t i = 0; i < pre.size(); i++) {
		if (pre[i] == '-') {
			if (i == 0) {
				pre.insert(0, 1, '0');
			}
			else if (pre[i - 1] == '(') {
				pre.insert(i, 1, '0');
			}
			else if (isOP(pre[i - 1]))
			{
				return "操作符误用";
			}
		}
	}
	//对pre的正确性进行判断吧！
	bool innum = false;//表示是否在数中
	bool dot = false;//表示是否进入小数部分
	int brack = 0;//括号的个数,为0代表ok，正数是没消掉的左括号数，负数则是直接死
	//记录上一个有效元素,1数字2点3操作符
	state = 0;
	for (size_t i = 0; i < pre.size(); i++)
	{
		char c = pre[i];
		if (isdigit(c))
		{
			if (state == 1 && dot)
			{
				return "小数位数错误";
			}
			innum = true;
			state = 1;
		}
		else if (c == '.')
		{
			if (state != 1)
			{
				return "小数点错误";
			}
			if (dot)
			{
				return "小数点错误";
			}
			dot = true;
			state = 2;
		}
		else if (c == '(')
		{
			if (state == 1 || state == 2)
			{
				return "操作符错误";
			}
			if (dot)
			{
				return "小数点错误";
			}
			if (innum)
			{
				return "操作符错误";
			}
			brack += 1;
			state = 0;
		}
		else if (c == ')')
		{
			if (state != 1)
			{
				return "操作符错误";
			}
			brack -= 1;
			if (brack < 0)
			{
				return "括号匹配错误";
			}
			dot = false;
			innum = false;
			state = 1;
		}
		else if (isOP(c))
		{
			if (state != 1)
			{
				return "操作符错误";
			}
			dot = false;
			innum = false;
			state = 3;
		}
	}
	if (brack != 0)
	{
		return "括号匹配错误";
	}
	string fina;
	change(pre, fina);
	return cal(fina);
}