#pragma once
#include<iostream>
using namespace std;

class Speaker
{
public:
	string m_Name;//姓名
	double m_Score[2];//分数，最多记录两轮的得分
};

//一般成员属性是设置为私有属性
//需要提供get/set的方法进行修改