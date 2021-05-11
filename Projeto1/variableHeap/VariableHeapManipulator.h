#ifndef _VARIABLE_HEAP_MANIPULATOR_
#define _VARIABLE_HEAP_MANIPULATOR_

#include <vector>
#include <cstring>
#include "../FileManipulator.h"
#include "VariableHeapHeader.h"
#include "../VariableRecord.h"
using namespace std;

class VariableHeapManipulator : public FileManipulator
{
    public:
        VariableHeapManipulator(string fileName) : FileManipulator(fileName){return;};
        
        int readRecords(int offset, VariableRecord * Record);

       
};
#endif