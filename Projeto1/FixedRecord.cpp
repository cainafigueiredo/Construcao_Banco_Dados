#include "FixedRecord.h"

int FixedRecord::readCSVLine(string line)
{
    char str[line.size()];
    strcpy(str, line.c_str());
    strcpy(this->nomedep, strtok(str, ","));
    strcpy(this->de, strtok(NULL, ","));
    strcpy(this->distr, strtok(NULL, ","));
    strcpy(this->mun, strtok(NULL, ","));
    this->tipoesc = strtoul(strtok(NULL, ","), NULL, 10);
    this->cod_esc = strtod(strtok(NULL, ","), NULL);
    strcpy(this->nomesc, strtok(NULL, ","));
    strcpy(this->ds_pais, strtok(NULL, ","));
    this->n_alunos = strtoul(strtok(NULL, "\0"), NULL, 10);

    return 0;
}

int FixedRecord::makeDeleted()
{
    this->id = -1;
    this->tipoesc = -1;
    this->n_alunos = -1;
    this->cod_esc = -1.0;
    strcpy(this->de, "DELETED");
    strcpy(this->distr, "DELETED");
    strcpy(this->ds_pais, "DELETED");
    strcpy(this->mun, "DELETED");
    strcpy(this->nomedep, "DELETED");
    strcpy(this->nomesc, "DELETED");

    return 0;
}