#include"manager.h"



//���캯��
SpeechManager::SpeechManager()
{
	//��ʼ�����������Եĺ���
	this->initSpeech();

	//����ѡ��
	this->creatSpeaker();

	//��ȡ�����¼
	this->loadRecord();        //�������ǳ���ͷ���ļ������ڵ������ԭ��

}

//�˵�����
void SpeechManager::show_Menu()
{
	cout << "------------------------------------" << endl;
	cout << "----------��ӭ�μ��ݽ�����----------" << endl;
	cout << "----------1����ʼ�ݽ�����-----------" << endl;
	cout << "----------2���鿴�����¼-----------" << endl;
	cout << "----------3����ձ�����¼-----------" << endl;
	cout << "----------0���˳���������-----------" << endl;
	cout << "------------------------------------" << endl;
	cout << endl;
}



//��ʼ������
void SpeechManager::initSpeech()
{
	//��֤�������ÿ�
	this->v1.clear();
	this->v2.clear();
	this->vVivtory.clear();
	this->m_Speaker.clear();

	//��ʼ�������ִ�
	this->m_Index = 1;

	//��ʼ����¼����
	this->m_Record.clear();
}


//��ʼ������12��ѡ��
void SpeechManager::creatSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";//������������
	for (int i = 0; i < nameSeed.size(); i++)
	{

		string name = "ѡ��";//ͨ��ѭ����ÿ��ѡ�ֽ��б��
		name += nameSeed[i];

		Speaker sp;//ͨ��ѡ���ഴ��ѡ�ֶ���
		sp.m_Name = name;//Ȼ���ÿ������������ѡ�ֽ�������

		///
		for (int i = 0; i < 2; i++)
		{
			sp.m_Score[i] = 0;//�����Դ�����ַ�����m_Score������ֵ0
		}
		///
		//12��ѡ�ֱ��,�ŵ�v1������
		this->v1.push_back(i + 10001);

		//ѡ�ֱ���Լ���Ӧ��ѡ�ִ�ŵ�map������
		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}

}


//��ʼ��ǩ
void SpeechManager::speechDraw()
{
	cout << "��" << this->m_Index << "�ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "----------------------------------------" << endl;
	cout << "��ǩ����ݽ�˳�����£�" << endl;


	//�����ǵڼ��ֱ���ͨ��һ���ж����
	if (this->m_Index == 1)
	{
		//��һ�ֱ�����ǩ
		random_shuffle(v1.begin(), v1.end());//STL �еĺ��� random_shuffle() ������һ��Ԫ�����н���������������ģ�-ͷ�ļ���#include <algorithm>
		//�����������ҡ����һ������������ݴ���

		//����ͨ��vector������������ǩ��ĳ�����Ų���ӡ
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		//�ڶ��ֱ�����ǩ
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



//��ǩ����ʽ����
void SpeechManager::speechContest()
{
	cout << "------��" << this->m_Index << "����ʽ������ʼ��-------" << endl;

	multimap<double, int, greater<double>>groupScore;//��ʱ����������key-���� value-ѡ�ֱ��//multimap������������ظ���ֵ-greater<double>Ϊ��������


	int num = 0;//��¼��Ա����6��Ϊ1��

	vector<int>v_Src;//��������Ա����-�����洢������ѡ�ֵ�����


	if (this->m_Index == 1)
	{
		v_Src = v1;//����ǵ�һ�ֱ����ͽ�����1��������ݸ�����ר�õ�����
	}
	else
	{
		v_Src = v2;
	}


	//����v_Src���������в���ѡ��
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;//��¼ѡ�ָ���

		//��ί���
		deque<double>d; //��ί��ֵ�����-deque˫�򿪿ڿɽ��ɳ������� -��ͷ���Ĳ���ɾ���ٶȿ�


		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 41 + 60) / 1.f;//60~100//�������Դ�����С��

			//cout << score << " ";//����ĵ÷�-���Դ���

			d.push_back(score);//Ȼ��ͨ��β�巨����ί�Ĵ�ִ洢��deque��������
		}


		sort(d.begin(), d.end(), greater<double>());//��������
		d.pop_front();//ȥ����߷�
		d.pop_back();//ȥ����ͷ�

		double sum = accumulate(d.begin(), d.end(), 0.0f);//��ȡ�ܷ�//��������������ʼ�ۼ�ֵ-ͷ�ļ���#include<numeric>
		double avg = sum / (double)d.size();//��ȡƽ����-�����õ���һ��ǿ��ת��

		//��ӡƽ����-���Դ���
		//cout << "��ţ�" << *it << "  ������" << this->m_Speaker[*it].m_Name << "  ��ȡƽ����:" << avg << endl;


		//���õ���ƽ���ַŵ����ڲ���ѡ�ֵ�������-��Ӧ���ѡ�ֵ÷ֵļ�¼
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;//double m_Score[2];//����������¼���ֵĵ÷�


		//���μӱ�����ѡ�ֵĵ÷ֺͱ�ŷŵ���ʱ��groupScore������
		groupScore.insert(make_pair(avg, *it));//key�ǵ÷֣�value�Ǿ���ѡ�ֵı��



		//ÿ6��ȡ��ǰ����-ÿ��6���Ʊ���
		if (num % 6 == 0)
		{
			cout << "��" << num / 6 << "С��������Σ� " << endl;

			//ͨ��������������ʱmultimap����groupScore�е�ѡ����Ϣ-����ӡ��Ϣ
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				//
				cout << "��ţ�" << it->second << "  ������" << this->m_Speaker[it->second].m_Name << "  �ɼ�:"
					<< this->m_Speaker[it->second].m_Score[this->m_Index - 1] << endl;
			}
			//

						//ȡ��ǰ����-����ʱ���ѡ����Ϣ�������У�������������Ϣ�ǲ��ý������еģ���ȡǰ������λ�ϴ��϶�����
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; count++, it++)
			{
				if (this->m_Index == 1)
				{	//����ǵ�һ�־ͽ�ѡ�ֵı�ŷŵ�����2�еȴ��ڶ��ֵı���
					v2.push_back((*it).second);
				}
				else
				{//������ǵ�һ�ֵı�����Ϊ�ڶ��ֱ���-��ȡ��ǰ�����Ժ�Ϊ�������Ľ��-��ŵ�ʤ����������
					vVivtory.push_back((*it).second);
				}

			}
			groupScore.clear();//������һ�α����Ժ�Ҫ��ʱ�Ľ���ʱ���������������յȴ���һ�α���������
			cout << endl;
		}


	}

	cout << "--------��<<" << this->m_Index << ">>�ֱ������-----" << endl;
	//�������Ѿ�������v_Src���������в���ѡ�ֵ���Ϣ-��Ϊ�����һ�α���

	system("pause");
}



//��ʾ�������
void  SpeechManager::showScore()
{
	cout << "------��" << this->m_Index << "�ֽ���ѡ����Ϣ���£�-------" << endl;

	vector<int>v;//funk-��һ������������������

	if (this->m_Index == 1)
	{
		v = v2;//����ǵ�һ�ֱ���-��ô����2�д�ŵ��ǽ���ѡ�ֵ���Ϣ-�����ͽ�����2�������Ϣ��ֵ������v
	}
	else
	{
		v = vVivtory;//������ǵ�һ�ֱ�����Ϊ�ڶ��ֱ���-��vVivtory�����д�������ǰ����ѡ�ֵ���Ϣ-���丳ֵ������v
	}

	//ͨ��������������ӡ����ѡ�ֵ���Ϣ
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "��ţ�" << *it << "  ������" << m_Speaker[*it].m_Name << "  �÷�:"
			<< m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;


	system("pause");
	system("cls");

	this->show_Menu();


}




//�����¼
void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);//�������ʽ���ļ�---д�ļ���append׷�ӵ�д�ļ�)

   //��ÿ������д�뵽�ļ���-����ֻд����ǰ����ѡ�ֵ���Ϣ-
	for (vector<int>::iterator it = vVivtory.begin(); it != vVivtory.end(); it++)
	{
		ofs << *it << "," << m_Speaker[*it].m_Score[1] << ",";//ofs��cout���ƣ�ofs�ǽ�������ʾ�����ļ����棬cout�ǽ�������ʾ���˱���������
	}//�����ö�����Ϊ���ڶ����ݵ�ʱ�򷽱㣡��������Ŀǰ������������

	ofs << endl;//�ļ����滻��

	//�ر��ļ�
	ofs.close();

	cout << "��¼�Ѿ�����" << endl;

	//�м�¼�ˣ��ļ���Ϊ��-�����ļ�Ϊ��Ϊ�յ�״̬
	this->fileIsEmpty = false;//�ж��ļ��Ƿ�Ϊ��

}



//��ȡ��¼����
void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);//���������󣬶�ȡ�ļ�

	//1���ļ������ڵ����
	if (!ifs.is_open())//�����ʧ��
	{
		this->fileIsEmpty = true;//���߱��������ļ��ǿյ�
		//cout << "�ļ������ڣ�" << endl;
		ifs.close();
		return;//���ֱ�ӷ�����ɶ��˼�أ�����������Ŀǰ����̫���������
	}

	//2���ļ���յ����
	char ch;
	ifs >> ch;//�Զ����ļ��е��ַ�����-����ֱ����������ǡ��ļ�βΪ�ա�-��Ϊ���ļ�
	if (ifs.eof())//�ж��Ƿ�������ļ�β
	{
		//cout << "�ļ�Ϊ�գ�" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	//3���ļ���Ϊ��
	this->fileIsEmpty = false;//�ļ���Ϊ��

	ifs.putback(ch);//�������ȡ�ĵ����ַ��Ż�ȥ-������ΪʲôҪ�Ż��أ���������
	///

	string data;//������һ��data�Ķ���

	//while (ifs >> data)
	//{  //����ǲ��Դ��룬����Ĵ����Ƕ���δ�����н���
	//	cout << data << endl;
	//	//10002,86.675,10009,81.3,10007,78.55,
	//}

	int index = 1;//�ڼ�����±�

	while (ifs >> data)
	{

		//���6���ַ�����Ϣ������
		vector<string>v;//----------

		int pos = -1;//�鵽"��"λ�õı���
		int start = 0;//ÿ�ν��в��ҵ���ʼλ��

		//һ��ѭ�������ֻ���Ѱ��
		while (true)
		{


			pos = data.find(",", start);//��start��ʼ���ҡ������ҵ��󷵻���λ����Ϣ

			//1��û���ҵ������
			if (pos == -1)
			{
				break;//�Ҳ���break����
			}

			//2���ҵ������
			//���ҵ�λ��-��ʼλ��
			string tmp = data.substr(start, pos - start);
			//�ҵ��ˣ����зָ�//����1-��ʼλ�ã�����2-��ȡ����
		   //���6��string���ַ���-ǰ��������Ϣ
			v.push_back(tmp);
			//cout << tmp << endl;

			start = pos + 1;//������ʼλ��


		}
		// ����������������ΪʲôҪ��m_Record��������������أ�//
		//m_Record�������
			this->m_Record.insert(make_pair(index, v));

		index++;
		///

	}

	ifs.close();

	///
	for (map<int, vector<string>>::iterator it = m_Record.begin(); it != m_Record.end(); it++)
	{
		//cout <<"��<<"<< it->first << ">>�ھ���ţ�" << it->second[0] << " ����:" << it->second[1] << endl;
	}
	///

}



//��ʾ����÷�
void SpeechManager::showRecord()
{

	if (this->fileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}

	else
	{
		for (map<int, vector<string>>::iterator it = m_Record.begin(); it != m_Record.end(); it++)
		{
			cout << "��<<" << it->first << ">>��ھ�����ţ�" << it->second[0] << " �÷�:" << it->second[1] <<
				"     �Ǿ�����ţ�" << it->second[2] << " �÷�:" << it->second[3] <<
				"     ��������ţ�" << it->second[4] << " �÷�:" << it->second[5] << endl;
			//����6���ַ���������0-1-2-3-4-5

		}

		//     for (int i = 0; i < this->m_Record.size(); i++)
			  //{//���������ŷ��ʻ�����⣬��֪��Ϊʲô

			  //	//�������ŵķ�ʽ��������
			  //	cout << "��" << i + 1 << "��";
			  //	cout << "�ھ���ţ�" << this->m_Record[i][0] << "�÷֣�" << this->m_Record[i][1] << " ";
			  //	cout << "�Ǿ���ţ�" << this->m_Record[i][2] << "�÷֣�" << this->m_Record[i][3] << " ";
			  //	cout << "������ţ�" << this->m_Record[i][4] << "�÷֣�" << this->m_Record[i][5] << endl;
			  //}

	}
	system("pause");
	system("cls");
}



//��ռ�¼
void SpeechManager::clearRecord()
{
	cout << "ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;

	int select = 0;
	cin >> select;
	if (select == 1)
	{
		//��ģʽios::trunc �������ɾ���ļ����´���
		ofstream ofs("speech.csv", ios::trunc);//trunc:����ǰ���ļ������Ƴ���Remove)-ate:���ļ�֮�����дλ�������ļ�β�ˣ�at end��

		ofs.close();

		//��ʼ������
		this->initSpeech();

		//����ѡ��
		this->creatSpeaker();

		//��ȡ�����¼
		this->loadRecord();

		cout << "��ճɹ���" << endl;


	}

	system("pause");
	system("cls");
}


//��ʼ����-������������
void SpeechManager::startSpeech()
{
	//��һ�ֱ���
	//1����ǩ
	this->speechDraw();

	//2������
	this->speechContest();

	//3����ʾ�������
	this->showScore();

	//�ڶ��ֱ���
	this->m_Index++;

	//1����ǩ
	this->speechDraw();

	//2������
	this->speechContest();

	//3����ʾ���ս��
	this->showScore();

	//4������������ļ���
	this->saveRecord();


	//���������еı����Ѿ������ˣ�
	//���ñ���-����֮ǰ�������Ѿ������ļ�����Ҫ�������е��������

	//��ʼ������
	this->initSpeech();

	//����ѡ��
	this->creatSpeaker();//������������η�װ��һ��������

	//��ȡ�����¼
	this->loadRecord();

	cout << "���������ϣ�" << endl;
	system("pause");
	system("cls");




}




//�˳�ϵͳ
void SpeechManager::exitSystem()
{
	cout << "��ӭ�´�ʹ�ã�" << endl;
	system("pause");

	exit(0);
}


//��������
SpeechManager::~SpeechManager()//�����������ǳ�Ա����
{

}