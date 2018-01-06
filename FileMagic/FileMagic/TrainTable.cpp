#include "stdafx.h"
#include <string.h>

TrainTable::TrainTable(int train_number, MyTime Departure, MyTime Destination, MyTime Travel, char* Day, int Destination_station, int Departure_station, int* Travel_station, int Count_station)
{
	int i;
	number = train_number;
	departure = Departure;
	day = new char[strlen(Day)+1];
	strcpy(day, Day);
	destination = Destination;
	travel = Travel;
	departure_station = Departure_station;
	destination_station = Destination_station;
	count_station = Count_station;
	travel_station = new int[count_station];
	for (i = 0; i < count_station; i++)
		travel_station[i] = Travel_station[i];
}

TrainTable::TrainTable(TrainTable& obj)
{
	int i;
	number = obj.number;
	departure = obj.departure;
	day = new char[strlen(obj.day)+1];
	strcpy(day, obj.day);
	destination = obj.destination;
	travel = obj.travel;
	departure_station = obj.departure_station;
	destination_station = obj.destination_station;
	count_station = obj.count_station;
	travel_station = new int[count_station];
	for (i = 0; i < count_station; i++)
		travel_station[i] = obj.travel_station[i];
}

TrainTable::TrainTable()
{
	number = 0;
	destination_station = 0;
	departure_station = 0;
	travel_station = nullptr;
	day = nullptr;
}

TrainTable::~TrainTable()
{
	if (travel_station != nullptr)
	{
		delete[] travel_station;
	}
	if (day!=nullptr)
	{
		delete[] day;
	}
	//cout << "Деструктор работает" << endl;
}

void TrainTable::Print()
{
	int i, buffer;
	cout << endl << "Номер поезда: " << number << endl
		<< "Время отправления: " << departure << endl
		<< "Время прибытия: " << destination << endl
		<< "Время в пути: " << travel << endl
		<< "Станция отправления: " << departure_station << endl
		<< "Станция прибытия: " << destination_station << endl
		<< "Дни недели: " << day << endl
		<< "Промежуточные станции: ";
	for (i = 0; i < count_station; i++)
	{
		buffer = travel_station[i];
		cout << buffer << " ";
	}
	cout << endl;
}

ostream& operator<< (ostream& os, TrainTable &p) 
{
	int i;
	os << endl << "Номер поезда: " << p.number << endl
		<< "Время отправления: " << p.departure << endl
		<< "Время прибытия: " << p.destination << endl
		<< "Время в пути: " << p.travel << endl
		<< "Станция отправления: " << p.departure_station << endl
		<< "Станция прибытия: " << p.destination_station << endl
		<< "Дни недели: " << p.day << endl
		<< "Промежуточные станции: ";
	for (i = 0; i < p.count_station; i++)
		os << (p.travel_station[i])<< " ";
	os << endl;
	return os;
}

/*istream& operator>> (istream& is, TrainTable &p) {
	is >> p.train >> p.MyTime;
	return is;
}

ofstream& operator <<(ofstream& os, TrainTable &p)
{
	os << p.train << " " << p.MyTime;
	return os;
}
ifstream& operator>>(ifstream& is, TrainTable &p)
{
	is >> p.train >> p.MyTime;
	return is;
}
*/


void TrainTable::operator = (TrainTable& obj)
{
	int i;
	number = obj.number;
	departure = obj.departure;
	day = new char[strlen(obj.day) + 1];
	strcpy(day, obj.day);
	destination = obj.destination;
	travel = obj.travel;
	departure_station = obj.departure_station;
	destination_station = obj.destination_station;
	count_station = obj.count_station;
	travel_station = new int[count_station];
	for (i = 0; i < count_station; i++)
		travel_station[i] = obj.travel_station[i];
}


void TrainTable::write(ostream& os)
{
	int i;
	os.write(reinterpret_cast<const char*>(&number), sizeof(int));
	os.write(reinterpret_cast<const char*>(&departure), sizeof(MyTime));
	os.write(reinterpret_cast<const char*>(&destination), sizeof(MyTime));
	os.write(reinterpret_cast<const char*>(&travel), sizeof(MyTime));
	os.write(reinterpret_cast<const char*>(&departure_station), sizeof(int));
	os.write(reinterpret_cast<const char*>(&destination_station), sizeof(int));
	os.write(reinterpret_cast<const char*>(&count_station),sizeof(int));
	for (i = 0; i < count_station; i++)
	{
		os.write(reinterpret_cast<const char*>(&(travel_station[i])), sizeof(int));
	}
	i = strlen(day);
	os.write(reinterpret_cast<const char*>(&i), sizeof(int));
	os.write(reinterpret_cast<const char*>(&day), sizeof(char)*(i+1));
}

void TrainTable::read(istream &is)
{
	int i;
	if (day != nullptr) delete[]day;
	if (travel_station != nullptr) delete[]travel_station;
	is.read(reinterpret_cast<char*>(&number), sizeof(int));
	is.read(reinterpret_cast<char*>(&departure), sizeof(MyTime));
	is.read(reinterpret_cast<char*>(&destination), sizeof(MyTime));
	is.read(reinterpret_cast<char*>(&travel), sizeof(MyTime));
	is.read(reinterpret_cast<char*>(&departure_station), sizeof(int));
	is.read(reinterpret_cast<char*>(&destination_station), sizeof(int));
	is.read(reinterpret_cast<char*>(&count_station), sizeof(int));
	travel_station = new int[count_station];
	for (i = 0; i < count_station; i++)
	{
		is.read(reinterpret_cast<char*>(&(travel_station[i])), sizeof(int));
	}
	is.read(reinterpret_cast<char*>(&i), sizeof(int));
	day = new char[i + 1];
	is.read(reinterpret_cast<char*>(&day), sizeof(char)*(i+1));
}