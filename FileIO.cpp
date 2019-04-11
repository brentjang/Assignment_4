#include "FileIO.h"
#include <iostream>
#include <fstream>

using namespace std;

FileIO::FileIO()
{
    lineCount = 0;
    allLines = 0;
    fileName = "";
}

FileIO::~FileIO()
{

}

bool FileIO::isFile(string name)
{
    ifstream file(name);
    if(!file.good())
    {
        cout << "Not a file." << endl;
        return false;
    }
    //check if the file is empty
    else if(file.peek() == ifstream::traits_type::eof())
    {
        cout << "File is empty." << endl;
        return false;
    }
    else
    {
        fileName = name;
    }
    return true;
}

//gets next int at a given line
int FileIO::getLine(int lines)
{
    if(isFile(fileName))
    {
        ifstream file(fileName);
        string line;
        int currLine = 0;
        int out;
        while(getline(file, line))
        {
            out = stoi(line);
            if(currLine == lines)
            {
                break;
            }
            currLine++;
        }
        return out;
    }
}

//compute line count in a file
void FileIO::totalLines()
{
    ifstream file(fileName);
    string line;
    while(getline(file, line))
    {
        allLines++;
    }
}

int FileIO::getTotalLines()
{
    return allLines;
}

string FileIO::getFileName()
{
    return fileName;
}
