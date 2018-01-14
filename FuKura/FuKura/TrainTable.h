#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "MyTime.h"

#define MAX_CHAR 255
#define MAX_INT 100

using namespace std;

class TrainTable
{
public:
	MyTime departure;
	MyTime travel;
	MyTime destination;
	int number;
	char day[MAX_CHAR];
	int destination_station;
	int departure_station;
	int travel_station[MAX_INT];
	int count_station;

	TrainTable();//конструктор по умолчанию
	TrainTable(const TrainTable&);
	TrainTable(int train_number, MyTime Departure, MyTime Destination, MyTime Travel, char* Day, int Destination_station, int Departure_station, int* Travel_station, int Count_station);//конструктор с параметрами
	~TrainTable();

	void Print();
	
	friend ostream& operator<< (ostream& os, TrainTable &p);
	friend istream& operator>> (istream& is, TrainTable &p);
	friend ofstream& operator<< (ofstream& os, TrainTable &p);
	friend ifstream& operator>> (ifstream& os, TrainTable &p);

	void operator = (const TrainTable&);
	int size();
	void consoleRead();
	void write(ostream&);
	void read(istream&);
	void read(istream& Fstream,int pos);
};