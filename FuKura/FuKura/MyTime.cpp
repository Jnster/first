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

void MyTime::write(ofstream& os)
{
	os.write(reinterpret_cast<const char*>(&hour), sizeof(int));
	os.write(reinterpret_cast<const char*>(&minute), sizeof(int));
}

void MyTime::read(ifstream& is)
{
	is.read(reinterpret_cast<char*>(&hour), sizeof(int));
	is.read(reinterpret_cast<char*>(&minute), sizeof(int));
}

ostream& operator<< (ostream& os, MyTime& t)
{
	os << t.hour << ':' << t.minute;
	return os;
}

istream& operator>> (istream& is, MyTime& t)
{
	is >> t.hour >> t.minute;
	return is;
}

MyTime& MyTime::operator = (const MyTime& t)
{
	hour = t.hour;
	minute = t.minute;
	return *this;
}