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
    this->outNewFile.seekp(sizeof(this->header), ios::beg);
    while(this->readCsvLine(newRecord) == 0)
    {
        newRecord.id = numbers++;
        this->outNewFile.write((char *) &newRecord, sizeof(newRecord));
        this->header.recordsAmount++;
    }
    // cout << endl;

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