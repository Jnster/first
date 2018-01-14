#include "stdafx.h"
#include <vector>
#include <cstring>
#include <iostream>
#include <fstream>
#include <cstring>
#define MAX_STRING 255

class BinaryFile : public std::fstream{		//����� �������� ���� ������, ������������� �� fstream
private:									//��������� ���� � �������
	vector<streampos> offsets;				//������ ������� ������������ ������ ����� 
	void update_offsets() {					//������� ���������� ������� �������
		clear();	//EOF ���� ����� ����� �������
		seekg(0, std::ios::beg);			//����������� ��������� ����� �� ������
		offsets.clear();					//������ ������
		while (peek() != EOF) {				//���� �� ����� �� ����� �����
			streampos prev_pos = tellg();			//��������� �����
			int count_bytes = 0;					//���������� ������, ���������� ����� ���������� ���������
			read((char*)&count_bytes, sizeof(int));		//��������� �����
			if (count_bytes > 0) {								//���� ������ ������ ����
				offsets.push_back(prev_pos);					//�������� � ������
				seekg(count_bytes, std::ios::cur);				//������������ ��������� ���������
			}
			else {									//���� ��� ���������
				break;								//���������� ����
			}
		}
		//������� ��������, ��������� � ��� ���� resize
		int size = offsets.size();
		bool chet = false;
		if (size % 2 == 0) chet = true;
		for (int i = 1; i < size; i++)
			for (int j = i; j < size-2; j++)
			{
				offsets.at(j) = offsets.at(j + 1);
			}
		if (chet)
		{
			size /= 2;
		}
		else
		{
			size /= 2;
			size++;
		}
		offsets.resize(size);
	}
	char filename[MAX_STRING];					//��� ��������� �����
public:
	BinaryFile(char * filename) {			//����������� ������ � ����������, ��� �����
		openFile(filename);
	}
	~BinaryFile() {
		close();
	}
	void openFile(char * filename) {		//������� �������� ����
		if (is_open()) {		//���� ������ ����
			close();			//�������
		}
		open(filename, std::ios::in | std::ios::out | std::ios::binary);	//������� ���� � �������� ������ ������ � ������
		if (!is_open()) {		//���� �� �������� ����
			open(filename, std::ios::app | std::ios::binary);		//������� ����� � �������
			close();
			open(filename, std::ios::in | std::ios::out | std::ios::binary);	//������� ������, ��� ��������� ����
		}
		update_offsets();						//�������� ������ �������
		strcpy_s(this->filename, filename);
	}
	char * get_filename() {
		return filename;
	}
	void defragmentationFile() {		//�������������� (������) �����
		vector<TrainTable> storageTrainTables;
		for (unsigned i = 0; i < offsets.size(); i++){		//��������� ��� �������� �� ��������� ������ �� ��������� �����
			 TrainTable temp = get_by_index(i);
			storageTrainTables.push_back(temp);
		}
		close();
		open(filename, std::ios::out | std::ios::trunc | std::ios::binary);	//������� ���� � �������� ������ ������ � ������
		close();
		open(filename, std::ios::in | std::ios::out | std::ios::binary);	//������� ���� � �������� ������ ������ � ������
		clear();
		seekp(0, std::ios::beg);
		for (unsigned i = 0; i < storageTrainTables.size(); i++){		//���������� ��� �������� �� ���������� ������� ������� � ����
			 TrainTable temp = storageTrainTables.at(i);
			addElement(temp);
		}
	}
	void addElement( TrainTable & value) {		//������� �������� � ����� �����
		clear();	//EOF ���� ����� ����� �������
		streampos pos = 0;		//����� �������
		int sizeValue = value.size();		//������ ��������� � ������
		int prevSize;
		if (offsets.size() > 0) {			//���� ������ ������� �� ������
			pos = offsets.at(offsets.size() - 1);		//����� ������� �� ��������� ��������� ������
			seekg(pos);
			read((char*)(&prevSize), sizeof(int));
			pos += sizeof(int)+prevSize;
		}
		seekp(pos, std::ios::beg);			//������� � ���� �������
		write((const char*)&sizeValue, sizeof(sizeValue));	//�������� ������ � ������
		value.write(*this);//write((const char*)&value, sizeValue);				//�������� ���� ���������
		int count_bytes = 0;
		write((const char*)&count_bytes, sizeof(int));	//� ����� ����� 0 ���� ��� ������� �� ��������� ������
		flush();								//��� ����������� ������ �������
		update_offsets();						//�������� ������ �������
	}
	bool edit_by_index(unsigned index,  TrainTable & value) {
		if (index < 0 || index >= offsets.size()) {			//���� ������ ����� �� �������
			return false;								//������� ������ ���������
		}
		clear();	//EOF ���� ����� ����� �������
		streampos pos = offsets.at(index);
		seekp(pos, std::ios::beg);
		int valueSize = sizeof(value);
		write((const char*)&valueSize, sizeof(valueSize));
		write((const char*)&value, valueSize);
		flush();								//��� ����������� ������ �������
		update_offsets();						//�������� ������ �������
		return true;
	}
	TrainTable get_by_index(unsigned index) {		//�������� ������� �� ����������� ������
		TrainTable pustoy;
		if (index < 0 || index >= offsets.size()) {			//���� ������ ����� �� �������
			return pustoy;								//������� ������ ���������
		}
		clear();	//EOF ���� ����� ����� �������
		streampos pos = offsets.at(index);		//������� ������, ����� �� ������� �� ����������� ������
		seekg(pos, std::ios::beg);			//������� ��������� �� ������� ������������ ������ �����
		int count_bytes = 0;				//������ � ������
		read((char*)&count_bytes, sizeof(int));		//��������� ������ � ������
		if (count_bytes > 0) {
			 TrainTable temp;				//��������� ���������� ��� ���������
			 temp.read(*this);//read((char*)&temp, count_bytes);			//������ ���������
			return temp;
		}
		return pustoy;			//������� ���������
	}
	bool remove_by_index(unsigned index){
		if (index < 0 || index >= offsets.size()) {			//���� ������ ����� �� �������
			return false;
		}
		clear();	//EOF ���� ����� ����� �������
		if (index>0 && index == offsets.size() - 1) {
			streampos pos = offsets.at(index - 1);
			seekp(pos, std::ios::beg);
			int count_bytes = 0;					//� ����� ����� 0 ����
			write((const char*)&count_bytes, sizeof(count_bytes));
			flush();								//��� ����������� ������ �������
			update_offsets();						//�������� ������ �������
			return true;
		}
		for (unsigned i = index; i < offsets.size() - 1; i++) {		//�������� ��� �������� �����
			 TrainTable next_element = get_by_index(i + 1);
			streampos pos = offsets.at(i);
			seekp(pos, std::ios::beg);
			int valueSize = sizeof(next_element);
			write((const char*)&valueSize, sizeof(valueSize));
			write((const char*)&next_element, valueSize);
		}
		streampos pos = offsets.at(offsets.size() - 1);
		seekp(pos, std::ios::beg);
		int count_bytes = 0;					//� ����� ����� 0 ����
		write((const char*)&count_bytes, sizeof(count_bytes));
		flush();								//��� ����������� ������ �������
		update_offsets();						//�������� ������ �������
		return true;
	}
	friend std::ostream& operator<< (std::ostream & out, BinaryFile & bin){	//��������������� ��������� ������
		for (unsigned i = 0; i < bin.offsets.size(); i++) {			//�������� ������
			 TrainTable temp;
			temp = bin.get_by_index(i);			//�������� ��������� �� �������
			out << "[" << i << "] ";
			out << temp << std::endl;			//���������� �� �����
		}
		return out;
	}
};
