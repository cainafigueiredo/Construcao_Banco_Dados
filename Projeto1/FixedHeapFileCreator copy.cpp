#include "FixedHeapFileCreator.h"


FixedHeapFileCreator::FixedHeapFileCreator()
{   
    this->header.headerSize = 0;
    this->header.recordSize = 0;
    this->header.recordsAmount = 0;
}

int FixedHeapFileCreator::insertHeader()
{
    this->newFile.write(&(this->header), sizeof(this->header));
    
}