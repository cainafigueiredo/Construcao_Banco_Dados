#include "FileCreator.h"
#include "FixedRecord.h"
#include "fixedHeap/FixedHeapFileCreator.h"
#include "fixedHeap/FixedHeapHeader.h"
#include "fixedHeap/FixedHeapManipulator.h"
#include "orderedFile/orderedHeader.h"
#include "orderedFile/orderedFileCreator.h"
#include "orderedFile/orderedManipulator.h"
#include <iostream>



int teste_ordenacao(orderedManipulator &om)
{
    FixedRecord *rec_curr,*rec_prev;
    while((rec_curr = om.findNext()))
    {
        wrapper cur(om.ordered_by,rec_curr),prev(om.ordered_by,rec_prev);
        if(compare_records(cur,prev))
        {
            cout<<"ARQUIVO NÃO ORDENADO!"<<endl;
            return 0;
        }
        rec_prev = rec_curr;
    }
    cout<<"ARQUIVO ORDENADO!"<<endl;
    return 1;
}

int main ()
{
    char fileName[MAX_STRING_SIZE] = "teste.csv";
    char newFileName[MAX_STRING_SIZE] = "newFile_teste";
    char orderField[MAX_STRING_SIZE] = "NOMEDEP";
    
    orderedFileCreator<char[MAX_ORDERED_FIELD_SIZE]> a (fileName, newFileName,orderField);
    orderedManipulator teste("newFile_teste");
    a.insertRecords();
    a.getHeader();
    a.printHeader();
    // teste.findOne(3);
    cout<<"Codigo ordenacao "<<teste.ordered_by<<endl;
    teste.ordenateFile();
    teste_ordenacao(teste);
    return 0;
}
