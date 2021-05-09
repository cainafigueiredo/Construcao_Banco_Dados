#ifndef _FILE_MANIPULATOR_
#define _FILE_MANIPULATOR_
#include <string>
#include <iostream>

using namespace std;


class FileManipulator
{
    public:
        FileManipulator();
        
        bool between (int attribute, int first, int last);
        bool unique (int attribute, string value);
        bool unique (int attribute, int value);
        bool unique (int attribute, double value);
        int findAll();
        int finOne();
        int select ();
        int deleteRecord ();
};
#endif