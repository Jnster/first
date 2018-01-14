#pragma once
#include <fstream>
using namespace std;

class MyTime
{
public:
	int hour, minute;
	MyTime();
	MyTime(int hour, int minute);
	MyTime(MyTime& MyTime);
	~MyTime();
	void write(fstream& stream);
	void read(fstream& stream);
	friend ostream& operator<< (ostream& os, MyTime& MyTime);
	MyTime& operator = (MyTime& MyTime);
};