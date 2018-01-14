#include "stdafx.h"
//#include "headers.h"


MyString::MyString(char *v)
{
	length = strlen(v);
	str = new char[length+1];
	strcpy(str, v);
	//str[length] = '\0';
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

void MyString::write(ofstream& os)
{
	os.write(reinterpret_cast<const char*>(&length), sizeof(length));
	os.write(str, strlen(str) + 1);
	os.write(reinterpret_cast<const char*>(&mytime), sizeof(mytime));
	os.write(reinterpret_cast<const char*>("\n"), sizeof(char));
	
	//os.write(reinterpret_cast<const char*>(this), sizeof(MyString));
}

void MyString::read(istream& is)
{
	is.read(reinterpret_cast<char*>(&length), sizeof(length));

	char ch;
	int i = 0;
	streampos s = is.tellg();

	while ((ch = is.get()) != '\0') { i++; }
	is.seekg(s);
	if (str != nullptr) { delete[] str; }
	str = new char[i + 1];
	is.read(str, i + 1);

	is.read(reinterpret_cast<char*>(&mytime), sizeof(mytime));
	/*is.read((char*)this, sizeof(MyString));*/
}

size_t _sizeof(MyString& p)
{
	return sizeof(p.str) + sizeof(p.length) + sizeof(p.mytime);
}