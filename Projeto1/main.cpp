#include <iostream>
#include "FileCreator.h"
#include "FixedRecord.h"
#include "fixedHeap/FixedHeapFileCreator.h"
#include "fixedHeap/FixedHeapHeader.h"
#include "fixedHeap/FixedHeapManipulator.h"
#include "orderedFile/orderedHeader.h"
#include "orderedFile/orderedFileCreator.h"
#include "orderedFile/orderedManipulator.h"
#include <iostream>
#include "./hashFile/HashFileCreator.h"
#include "./fixedHeap/FixedHeapFileCreator.h"
#include "FileManager.h"

using namespace std;

#define NEW_BASE_INSTRUCTION "newBase"
#define LOAD_BASE_INSTRUCTION "loadBase"
#define INSERT_ONE_INSTRUCTION "insertOne"
#define INSERT_MULTIPLE_INSTRUCTION "insertMultiple"
#define FIND_ONE_BY_ID_INSTRUCTION "findOneById"
#define FIND_WHERE_EQUAL_INSTRUCTION "findWhereEqual"
#define FIND_WHERE_BETWEEN_INSTRUCTION "findWhereBetween"
#define REMOVE_ONE_BY_ID_INSTRUCTION "removeOneById"
#define REMOVE_WHERE_BETWEEN_INSTRUCTION "removeWhereBetween"
#define REORGANIZE_INSTRUCTION "reorganize"
#define HEADER_INFO_INSTRUCTION "headerInfo"

#define FIXED_HEAP_ORGANIZATION "fixedHeap"
#define HASH_ORGANIZATION "externalHash"

#define NEW_BASE_HELP "newBase:\nOrganização do arquivo | Caminho para o CSV | Caminho e nome do arquivo de destino\n"

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


int main(int argc, char *argv[]) {
	char fileName[MAX_STRING_SIZE] = "teste.csv";
    char newFileName[MAX_STRING_SIZE] = "newTeste_file.csv";
    char orderField[MAX_STRING_SIZE] = "DE";
    
    orderedFileCreator<char[MAX_ORDERED_FIELD_SIZE]> a (fileName, newFileName,orderField);
    orderedManipulator teste("newTeste_file.csv");
    a.insertRecords();
    a.getHeader();
    a.printHeader();
    // cout<<"Codigo ordenacao "<<teste.ordered_by<<endl;
    teste.ordenateFile(teste.fileName);
    teste_ordenacao(teste);
    return 0;
}
