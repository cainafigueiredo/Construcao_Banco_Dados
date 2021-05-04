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
        fstream rawDataFile, newFile, dictFile, schemaFile;
        string rawFileName, newFileName;
        fileType type;
        int openRawFile();
        int openNewFileReading();
        int openNewFileWriting();
        int closeNewFile();
        int addDict();
        virtual int insertHeader (){return 0;};
        virtual int insertRecords (){return 0;};
        virtual int getHeader (){return 0;};
        virtual int readCsvLine(){return 0;};
};
#endif