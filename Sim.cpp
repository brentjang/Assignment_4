#include <iostream>
#include <fstream>
#include <algorithm>
#include "Sim.h"

using namespace std;

Sim::Sim()
{
    myQueue = new GenQueue<Student>();
    totalStudents = new GenDDL<Student>();
    windowIdle = new GenDDL<int>();
}

Sim::~Sim()
{
    delete myQueue;
    delete totalStudents;
    delete windowIdle;
}

void Sim::runSim(string name)
{
    bool flag = false;
    int line = 1;
    int numStudents, studentTime;
    int dequeueCount = 0;
    Student student;
    int master = 0;

    //check if the file is good
    if(!file.isFile(name))
    {
        return;
    }
    file.totalLines(); //get total file lines for end case
    read();

    //open array of windows
    openWindows = file.getLine(0);
    windowArray = new Window[openWindows];
    for(int i = 0; i < openWindows; i++)
    {
        Window window;
        windowArray[i] = window;
    }

    //main loop
    while(!flag)
    {
        cout << master << "|||||" << endl;;

        //add more students in the queue
        if(master == file.getLine(line))
        {
            line++;
            numStudents = file.getLine(line++);
            cout << "# next students: " << numStudents << endl;
            //insert students in queue
            for(int x = line; x < (line+numStudents); x++)
            {
                studentTime = file.getLine(x);
                student.setTimeNeeded(studentTime);
                myQueue->insert(student);
            }
            line = line + numStudents;
        }

        //update wait for students still in the queue
        if(!myQueue->isEmpty())
        {
            updateWait();
        }

        //dequeue students if window are open
        for(int y = 0; y < openWindows; y++)
        {
            //assign student to window
            if(windowArray[y].isOpen() && !myQueue->isEmpty())
            {
                Student s;
                s = myQueue->remove();
                dequeueCount++;
                totalStudents->insertFront(s); //store student for stats
                windowArray[y].setTimeBusy(s.getTimeNeeded());
            }
            //update busy time is window is closed
            else if(!windowArray[y].isOpen())
            {
                windowArray[y].decreaseBusy();
            }
            //update idle time is window is open and no students in the queue
            else if(myQueue->isEmpty())
            {
                windowArray[y].increaseIdle();
            }
            cout << windowArray[y].getTimeIdle() << '|';
        }
        cout << '\n';

        //print for visual
        for(int t = 0; t < openWindows; t++)
        {
            cout << windowArray[t].getTimeBusy() << '|';
        }
        cout << '\n';
        cout << '\n';

        //end loop case
        cout << dequeueCount << '|' << sumStudents << endl;
        if(dequeueCount == sumStudents)
        {
            for(int k = 0; k < openWindows; k++)
            {
                windowIdle->insertFront(windowArray[k].getTimeIdle()); //save window stats
            }
            printAll();
            flag = true;
        }
        master++;
    }
}

//initial read of the file to compute end case
void Sim::read()
{
    ifstream test(file.getFileName());
    int line = 2;
    sumStudents = 0;
    int numStudents = 0;
    while(line <= file.getTotalLines())
    {
        numStudents = file.getLine(line);
        sumStudents += numStudents;
        line = line + 2 + numStudents;
    }
}

//update waits of students in the queue
void Sim::updateWait()
{
    GenQueue<Student> copy;
    Student s;
    while(!myQueue->isEmpty())
    {
        s = myQueue->remove();
        s.increaseWait();
        copy.insert(s);
    }
    while(!copy.isEmpty())
    {
        s = copy.remove();
        myQueue->insert(s);
    }
}

//print summary statistics
void Sim::printAll()
{
    int numStudents = totalStudents->getSize();
    int studentStats[numStudents];
    int windowStats[openWindows];
    int idx = 0;

    double medianStudent = 0;
    double meanStudent = 0;
    double meanWindow = 0;
    int student10 = 0;
    int longestStudent = 0;
    int window5 = 0;
    int longestWindow = 0;
    int temp = 0;

    //copy stats to arrays for easier sorting and indexing
    while(!totalStudents->isEmpty())
    {
        studentStats[idx++] = totalStudents->removeBack().getTimeWaiting();
    }

    idx = 0;
    while(!windowIdle->isEmpty())
    {
        windowStats[idx++] = windowIdle->removeBack();
    }

    //STL sort
    sort(studentStats, studentStats + numStudents);
    sort(windowStats, windowStats + openWindows);

    cout << "Sorted Student Wait Times: ";
    for(int i = 0; i < numStudents; i++)
    {
        cout << studentStats[i] << '|';
    }
    cout << '\n';

    cout << "Sorted Window Idle Times: ";
    for(int i = 0; i < openWindows; i++)
    {
        cout << windowStats[i] << '|';
    }
    cout << '\n';

    //find median student wait
    if((numStudents%2) == 1)
    {
        medianStudent = (studentStats[(numStudents/2)]);
    }
    else
    {
        medianStudent = (studentStats[numStudents/2] + studentStats[(numStudents/2)-1]);
    }

    //mean student wait
    for(int i = 0; i < numStudents; i++)
    {
        temp += studentStats[i];
        //number of students over 10 min wait
        if(studentStats[i] >= 10)
        {
            student10++;
        }
    }
    meanStudent = double(temp)/double(numStudents);
    longestStudent = studentStats[numStudents-1];

    temp = 0;
    //mean window idle time
    for(int j = 0; j < openWindows; j++)
    {
        temp += windowStats[j];
        if(windowStats[j] >= 5)
        {
            window5++;
        }
    }
    meanWindow = double(temp)/double(openWindows);
    longestWindow = windowStats[openWindows-1];

    cout << "Total Number of Students: " << numStudents << endl;
    cout << "Mean Student Wait Time: " << meanStudent << endl;
    cout << "Median Student Wait Time: " << medianStudent << endl;
    cout << "Students Waiting Over 10 Minutes: " << student10 << endl;
    cout << "Longest Student Wait Time: " << longestStudent << endl;
    cout << "Mean Window Idle Time: " << meanWindow << endl;
    cout << "Window Idle Over 5 Minutes: " << window5 << endl;
    cout << "Longest Window Idle Time: " << longestWindow << endl;
}
