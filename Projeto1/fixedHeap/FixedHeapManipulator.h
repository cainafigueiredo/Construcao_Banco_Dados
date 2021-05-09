#ifndef _FIXED_HEAP_MANIPULATOR_
#define _FIXED_HEAP_MANIPULATOR_

#include "../FileManipulator.h"
#include "FixedHeapHeader.h"
#include "../FixedRecord.h"

using namespace std;

class FixedHeapManipulator : public FileManipulator
{
    public:
        FixedHeapManipulator(string fileName) : FileManipulator(fileName){return;};
        int findOne(int id);
};

#endif