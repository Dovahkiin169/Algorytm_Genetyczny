#include "Timer.h"

Timer::Timer(void)
{

}

void Timer::startTimer()//poczatek timera
{
	QueryPerformanceFrequency(&clockFrequency);
	QueryPerformanceCounter(&start);
}

double Timer::endTimer()//koniec timera
{
	QueryPerformanceCounter(&finish);
	delta.QuadPart = finish.QuadPart - start.QuadPart;
	return ((double)delta.QuadPart) / clockFrequency.QuadPart;
}

void Timer::ZapiszDoPlikuEndTimer(double Czas, string Text)//koniec timera i zapisywanie wynikow do pliku
{
	Czas = 0;
	Czas = endTimer();
	CzasPlik("CzasPlik.txt", Text, Czas);
	cout << "Czas wykonywania programu  " << Czas << " s" << endl;
}

void Timer::CzasPlik(string filename, string Text, double Czas)
{

	ofstream file;
	file.open(filename, ios::out | ios::app);
	if (file.is_open())
	{
		file << Text << Czas << "\n\n";
	}
	else
	{
		cout << "Blad podczas otwierania pliku!" << endl;
	}
}

Timer::~Timer(void)
{

}