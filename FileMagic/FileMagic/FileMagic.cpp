// FileMagic.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <locale>
//#include"headers.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");
	ifstream fileIn;
	char obj[] = "Kate is drinking with cat.";
	char input[28];
	MyString oba("Messi");
	fileIn.open("test.bin", ios::out, ios::binary);
	fileIn << oba;
	fileIn.close();
	ofstream fileOut;
	fileOut.open("test.bin", ios::in, ios::binary);
	//file.getline(input, sizeof(char) * 28);//считывание массива char
	//file.read(oba, sizeof(MyString)); //считывание чисел или до первого разделителя (пробел, табуляция, переход на новую строку)
	fileOut >> oba;
	fileOut.close();
	cout << oba;
	system("pause");
	return 0;
}

