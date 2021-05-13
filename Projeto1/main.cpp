#include "FileCreator.h"
#include "FixedRecord.h"
#include "fixedHeap/FixedHeapFileCreator.h"
#include "fixedHeap/FixedHeapHeader.h"
#include "fixedHeap/FixedHeapManipulator.h"
#include "orderedFile/orderedHeader.h"
#include "orderedFile/orderedFileCreator.h"

#include <iostream>

int main ()
{
    char fileName[MAX_STRING_SIZE] = "teste.csv";
    char newFileName[MAX_STRING_SIZE] = "newFile_teste";
    char orderField[MAX_STRING_SIZE] = "some_field";
    orderedFileCreator<int> a (fileName, newFileName,orderField);
    a.insertRecords();
    a.getHeader();
    a.printHeader();
    return 0;
}
