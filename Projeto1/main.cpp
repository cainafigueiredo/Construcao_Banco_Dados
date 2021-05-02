#include "fixedHeap/FixedHeapFileCreator.h"
#include <iostream>

int main ()
{
    FixedHeapFileCreator file ("teste.csv", "newFile_teste");
    file.insertRecords();
    return 0;
}