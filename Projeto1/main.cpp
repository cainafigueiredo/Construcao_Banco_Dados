#include "FileCreator.h"
#include "FixedRecord.h"
#include "fixedHeap/FixedHeapFileCreator.h"
#include "fixedHeap/FixedHeapHeader.h"
#include "fixedHeap/FixedHeapManipulator.h"
#include "orderedFile/orderedHeader.h"
#include "orderedFile/orderedFileCreator.h"
#include "orderedFile/orderedManipulator.h"
#include <iostream>


int main ()
{
    char fileName[MAX_STRING_SIZE] = "teste.csv";
    char newFileName[MAX_STRING_SIZE] = "newFile_teste";
    char orderField[MAX_STRING_SIZE] = "TIPOESC";
    
    orderedFileCreator<char[MAX_ORDERED_FIELD_SIZE]> a (fileName, newFileName,orderField);
    orderedManipulator teste("newFile_teste");
    a.insertRecords();
    a.getHeader();
    a.printHeader();
    double t = 30000;
    double g = 50000;
    teste.removeBetween("TIPOESC", 10, 20);
    teste.findWhereBetween("TIPOESC", 0, 500);

    return 0;
}