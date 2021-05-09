#ifndef _FILE_MANIPULATOR_
#define _FILE_MANIPULATOR_
#include <string>
#include <iostream>
#include <fstream>

using namespace std;


class FileManipulator
{
    public:
        FileManipulator(string filename);
        
        string fileName;
        ifstream fileRead;
        ofstream fileWrite;
        
        int openForReading();
        int openForWriting();
        int closeForReading();
        int closeForWriting();

        // virtual int findOne(int id){return 0;};

        bool between (int attribute, int first, int last);
        bool unique (int attribute, string value);
        bool unique (int attribute, int value);
        bool unique (int attribute, double value);
        int findAll();
        int select ();
        int deleteRecord ();
};
#endif