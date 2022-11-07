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
		cout << "����������ִ�еĲ������(0-3)" << endl;
		cin >> choice;
		//for (map<int, Speaker>::iterator it = sm.s.begin(); it != sm.s.end(); it++)
		//{
		//	cout << it->first << " " << it->second.name << " " << it->second.score << endl;
		//}

		switch (choice)
		{
		case 0: // �˳�����
			sm.exitSystem();
			break;
		case 1: // ��ʼ����'
			sm.startSpeech();
			break;
		case 2: // �鿴��¼
			sm.showRecord();
			break;
		case 3: // ��ռ�¼
			sm.clearRecord();
			break;
		default:
			system("cls");
			break;
		}
	}
	
	return 0;
}