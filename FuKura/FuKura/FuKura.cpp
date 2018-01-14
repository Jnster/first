// FuKura.cpp: ���������� ����� ����� ��� ����������� ����������.
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
	TrainTable fifth(5, re, re, re, "�� cfhfq", 86, 74, station, 3);
	TrainTable sixth(6, re, re, re, "�� cfhfq", 86, 74, station, 3);
	bool code = 0;
	while (menu != 0) {
		cout << "����:" << endl;
		cout << "1 - ������� �������� ����" << endl;
		cout << "2 - �������� ��� ��������� ��������� �����" << endl;
		cout << "3 - ������� �� ����� ��� ��������� ��������� �����" << endl;
		cout << "4 - �������� ������ (��������� ���������� ������) � �������� ����" << endl;
		cout << "5 - ������� �� ����� �� ����������� ������ ������ �� �����" << endl;
		cout << "6 - ������� �� ����������� ������ (�������) ������" << endl;
		cout << "7 - ������������� ������ �� ����������� ������ (�������)" << endl;
		cout << "8 - ������� � ��������� ����" << endl;
		cout << "9 - ������ ����� (��������������)" << endl;
		cout << "0 - �����" << endl;
		cin >> menu;
		std::cin.clear(); //clear the flag
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  //����� �������� ���� ���� �� ����
		switch (menu) {
		case 1:
			char filename[MAX_STRING];
			cout << "������� ��� ��������� ����� ��� ��������: " << endl;
			cin.getline(filename, MAX_STRING);
			binaryFile.openFile(filename);
			break;
		case 2:
			cout << "��� ��������� ��������� �����: " << binaryFile.get_filename() << endl;
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
			cout << "������� ���������� ����� (������) ������ ��� ����������: ";
			cin >> index;
			cout << binaryFile.get_by_index(index) << endl;
			break;
		case 6:
			cout << "������� ���������� ����� (������) ������ ��� ��������: ";
			cin >> index;
			code = binaryFile.remove_by_index(index);
			if (code) {
				cout << "������ ������� �������." << endl;
			}
			else {
				cout << "�� ������� ������� ������." << endl;
			}
			break;
		case 7:
			cout << "������� ���������� ����� (������) ������ ��� ��������������: ";
			cin >> index;
			std::cin.clear(); //clear the flag
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  //����� �������� ���� ���� �� ����
			temp.consoleRead();
			code = binaryFile.edit_by_index(index, temp);
			if (code) {
				cout << "������ ������� ���������������." << endl;
			}
			else {
				cout << "�� ������� ���������������� ������." << endl;
			}
			break;
		case 8:
			cout << "������� ��� ���������� �����: " << endl;
			cin.getline(filename, MAX_STRING);
			fout.open(filename);
			fout << binaryFile;
			break;
		case 9:
			binaryFile.defragmentationFile();
			cout << "������ ����� ������� ���������." << endl;
			break;
		}
	}
	return 0;
}

