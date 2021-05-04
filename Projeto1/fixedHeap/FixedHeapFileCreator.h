#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <forward_list>
#include "../FileCreator.h"
#include "./FixedRecord.h"
#include "FixedHeapHeader.h"

using namespace std;


class FixedHeapFileCreator : public FileCreator
{
    public:
        FixedHeapFileCreator(string fileName, string newFileName);
        FixedHeapHeader header;
        int insertHeader();
        int insertRecords();
        int getHeader();
        using FileCreator::readCsvLine;
        int readCsvLine(FixedRecord &newRecord);
};