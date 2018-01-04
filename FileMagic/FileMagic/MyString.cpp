#include "stdafx.h"
#include <string.h>
//#include "headers.h"


MyString::MyString(char *v)
{
	length = strlen(v);
	str = new char[length+1];
	strcpy(str, v);
	_strtime(mytime);
}

MyString::MyString()
{
	length = 0;
	
	mytime[0] = '\0';

	str = nullptr;
}

MyString::MyString(MyString &second_object)
{
	length = second_object.length;
	strcpy(mytime, second_object.mytime);
	//if (str != nullptr) delete[]str;
	str = new char[length+1];
	strcpy(str, second_object.str);
	//str[length] = '\0';
}

MyString::~MyString()
{
	if (str != nullptr) {
		delete[] str;
	}
	//cout <<endl<< "the destructor worked" << endl;
}

void MyString::Print()
{
	cout << "Строка: " << str << endl << "Длина: " << length << endl << "Время: " << mytime << endl;
}

ofstream& operator<<(ofstream& os, MyString &p)
{
	os << p.length; os.write(p.str, sizeof(char)*p.length+1);//<< ' ' << p.mytime;
	return os;
}

ifstream& operator>>(ifstream& is, MyString &p)
{
	is >> p.length >> p.str >> p.mytime;
	return is;
}

ostream& operator<< (ostream& os, MyString &p) {
	os << " Длина: " << p.length << ", Строка: " << p.str << ", Время: " << p.mytime;
	return os;
}

istream& operator>> (istream& is, MyString &p) {
	is >> p.length >> p.str >> p.mytime;
	return is;
}

void MyString::operator= (MyString res)
{
	length = res.length;
	if (str != nullptr)
	{
		delete [] str;
	}
	str = new char[length];
	strcpy(str, res.str);
	strcpy(mytime, res.mytime);
}
void MyString::write(ofstream& os)
{
	os.write(reinterpret_cast<const char*>(&length), sizeof(int));
	os.write(reinterpret_cast<const char*>(str), sizeof(char)*(length+1));
	os.write(reinterpret_cast<const char*>(&mytime), sizeof(char)*9);
	//os.write(reinterpret_cast<const char*>("\n"), sizeof(char));
}

void MyString::read(istream& is)
{
	is.read(reinterpret_cast<char*>(&length), sizeof(int));
	int i = 0;
	if (str != nullptr) { delete[] str; }
	str = new char[length+1];
	is.read(reinterpret_cast<char*>(str), sizeof(char)* (length+1));
	is.read(reinterpret_cast<char*>(&mytime), sizeof(char)*9);
}

size_t _sizeof(MyString& p)
{
	return sizeof(p.str) + sizeof(p.length) + sizeof(p.mytime);
}