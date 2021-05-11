#include "VariableHeapFileCreator.h"


VariableHeapFileCreator::VariableHeapFileCreator(string fileName, string newFileName) : FileCreator (fileName, newFileName)
{
    this->insertHeader();
}

int VariableHeapFileCreator::insertHeader()
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

int VariableHeapFileCreator::getHeader()
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
int VariableHeapFileCreator::readCsvLine(VariableRecord &newRecord)
{
    string line;
    if (!getline(this->rawDataFile, line))
    {
        return -1;
    }

    newRecord.readCSVLine(line);

    return 0;
}

int VariableHeapFileCreator::insertRecords()
{
    int firstDeleted;
    VariableRecord newRecord;
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

        this->outNewFile.write((char *) &newRecord.total_size, sizeof(int));
        this->outNewFile.write((char *) &newRecord.nomedep_s, sizeof(int));
        this->outNewFile.write((char *) &newRecord.de_s, sizeof(int));
        this->outNewFile.write((char *) &newRecord.distr_s, sizeof(int));
        this->outNewFile.write((char *) &newRecord.mun_s, sizeof(int));
        this->outNewFile.write((char *) &newRecord.nomesc_s, sizeof(int));
        this->outNewFile.write((char *) &newRecord.ds_pais_s, sizeof(int));
        this->outNewFile.write((char *) &newRecord.id, sizeof(int));
        this->outNewFile.write((char *) &newRecord.tipoesc, sizeof(int));
        this->outNewFile.write((char *) &newRecord.n_alunos, sizeof(int));
        this->outNewFile.write((char *) &newRecord.cod_esc, sizeof(double));

        this->outNewFile.write(newRecord.nomedep, newRecord.nomedep_s);
        this->outNewFile.write( newRecord.de, newRecord.de_s);
        this->outNewFile.write( newRecord.distr, newRecord.distr_s);
        this->outNewFile.write( newRecord.mun, newRecord.mun_s);
        this->outNewFile.write( newRecord.nomesc, newRecord.nomesc_s);
        this->outNewFile.write( newRecord.ds_pais, newRecord.ds_pais_s);
        
        
        
        this->header.recordsAmount++;

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



