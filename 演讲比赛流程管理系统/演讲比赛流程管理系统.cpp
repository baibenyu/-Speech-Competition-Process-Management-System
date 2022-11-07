#include<ctime>
#include"SpeechManager.h"


int main()
{
	srand((unsigned int)time(NULL));
	SpeechManager sm;
	int choice = 0;
	
	while (true)
	{
		sm.showMenu();
		cout << "请输入您想执行的操作编号(0-3)" << endl;
		cin >> choice;
		//for (map<int, Speaker>::iterator it = sm.s.begin(); it != sm.s.end(); it++)
		//{
		//	cout << it->first << " " << it->second.name << " " << it->second.score << endl;
		//}

		switch (choice)
		{
		case 0: // 退出程序
			sm.exitSystem();
			break;
		case 1: // 开始比赛'
			sm.startSpeech();
			break;
		case 2: // 查看记录
			sm.showRecord();
			break;
		case 3: // 清空记录
			sm.clearRecord();
			break;
		default:
			system("cls");
			break;
		}
	}
	
	return 0;
}