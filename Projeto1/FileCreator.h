#include <fstream>
#include <string>
#include <iostream>
using namespace std;

typedef enum {FixedHeap} fileType;

class FileCreator
{
    public:
        FileCreator(string rawfileName, string newFileName);
        fstream rawDataFile, newFile, dictFile;
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