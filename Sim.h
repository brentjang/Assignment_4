#include <iostream>
#include "FileIO.h"
#include "Window.h"
#include "Student.h"
#include "GenQueue.h"

using namespace std;

class Sim
{
public:
    Sim();
    ~Sim();
    void runSim(string name);
    void read();
    void updateWait();
    void printAll();

private:
    int openWindows;
    int sumStudents;
    Window* windowArray;
    GenQueue<Student> *myQueue;
    GenDDL<Student> *totalStudents;
    GenDDL<int> *windowIdle;
    FileIO file;
};
