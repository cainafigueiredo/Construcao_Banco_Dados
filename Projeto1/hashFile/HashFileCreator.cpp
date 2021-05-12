#include "HashFileCreator.h"


HashFileCreator::HashFileCreator(string fileName, string newFileName) : FileCreator (fileName, newFileName)
{
    this->insertHeader();
}

int HashFileCreator::insertHeader()
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

int HashFileCreator::getHeader()
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
int HashFileCreator::readCsvLine(HashFixedRecord &newRecord)
{
    string line;
    if (!getline(this->rawDataFile, line))
    {
        return -1;
    }

    newRecord.readCSVLine(line);

    return 0;
}

int HashFileCreator::insertRecords()
{
    HashFixedRecord newRecord;
    int numbers = 0;
    int bucket_id, block_addr, n_recordsInBlock, recordAddr;

    if (this->getHeader() == -1)
    {
        return -1;
    }

    this->openNewFileWriting();
    while(this->readCsvLine(newRecord) == 0)
    {
        newRecord.id = numbers++;
        bucket_id = this->header.hashFunction(newRecord.id);
        block_addr = this->header.buckets[bucket_id].block_addr;
        n_recordsInBlock = this->header.buckets[bucket_id].numberOfRecords;
        recordAddr = (block_addr * this->header.blockSize) + (n_recordsInBlock * sizeof(newRecord));

        this->outNewFile.seekp(sizeof(this->header) + recordAddr, ios::beg);
        
        this->outNewFile.write((char *) &newRecord, sizeof(newRecord));
        this->header.recordsAmount++;
        this->header.buckets[bucket_id].incrementNumberOfRecords();
    }
    // cout << endl;
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