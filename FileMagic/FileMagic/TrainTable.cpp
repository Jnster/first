#include "stdafx.h"
#include <string.h>

TrainTable::TrainTable(int train_number, char Departure_time[], char Destination_time[], char* Travel_time, char* Day, int Destination_station, int Departure_station, int* Travel_station, int Count_station)
{
	int i;
	number = train_number;
	strcpy(departure_time, Departure_time);
	day = new char[strlen(Day)+1];
	strcpy(day, Day);
	strcpy(destination_time, Destination_time);
	strcpy(travel_time, Travel_time);
	departure_station = Departure_station;
	destination_station = Destination_station;
	count_station = Count_station;
	travel_station = new int[count_station];
	for (i = 0; i < count_station; i++)
		travel_station[i] = Travel_station[i];
	//travel_station -= (i - 1);
}

//ДОДЕЛАААААТТЬЬ=================================================
TrainTable::TrainTable(TrainTable& obj)
{
	int i;
	number = obj.number;
	strcpy(departure_time, obj.departure_time);
	day = new char[strlen(obj.day)+1];
	strcpy(day, obj.day);
	strcpy(destination_time, obj.destination_time);
	strcpy(travel_time, obj.travel_time);
	departure_station = obj.departure_station;
	destination_station = obj.destination_station;
	travel_station = new int[3];
	count_station = obj.count_station;
	for (i = 0; i < count_station; i++)
		travel_station[i] = obj.travel_station[i];
}
//===============================================================

TrainTable::TrainTable()
{
	departure_time[0] = '\0';
	number = 0;
	destination_station = 0;
	departure_station = 0;
	destination_time[0] = '\0';
	travel_station = nullptr;
	travel_time[0] = '\0';
	day = nullptr;
}
/*
TrainTable::TrainTable(const TrainTable &second_object)
{
	number = second_object.number;
	strcpy(departure_time, second_object.departure_time);
	strcpy(day, second_object.day);
	strcpy(destination_time, second_object.destination_time);
	strcpy(travel_time, second_object.travel_time);
	departure_station = second_object.departure_station;
	destination_station = second_object.destination_station;
	travel_station = second_object.travel_station;
}
*/
TrainTable::~TrainTable()
{
	if (travel_station != nullptr)
	{
		delete[] travel_station;
		//travel_station = nullptr;
	}
	if (day!=nullptr)
	{
		delete[] day;
		//day = nullptr;
	}
	//cout << "Деструктор работает" << endl;
}

void TrainTable::Print()
{
	int i, buffer;
	cout << endl << "Номер поезда: " << number << endl
		<< "Время отправления: " << departure_time << endl
		<< "Время прибытия: " << destination_time << endl
		<< "Время в пути: " << travel_time << endl
		<< "Станция отправления: " << departure_station << endl
		<< "Станция прибытия: " << destination_station << endl
		<< "Дни недели: " << day << endl
		<< "Промежуточные станции: ";
	for (i = 0; i < count_station; i++)
	{
		buffer = travel_station[i];
		cout << buffer << " ";
	}
		//cout<< *(travel_station+i)<<" ";
	cout << endl;
}

ostream& operator<< (ostream& os, TrainTable &p) 
{
	int i;
	os << endl << "Номер поезда: " << p.number << endl
		<< "Время отправления: " << p.departure_time << endl
		<< "Время прибытия: " << p.destination_time << endl
		<< "Время в пути: " << p.travel_time << endl
		<< "Станция отправления: " << p.departure_station << endl
		<< "Станция прибытия: " << p.destination_station << endl
		<< "Дни недели: " << p.day << endl
		<< "Промежуточные станции: ";
	for (i = 0; i < p.count_station; i++)
		os << p.travel_station[i]<< " ";
	os << endl;
	return os;
}

/*istream& operator>> (istream& is, TrainTable &p) {
	is >> p.train >> p.time;
	return is;
}

ofstream& operator <<(ofstream& os, TrainTable &p)
{
	os << p.train << " " << p.time;
	return os;
}
ifstream& operator>>(ifstream& is, TrainTable &p)
{
	is >> p.train >> p.time;
	return is;
}
*/


void TrainTable::write(ostream& os)
{
	int i, buffer;
	os.write(reinterpret_cast<const char*>(&number), sizeof(int));
	os.write(reinterpret_cast<const char*>(&departure_time), sizeof(char)*6);
	os.write(reinterpret_cast<const char*>(&destination_time), sizeof(char)*6);
	os.write(reinterpret_cast<const char*>(&travel_time), sizeof(char)*6);
	os.write(reinterpret_cast<const char*>(&departure_station), sizeof(int));
	os.write(reinterpret_cast<const char*>(&destination_station), sizeof(int));
	os.write(reinterpret_cast<const char*>(&count_station),sizeof(int));
	for (i = 0; i < count_station; i++)
	{
		buffer = travel_station[i];
		os.write(reinterpret_cast<const char*>(&buffer), sizeof(int));
	}
	i = strlen(day);
	os.write(reinterpret_cast<const char*>(&i), sizeof(int));
	os.write(reinterpret_cast<const char*>(&day), sizeof(char)*(i+1));
}

void TrainTable::read(istream &is)
{
	int i, buffer;
	is.read(reinterpret_cast<char*>(&number), sizeof(int));
	is.read(reinterpret_cast<char*>(&departure_time), sizeof(char) * 6);
	is.read(reinterpret_cast<char*>(&destination_time), sizeof(char) * 6);
	is.read(reinterpret_cast<char*>(&travel_time), sizeof(char) * 6);
	
	is.read(reinterpret_cast<char*>(&departure_station), sizeof(int));
	is.read(reinterpret_cast<char*>(&destination_station), sizeof(int));
	is.read(reinterpret_cast<char*>(&count_station), sizeof(int));
	travel_station = new int[count_station];
	for (i = 0; i < count_station; i++)
	{
		is.read(reinterpret_cast<char*>(&buffer), sizeof(int));
		travel_station[i] = buffer;
	}
	is.read(reinterpret_cast<char*>(&i), sizeof(int));
	day = new char[i + 1];
	is.read(reinterpret_cast<char*>(&day), sizeof(char)*(i+1));
}