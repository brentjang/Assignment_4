#include "Student.h"
#include <iostream>
#include <fstream>

using namespace std;

Student::Student()
{
    timeNeeded = 0;
    timeWaiting = 0;
}

Student::Student(int time)
{
    timeNeeded = time;
}

Student::~Student()
{

}

void Student::setTimeNeeded(int set)
{
    timeNeeded = set;
}
int Student::getTimeNeeded()
{
    return timeNeeded;
}

void Student::increaseWait()
{
    timeWaiting++;
}

int Student::getTimeWaiting()
{
    return timeWaiting;
}

//overloaded operator to print student class
ostream& operator<<(ostream& os, const Student& s)
{
    os << s.timeNeeded;
    return os;
}
