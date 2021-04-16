#include"manager.h"



//构造函数
SpeechManager::SpeechManager()
{
	//初始化容器和属性的函数
	this->initSpeech();

	//创建选手
	this->creatSpeaker();

	//获取往届记录
	this->loadRecord();        //这条就是出现头行文件不存在的情况的原因

}

//菜单功能
void SpeechManager::show_Menu()
{
	cout << "------------------------------------" << endl;
	cout << "----------欢迎参加演讲比赛----------" << endl;
	cout << "----------1、开始演讲比赛-----------" << endl;
	cout << "----------2、查看往届记录-----------" << endl;
	cout << "----------3、清空比赛记录-----------" << endl;
	cout << "----------0、退出比赛程序-----------" << endl;
	cout << "------------------------------------" << endl;
	cout << endl;
}



//初始化属性
void SpeechManager::initSpeech()
{
	//保证容器都置空
	this->v1.clear();
	this->v2.clear();
	this->vVivtory.clear();
	this->m_Speaker.clear();

	//初始化比赛轮次
	this->m_Index = 1;

	//初始化记录容器
	this->m_Record.clear();
}


//初始化创建12名选手
void SpeechManager::creatSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";//创建名称种子
	for (int i = 0; i < nameSeed.size(); i++)
	{

		string name = "选手";//通过循环给每个选手进行标号
		name += nameSeed[i];

		Speaker sp;//通过选手类创建选手对象
		sp.m_Name = name;//然后给每个创建出来的选手进行命名

		///
		for (int i = 0; i < 2; i++)
		{
			sp.m_Score[i] = 0;//将可以存放两轮分数的m_Score都赋初值0
		}
		///
		//12名选手编号,放到v1容器中
		this->v1.push_back(i + 10001);

		//选手编号以及对应的选手存放到map容器中
		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}

}


//开始抽签
void SpeechManager::speechDraw()
{
	cout << "第" << this->m_Index << "轮比赛选手正在抽签" << endl;
	cout << "----------------------------------------" << endl;
	cout << "抽签后的演讲顺序如下：" << endl;


	//区别是第几轮比赛通过一个判断语句
	if (this->m_Index == 1)
	{
		//第一轮比赛抽签
		random_shuffle(v1.begin(), v1.end());//STL 中的函数 random_shuffle() 用来对一个元素序列进行重新排序（随机的）-头文件是#include <algorithm>
		//这里就类似于摇号箱一样将里面的内容打乱

		//这里通过vector迭代器遍历抽签后的出场编号并打印
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		//第二轮比赛抽签
		random_shuffle(v2.begin(), v2.end());


		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}

	system("pause");
	cout << endl;
}



//抽签后正式比赛
void SpeechManager::speechContest()
{
	cout << "------第" << this->m_Index << "轮正式比赛开始：-------" << endl;

	multimap<double, int, greater<double>>groupScore;//临时容器，保存key-分数 value-选手编号//multimap容器允许出现重复的值-greater<double>为降序排列


	int num = 0;//记录人员数，6个为1组

	vector<int>v_Src;//比赛的人员容器-用来存储比赛中选手的容器


	if (this->m_Index == 1)
	{
		v_Src = v1;//如果是第一轮比赛就将容器1里面的数据给比赛专用的容器
	}
	else
	{
		v_Src = v2;
	}


	//遍历v_Src容器里所有参赛选手
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;//记录选手个数

		//评委打分
		deque<double>d; //评委打分的容器-deque双向开口可进可出的容器 -对头部的插入删除速度快


		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 41 + 60) / 1.f;//60~100//这样可以创建出小数

			//cout << score << " ";//具体的得分-测试代码

			d.push_back(score);//然后通过尾插法将评委的打分存储到deque的容器中
		}


		sort(d.begin(), d.end(), greater<double>());//降序排列
		d.pop_front();//去掉最高分
		d.pop_back();//去掉最低分

		double sum = accumulate(d.begin(), d.end(), 0.0f);//获取总分//第三个参数是起始累加值-头文件是#include<numeric>
		double avg = sum / (double)d.size();//获取平均分-这里用到了一个强制转换

		//打印平均分-测试代码
		//cout << "编号：" << *it << "  姓名：" << this->m_Speaker[*it].m_Name << "  获取平均分:" << avg << endl;


		//将得到的平均分放到正在参赛选手的容器中-对应存放选手得分的记录
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;//double m_Score[2];//分数，最多记录两轮的得分


		//将参加比赛的选手的得分和编号放到临时的groupScore容器中
		groupScore.insert(make_pair(avg, *it));//key是得分，value是具体选手的编号



		//每6人取出前三名-每轮6人制比赛
		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "小组比赛名次： " << endl;

			//通过迭代器遍历临时multimap容器groupScore中的选手信息-并打印信息
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				//
				cout << "编号：" << it->second << "  姓名：" << this->m_Speaker[it->second].m_Name << "  成绩:"
					<< this->m_Speaker[it->second].m_Score[this->m_Index - 1] << endl;
			}
			//

						//取走前三名-在临时存放选手信息的容器中（这个容器里的信息是采用降序排列的）截取前三名几位老大老二老三
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; count++, it++)
			{
				if (this->m_Index == 1)
				{	//如果是第一轮就将选手的编号放到容器2中等待第二轮的比赛
					v2.push_back((*it).second);
				}
				else
				{//如果不是第一轮的比赛即为第二轮比赛-截取到前三名以后即为最后比赛的结果-存放到胜利的容器中
					vVivtory.push_back((*it).second);
				}

			}
			groupScore.clear();//举行完一次比赛以后要及时的将临时容器里面的数据清空等待下一次比赛的运用
			cout << endl;
		}


	}

	cout << "--------第<<" << this->m_Index << ">>轮比赛完毕-----" << endl;
	//到这里已经遍历了v_Src容器里所有参赛选手的信息-即为完成了一次比赛

	system("pause");
}



//显示比赛结果
void  SpeechManager::showScore()
{
	cout << "------第" << this->m_Index << "轮晋级选手信息如下：-------" << endl;

	vector<int>v;//funk-又一个容器啊！！！！！

	if (this->m_Index == 1)
	{
		v = v2;//如果是第一轮比赛-那么容器2中存放的是晋级选手的信息-这样就将容器2里面的信息赋值给容器v
	}
	else
	{
		v = vVivtory;//如果不是第一轮比赛即为第二轮比赛-则vVivtory容器中存放了最后前三名选手的信息-将其赋值给容器v
	}

	//通过迭代器遍历打印晋级选手的信息
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "编号：" << *it << "  姓名：" << m_Speaker[*it].m_Name << "  得分:"
			<< m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;


	system("pause");
	system("cls");

	this->show_Menu();


}




//保存记录
void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);//用输出方式打开文件---写文件（append追加的写文件)

   //将每个数据写入到文件中-这里只写决赛前三名选手的信息-
	for (vector<int>::iterator it = vVivtory.begin(); it != vVivtory.end(); it++)
	{
		ofs << *it << "," << m_Speaker[*it].m_Score[1] << ",";//ofs和cout类似，ofs是将数据显示在了文件里面，cout是将数据显示到了编译器上面
	}//这里用逗号是为了在读数据的时候方便！！！！！目前我是这样理解的

	ofs << endl;//文件里面换行

	//关闭文件
	ofs.close();

	cout << "记录已经保存" << endl;

	//有记录了，文件不为空-更改文件为不为空的状态
	this->fileIsEmpty = false;//判断文件是否为空

}



//读取记录分数
void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);//输入流对象，读取文件

	//1、文件不存在的情况
	if (!ifs.is_open())//如果打开失败
	{
		this->fileIsEmpty = true;//告诉编译器，文件是空的
		//cout << "文件不存在！" << endl;
		ifs.close();
		return;//这个直接返回是啥意思呢！！！！！！目前还不太清楚！！！
	}

	//2、文件清空的情况
	char ch;
	ifs >> ch;//自动将文件中的字符输入-加入直接是输入的是”文件尾为空“-即为空文件
	if (ifs.eof())//判断是否读到了文件尾
	{
		//cout << "文件为空！" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	//3、文件不为空
	this->fileIsEmpty = false;//文件不为空

	ifs.putback(ch);//将上面读取的单个字符放回去-？？？为什么要放回呢？？？？？
	///

	string data;//创建了一个data的对象

	//while (ifs >> data)
	//{  //这段是测试代码，下面的代码是对这段代码进行解析
	//	cout << data << endl;
	//	//10002,86.675,10009,81.3,10007,78.55,
	//}

	int index = 1;//第几届的下标

	while (ifs >> data)
	{

		//存放6个字符串信息的容器
		vector<string>v;//----------

		int pos = -1;//查到"，"位置的变量
		int start = 0;//每次进行查找的起始位置

		//一个循环进行轮换的寻找
		while (true)
		{


			pos = data.find(",", start);//从start开始查找”，”找到后返回其位置信息

			//1、没有找到的情况
			if (pos == -1)
			{
				break;//找不到break返回
			}

			//2、找到的情况
			//查找的位置-起始位置
			string tmp = data.substr(start, pos - start);
			//找到了，进行分割//参数1-起始位置，参数2-截取长度
		   //存放6个string的字符串-前三名的信息
			v.push_back(tmp);
			//cout << tmp << endl;

			start = pos + 1;//更改起始位置


		}
		// ？？？？？？这里为什么要向m_Record容器中添加数据呢？//
		//m_Record添加数据
			this->m_Record.insert(make_pair(index, v));

		index++;
		///

	}

	ifs.close();

	///
	for (map<int, vector<string>>::iterator it = m_Record.begin(); it != m_Record.end(); it++)
	{
		//cout <<"第<<"<< it->first << ">>冠军编号：" << it->second[0] << " 分数:" << it->second[1] << endl;
	}
	///

}



//显示往届得分
void SpeechManager::showRecord()
{

	if (this->fileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}

	else
	{
		for (map<int, vector<string>>::iterator it = m_Record.begin(); it != m_Record.end(); it++)
		{
			cout << "第<<" << it->first << ">>届冠军：编号：" << it->second[0] << " 得分:" << it->second[1] <<
				"     亚军：编号：" << it->second[2] << " 得分:" << it->second[3] <<
				"     季军：编号：" << it->second[4] << " 得分:" << it->second[5] << endl;
			//存了6个字符串所以是0-1-2-3-4-5

		}

		//     for (int i = 0; i < this->m_Record.size(); i++)
			  //{//这里中括号访问会出问题，不知道为什么

			  //	//以中扩号的方式访问数据
			  //	cout << "第" << i + 1 << "届";
			  //	cout << "冠军编号：" << this->m_Record[i][0] << "得分：" << this->m_Record[i][1] << " ";
			  //	cout << "亚军编号：" << this->m_Record[i][2] << "得分：" << this->m_Record[i][3] << " ";
			  //	cout << "季军编号：" << this->m_Record[i][4] << "得分：" << this->m_Record[i][5] << endl;
			  //}

	}
	system("pause");
	system("cls");
}



//清空记录
void SpeechManager::clearRecord()
{
	cout << "确认清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、返回" << endl;

	int select = 0;
	cin >> select;
	if (select == 1)
	{
		//打开模式ios::trunc 如果存在删除文件重新创建
		ofstream ofs("speech.csv", ios::trunc);//trunc:将先前的文件内容移除（Remove)-ate:打开文件之后令读写位置移至文件尾端（at end）

		ofs.close();

		//初始化属性
		this->initSpeech();

		//创建选手
		this->creatSpeaker();

		//获取往届记录
		this->loadRecord();

		cout << "清空成功！" << endl;


	}

	system("pause");
	system("cls");
}


//开始比赛-比赛控制流程
void SpeechManager::startSpeech()
{
	//第一轮比赛
	//1、抽签
	this->speechDraw();

	//2、比赛
	this->speechContest();

	//3、显示晋级结果
	this->showScore();

	//第二轮比赛
	this->m_Index++;

	//1、抽签
	this->speechDraw();

	//2、比赛
	this->speechContest();

	//3、显示最终结果
	this->showScore();

	//4、保存分数到文件中
	this->saveRecord();


	//到这里所有的比赛已经结束了！
	//重置比赛-这里之前的数据已经存入文件，需要将容器中的数据清空

	//初始化属性
	this->initSpeech();

	//创建选手
	this->creatSpeaker();//这三个函数如何封装在一个函数中

	//获取往届记录
	this->loadRecord();

	cout << "本届比赛完毕！" << endl;
	system("pause");
	system("cls");




}




//退出系统
void SpeechManager::exitSystem()
{
	cout << "欢迎下次使用！" << endl;
	system("pause");

	exit(0);
}


//析构函数
SpeechManager::~SpeechManager()//加上作用域是成员函数
{

}