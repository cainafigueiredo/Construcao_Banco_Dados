#include "FileCreator.h"
#include "FixedRecord.h"
#include "fixedHeap/FixedHeapFileCreator.h"
#include "fixedHeap/FixedHeapHeader.h"
#include "fixedHeap/FixedHeapManipulator.h"

#include <iostream>

int main ()
{
    FixedHeapFileCreator a ("teste.csv", "newFile_teste");
    a.insertRecords();
    FixedHeapManipulator teste("newFile_teste");
    teste.findWhereBetween("id", 2, 5);
    return 0;
}
