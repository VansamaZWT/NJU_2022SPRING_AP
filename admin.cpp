#include "admin.h"
bool admin::adminload()
{
	char your_id[15];
	char your_secret[15];
	cout << "���������Ա������";
	cin >> your_id;
	cout << "���������룺";
	cin >> your_secret;
	if (strcmp(your_id, ID)==0 && strcmp(your_secret, secret)==0)
	{
		cout << endl;
		cout << "----��¼�ɹ�----";
		cout << endl;
		cout << endl;
		return true;
	}
	else
	{
		cout << endl;
		cout << "----��½ʧ�ܣ��Լ���˼һ�£�----";
		cout << endl;
		cout << endl;
		return false;
	}
}void admin::adminmeun()
{
	cout << "=====================================================================================" << endl;
	cout << "1.�鿴������Ʒ 2.������Ʒ 3.�¼���Ʒ 4.�鿴���ж��� 5.�鿴�����û� 6.�����û� 7.ע��" << endl;
	cout << "=====================================================================================" << endl;
	cout << endl;
	cout << "�����������";
}
void admin::checkusers(User* users)
{
	cout << "*******************************************************************" << endl;
	cout << "�û�ID    �û���      ��ϵ��ʽ       ��ַ        ���     ����״̬" << endl;
	for (int i=0;i<UID;i++)
	{
		cout << users[i].uid << "       " << users[i].name << "         " << users[i].phone <<
			"       " << users[i].address << "        " <<setiosflags(ios::fixed) << setprecision(2)
			<< users[i].money << "     "<< users[i].exist<<endl;
	}
	cout << "*******************************************************************" << endl;
	cout << endl;
	cout << endl;
}
void admin::checkallgoods(Good* goods)
{
	Good* p = goods;
	cout << "*******************************************************************************" << endl;
	cout << "��ƷID     ����      �۸�       ��Ŀ           �ϼ�ʱ��            ״̬��1.���ϼ�2.���۳�3.���¼ܣ�" << endl;
	for (; p->next != NULL; p = p->next)
	{
		cout << p->mid << "      " << p->name << "     " << setiosflags(ios::fixed) << setprecision(1) << p->price << "      " << p->num << "       " <<
			p->time << "        " << p->state << endl;
	}
	cout << "*******************************************************************************" << endl;
	cout << endl;
	cout << endl;
}
void admin::find(Good* goods,char* name)
{
	string str1(name);
	cout << "************************************************************************************" << endl;
	cout << "��ƷID        ����          �۸�          �ϼ�ʱ��             ����ID           ״̬" << endl;
	for (Good* p = goods; p->next != NULL; p = p->next)
	{
		string str2(p->name);
		int i = str2.find(str1);
		if (i != -1)
		{
			cout << p->mid << "        " << p->name << "          " << p->price << "      " << p->time 
				<< "      " << p->seller <<"           "<<p->state<< endl;
		}
	}
	cout << "************************************************************************************" << endl;
	cout << endl;
	cout << endl;
}
void  admin::checkdeal(Deal* deals)
{
	cout << "*******************************************************************************" << endl;
	cout << "ID       ��ƷID        ����           ����ʱ��          ��Ŀ    ���ID    ����ID" << endl;
	for (Deal* p = deals; p->next != NULL; p = p->next)
	{
		if (true)
		{
			cout << p->tid << "      " << p->good << "         " << p->singleprice << "       "
				<< p->time << "        " << p->num << "    " << p->buyer << "    "<<p->seller<<endl;
		}
	}
	cout << "*******************************************************************************" << endl;
}
void admin::takedown(Good* goods,char* goodid)
{
	Good* p = goods;
	goodid[1];
	for (; p != NULL; p = p->next)
	{
		int i = strcmp(p->mid,goodid);
		if (i== 0)
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
		cout << p->mid << "            " << p->name << "       " << setiosflags(ios::fixed) << setprecision(1)
			<< p->price << "      " << p->num << "       " <<
			p->time << "        " << p->seller << "      " << p->state << endl;
		cout << "**********************************************************************************************************************" << endl;
		char yon[101];
		while (true)
		{
			cin >> yon;
			if (strcmp(yon, "y") == 0)
			{
				p->state=3;
				cout << "��Ϊ���¼�" << endl;
				break;
			}
			else if (strcmp(yon, "n") == 0)
			{
				cout << "��ȡ���¼�" << endl;
				break;
			}
			else
			{
				cout << endl;
				cout << "----�Ƿ����������������룡----";
				cout << endl;
			};

		}
		
	}
	cout << endl;
}
void admin::kill(User* users,Good* goods,char* death)
{
	int i = 0;
	for (; i < UID; i++)
	{
		if (strcmp(users[i].uid, death)==0)
		{
			break;
		}
	}
	if (i < UID)
	{
		cout << "ȷ��������û���" << endl;
		cout << "*******************************************************************" << endl;
		cout << "�û�ID    �û���      ��ϵ��ʽ       ��ַ        ���     ����״̬" << endl;
		cout << users[i].uid << "       " << users[i].name << "          " << users[i].phone <<
			"       " << users[i].address << "        " << setiosflags(ios::fixed) << setprecision(2)
			<< users[i].money << "     " << users[i].exist << endl;
		cout << "*******************************************************************" << endl;
		cout << "��ѡ��y/n����";
		char yon[101];
		while (true)
		{
			cin >> yon;
			if (strcmp(yon, "y") == 0)
			{
				users[i].exist= false;
				cout << "����ɹ�" << endl;
				cout << endl;
				for (Good* p = goods; p->next != NULL; p = p->next)
				{
					if (strcmp(p->seller, users[i].uid) == 0)
					{
						p->state = 3;
					}
				}
				break;
			}
			else if (strcmp(yon, "n") == 0)
			{
				cout << "��ȡ�����⣡" << endl;
				break;
			}
			else
			{
				cout << endl;
				cout << "----�Ƿ����������������룡----";
				cout << endl;
			}
		}
	}
	else
	{
		cout << "******���޴���!******" << endl;
		cout << endl;
	}
}