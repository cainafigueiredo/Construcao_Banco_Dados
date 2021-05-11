#ifndef _VARIABLE_HEAP_FILE_CREATOR_
#define _VARIABLE_HEAP_FILE_CREATOR_

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <forward_list>
#include "../FileCreator.h"
#include "../VariableRecord.h"
#include "VariableHeapHeader.h"

using namespace std;


class VariableHeapFileCreator : public FileCreator
{
    public:
        VariableHeapFileCreator(string fileName, string newFileName);
        ~VariableHeapFileCreator(){return;};
        VariableHeapHeader header;
        int insertHeader();
        int insertRecords();
        int getHeader();
        using FileCreator::readCsvLine;
        int readCsvLine(VariableRecord &newRecord);
        
        
};
#endif