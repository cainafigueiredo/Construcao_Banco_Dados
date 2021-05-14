#ifndef __ORDERED_FILE_CREATOR__
#define __ORDERED_FILE_CREATOR__
#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <sstream>
#include "../FileCreator.h"
#include "orderedHeader.h"

using namespace std;

template <class T>
class orderedFileCreator : public FileCreator
{
    public:
        orderedFileCreator(char* fileName,char* newFileName,char* order_by);
        orderedHeader <char[MAX_ORDERED_FIELD_SIZE]> header;
        int insertHeader();
        int insertRecords();
        int getHeader();
        void printHeader();
        using FileCreator::readCsvLine;
        int readCsvLine(FixedRecord &newRecord);
};

template <class T>
orderedFileCreator<T>::orderedFileCreator(char* fileName,char* newFileName,char* order_by) : 
FileCreator (fileName, newFileName), header(strcat(newFileName,"_extension\0"),order_by)
{
    this->insertHeader();
};

template <class T>
int orderedFileCreator<T>::insertHeader()
{
    if(this->openNewFileWriting() == -1)
    {
        cout << "Error opening the file for writing";
        this->closeNewFileWriting();
        return -1;
    }
    this->outNewFile.seekp(0, ios::beg);
    this->outNewFile.write((char *) &(this->header), sizeof(this->header));
    this->closeNewFileWriting();
    return 0;
};

template <class T>
int orderedFileCreator<T>::getHeader()
{   
    this->openNewFileReading();
    this->inNewFile.seekg(0, ios::beg);
    if (!this->inNewFile.read((char *) &(this->header), this->header.headerSize))
    {
        this->closeNewFileReading();
        return -1;
    }
    this->closeNewFileReading();
    return 0;
};

template <class T>
void orderedFileCreator<T>::printHeader()
{  
    cout<<"\n----------\n"<<"Extension file " << this->header.extension_file << " Ordered By: " << 
    this->header.ordered_by << " Limit Value: " << this->header.limitValue <<endl;
};


template <class T>
/*considers first line already has data.*/
int orderedFileCreator<T>::readCsvLine(FixedRecord &newRecord)
{
    string line;
    if (!getline(this->rawDataFile, line))
    {
        return -1;
    }

    newRecord.readCSVLine(line);

    return 0;
}

template <class T>
int orderedFileCreator<T>::insertRecords()
{
    FixedRecord newRecord;
    int numbers = 0;

    if (this->getHeader() == -1)
    {
        return -1;
    }

    this->openNewFileWriting();
    this->outNewFile.seekp(sizeof(this->header), ios::beg);
    while(this->readCsvLine(newRecord) == 0)
    {
        newRecord.id = numbers++;
        this->outNewFile.write((char *) &newRecord, sizeof(newRecord));
        this->header.recordsAmount++;
    }
    this->header.lastID = header.recordsAmount - 1;
    this->closeRawFile();
    this->closeNewFileWriting();
    this->insertHeader();
 
    return 0;

}

#endif