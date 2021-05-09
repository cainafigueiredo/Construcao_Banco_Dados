#ifndef __FILE_CREATOR__
#define __FILE_CREATOR__
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

typedef enum {FixedHeap, Ordered} fileType;

class FileCreator
{
    public:
        FileCreator(string rawfileName, string newFileName);
        fstream dictFile, schemaFile;
        fstream outNewFile;
        ifstream inNewFile, rawDataFile;
        string rawFileName, newFileName;
        int openRawFile();
        int closeRawFile();
        int createNewFile();
        int openNewFileReading();
        int openNewFileWriting();
        int closeNewFileWriting();
        int closeNewFileReading();
        virtual int insertHeader (){return 0;};
        virtual int insertRecords (){return 0;};
        virtual int getHeader (){return 0;};
        virtual int readCsvLine(){return 0;};
};
#endif