// FileMagic.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <locale>

using namespace std;

int main(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");
	
	//FileManipulator<MyString> opa("out.bin");
	FileManipulator<TrainTable> opa("out.bin");
	int* station = new int[3];
	int i;
	station[0] = 87;
	station[1] = 54;
	station[2] = 7;
	char* d = new char[12];
	d = "friday";
	MyTime re(11, 11);
	TrainTable empt;
	TrainTable empt2;
	TrainTable empt3;
	TrainTable empt4;
	TrainTable empt5;
	TrainTable empt6;
	TrainTable first(1, re, re, re, d, 34, 65, station, 3);
	TrainTable second(2, re, re, re, d, 86, 74, station, 3);
	TrainTable third(3, re,re, re, d, 86, 74, station, 3);
	TrainTable forth(4, re, re, re, d, 86, 74, station, 3);
	TrainTable fifth(5, re, re, re, "пт cfhfq", 86, 74, station, 3);
	TrainTable sixth(6, re, re, re, "пт cfhfq", 86, 74, station, 3);
	
	/*
	MyString empt;
	MyString empt2;
	MyString empt3;
	MyString empt4;
	MyString empt5;
	MyString empt6;
	MyString first("first 1");
	MyString second("second 2");
	MyString third("third 3");
	MyString forth("forth 4");
	MyString fifth("fifth5");
	MyString sixth("sixth    6");*/
	
	opa.write(&first);
	cout << opa.stream.tellp() << endl;
	opa.write(&second);
	cout << opa.stream.tellp() << endl;
	opa.write(&third);
	cout << opa.stream.tellp() << endl;
	opa.write(&forth);
	cout << opa.stream.tellp() << endl;
	opa.write(&fifth);
	cout << opa.stream.tellp() << endl;
	opa.write(&sixth);
	//opa.writePos(&fifth, 4);

	opa.GetStruct();

	opa.close();
	
	
	system("pause");
	return 0;
}