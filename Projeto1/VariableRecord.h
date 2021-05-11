#ifndef __VARIABLE_RECORD__
#define __VARIABLE_RECORD__

#include <string>
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;
class VariableRecord
{
    public:
    VariableRecord(){return;};

    int readCSVLine(string line);
    int makeDeleted();

    int total_size;
    int nomedep_s, de_s, distr_s, mun_s, nomesc_s, ds_pais_s;
    int id;
    int tipoesc, n_alunos;
    double cod_esc;
    char * nomedep;
    char * de;  
    char * distr;
    char * mun;
    char * nomesc;
    char * ds_pais;





};
#endif
