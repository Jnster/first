#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <fstream>

using namespace std;

class MyString
{
public:
	char *str;
	int length;
	char mytime[9];

	MyString();//конструктор по умолчанию
	MyString(const MyString &second_object);//конструктор копирования
	MyString(char* v);//конструктор с параметрами
	~MyString();

	void Print();
	friend ofstream& operator<< (ofstream&, MyString&);
	friend ifstream& operator>> (ifstream&, MyString&);
	friend ostream& operator << (ostream&, MyString&);
	friend istream& operator >> (istream&, MyString&);
	void write(ofstream&);
	void read(istream&);
	friend size_t _sizeof(MyString&);
};