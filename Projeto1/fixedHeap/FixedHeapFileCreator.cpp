#include "FixedHeapFileCreator.h"


FixedHeapFileCreator::FixedHeapFileCreator(string fileName, string newFileName) : FileCreator (fileName, newFileName)
{
    this->insertHeader();
}

int FixedHeapFileCreator::insertHeader()
{
    if(this->openNewFileWriting() == -1)
    {
        this->closeNewFileWriting();
        cout << "Error opening the file for writing";
        return -1;
    }
    this->outNewFile.seekp(0, ios::beg);
    this->outNewFile.write((char *) &(this->header), sizeof(this->header));
    this->closeNewFileWriting();
    return 0;
}

int FixedHeapFileCreator::getHeader()
{   
    this->openNewFileReading();
    this->inNewFile.seekg(0, ios::beg);
    if (!this->inNewFile.read((char *) &(this->header), sizeof(this->header)))
    {
        this->closeNewFileReading();
        return -1;
    }
    this->closeNewFileReading();
    return 0;
}

/*considers first line already has data.*/
int FixedHeapFileCreator::readCsvLine(FixedRecord &newRecord)
{
    string line;
    if (!getline(this->rawDataFile, line))
    {
        return -1;
    }

    newRecord.readCSVLine(line);

    return 0;
}

int FixedHeapFileCreator::insertRecords()
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

/*CODE FOR THE MANAGER*/
/*    if (!this->header.freeList.empty())
    {
        firstDeleted = this->header.freeList.front();
        this->header.freeList.pop_front();
    }
*/