#include "VariableRecord.h"


int VariableRecord::readCSVLine(string line)
{
    char str[line.size()];
    string tmp;
    strcpy(str, line.c_str());

    tmp = strtok(str, ",");
    this->nomedep_s = tmp.size();
    this->nomedep = (char *) malloc (sizeof(char)*this->nomedep_s);
    strcpy(this->nomedep, tmp.c_str());


    tmp = strtok(NULL, ",");
    this->de_s = tmp.size();
    this->de = (char *) malloc (sizeof(char)*this->de_s);
    strcpy(this->de, tmp.c_str());

    tmp = strtok(NULL, ",");
    this->distr_s = tmp.size();
    this->distr = (char *) malloc (sizeof(char)*this->distr_s);
    strcpy(this->distr, tmp.c_str());

    tmp = strtok(NULL, ",");
    this->mun_s = tmp.size();
    this->mun = (char *) malloc (sizeof(char)*this->mun_s);
    strcpy(this->mun, tmp.c_str());


    this->tipoesc = strtoul(strtok(NULL, ","), NULL, 10);
    this->cod_esc = strtod(strtok(NULL, ","), NULL);

    tmp = strtok(NULL, ",");
    this->nomesc_s = tmp.size();
    this->nomesc = (char *) malloc (sizeof(char)*this->nomesc_s);
    strcpy(this->nomesc, tmp.c_str());

    tmp = strtok(NULL, ",");
    this->ds_pais_s = tmp.size();
    this->ds_pais = (char *) malloc (sizeof(char)*this->ds_pais_s);
    strcpy(this->ds_pais, tmp.c_str());

    this->n_alunos = strtoul(strtok(NULL, "\0"), NULL, 10);

    this->total_size = 10*sizeof(int) +sizeof(double)+this->nomedep_s+ 
    this->de_s + this->distr_s + this->mun_s + this->nomesc_s + this->ds_pais_s;

    return 0;
}

int VariableRecord::makeDeleted()
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