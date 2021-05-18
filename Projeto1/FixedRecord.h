#ifndef __FIXED_RECORD__
#define __FIXED_RECORD__

#include <string>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iostream>
#define MAX_STRING_SIZE  64


using namespace std;

class FixedRecord
{
    public:
    
    FixedRecord(){return;};

    int readCSVLine(string line, bool hasId = false);
    int makeDeleted();
    int isDeleted();
    void getRecordFieldsAsCSV(char * out, int numberOfCharacters, bool hasId = false);

    int id;
    char nomedep[MAX_STRING_SIZE], de[MAX_STRING_SIZE], distr[MAX_STRING_SIZE],
    mun[MAX_STRING_SIZE], nomesc[MAX_STRING_SIZE], ds_pais[MAX_STRING_SIZE];
    int tipoesc, n_alunos;
    double cod_esc;
};

#endif