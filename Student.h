#include <iostream>

using namespace std;

class Student
{
public:
    Student();
    Student(int time);
    ~Student();
    void setTimeNeeded(int set);
    int getTimeNeeded();
    void increaseWait();
    int getTimeWaiting();
    friend ostream& operator<<(ostream& os, const Student& s); //overloaded

private:
    int timeNeeded;
    int timeWaiting;
};
