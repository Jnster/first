// FileMagic.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <iostream>
#include <locale>

using namespace std;

int main(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");
	
	FileManipulator<TrainTable> opa("default.bin");
	//int* station = new int[3];
	int i, ans = -1, pos;
	TrainTable empt;
	char name[255];
	/*
	station[0] = 87;
	station[1] = 54;
	station[2] = 7;
	char* d = new char[12];
	d = "friday";
	MyTime re(11, 11);
	TrainTable empt2;
	TrainTable empt3;
	TrainTable empt4;
	TrainTable empt5;
	TrainTable empt6;
	TrainTable first(1, re, re, re, d, 34, 65, station, 3);
	TrainTable second(2, re, re, re, d, 86, 74, station, 3);
	TrainTable third(3, re,re, re, d, 86, 74, station, 3);
	TrainTable forth(4, re, re, re, d, 86, 74, station, 3);
	TrainTable fifth(5, re, re, re, "�� cfhfq", 86, 74, station, 3);
	TrainTable sixth(6, re, re, re, "�� cfhfq", 86, 74, station, 3);*/
		
	while (ans != 0)
	{
		cout << "����:" << endl
			<< "1)������� ����." << endl
			<< "2)�������� �������." << endl
			<< "3)������� �������� ������ �� �����." << endl
			<< "4)������� �� ����� ������� �� �������." << endl
			<< "5)������� ������� �� �������." << endl
			<< "6)����� ����." << endl
			<< "7)�������� ������� �� �������." << endl
			<< "8)���������� �� �������." << endl
			<< "0)�����." << endl;

		cin >> ans;

		switch (ans)
		{
		case 1:
		{
			cout << "������� �������� �����: ";
			cin.getline(name, 255);
			cin.getline(name, 255);
			opa.open(name);
			cout << "���� ������" << endl;
			break;
		}
		case 2:
		{
			cout << "������� ������:" << endl;
			empt.consoleRead();
			opa.write(&empt);
			cout << "������� ��������." << endl;
			break;
		}
		case 3:
		{
			opa.GetStruct();
			break;
		}
		case 4:
		{
			cout << "������� �������: ";
			cin >> pos;
			empt = opa.readPos(pos);
			cout << empt << endl;
			break;
		}
		case 5:
		{
			cout << "������� �������: ";
			cin >> pos;
			opa.deletePos(pos);
			cout << "�������� ���������." << endl;
			break;
		}
		case 6:
		{
			opa.defragmentation();
			cout << "������ ���������." << endl;
			break;
		}
		case 7:
		{
			cout << "������� �������: ";
			cin >> pos;
			cout << "������� ����� ������:" << endl;
			empt.consoleRead();
			opa.edit(empt, pos);
			cout << "������� �������." << endl;
			break;
		}
		case 8:
		{
			cout << "������� �������: ";
			cin >> pos;
			cout << "������� �������:" << endl;
			empt.consoleRead();
			opa.writePos(&empt, pos);
			cout << "������� ��������." << endl;
			break;
		}
		default:
			break;
		}
	}

	//opa.write(&first);
	//cout << opa.stream.tellp() << endl;
	//opa.write(&second);
	//cout << opa.stream.tellp() << endl;
	//opa.write(&third);
	//cout << opa.stream.tellp() << endl;
	//opa.write(&forth);
	//cout << opa.stream.tellp() << endl;
	//opa.write(&fifth);
	//cout << opa.stream.tellp() << endl;
	//opa.write(&sixth);
	////opa.write(&third);
	//opa.writePos(&fifth, 3);
	////opa.toStart();
	//opa.GetStruct();

	//system("pause");
	opa.close();
	return 0;
}