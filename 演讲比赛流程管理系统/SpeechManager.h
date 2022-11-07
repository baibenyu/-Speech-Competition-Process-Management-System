#pragma once
#include <functional> 
#include<algorithm>
#include<vector>
#include<string>
#include<deque>
#include<map>
#include<numeric>
#include<iostream>
#include<fstream>
#include "Speaker.h"
using namespace std;

class SpeechManager
{
public:
	vector<int>v1;
	vector<int>v2;
	vector<int>vt;
	map<int, Speaker>s;
	int index;
	bool fileIsEmpty;
	map<int, vector<string>>record;


	SpeechManager();

	void showMenu();

	void initSpeech();

	void createSpeaker();

	void SpeechDraw();

	void SpeechContest();

	void showScore();

	void saveRecord();

	void loadRecord();

	void showRecord();

	void clearRecord();

	void startSpeech();

	void exitSystem();

	~SpeechManager();
};