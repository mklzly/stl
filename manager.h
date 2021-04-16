#pragma once
#include<iostream>
using namespace std;
#include<vector>
#include<map>
#include"Speaker.h"
#include<algorithm>
#include<deque>
#include<functional>
#include<numeric>
#include<fstream>
#include<ctime>

//设计演讲比赛的管理类
//功能描述
/*1、提供菜单界面与用户交互
* 2、对演讲比赛流程进行控制
* 3、与文件的读写交互
*/
//管理者类中包含了所有要执行的操作的成员函数-和要表达的成员属性
class SpeechManager
{
public:
	//构造函数
	SpeechManager();

	//展示菜单
	void show_Menu();

	//初始化属性
	void initSpeech();

	//退出系统
	void exitSystem();

	//初始化创建12名选手
	void creatSpeaker();

	//开始比赛-比赛控制流程
	void startSpeech();//这个函数用来控制整个比赛的流程

	//开始抽签
	void speechDraw();

	//正式比赛
	void speechContest();

	//显示比赛结果
	void showScore();

	//保存记录
	void saveRecord();

	//读取记录分数
	void loadRecord();

	//判断文件为空的标志
	bool fileIsEmpty;

	//显示往届得分
	void showRecord();

	//清空记录
	void clearRecord();


	//析构函数
	~SpeechManager();

	//在头文件里面只写函数的声明不写实现
	//构造函数和析构函数，如果自己不写，编译器也会给我们写上

 //成员属性
 //保存第一轮比赛选手编号容器
	vector<int>v1;

	//第一轮晋级参加第二轮比赛选手编号的容器
	vector<int>v2;

	//胜出前三名选手编号容器
	vector<int>vVivtory;

	//存放编号以及对应具体选手容器
	map<int, Speaker>m_Speaker;//这个容器哈哈哈-里面编号，选手姓名-分数它都有

	//往届记录
	map<int, vector<string>>m_Record;//key代表第几届，value记录所有信息

	//记录比赛轮次
	int m_Index;
};