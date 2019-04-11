#include <iostream>
using namespace std;

class FileIO
{
public:
    FileIO();
    ~FileIO();
    bool isFile(string name);
    int getLine(int line);
    void totalLines();
    int getTotalLines();
    string getFileName();

private:
    int lineCount;
    int allLines;
    string fileName;
};
