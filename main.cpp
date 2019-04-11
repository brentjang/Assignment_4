#include "Sim.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    Sim sim;
    string input;
    if(argc == 2)
    {
        input = argv[1];
        sim.runSim(input);
    }
    else
    {
        cout << "Invalid Arguements." << endl;
    }
    return 0;
}
