#include "FixedRecord.h"

int FixedRecord::readCSVLine(string line)
{
    char str[line.size()];
    strncpy(str, line.c_str(), line.size());
    strncpy(this->nomedep, strtok(str, ","), MAX_STRING_SIZE);
    strncpy(this->de, strtok(NULL, ","), MAX_STRING_SIZE);
    strncpy(this->distr, strtok(NULL, ","), MAX_STRING_SIZE);
    strncpy(this->mun, strtok(NULL, ","), MAX_STRING_SIZE);
    this->tipoesc = strtoul(strtok(NULL, ","), NULL, 10);
    this->cod_esc = strtod(strtok(NULL, ","), NULL);
    strncpy(this->nomesc, strtok(NULL, ","), MAX_STRING_SIZE);
    strncpy(this->ds_pais, strtok(NULL, ","), MAX_STRING_SIZE);
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

int FixedRecord::isDeleted()
{
    return this->id == -1;
}