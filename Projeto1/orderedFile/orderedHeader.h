#include <forward_list>
#include <type_traits>
#include <string>
#include "../FixedRecord.h"

using namespace std;

template <class T = int>
class orderedHeader
{
    public:
        orderedHeader(string extension_filename = "newFile_teste_extension", string order_by = "nothing");
        int headerSize;
        int recordSize;
        //lista encadeada que mantém a posicao (offset) de todos os registros que foram deletados
        forward_list<int> freeList;
        //nome do arquivo de extensão 
        string extension_file;
        //nome do campo utilizado pela ordenacao
        string ordered_by;
        //valor do maior (menor) campo. Foi usado template pois pode ser string, int...
        T limitValue;
        int recordsAmount;
};

template <class T>
orderedHeader<T>::orderedHeader(string extension_filename, string order_by)
{
    extension_filename.resize(FILENAME_MAX);
    order_by.resize(MAX_STRING_SIZE);
    this->headerSize = sizeof(*this);
    this->recordSize = sizeof(FixedRecord);
    this->extension_file = extension_filename;
    this->ordered_by = order_by;
    this->limitValue = T();
    // if(is_same<type(this->limitValue), string>)
    // {
    //     this->limitValue.resize(MAX_STRING_SIZE);    
    // }
    this->recordsAmount = 0;
};