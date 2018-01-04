#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdlib>
//#include <time.h>
#include <fstream>
#include <string>
using namespace std;

class TrainTable
{
public:
	//streampos prev;
	char departure_time[6];
	char destination_time[6];
	int number;
	char* day;
	char travel_time[6];
	int destination_station;
	int departure_station;
	int* travel_station;
	int count_station;
	//int next;

	TrainTable();//конструктор по умолчанию
	TrainTable(TrainTable&);
	TrainTable(int train_number, char Departure_time[], char Destination_time[], char Travel_time[], char* Day, int Destination_station, int Departure_station, int* Travel_station, int Count_station);//конструктор с параметрами
	~TrainTable();

	void Print();
	
	friend ostream& operator<< (ostream& os, TrainTable &p);
	friend istream& operator>> (istream& is, TrainTable &p);
	friend ofstream& operator<< (ofstream& os, TrainTable &p);
	friend ifstream& operator>> (ifstream& os, TrainTable &p);

	void write(ostream&);
	void read(istream&);
	void read(istream& Fstream,int pos);
};