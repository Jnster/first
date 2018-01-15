// FileMagic.cpp: определяет точку входа для консольного приложения.
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
	TrainTable fifth(5, re, re, re, "пт cfhfq", 86, 74, station, 3);
	TrainTable sixth(6, re, re, re, "пт cfhfq", 86, 74, station, 3);*/
		
	while (ans != 0)
	{
		cout << "Меню:" << endl
			<< "1)Открыть файл." << endl
			<< "2)Добавить элемент." << endl
			<< "3)Вывести элементы списка на экран." << endl
			<< "4)Вывести на экран элемент по позиции." << endl
			<< "5)Удалить элемент на позиции." << endl
			<< "6)Сжать файл." << endl
			<< "7)Изменить элемент на позиции." << endl
			<< "8)Добавление по позиции." << endl
			<< "0)Выход." << endl;

		cin >> ans;

		switch (ans)
		{
		case 1:
		{
			cout << "Введите название файла: ";
			cin.getline(name, 255);
			cin.getline(name, 255);
			opa.open(name);
			cout << "Файл открыт" << endl;
			break;
		}
		case 2:
		{
			cout << "Введите данные:" << endl;
			empt.consoleRead();
			opa.write(&empt);
			cout << "Элемент добавлен." << endl;
			break;
		}
		case 3:
		{
			opa.GetStruct();
			break;
		}
		case 4:
		{
			cout << "Введите позицию: ";
			cin >> pos;
			empt = opa.readPos(pos);
			cout << empt << endl;
			break;
		}
		case 5:
		{
			cout << "Введите позицию: ";
			cin >> pos;
			opa.deletePos(pos);
			cout << "Удаление завершено." << endl;
			break;
		}
		case 6:
		{
			opa.defragmentation();
			cout << "Сжатие завершено." << endl;
			break;
		}
		case 7:
		{
			cout << "Введите позицию: ";
			cin >> pos;
			cout << "Введите новый объект:" << endl;
			empt.consoleRead();
			opa.edit(empt, pos);
			cout << "Элемент изменен." << endl;
			break;
		}
		case 8:
		{
			cout << "Введите позицию: ";
			cin >> pos;
			cout << "Введите элемент:" << endl;
			empt.consoleRead();
			opa.writePos(&empt, pos);
			cout << "Элемент добавлен." << endl;
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