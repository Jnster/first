#include "stdafx.h"
//#include "headers.h"

MyString::MyString(char *v)
{
	length = strlen(v);
	str = new char[length+1];
	for (int i = 0; i < length; i++)
		str[i] = v[i];
	str[length] = '\0';
	_strtime(mytime);
}

MyString::MyString()
{
	length = 0;
	
	mytime[0] = '\0';

	str = new char[1];
	str[0]= '\0';
}

MyString::MyString(const MyString &second_object)
{
	length = second_object.length;
	strcpy(mytime, second_object.mytime);
	str = new char[length + 1];
	strcpy(str, second_object.str);
	//str[length] = '\0';
}

MyString::~MyString()
{
	if (str != nullptr) {
		delete[] str;
	}
	cout <<endl<< "the destructor worked" << endl;
}

void MyString::Print()
{
	cout << "Строка: " << str << endl << "Длина: " << length << endl << "Время: " << mytime << endl;
}

ostream& operator<< (ostream& os, MyString &p) {
	os << " Длина: " << p.length << ", Строка: " << p.str << ", Время: " << p.mytime;
	return os;
}

istream& operator>> (istream& is, MyString &p) {
	is >> p.length >> p.str >> p.mytime;
	return is;
}

ofstream& operator<<(ofstream& os, MyString &p)
{
	os << p.length << " " << p.str << " " << p.mytime;
	return os;
}
ifstream& operator>>(ifstream& is, MyString &p)
{
	is >> p.length >> p.str >> p.mytime;
	return is;
}

ofstream& operator<<(ofstream& os, MyString p)
{
	os << p.length << " " << p.str << " " << p.mytime;
	return os;
}

ifstream& operator>>(ifstream& is, MyString p)
{
	is >> p.length >> p.str >> p.mytime;
	return is;
}