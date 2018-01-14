#include "stdafx.h"
#include <vector>
#include <cstring>
#include <iostream>
#include <fstream>
#include <cstring>
#define MAX_STRING 255

class BinaryFile : public std::fstream{		//класс Двоичный файл список, наследованный от fstream
private:									//приватные поля и функции
	vector<streampos> offsets;				//массив сдвигов относительно начала файла 
	void update_offsets() {					//функция обновления массива сдвигов
		clear();	//EOF флаг конца файла очищаем
		seekg(0, std::ios::beg);			//переместить указатель ввода на начало
		offsets.clear();					//пустой массив
		while (peek() != EOF) {				//пока не дошли до конца файла
			streampos prev_pos = tellg();			//вычислить сдвиг
			int count_bytes = 0;					//количество байтов, занимаемый нашей Структурой Студентов
			read((char*)&count_bytes, sizeof(int));		//считываем байты
			if (count_bytes > 0) {								//если байтов больше нуля
				offsets.push_back(prev_pos);					//добавить в массив
				seekg(count_bytes, std::ios::cur);				//перепрыгнуть структуру Студентов
			}
			else {									//если нет структуры
				break;								//остановить цикл
			}
		}
		//удалить нечётные, уменьшить в два раза resize
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
	char filename[MAX_STRING];					//имя открытого файла
public:
	BinaryFile(char * filename) {			//конструктор класса с параметром, имя файла
		openFile(filename);
	}
	~BinaryFile() {
		close();
	}
	void openFile(char * filename) {		//открыть двоичный файл
		if (is_open()) {		//если открыт файл
			close();			//закрыть
		}
		open(filename, std::ios::in | std::ios::out | std::ios::binary);	//открыть файл в двоичном режиме чтения и записи
		if (!is_open()) {		//если не открылся файл
			open(filename, std::ios::app | std::ios::binary);		//создать новый и закрыть
			close();
			open(filename, std::ios::in | std::ios::out | std::ios::binary);	//открыть только, что созданный файл
		}
		update_offsets();						//обновить массив сдвигов
		strcpy_s(this->filename, filename);
	}
	char * get_filename() {
		return filename;
	}
	void defragmentationFile() {		//дефрагментация (сжатие) файла
		vector<TrainTable> storageTrainTables;
		for (unsigned i = 0; i < offsets.size(); i++){		//сохраняем все элементы во временный массив из двоичного файла
			 TrainTable temp = get_by_index(i);
			storageTrainTables.push_back(temp);
		}
		close();
		open(filename, std::ios::out | std::ios::trunc | std::ios::binary);	//открыть файл в двоичном режиме чтения и записи
		close();
		open(filename, std::ios::in | std::ios::out | std::ios::binary);	//открыть файл в двоичном режиме чтения и записи
		clear();
		seekp(0, std::ios::beg);
		for (unsigned i = 0; i < storageTrainTables.size(); i++){		//записываем все элементы из временного массива обратно в файл
			 TrainTable temp = storageTrainTables.at(i);
			addElement(temp);
		}
	}
	void addElement( TrainTable & value) {		//функция добавить в конец файла
		clear();	//EOF флаг конца файла очищаем
		streampos pos = 0;		//сдвиг позиции
		int sizeValue = value.size();		//размер структуры в байтах
		int prevSize;
		if (offsets.size() > 0) {			//если массив сдвигов не пустой
			pos = offsets.at(offsets.size() - 1);		//взять позицию за последним элементом списка
			seekg(pos);
			read((char*)(&prevSize), sizeof(int));
			pos += sizeof(int)+prevSize;
		}
		seekp(pos, std::ios::beg);			//перейти к этой позиции
		write((const char*)&sizeValue, sizeof(sizeValue));	//записать размер в байтах
		value.write(*this);//write((const char*)&value, sizeValue);				//записать саму структуру
		int count_bytes = 0;
		write((const char*)&count_bytes, sizeof(int));	//в конце пишем 0 байт для отметки об окончании списка
		flush();								//для немедленной записи буффера
		update_offsets();						//Обновить массив сдвигов
	}
	bool edit_by_index(unsigned index,  TrainTable & value) {
		if (index < 0 || index >= offsets.size()) {			//если индекс вышел за границы
			return false;								//вернуть пустую структуру
		}
		clear();	//EOF флаг конца файла очищаем
		streampos pos = offsets.at(index);
		seekp(pos, std::ios::beg);
		int valueSize = sizeof(value);
		write((const char*)&valueSize, sizeof(valueSize));
		write((const char*)&value, valueSize);
		flush();								//для немедленной записи буффера
		update_offsets();						//Обновить массив сдвигов
		return true;
	}
	TrainTable get_by_index(unsigned index) {		//получить элемент по логическому номеру
		TrainTable pustoy;
		if (index < 0 || index >= offsets.size()) {			//если индекс вышел за границы
			return pustoy;								//вернуть пустую структуру
		}
		clear();	//EOF флаг конца файла очищаем
		streampos pos = offsets.at(index);		//позиция сдвига, берем из массива по логическому номеру
		seekg(pos, std::ios::beg);			//смещаем указатель на позицию относительно начала файла
		int count_bytes = 0;				//размер в байтах
		read((char*)&count_bytes, sizeof(int));		//считываем размер в байтах
		if (count_bytes > 0) {
			 TrainTable temp;				//временная переменная для структуры
			 temp.read(*this);//read((char*)&temp, count_bytes);			//читаем структуру
			return temp;
		}
		return pustoy;			//вернуть структуру
	}
	bool remove_by_index(unsigned index){
		if (index < 0 || index >= offsets.size()) {			//если индекс вышел за границы
			return false;
		}
		clear();	//EOF флаг конца файла очищаем
		if (index>0 && index == offsets.size() - 1) {
			streampos pos = offsets.at(index - 1);
			seekp(pos, std::ios::beg);
			int count_bytes = 0;					//в конце файла 0 байт
			write((const char*)&count_bytes, sizeof(count_bytes));
			flush();								//для немедленной записи буффера
			update_offsets();						//Обновить массив сдвигов
			return true;
		}
		for (unsigned i = index; i < offsets.size() - 1; i++) {		//сдвинуть все элементы влево
			 TrainTable next_element = get_by_index(i + 1);
			streampos pos = offsets.at(i);
			seekp(pos, std::ios::beg);
			int valueSize = sizeof(next_element);
			write((const char*)&valueSize, sizeof(valueSize));
			write((const char*)&next_element, valueSize);
		}
		streampos pos = offsets.at(offsets.size() - 1);
		seekp(pos, std::ios::beg);
		int count_bytes = 0;					//в конце файла 0 байт
		write((const char*)&count_bytes, sizeof(count_bytes));
		flush();								//для немедленной записи буффера
		update_offsets();						//Обновить массив сдвигов
		return true;
	}
	friend std::ostream& operator<< (std::ostream & out, BinaryFile & bin){	//переопределение оператора вывода
		for (unsigned i = 0; i < bin.offsets.size(); i++) {			//проходим циклом
			 TrainTable temp;
			temp = bin.get_by_index(i);			//получаем структуру по индексу
			out << "[" << i << "] ";
			out << temp << std::endl;			//отправляем на вывод
		}
		return out;
	}
};
