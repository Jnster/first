#include <fstream>
#include <string.h>
#include <cstdio>

#define MAX_STRING 255

using namespace std;

template<class T>
class FileManipulator
{
private:

public:
	char fileName[MAX_STRING];
	fstream stream;
	long long head, next, nextW;
	T data;
	int counter;

	FileManipulator(char* FileName);

	~FileManipulator();
	
	T read();//считывание по порядку
	T readPos(int pos);//считывание по позиции
	void GetStruct();//вывести на экран все элементы в файле
	void write(T* object);//записать элемент в конец списка
	void writePos(T* object, int pos);//записаь на позицию
	void close();//закрыть файловый поток
	void deletePos(int pos);//удалить по позиции
	void edit(T obj, int pos);//редактировать элемент
	void defragmentation();//сжатие (дефрагментация)
	void deleteFile();//удалить файл
	void open(char* FileName);//открыть файлоый поток
	void toStart();//начать считывание по порядку с первого элемента
	//TODO:Реализовать
	T* search(char*);
};

template<class T>
FileManipulator<T>::FileManipulator(char* FileName)
{
	strcpy(this->fileName, FileName);
	stream.open(fileName, ios::in | ios::out | ios::binary);
	if (!stream.is_open()) stream.open(fileName, ios::in | ios::out | ios::binary | ios::trunc);
	counter = 0;
	head = 0;
	next = head;
	nextW = head;
}

template<class T>
FileManipulator<T>::~FileManipulator()
{
//	if (fileName != nullptr)delete[] fileName;
	if (stream.is_open()) stream.close();
}

template<class T>
void FileManipulator<T>::deleteFile()
{
	stream.close();
	remove(fileName);
}

template<class T>
void FileManipulator<T>::open(char* name)
{
	if (stream.is_open()) stream.close();
	stream.open(name, ios::in | ios::out | ios::binary);
	if (!stream.is_open()) stream.open(fileName, ios::in | ios::out | ios::binary | ios::trunc);
}

template<class T>
void FileManipulator<T>::defragmentation()
{
	char bufName[255] = "BUFFER";
	strcat(bufName, fileName);
	FileManipulator buffer(bufName);

	toStart();
	
	do
	{
		data = read();
		buffer.write(&data);

	} while (next != head);

	stream.close();
	stream.open(fileName, ios::in | ios::out | ios::binary | ios::trunc);
	counter = 0;
	head = 0;
	next = head;
	nextW = head;

	buffer.toStart();

	do
	{
		data = buffer.read();
		write(&data);
	} while (buffer.next != buffer.head);

	stream.close();
	open(fileName);

	buffer.deleteFile();
}

template<class T>
void FileManipulator<T>::toStart() //считывание начать с головы
{
	next = head;
}

template<class T> void FileManipulator<T>::GetStruct()
{
	T info;
	int i = 0;
	if (!stream.is_open()) stream.open(fileName, ios::in | ios::out | ios::binary);
	long long y, d;
	//stream.seekg(0, ios_base::beg);
	stream.seekg(head);
	if (counter == 0) return;
	if (counter == 1)
	{
		stream.seekg(sizeof(long long), ios_base::cur);
		stream.read(reinterpret_cast<char*>(&d), sizeof(long long));
		stream.seekg(d);
		info.read(stream);
		cout << "Запись с индексом: " << 0 << endl;
		cout << info << endl;
	}
	else
	{
		for (i = 0; i < counter; i++)
		{
			stream.read(reinterpret_cast<char*>(&y), sizeof(long long));
			//stream.seekg(sizeof(long long) * 2, ios_base::cur);
			stream.read(reinterpret_cast<char*>(&d), sizeof(long long));
			stream.seekg(d);
			info.read(stream);
			cout << "Запись с индексом: " << i << endl;
			cout << info << endl;
			stream.seekg(y);
		}
	}
}

template<class T>
void FileManipulator<T>::edit(T obj, int pos)
{
	long long buffer, prevnew;
	stream.seekg(head);
	//подумать ещё о позиции нулевой
	for (int i = 1; i <= pos; i++)
	{
		stream.read(reinterpret_cast<char*>(&buffer), sizeof(long long));
		stream.seekg(buffer);
	}

	stream.seekg(sizeof(long long), ios_base::cur);
	//buffer = stream.tellg();
	stream.write(reinterpret_cast<const char*>(&nextW), sizeof(long long));
	stream.seekg(nextW);
	stream.seekg(sizeof(long long) * 2, ios_base::cur);
	stream.read(reinterpret_cast<char*>(&prevnew), sizeof(long long));
	stream.seekg(nextW);
	obj.write(stream);
	nextW = stream.tellg();
	stream.seekg(sizeof(long long) * 2, ios_base::cur);
	stream.write(reinterpret_cast<const char*>(&prevnew), sizeof(long long));
}

template<class T>
void FileManipulator<T>::deletePos(int pos)
{
	if (!stream.is_open()) stream.open(fileName, ios::in | ios::out | ios::binary);
	
	long long buffer,next,prev;

		stream.seekg(head);
	for (int i = 1; i <= pos; i++)
	{
		stream.read(reinterpret_cast<char*>(&buffer), sizeof(long long));
		stream.seekg(buffer);
	}
	stream.read(reinterpret_cast<char*>(&next), sizeof(long long));
	stream.seekg(sizeof(long long), ios_base::cur);
	stream.read(reinterpret_cast<char*>(&prev), sizeof(long long));
	stream.seekp(next); //(next + sizeof(long long) * 2); ????
	stream.seekp(sizeof(long long) * 2, ios_base::cur);
	stream.write(reinterpret_cast<const char*>(&prev), sizeof(long long));
	stream.seekp(prev);
	stream.write(reinterpret_cast<const char*>(&next), sizeof(long long));
	if ((pos == 0) && (this->next == head))
	{
		this->next = next;
	}
	if (pos == 0) head = next;
	counter--;
}

template<class T>
T FileManipulator<T>::read()
{
	//cout << "read" << endl;
	long long dat;
	if (!stream.is_open()) stream.open(fileName, ios::in | ios::out | ios::binary);
	stream.seekg(next);
	stream.read(reinterpret_cast<char*>(&next), sizeof(long long));
	stream.read(reinterpret_cast<char*>(&dat), sizeof(long long));
	//cout << "next " << next;
	stream.seekg(dat);
	data.read(stream);
	return data;
}

template <class T>
void FileManipulator<T>::write(T* obj)
{
	if (!stream.is_open()) stream.open(fileName, ios::in | ios::out | ios::binary);
	long long p, buffer;
	if (counter == 0) //Запись первого объекта
	{
		stream.seekp(head);
		stream.write(reinterpret_cast<const char*>(&head), sizeof(long long));
		buffer = stream.tellp();
		stream.seekp(sizeof(long long), ios_base::cur);
		stream.write(reinterpret_cast<const char*>(&head), sizeof(long long));
		p = stream.tellp();
		stream.seekp(buffer);
		stream.write(reinterpret_cast<const char*>(&p), sizeof(long long));
		stream.seekp(p);
		obj->write(stream);
		nextW = stream.tellp();
		stream.seekp(sizeof(long long)*2, ios_base::cur);
		stream.write(reinterpret_cast<const char*>(&head), sizeof(long long));
	}
	else
	{
		long long prev, s = stream.tellp();
		stream.seekg(nextW);
		stream.write(reinterpret_cast<const char*>(&head), sizeof(long long));// замыкаем список указатель "следующего" только что записанного объекта на первый
		stream.seekp(sizeof(long long), ios_base::cur); //память под указатели
		stream.read(reinterpret_cast<char*>(&prev), sizeof(long long));
		p = stream.tellg(); //позиция перед записью
		stream.seekp(s);
		stream.seekp(sizeof(long long), ios_base::cur);
		stream.write(reinterpret_cast<const char*>(&p), sizeof(long long));
		stream.seekg(p);
		obj->write(stream); //запись объекта
		nextW = stream.tellp(); //позиция после записи
		stream.seekp(sizeof(long long) * 2, ios_base::cur); //память под указатель "следующего" следующего объекта
		stream.write(reinterpret_cast<const char*>(&s), sizeof(long long));// записываем в указатель "предыдущего" следующего объекта только что созданный
		stream.seekp(head);
		stream.seekp(sizeof(long long)*2, ios_base::cur);
		stream.write(reinterpret_cast<const char*>(&s), sizeof(long long));// замыкаем список указатель "предыдущего" первого объекта на только что записанный
		stream.seekp(prev, ios_base::beg);
		stream.write(reinterpret_cast<const char*>(&s), sizeof(long long));
	}
	stream.seekp(nextW);
	counter++;
}

template<class T>
void FileManipulator<T>::close()
{
	if (stream.is_open()) stream.close();
}

/*
template<class T>
T FileManipulator<T>::read(int pos)
{
	int i;
	if (!stream.is_open()) stream.open(fileName, ios::in | ios::out | ios::binary);
	long long y;
	if (pos > 0)
		for (i = 0; i < pos; i++)
		{
			stream.read(reinterpret_cast<char*>(&y), sizeof(long long));
			stream.seekg(y);
		}
	else if (pos < 0)
		for (i = pos; i <= 0; i++)
		{
			stream.seekg(sizeof(long long),ios_base::cur);
			stream.read(reinterpret_cast<char*>(&y), sizeof(long long));
			stream.seekg(y,ios_base::beg);
		}
	stream.seekg(sizeof(long long)*2, ios_base::cur);
	data->read(stream);
	currentR+=pos;
	return *data;
}

*/

template<class T> 
T FileManipulator<T>::readPos(int pos)
{
	int i;
	if (!stream.is_open()) stream.open(fileName, ios::in | ios::out | ios::binary);
	long long y, d;
	stream.seekg(0, ios_base::beg);
	if (pos == 0)
	{
		stream.seekg(sizeof(long long), ios_base::cur);
		stream.read(reinterpret_cast<char*>(&d), sizeof(long long));
		stream.seekg(d);
		data.read(stream);
	}
	else
	{
		for (i = 0; i < pos; i++)
		{
			stream.read(reinterpret_cast<char*>(&y), sizeof(long long));
			stream.seekg(y);
		}
		stream.seekg(sizeof(long long), ios_base::cur);
		stream.read(reinterpret_cast<char*>(&d), sizeof(long long));
		stream.seekg(d);
		data.read(stream);
	}
	return data;
}

template<class T>
void FileManipulator<T>::writePos(T* obj, int pos)
{
	int i;
	long long y, b, prev, nextu, now, prevnew;
	if (!stream.is_open()) stream.open(fileName, ios::in | ios::out | ios::binary);
	now = nextW;
	stream.seekg(nextW);
	stream.seekp(sizeof(long long) * 2, ios_base::cur);
	stream.read(reinterpret_cast<char*>(&prevnew), sizeof(long long));//Для запоминания ссылки на последний, записанный по порядку
	stream.seekg(head);
	if (counter >= pos)
	{
		//Находим позицию
		for (i = 1; i <= pos; i++)
		{
			stream.read(reinterpret_cast<char*>(&y), sizeof(long long));
			stream.seekg(y);
		}
		nextu = stream.tellg();
		stream.seekg(sizeof(long long) * 2, ios_base::cur);
		stream.read(reinterpret_cast<char*>(&prev), sizeof(long long));
		stream.seekp(nextW);
		stream.write(reinterpret_cast<const char*>(&nextu), sizeof(long long));
		//stream.seekg(sizeof(long long), ios_base::cur);
		b = nextW + sizeof(long long) * 3;
		stream.write(reinterpret_cast<const char*>(&b), sizeof(long long));

		stream.write(reinterpret_cast<const char*>(&prev), sizeof(long long));
		//y = stream.tellg();
		//stream.seekg(nextW);
//		stream.seekg(sizeof(long long), ios_base::cur);
		//stream.write(reinterpret_cast<const char*>(&y), sizeof(long long));
		//stream.seekg(y);
		obj->write(stream);
		nextW = stream.tellp();
		stream.seekp(prev);
		stream.write(reinterpret_cast<const char*>(&now), sizeof(long long));
		stream.seekp(nextu);
		stream.seekp(sizeof(long long) * 2, ios_base::cur);
		stream.write(reinterpret_cast<const char*>(&now), sizeof(long long));
		stream.seekp(nextW);
		stream.seekp(sizeof(long long) * 2, ios_base::cur);
		stream.write(reinterpret_cast<const char*>(&prevnew), sizeof(long long));
		counter++;
	}
}