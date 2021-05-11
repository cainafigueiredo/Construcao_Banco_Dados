#include "FileCreator.h"
#include "FixedRecord.h"
#include "fixedHeap/FixedHeapFileCreator.h"
#include "fixedHeap/FixedHeapHeader.h"
#include "fixedHeap/FixedHeapManipulator.h"

#include <iostream>

int main ()
{
    FixedHeapFileCreator a ("teste.csv", "newFile_teste");
    FixedHeapManipulator teste("newFile_teste");
    a.insertRecords();
    a.getHeader();
    // cout << "FRONT: " << a.header.freeList<< endl;

    teste.findWhereBetween("id", 0, 12);
    teste.removeBetween("id", 0, 2);
    teste.findWhereBetween("id", 0, 12);
    // teste.reorganize();
    // teste.findWhereBetween("id", -1, 12);
    return 0;
}
