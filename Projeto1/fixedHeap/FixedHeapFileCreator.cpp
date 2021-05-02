#include "FixedHeapFileCreator.h"


FixedHeapFileCreator::FixedHeapFileCreator(string fileName, string newFileName) : FileCreator (fileName, newFileName)
{
    this->insertHeader();
    this->type = FixedHeap;
    this->addDict();
    
}

int FixedHeapFileCreator::insertHeader()
{
    if(this->openNewFileWriting() == -1)
    {
        cout << "Error opening the file for writing";
        this->closeNewFile();
        return -1;
    }
    this->newFile.seekg(0);
    this->newFile.write((char *) &(this->header), this->header.headerSize);
    this->closeNewFile();
    return 0;
}

int FixedHeapFileCreator::getHeader()
{   
    this->openNewFileReading();
    this->newFile.seekg(0);
    if (!this->newFile.read((char *) &(this->header), this->header.headerSize))
    {
        this->closeNewFile();
        return -1;
    }
    this->closeNewFile();
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

    stringstream ss(line);
    
    getline(ss, newRecord.nomedep, ',');
    ss.ignore();
    getline(ss, newRecord.de, ',');
    ss.ignore();
    getline(ss, newRecord.distr, ',');
    ss.ignore();
    getline(ss, newRecord.mun, ',');
    ss.ignore();
    ss >> newRecord.tipoesc;
    ss.ignore();
    ss >> newRecord.cod_esc;
    ss.ignore();
    getline(ss, newRecord.nomesc, ',');
    ss.ignore();
    getline(ss, newRecord.ds_pais, ',');
    ss.ignore();
    ss >> newRecord.n_alunos;

    return 0;
}

int FixedHeapFileCreator::insertRecords()
{
    int firstDeleted;
    FixedRecord newRecord;
    int numbers = 0;

    if (this->getHeader() == -1)
    {
        return -1;
    }

    this->openNewFileWriting();
    while(this->readCsvLine(newRecord) == 0)
    {
        newRecord.id = numbers++;
        this->newFile.write((char *) &newRecord, sizeof(newRecord));
        this->header.recordsAmount++;
    }   
    cout << endl;

    /*closed for reading*/
    this->closeNewFile();
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