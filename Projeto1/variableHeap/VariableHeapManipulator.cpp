#include "VariableHeapManipulator.h"

int VariableHeapManipulator::readRecords(int offset, VariableRecord * Record)
{   
    this->fileRead.open(this->fileName, fstream::in | fstream::binary);
    this->fileRead.seekg(offset, ios::beg);
    int ts;
    this->fileRead.read(reinterpret_cast<char*>(&ts), 4);
    Record->total_size = ts;
    int ns; 
    this->fileRead.read(reinterpret_cast<char*>(&ns), 4);
    Record->nomedep_s = ns; 
    int ds; 
    this->fileRead.read(reinterpret_cast<char*>(&ds), 4);
    Record->de_s = ds;
    int dis; 
    this->fileRead.read(reinterpret_cast<char*>(&dis), 4);
    Record->distr_s = dis;
    int mus; 
    this->fileRead.read(reinterpret_cast<char*>(&mus), 4);
    Record->mun_s = mus;
    int nom; 
    this->fileRead.read(reinterpret_cast<char*>(&nom), 4);
    Record->nomesc_s = nom; 
    int dsp; 
    this->fileRead.read(reinterpret_cast<char*>(&dsp), 4);
    Record->ds_pais_s = dsp;
    int id, tipoesc, n_alunos;
    this->fileRead.read(reinterpret_cast<char*>(&id), 4);
    this->fileRead.read(reinterpret_cast<char*>(&tipoesc), 4);
    this->fileRead.read(reinterpret_cast<char*>(&n_alunos), 4);
    Record->id = id;
    Record->tipoesc = tipoesc;
    Record->n_alunos = n_alunos;
    double cod_esc;
    this->fileRead.read(reinterpret_cast<char*>(&cod_esc), 8);
    Record->cod_esc = cod_esc;
    char nomedep[Record->nomedep_s], de[Record->de_s] ,
    distr[Record->distr_s], mun[Record->mun_s],
    nomesc[Record->nomesc_s] , ds_pais[Record->ds_pais_s];


    this->fileRead.read(reinterpret_cast<char*> (&nomedep), ns);
    this->fileRead.read(reinterpret_cast<char*> (&de), ds);
    this->fileRead.read(reinterpret_cast<char*> (&distr), dis);
    this->fileRead.read(reinterpret_cast<char*> (&mun), mus);
    this->fileRead.read(reinterpret_cast<char*> (&nomesc), nom);
    this->fileRead.read(reinterpret_cast<char*> (&ds_pais), dsp);


    Record->nomedep = nomedep;
    //printf ("%s \n" , Record.nomedep);
    //printf ("%d \n" , Record.nomedep_s);
    Record->de = de;
    //printf ("%s \n" , Record.de);
    //printf ("%d \n" , Record.de_s);
    Record->distr = distr;
    //printf ("%s \n" , Record.distr);
    //printf ("%d \n" , Record.distr_s);
    Record->mun = mun;
    //printf ("%s \n" , Record.mun);
    //printf ("%d \n" , Record.mun_s);
    Record->nomesc = nomesc;
    //printf ("%s \n" , Record.nomesc);
    //printf ("%d \n" , Record.nomesc_s);
    Record->ds_pais = ds_pais;
    //printf ("%s \n" , Record.ds_pais);
    //printf ("%d \n" , Record.ds_pais_s);

    this->fileRead.close();





    return 0;
}
