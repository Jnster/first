// FileMagic.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
//#include <fstream>
#include <iostream>
#include <locale>
//#include"headers.h"

using namespace std;

int main(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");
	
	//FileManipulator<MyString> opa("out.bin");
	FileManipulator<TrainTable> opa("out.bin");
	int* station = new int[3];
	int i;
	station[0] = 6;
	station[1] = 87;
	station[2] = 23;
	char* d = new char[12];
	d = "пт вт ср шгуе";
	
	TrainTable empt;
	TrainTable empt2;
	TrainTable empt3;
	TrainTable empt4;
	TrainTable empt5;
	TrainTable empt6;
	TrainTable first(1, "34:67", "34:87", "ty1yg", d, 34, 65, station, 3);
	TrainTable second(2, "04:67", "30:87", "ty2yg", d, 86, 74, station, 3);
	TrainTable third(3, "07:45", "3:tr7", "y34yg", d, 86, 74, station, 3);
	TrainTable forth(4, "04:67", "30:87", "ty4yg", d, 86, 74, station, 3);
	TrainTable fifth(5, "04:67", "30:87", "ty5yg", "пт cfhfq", 86, 74, station, 3);
	TrainTable sixth(6, "04:67", "30:87", "ty6yg", "пт cfhfq", 86, 74, station, 3);
	
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
	cout << opa.output.tellp() << endl;
	/*opa.write(&second);
	cout << opa.output.tellp() << endl;
	opa.write(&third);
	cout << opa.output.tellp() << endl;
	opa.write(&forth);
	cout << opa.output.tellp() << endl;
	opa.write(&fifth);
	cout << opa.output.tellp() << endl;
	opa.write(&sixth);*/
//	opa.writePos(&sixth, 3);
	//first.Print();

	/*for (i = 0; i < opa.counter; i++)
	{
		MyString *e;
		e = opa.read();
		e->Print();
	}*/
	
	//cout << opa.input.tellg() << " " << sizeof(re) << endl;
	empt = opa.read();
	empt.Print();
	first.Print();
	cout << empt << endl;
//	empt->Print(); TRUUUUBBLLEE print()
	empt2 = opa.read();
	cout << empt2 << endl;
	//empt2->Print();
	//cout << empt <<" "<<sizeof(empt) << endl;
	//empt2 = opa.read();
	//cout << empt2 << " " << sizeof(empt2) << endl;
	empt3 = opa.read();
	cout << empt3 << " " << sizeof(empt3) << endl;
	empt4 = opa.read();
	cout << empt4 << " " << sizeof(empt4) << endl;
	empt5 = opa.read();
	cout << empt5 << " " << sizeof(empt5) << endl;
	
	opa.close();
	
	
	//cout << emp << endl; //<< ira << endl << ty << endl << re << endl;
	system("pause");
	return 0;
}

