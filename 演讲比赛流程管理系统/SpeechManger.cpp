#include "SpeechManager.h"

SpeechManager::SpeechManager()
{
	this->initSpeech();
	this->createSpeaker();
	this->loadRecord();
};

void SpeechManager::showMenu()
{
	cout << "��ӭʹ���ݽ���������ϵͳ!" << endl;
	cout << "1.��ʼ����" << endl;
	cout << "2.�鿴��¼" << endl;
	cout << "3.��ռ�¼" << endl;
	cout << "0.�˳�����" << endl;
}

void SpeechManager::initSpeech()
{
	this->v1.clear();
	this->v2.clear();
	this->vt.clear();
	this->s.clear();
	this->record.clear();

	this->index = 1;
}

void SpeechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "ѡ��";
		name += nameSeed[i];
		Speaker sk;
		sk.name = name;
		for (int j = 0; j < 2; j++)
		{
			sk.score[j] = 0;
		}

		this->v1.push_back(i + 10001);
		this->s.insert(make_pair(i + 10001, sk));
	}
}

void SpeechManager::SpeechDraw()
{
	cout << "��" << this->index << "�ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "��ǩ���ݽ�˳������" << endl;
	if (this->index == 1)
	{
		random_shuffle(v1.begin(), v1.end()); // �������
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
}

void SpeechManager::SpeechContest()
{
	cout << "��" << this->index << "�ֱ�����ʽ��ʼ" << endl;
	multimap<double, int, greater<double>>groupScore; // ����key����,valueѡ�ֱ��
	int num = 0;

	vector<int>Src;
	if (this->index == 1)
	{
		Src = this->v1;
	}
	else
	{
		Src = this->v2;
	}

	for (vector<int>::iterator it = Src.begin(); it != Src.end(); it++)
	{
		num += 1;

		deque<double>d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;
			d.push_back(score);
		}

		sort(d.begin(), d.end(), greater<double>());
		d.pop_front(); // ȥ����ߺ����
		d.pop_back();

		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double avg = sum / (double)d.size();

		this->s[*it].score[this->index - 1] = avg;

		groupScore.insert(make_pair(avg, *it));
		if (num % 6 == 0)
		{
			cout << "��" << num / 6 << "С���������" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << it->second << " " << this->s[it->second].name << " " << this->s[it->second].score[this->index - 1] << endl;
			}

			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end() and count < 3; it++, count++)
			{
				if (this->index == 1)
				{
					v2.push_back(it->second);
				}
				else
				{
					vt.push_back(it->second);
				}
			}
			groupScore.clear();
			cout << endl;
		}
	}

	cout << "��" << this->index <<"�ֱ������" << endl;
}

void SpeechManager::showScore()
{
	cout << "��" << this->index << "�ֽ���ѡ����Ϣ����" << endl;
	vector<int>v;
	if (this->index == 1)
	{
		v = this->v2;
	}
	else
	{
		v = this->vt;
	}

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << " " << this->s[*it].name << " " << this->s[*it].score[this->index - 1] << endl;
	}
	cout << endl;

}

void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);// ������ķ�ʽ���ļ� -- д�ļ�

	for (vector<int>::iterator it = vt.begin(); it != vt.end(); it++)
	{
		ofs << *it << "," << this->s[*it].score[1] << ",";
	}
	ofs << endl;

	ofs.close();
	this->fileIsEmpty = false;
	cout << "����ɹ�" << endl;
}

void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv",ios::in);

	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "�ļ�Ϊ��" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	this->fileIsEmpty = false;

	ifs.putback(ch);

	string data;
	int index = 0;
	while (ifs >> data)
	{
		vector<string>v;
		int pos = -1;
		int start = 0;
		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				break;
			}
			string tmp = data.substr(start, pos - start);
			v.push_back(tmp);
			start = pos + 1;
		}
		this->record.insert(make_pair(index, v));
		index += 1;
	}

	ifs.close();
	
}

void SpeechManager::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "�ļ�Ϊ�ջ򲻴���!" << endl;
	}
	else
	{
		for (int i = 0; i < this->record.size(); i++)
		{
			cout << "��" << i + 1 << "��" <<
				"�ھ�: " << this->record[i][0] << " �÷�: " << this->record[i][1] << " "
				"�Ǿ�: " << this->record[i][2] << " �÷�: " << this->record[i][3] << " "
				"����: " << this->record[i][4] << " �÷�: " << this->record[i][5] << " " << endl;
		}
	}
	
}

void SpeechManager::clearRecord()
{
	cout << "ȷ���Ƿ����?" << endl;
	cout << "0.�� 1.��" << endl;
	bool select = 0;
	cin >> select;

	if (select == 1)
	{
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();
		this->initSpeech();
		this->createSpeaker();
		this->loadRecord();
		cout << "��ճɹ�" << endl;
	}
}

void SpeechManager::startSpeech()
{
	this->SpeechDraw();
	this->SpeechContest();
	this->showScore();

	this->index += 1;

	this->SpeechDraw();
	this->SpeechContest();
	this->showScore();

	this->saveRecord();

	// �����ļ�״̬
	this->initSpeech();
	this->createSpeaker();
	this->loadRecord();
}

void SpeechManager::exitSystem()
{
	cout << "��лʹ��,�ټ�!" << endl;
	exit(0);
}

SpeechManager::~SpeechManager()
{

};
