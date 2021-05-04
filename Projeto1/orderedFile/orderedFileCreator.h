#ifndef __ORDERED_FILE_CREATOR__
#define __ORDERED_FILE_CREATOR__
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <forward_list>
#include "../FileCreator.h"
#include "orderedHeader.h"
#include "newFile_teste_class_gabarito.h"

using namespace std;

template <class T = int>
class orderedFileCreator : public FileCreator
{
    public:
        orderedFileCreator(string fileName, string newFileName, string order_by);
        orderedHeader<T> header;
        int insertHeader();
        int insertRecords();
        int addSchema(string _schema_);
        int getHeader();
        void printHeader();
        using FileCreator::readCsvLine;
        int readCsvLine(NEWFILE_TESTE_attr &newRecord);
};

//Supoe que o schema seja uma string no formato nome-tipo|nome-tipo|...|\n
template <class T>
int orderedFileCreator<T>::addSchema(string _schema_)
{
    this->schemaFile.open(this->newFileName.append("_schema.txt"), fstream::out);
    if (!this->schemaFile.good())
    {
        return -1;
    }
    this->schemaFile<<_schema_;
    this->schemaFile.close();
    return 0;
};

template <class T>
orderedFileCreator<T>::orderedFileCreator(string fileName, string newFileName, string order_by) : FileCreator (fileName, newFileName), header(newFileName.append("_extension\0"),order_by)
{
    this->insertHeader();
    this->type = Ordered;
    this->addDict();
    string schema;
    cout<<"Insira o schema da tabela no formato |nome_coluna-tipo|nome_coluna-tipo|...|\n";
    getline(cin,schema);
    cout<<schema<<endl;
    // addSchema(schema);
};

template <class T>
int orderedFileCreator<T>::insertHeader()
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
};

template <class T>
int orderedFileCreator<T>::getHeader()
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
};

template <class T>
void orderedFileCreator<T>::printHeader()
{  
    cout<<"\n----------\n"<<"Extension file " + this->header.extension_file + " Ordered By: " + 
    this->header.ordered_by + " Limit Value: " << this->header.limitValue <<endl;
};


template <class T>
/*considers first line already has data.*/
int orderedFileCreator<T>::readCsvLine(NEWFILE_TESTE_attr &newRecord)
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
};

template <class T>
int orderedFileCreator<T>::insertRecords()
{
    int firstDeleted;
    NEWFILE_TESTE_attr newRecord;
    int numbers = 0;

    if (this->getHeader() == -1)
    {
        return -1;
    }

    this->openNewFileWriting();
    while(this->readCsvLine(newRecord) == 0)
    {
        if(!numbers)
            cout<<sizeof(newRecord)<<endl;
        newRecord.id = numbers++;
        this->newFile.write((char *) &newRecord, sizeof(newRecord));
        this->header.recordsAmount++;
        cout<<"|"<<newRecord.nomedep<<"|"<<"|"<<newRecord.de<<"|"<<"|"<<newRecord.distr<<"|"<<"|"<<newRecord.mun<<"|"<<"|"<<newRecord.tipoesc<<"|"<<"|"<<newRecord.cod_esc<<"|"<<"|"<<newRecord.nomesc<<"|"<<"|"<<newRecord.ds_pais<<"|"<<"|"<<newRecord.n_alunos<<"|"<<"|"<<newRecord.id<<"|"<<endl; 

    }   

    /*closed for reading*/
    this->closeNewFile();
    this->insertHeader();

    return 0;

};
#endif