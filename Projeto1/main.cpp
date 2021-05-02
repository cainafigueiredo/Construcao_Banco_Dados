#include "fixedHeap/FixedHeapFileCreator.h"
#include <iostream>

int main ()
{
    FixedHeapFileCreator file ("teste.csv", "newFile_teste");
    file.insertRecords();
    // cout << "header_size " << file.header.headerSize << endl;
    return 0;
}