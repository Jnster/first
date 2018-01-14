#include <fstream>
#include <string.h>

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
	int currentW;
	int currentR;

	FileManipulator(char* FileName);

	~FileManipulator();
	
	T read();
	T read(int pos);
	T readPos(int pos);
	void write(T* object);
	void writePos(T* object, int pos);
	void close();
	void deletePos(int pos);
	void edit(T obj, int pos);
	//���� ��� �������
	void toStart();
	//TODO:�����������
	T* search(char*);
};

template<class T>
FileManipulator<T>::FileManipulator(char* FileName)
{
	strcpy(this->fileName, FileName);
	counter = 0;
	currentW = 0;
	currentR = 0;
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
void FileManipulator<T>::toStart()
{
	next = head;
}

template<class T>
void FileManipulator<T>::edit(T obj, int pos)
{
	long long buffer, prevnew;
	stream.seekg(head);
	//�������� ��� � ������� �������
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
	
	long long buffer,b,next,prev;

	b = stream.tellg();
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
		b = next;
		this->next = next;
	}
	if (pos == 0) head = next;
	stream.seekg(b);
	
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
	currentR++;
	return data;
}

template <class T>
void FileManipulator<T>::write(T* obj)
{
	if (!stream.is_open()) stream.open(fileName, ios::in | ios::out | ios::binary);
	long long p, buffer;
	if (counter == 0) //������ ������� �������
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
		stream.write(reinterpret_cast<const char*>(&head), sizeof(long long));// �������� ������ ��������� "����������" ������ ��� ����������� ������� �� ������
		stream.seekp(sizeof(long long), ios_base::cur); //������ ��� ���������
		stream.read(reinterpret_cast<char*>(&prev), sizeof(long long));
		p = stream.tellg(); //������� ����� �������
		stream.seekp(s);
		stream.seekp(sizeof(long long), ios_base::cur);
		stream.write(reinterpret_cast<const char*>(&p), sizeof(long long));
		stream.seekg(p);
		obj->write(stream); //������ �������
		nextW = stream.tellp(); //������� ����� ������
		stream.seekp(sizeof(long long) * 2, ios_base::cur); //������ ��� ��������� "����������" ���������� �������
		stream.write(reinterpret_cast<const char*>(&s), sizeof(long long));// ���������� � ��������� "�����������" ���������� ������� ������ ��� ���������
		stream.seekp(head);
		stream.seekp(sizeof(long long)*2, ios_base::cur);
		stream.write(reinterpret_cast<const char*>(&s), sizeof(long long));// �������� ������ ��������� "�����������" ������� ������� �� ������ ��� ����������
		stream.seekp(prev, ios_base::beg);
		stream.write(reinterpret_cast<const char*>(&s), sizeof(long long));
	}
	stream.seekp(nextW);
	counter++;
	currentW++;
}

template<class T>
void FileManipulator<T>::close()
{
	if (stream.is_open()) stream.close();
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

template<class T>
T FileManipulator<T>::readPos(int pos)
{
	int i;
	if (!stream.is_open()) stream.open(fileName, ios::in | ios::out | ios::binary);
	long long y;
	stream.seekg(0, ios_base::beg);
	for (i = 0; i < pos; i++)
	{
		stream.read(reinterpret_cast<char*>(&y), sizeof(long long));
		stream.seekg(y);
	}
	stream.seekg(sizeof(long long) * 2, ios_base::cur);
	data->read(stream);
	currentR += pos;
	return *data;
}*/

template<class T>
void FileManipulator<T>::writePos(T* obj, int pos)
{
	int i;
	long long y,prev,next,now,b,prevnew;
	if (!stream.is_open()) stream.open(fileName, ios::in | ios::out | ios::binary);
	b = stream.tellg();
	now = stream.tellp();
	stream.seekp(sizeof(long long), ios_base::cur);
	y = stream.tellp();
	stream.seekg(y);
	stream.read(reinterpret_cast<char*>(&prevnew), sizeof(long long));//��� ����������� ������ �� ���������, ���������� �� �������
	stream.seekg(head);
	if (counter >= pos)
	{
		//������� �������
		cout << stream.tellg() << endl;
		for (i = 0; i < pos; i++)
		{
			stream.read(reinterpret_cast<char*>(&y), sizeof(long long));
			stream.seekg(y);
			cout << stream.tellg() << endl;
		}
		stream.read(reinterpret_cast<char*>(&next), sizeof(long long));
		cout <<"next "<<next<< endl;
		stream.read(reinterpret_cast<char*>(&prev), sizeof(long long));
		cout << "prev " << prev << endl;
		cout << "now " << now << endl;
		stream.seekp(now);
		stream.write(reinterpret_cast<const char*>(&next), sizeof(long long));
		stream.write(reinterpret_cast<const char*>(&prev), sizeof(long long));
		this->write(obj);
		y = stream.tellp();
		stream.seekp(prev);
		stream.write(reinterpret_cast<const char*>(&now), sizeof(long long));
		stream.seekp(next);
		stream.seekp(sizeof(long long), ios_base::cur);
		stream.write(reinterpret_cast<const char*>(&now), sizeof(long long));
		stream.seekp(y);
		stream.seekp(sizeof(long long), ios_base::cur);
		stream.write(reinterpret_cast<const char*>(&prevnew), sizeof(long long));
		cout << "prevnew " << prevnew << endl;
		stream.seekp(y);
		counter++;
		stream.seekg(b);
	}
}