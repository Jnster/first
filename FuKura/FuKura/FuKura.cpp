// FuKura.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
using namespace std;

#define DEFAULT_FILENAME "default.dat"



int main(int argc, char * argv[]) {
	setlocale(LC_ALL, "Russian");
	int menu = -1;
	BinaryFile binaryFile(DEFAULT_FILENAME);
	TrainTable temp;
	ofstream fout;
	ifstream finp;
	MyTime re(12, 35);
	int* station = new int[3];
	station[0] = 87;
	station[1] = 54;
	station[2] = 7;
	char* d = new char[12];
	d = "friday";
	TrainTable first(1, re, re, re, d, 34, 65, station, 3);
	TrainTable second(2, re, re, re, d, 86, 74, station, 3);
	TrainTable third(3, re, re, re, d, 86, 74, station, 3);
	TrainTable forth(4, re, re, re, d, 86, 74, station, 3);
	TrainTable fifth(5, re, re, re, "пт cfhfq", 86, 74, station, 3);
	TrainTable sixth(6, re, re, re, "пт cfhfq", 86, 74, station, 3);
	bool code = 0;
	while (menu != 0) {
		cout << "Меню:" << endl;
		cout << "1 - Открыть двоичный файл" << endl;
		cout << "2 - Показать имя открытого двоичного файла" << endl;
		cout << "3 - Вывести на экран все структуры двоичного файла" << endl;
		cout << "4 - Добавить запись (структура Расписание Поезда) в двоичный файл" << endl;
		cout << "5 - Извлечь на экран по логическому номеру запись из файла" << endl;
		cout << "6 - Удалить по логическому номеру (индексу) запись" << endl;
		cout << "7 - Редактировать запись по логическому номеру (индексу)" << endl;
		cout << "8 - Экспорт в текстовый файл" << endl;
		cout << "9 - Сжатие файла (дефрагментация)" << endl;
		cout << "0 - Выход" << endl;
		cin >> menu;
		std::cin.clear(); //clear the flag
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  //чтобы защитить ввод цифр от букв
		switch (menu) {
		case 1:
			char filename[MAX_STRING];
			cout << "Введите имя двоичного файла для открытия: " << endl;
			cin.getline(filename, MAX_STRING);
			binaryFile.openFile(filename);
			break;
		case 2:
			cout << "Имя открытого двоичного файла: " << binaryFile.get_filename() << endl;
			break;
		case 3:
			cout << binaryFile;
			break;
		case 4:
			/*temp.consoleRead();
			binaryFile.addElement(temp);*/
			binaryFile.addElement(first);
			binaryFile.addElement(second);
			binaryFile.addElement(third);
			binaryFile.addElement(forth);
			binaryFile.addElement(fifth);
			binaryFile.addElement(sixth);
			break;
		case 5:
			int index;
			cout << "Введите логический номер (индекс) записи для извлечения: ";
			cin >> index;
			cout << binaryFile.get_by_index(index) << endl;
			break;
		case 6:
			cout << "Введите логический номер (индекс) записи для удаления: ";
			cin >> index;
			code = binaryFile.remove_by_index(index);
			if (code) {
				cout << "Запись успешно удалена." << endl;
			}
			else {
				cout << "Не удалось удалить запись." << endl;
			}
			break;
		case 7:
			cout << "Введите логический номер (индекс) записи для редактирования: ";
			cin >> index;
			std::cin.clear(); //clear the flag
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  //чтобы защитить ввод цифр от букв
			temp.consoleRead();
			code = binaryFile.edit_by_index(index, temp);
			if (code) {
				cout << "Запись успешно отредактирована." << endl;
			}
			else {
				cout << "Не удалось подредактировать запись." << endl;
			}
			break;
		case 8:
			cout << "Введите имя текстового файла: " << endl;
			cin.getline(filename, MAX_STRING);
			fout.open(filename);
			fout << binaryFile;
			break;
		case 9:
			binaryFile.defragmentationFile();
			cout << "Сжатие файла успешно завершена." << endl;
			break;
		}
	}
	return 0;
}

