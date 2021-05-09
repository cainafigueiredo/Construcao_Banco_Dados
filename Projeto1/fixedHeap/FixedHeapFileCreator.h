#ifndef _FIXED_HEAP_FILE_CREATOR_
#define _FIXED_HEAP_FILE_CREATOR_

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <forward_list>
#include "../FileCreator.h"
#include "../FixedRecord.h"
#include "FixedHeapHeader.h"

using namespace std;


class FixedHeapFileCreator : public FileCreator
{
    public:
        FixedHeapFileCreator(string fileName, string newFileName);
        ~FixedHeapFileCreator(){return;};
        FixedHeapHeader header;
        int insertHeader();
        int insertRecords();
        int getHeader();
        using FileCreator::readCsvLine;
        int readCsvLine(FixedRecord &newRecord);
};
#endif