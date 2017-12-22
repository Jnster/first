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

	MyString();//����������� �� ���������
	MyString(const MyString &second_object);//����������� �����������
	MyString(char* v);//����������� � �����������
	~MyString();

	void Print();
	
	friend ostream& operator<< (ostream& os, MyString &p);
	friend istream& operator>> (istream& is, MyString &p);
	friend ofstream& operator<< (ofstream& os, MyString &p);
	friend ifstream& operator>> (ifstream& is, MyString &p);
	friend ofstream& operator<< (ofstream& os, MyString p);
	friend ifstream& operator>> (ifstream& os, MyString p);
};