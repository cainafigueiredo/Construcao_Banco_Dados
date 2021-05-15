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
    cout<<"checking ordered file"<<endl;
    // rec_prev = om.findNext();
    om.currPos = 0;
    rec_prev = om.findNext();
    rec_curr = om.findNext();
    while(!strcmp(rec_curr->de,""))
    {
        wrapper cur(om.ordered_by,rec_curr),prev(om.ordered_by,rec_prev);
        if(compare_records(prev,cur) != true)
        {
            cout<<"ARQUIVO NÃO ORDENADO!"<<endl;
            return 0;
        }
        rec_prev = rec_curr;
        // cout<<rec_curr->de<<endl;
        rec_curr = om.findNext();
        // cout<<"|"<<rec_curr<<"|"<<endl;
    }
    cout<<"ARQUIVO ORDENADO!"<<endl;
    return 1;
}

int main ()
{
    char fileName[MAX_STRING_SIZE] = "teste.csv";
    char newFileName[MAX_STRING_SIZE] = "newFile_teste";
    char orderField[MAX_STRING_SIZE] = "DE";
    
    orderedFileCreator<char[MAX_ORDERED_FIELD_SIZE]> a (fileName, newFileName,orderField);
    orderedManipulator teste("newFile_teste");
    a.insertRecords();
    a.getHeader();
    a.printHeader();
    // teste.findOne(3);
    cout<<"Codigo ordenacao "<<teste.ordered_by<<endl;
    teste.ordenateFile();
    teste_ordenacao(teste);
    // teste.findNext();
    return 0;
}
