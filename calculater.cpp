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
void change(string& before, string& after)//��׺ת��׺
{
	int state = 1;//����state������С��������1���������⣬0����������
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
string cal(string& expr)//�����׺���ʽ
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
						else { return "�������"; }
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
{//�ȴ���ո�
	string pre;
	//��¼��һ����ЧԪ��,1����2��3������
	int state = 0;
	for (int i = 0; i < ori.length(); i++)
	{
		char c = ori[i];
		if ((c < '0' || c>'9') && !isOP(c) && c != '\0' && c != ' ')
		{
			return "�Ƿ�����ֵ";
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
				return "�ո����";
			}
			else if (state == 1)
			{
				if (isdigit(ori[i + 1]))
				{
					return "�ո����";
				}
			}
		}
	}
	//�ٴ��������
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
				return "����������";
			}
		}
	}
	//��pre����ȷ�Խ����жϰɣ�
	bool innum = false;//��ʾ�Ƿ�������
	bool dot = false;//��ʾ�Ƿ����С������
	int brack = 0;//���ŵĸ���,Ϊ0����ok��������û������������������������ֱ����
	//��¼��һ����ЧԪ��,1����2��3������
	state = 0;
	for (size_t i = 0; i < pre.size(); i++)
	{
		char c = pre[i];
		if (isdigit(c))
		{
			if (state == 1 && dot)
			{
				return "С��λ������";
			}
			innum = true;
			state = 1;
		}
		else if (c == '.')
		{
			if (state != 1)
			{
				return "С�������";
			}
			if (dot)
			{
				return "С�������";
			}
			dot = true;
			state = 2;
		}
		else if (c == '(')
		{
			if (state == 1 || state == 2)
			{
				return "����������";
			}
			if (dot)
			{
				return "С�������";
			}
			if (innum)
			{
				return "����������";
			}
			brack += 1;
			state = 0;
		}
		else if (c == ')')
		{
			if (state != 1)
			{
				return "����������";
			}
			brack -= 1;
			if (brack < 0)
			{
				return "����ƥ�����";
			}
			dot = false;
			innum = false;
			state = 1;
		}
		else if (isOP(c))
		{
			if (state != 1)
			{
				return "����������";
			}
			dot = false;
			innum = false;
			state = 3;
		}
	}
	if (brack != 0)
	{
		return "����ƥ�����";
	}
	string fina;
	change(pre, fina);
	return cal(fina);
}