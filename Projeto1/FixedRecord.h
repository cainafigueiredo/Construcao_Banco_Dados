#ifndef __FIXED_RECORD__
#define __FIXED_RECORD__

#include <string>
#include <stdio.h>
#include <string.h>
#include <iostream>
#define MAX_STRING_SIZE  64

using namespace std;

class FixedRecord
{
    public:
    
    FixedRecord(){return;};

    int readCSVLine(string line);
    int makeDeleted();

    int id;
    char nomedep[MAX_STRING_SIZE], de[MAX_STRING_SIZE], distr[MAX_STRING_SIZE],
    mun[MAX_STRING_SIZE], nomesc[MAX_STRING_SIZE], ds_pais[MAX_STRING_SIZE];
    int tipoesc, n_alunos;
    double cod_esc;
};

class HashFixedRecord : public FixedRecord 
{
    public:
        HashFixedRecord() : FixedRecord(){this->nextRecord = -1;};
        int nextRecord;
};

#endif