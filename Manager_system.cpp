#include<iostream>
using namespace std;
#include"manager.h"

int main()
{
	//�����������,����������ÿ�����г��������ݾͻ᲻һ��

	//����������Ķ���-ͨ���������ഴ�����������߶��������ù�����������ĳ�Ա����
	SpeechManager sm;

	//����12��ѡ�ֵĴ���//map��������������ͬ��ֵ
	//	for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++)
	//	{
	//		cout << "ѡ�ֱ�ţ�" << it->first << "������" << it->second.m_Name << "������" << it->second.m_Score << endl;
	//	}

	int choice = 0;//���ڽ����û�������

	while (true)//����һ�����޵�ѭ��������������ʱ������һֱ�����ѭ���н���֪�������˳�
	{
		//1����ʾ�˵�-ͨ�������߶�����������ʾ�˵��ĳ�Ա����
		sm.show_Menu();

		cout << "���������ѡ��" << endl;
		cin >> choice;
		switch (choice)
		{
			//��ʼ����
		case 1:
			sm.startSpeech();//���ÿ�ʼ�����ĳ�Ա����
		   // system("cls");
			break;
			//�鿴���������¼
		case 2:
			sm.showRecord();
			break;
			//��ձ�����¼
		case 3:
			sm.clearRecord();
			break;
			//�˳�ϵͳ
		case 0:
			sm.exitSystem();
			break;

		default:
			//  system("cls");
			break;
		}
	}




	//system("pause");
	return 0;
}