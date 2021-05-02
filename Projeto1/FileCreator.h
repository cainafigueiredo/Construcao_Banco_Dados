#include <fstream>
#include <string>
#include <iostream>
using namespace std;

class FileCreator
{
    public:
        FileCreator(string rawfileName, string newFileName);
        fstream rawDataFile, newFile;
        string rawFileName, newFileName;
        int openRawFile();
        int openNewFileReading();
        int openNewFileWriting();
        int closeNewFile();
        virtual int insertHeader (){return 0;};
        virtual int insertRecords (){return 0;};
        virtual int getHeader (){return 0;};
        virtual int readCsvLine(){return 0;};
};