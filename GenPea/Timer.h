#include <string>
#include <fstream>
#include <iostream>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include "windows.h"
#include <stdio.h>
#include <tchar.h>
using namespace std;

class Timer
{
	LARGE_INTEGER start, finish, clockFrequency, delta;
public:
	Timer(void);
	void startTimer();
	double endTimer();
	void ZapiszDoPlikuEndTimer(double Czas, string Text);
	void CzasPlik(string filename, string Text, double Czas);
	~Timer(void);
};


