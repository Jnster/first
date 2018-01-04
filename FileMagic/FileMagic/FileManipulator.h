#include <fstream>
#include <string.h>

using namespace std;

template<class T>
class FileManipulator
{
private:

public:
	char *INputFileName, *OUTputFileName;
	ifstream input;
	ofstream output;
	T data;
	int counter;
	int currentW;
	int currentR;

	FileManipulator(char* INputFileName,char* OUTputFileName);
	FileManipulator(char* FileName);

	~FileManipulator();
	
	T read();
	T read(int pos);
	T readPos(int pos);
	void write(T* object);
	void writePos(T* object, int pos);
	void close();
	//TODO:Реализовать
	T* search(char*);
};

template<class T>
FileManipulator<T>::FileManipulator(char* InputFileName, char* OutputFileName)
{
	INputFileName = new char[sizeof(InputFileName)];
	OUTputFileName = new char[sizeof(OutputFileName)];
	strcpy(INputFileName, InputFileName);
	strcpy(OUTputFileName, OutputFileName);
	counter = 0;
	currentW = 0;
	currentR = 0;
}

template<class T>
FileManipulator<T>::FileManipulator(char* FileName)
{
	INputFileName = new char[sizeof(FileName)];
	strcpy(INputFileName, FileName);
	OUTputFileName = INputFileName;
	counter = 0;
	currentW = 0;
	currentR = 0;
}

template<class T>
FileManipulator<T>::~FileManipulator()
{
	if (INputFileName != nullptr)delete[] INputFileName;
	if ((OUTputFileName != nullptr) && (OUTputFileName != INputFileName))delete[] OUTputFileName;
	if (input.is_open()) input.close();
	if (output.is_open())output.close();
}

template<class T>
T FileManipulator<T>::read()
{
	if (!input.is_open()) input.open(INputFileName, ios::binary);
	/*if (data != nullptr) delete data;
	data = new T;*/
	input.seekg(sizeof(streampos)*2, ios_base::cur);
	data.read(input);
	currentR++;
	return data;
}

template <class T>
void FileManipulator<T>::write(T* obj)
{
	if (!output.is_open()) output.open(OUTputFileName, ios::binary);
	streampos p,d;
	streampos s = output.tellp();
	output.seekp(sizeof(streampos)*2, ios_base::cur);
	obj->write(output);
	p = output.tellp();
	output.seekp(s);
	output.write(reinterpret_cast<const char*>(&p), sizeof(streampos));
	output.seekp(p);
	output.seekp(sizeof(streampos), ios_base::cur);
	output.write(reinterpret_cast<const char*>(&s), sizeof(streampos));
	output.seekp(p);
	counter++;
	currentW++;
}

template<class T>
void FileManipulator<T>::close()
{
	if (input.is_open()) input.close();
	if (output.is_open()) output.close();
}

template<class T>
T FileManipulator<T>::read(int pos)
{
	int i;
	if (!input.is_open()) input.open(INputFileName, ios::binary);
	streampos y;
	if (pos > 0)
		for (i = 0; i < pos; i++)
		{
			input.read(reinterpret_cast<char*>(&y), sizeof(streampos));
			input.seekg(y);
			//cout << y << endl;
		}
	else if (pos < 0)
		for (i = pos; i <= 0; i++)
		{
			input.seekg(sizeof(streampos),ios_base::cur);
			input.read(reinterpret_cast<char*>(&y), sizeof(streampos));
			input.seekg(y,ios_base::beg);
			//cout << y << endl;
		}
	input.seekg(sizeof(streampos)*2, ios_base::cur);
	data->read(input);
	currentR+=pos;
	return *data;
}

template<class T>
T FileManipulator<T>::readPos(int pos)
{
	int i;
	if (!input.is_open()) input.open(INputFileName, ios::binary);
	streampos y;
	input.seekg(0, ios_base::beg);
	for (i = 0; i < pos; i++)
	{
		input.read(reinterpret_cast<char*>(&y), sizeof(streampos));
		input.seekg(y);
		//cout << y << endl;
	}
	input.seekg(sizeof(streampos) * 2, ios_base::cur);
	data->read(input);
	currentR += pos;
	return *data;
}

template<class T>
void FileManipulator<T>::writePos(T* obj, int pos)
{
	int i;
	streampos y,prev,next,now;
	output.seekp(0, ios_base::beg);
	input.seekg(0, ios_base::beg);
	if (counter >= pos)
	{
		//Находим позицию
		for (i = 0; i < pos; i++)
		{
			input.read(reinterpret_cast<char*>(&y), sizeof(streampos));
			input.seekg(y);
		}
		input.seekg(sizeof(streampos), ios_base::cur);
		prev = input.tellg();
		input.seekg(prev);
		next = input.tellg();
		//переходим в  указатель следующий в конце файла
		output.seekp(0,ios_base::end);
		now = output.tellp();
		output.write(reinterpret_cast<const char*>(&next), sizeof(streampos));
		output.write(reinterpret_cast<const char*>(&prev), sizeof(streampos));
		this->write(obj);
		output.seekp(prev);
		output.write(reinterpret_cast<const char*>(&now), sizeof(streampos));
		output.seekp(next);
		output.seekp(sizeof(streampos), ios_base::cur);
		output.write(reinterpret_cast<const char*>(&now), sizeof(streampos));
		counter++;
	}
}