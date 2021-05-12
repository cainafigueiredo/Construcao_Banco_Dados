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
#include "HashHeader.h"

using namespace std;


class HashFileCreator : public FileCreator
{
    public:
        HashFileCreator(string fileName, string newFileName);
        ~HashFileCreator(){return;};
        HashHeader header;
        int insertHeader();
        int insertRecords();
        int getHeader();
        using FileCreator::readCsvLine;
        int readCsvLine(HashFixedRecord &newRecord);
};
#endif