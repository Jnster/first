#include "stdafx.h"
#include "MyTime.h"


MyTime::MyTime()
{
	hour = 0;
	minute = 0;
}

MyTime::MyTime(int h, int m)
{
	hour = h;
	minute = m;
}

MyTime::MyTime(MyTime& t)
{
	hour = t.hour;
	minute = t.minute;
}

MyTime::~MyTime()
{
}

void MyTime::write(fstream& os)
{
	os.write(reinterpret_cast<const char*>(&hour), sizeof(int));
	os.write(reinterpret_cast<const char*>(&minute), sizeof(int));
}

void MyTime::read(fstream& is)
{
	is.read(reinterpret_cast<char*>(&hour), sizeof(int));
	is.read(reinterpret_cast<char*>(&minute), sizeof(int));
}

istream& operator>> (istream& is, MyTime& t)
{
	char ch;
	is >> t.hour >> ch >> t.minute;
	return is;
}

ostream& operator<< (ostream& os, MyTime& t)
{
	if (t.hour < 10) os << '0';
	os << t.hour << ':';
	if (t.minute < 10) os << '0';
	os << t.minute;
	return os;
}

MyTime& MyTime::operator = (MyTime& t)
{
	hour = t.hour;
	minute = t.minute;
	return *this;
}