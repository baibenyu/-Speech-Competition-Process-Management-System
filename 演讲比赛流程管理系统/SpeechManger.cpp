#include "SpeechManager.h"

SpeechManager::SpeechManager()
{
	this->initSpeech();
	this->createSpeaker();
	this->loadRecord();
};

void SpeechManager::showMenu()
{
	cout << "欢迎使用演讲比赛管理系统!" << endl;
	cout << "1.开始比赛" << endl;
	cout << "2.查看记录" << endl;
	cout << "3.清空记录" << endl;
	cout << "0.退出程序" << endl;
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
		string name = "选手";
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
	cout << "第" << this->index << "轮比赛选手正在抽签" << endl;
	cout << "抽签后演讲顺序如下" << endl;
	if (this->index == 1)
	{
		random_shuffle(v1.begin(), v1.end()); // 随机打乱
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
	cout << "第" << this->index << "轮比赛正式开始" << endl;
	multimap<double, int, greater<double>>groupScore; // 保存key分数,value选手编号
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
		d.pop_front(); // 去掉最高和最低
		d.pop_back();

		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double avg = sum / (double)d.size();

		this->s[*it].score[this->index - 1] = avg;

		groupScore.insert(make_pair(avg, *it));
		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "小组比赛名次" << endl;
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

	cout << "第" << this->index <<"轮比赛完毕" << endl;
}

void SpeechManager::showScore()
{
	cout << "第" << this->index << "轮晋级选手信息如下" << endl;
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
	ofs.open("speech.csv", ios::out | ios::app);// 用输出的方式打开文件 -- 写文件

	for (vector<int>::iterator it = vt.begin(); it != vt.end(); it++)
	{
		ofs << *it << "," << this->s[*it].score[1] << ",";
	}
	ofs << endl;

	ofs.close();
	this->fileIsEmpty = false;
	cout << "保存成功" << endl;
}

void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv",ios::in);

	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件为空" << endl;
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
		cout << "文件为空或不存在!" << endl;
	}
	else
	{
		for (int i = 0; i < this->record.size(); i++)
		{
			cout << "第" << i + 1 << "届" <<
				"冠军: " << this->record[i][0] << " 得分: " << this->record[i][1] << " "
				"亚军: " << this->record[i][2] << " 得分: " << this->record[i][3] << " "
				"季军: " << this->record[i][4] << " 得分: " << this->record[i][5] << " " << endl;
		}
	}
	
}

void SpeechManager::clearRecord()
{
	cout << "确认是否清空?" << endl;
	cout << "0.否 1.是" << endl;
	bool select = 0;
	cin >> select;

	if (select == 1)
	{
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();
		this->initSpeech();
		this->createSpeaker();
		this->loadRecord();
		cout << "清空成功" << endl;
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

	// 更新文件状态
	this->initSpeech();
	this->createSpeaker();
	this->loadRecord();
}

void SpeechManager::exitSystem()
{
	cout << "感谢使用,再见!" << endl;
	exit(0);
}

SpeechManager::~SpeechManager()
{

};
