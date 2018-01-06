#include <fstream>
using namespace std;

class MyTime
{
public:
	int hour, minute;
	MyTime();
	MyTime(int hour, int minute);
	MyTime(MyTime& MyTime);
	~MyTime();
	void write(ofstream& stream);
	void read(ifstream& stream);
	friend ostream& operator<< (ostream& os, MyTime& MyTime);
	void operator = (MyTime& MyTime);
};

