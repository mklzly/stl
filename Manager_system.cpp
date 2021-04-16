#include<iostream>
using namespace std;
#include"manager.h"

int main()
{
	//随机数的种子,这样编译器每次运行出来的数据就会不一样

	//创建管理类的对象-通过管理者类创建出来管理者对象来调用管理者类里面的成员函数
	SpeechManager sm;

	//测试12名选手的创建//map容器不允许储存相同的值
	//	for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++)
	//	{
	//		cout << "选手编号：" << it->first << "姓名：" << it->second.m_Name << "分数：" << it->second.m_Score << endl;
	//	}

	int choice = 0;//用于接受用户的输入

	while (true)//创建一个无限的循环，当程序启动时，将会一直在这个循环中进行知道操作退出
	{
		//1、显示菜单-通过管理者对象来调用显示菜单的成员函数
		sm.show_Menu();

		cout << "请输入你的选择：" << endl;
		cin >> choice;
		switch (choice)
		{
			//开始比赛
		case 1:
			sm.startSpeech();//调用开始比赛的成员函数
		   // system("cls");
			break;
			//查看往届比赛记录
		case 2:
			sm.showRecord();
			break;
			//清空比赛记录
		case 3:
			sm.clearRecord();
			break;
			//退出系统
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