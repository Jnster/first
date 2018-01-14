#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "MyTime.h"

using namespace std;

class TrainTable
{
public:
	MyTime departure;
	MyTime travel;
	MyTime destination;
	int number;
	char* day;
	int destination_station;
	int departure_station;
	int* travel_station;
	int count_station;

	TrainTable();//конструктор по умолчанию
	TrainTable(TrainTable&);//конструктор копирования
	//конструктор с параметрами
	TrainTable(int train_number, MyTime Departure, MyTime Destination, MyTime Travel, char* Day, int Destination_station, int Departure_station, int* Travel_station, int Count_station);//конструктор с параметрами
	~TrainTable();

	void Print();
	
	friend ostream& operator<< (ostream& os, TrainTable &p);
	friend istream& operator>> (istream& is, TrainTable &p);
	friend ofstream& operator<< (ofstream& os, TrainTable &p);
	friend ifstream& operator>> (ifstream& os, TrainTable &p);

	void operator = (TrainTable&);

	void consoleRead();
	void write(fstream&);
	void read(fstream&);
	void read(istream& Fstream,int pos);
};