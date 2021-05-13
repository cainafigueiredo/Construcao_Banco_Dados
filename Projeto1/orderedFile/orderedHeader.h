#ifndef __ORDERED_HEADER__
#define __ORDERED_HEADER__
#include <type_traits>
#include <cstring>
#include "../FixedRecord.h"

using namespace std;

template <class T = int>
class orderedHeader : public FileHeader 
{
    public:
        orderedHeader(char* extension_filename, char* order_by);
        int headerSize;
        int recordSize;
        //lista encadeada que mantém a posicao (offset) de todos os registros que foram deletados
        int freeList;
        //nome do arquivo de extensão 
        char extension_file[MAX_STRING_SIZE];
        //nome do campo utilizado pela ordenacao
        char ordered_by[MAX_STRING_SIZE];
        //valor do maior (menor) campo. Foi usado template pois pode ser string, int...
        T limitValue;
        int recordsAmount;
        int lastID;
};

template <class T>
orderedHeader<T>::orderedHeader(char* extension_filename, char* order_by)
{
    this->headerSize = sizeof(*this);
    this->recordSize = sizeof(FixedRecord);
    strcpy(this->extension_file,extension_filename);
    strcpy(this->ordered_by,order_by);
    this->limitValue = T();
    this->recordsAmount = 0;
    this->fileOrganization = Ordered;
};

#endif