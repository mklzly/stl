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

//����ݽ������Ĺ�����
//��������
/*1���ṩ�˵��������û�����
* 2�����ݽ��������̽��п���
* 3�����ļ��Ķ�д����
*/
//���������а���������Ҫִ�еĲ����ĳ�Ա����-��Ҫ���ĳ�Ա����
class SpeechManager
{
public:
	//���캯��
	SpeechManager();

	//չʾ�˵�
	void show_Menu();

	//��ʼ������
	void initSpeech();

	//�˳�ϵͳ
	void exitSystem();

	//��ʼ������12��ѡ��
	void creatSpeaker();

	//��ʼ����-������������
	void startSpeech();//�����������������������������

	//��ʼ��ǩ
	void speechDraw();

	//��ʽ����
	void speechContest();

	//��ʾ�������
	void showScore();

	//�����¼
	void saveRecord();

	//��ȡ��¼����
	void loadRecord();

	//�ж��ļ�Ϊ�յı�־
	bool fileIsEmpty;

	//��ʾ����÷�
	void showRecord();

	//��ռ�¼
	void clearRecord();


	//��������
	~SpeechManager();

	//��ͷ�ļ�����ֻд������������дʵ��
	//���캯������������������Լ���д��������Ҳ�������д��

 //��Ա����
 //�����һ�ֱ���ѡ�ֱ������
	vector<int>v1;

	//��һ�ֽ����μӵڶ��ֱ���ѡ�ֱ�ŵ�����
	vector<int>v2;

	//ʤ��ǰ����ѡ�ֱ������
	vector<int>vVivtory;

	//��ű���Լ���Ӧ����ѡ������
	map<int, Speaker>m_Speaker;//�������������-�����ţ�ѡ������-����������

	//�����¼
	map<int, vector<string>>m_Record;//key����ڼ��죬value��¼������Ϣ

	//��¼�����ִ�
	int m_Index;
};