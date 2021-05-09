#ifndef _FIXED_HEAP_MANIPULATOR_
#define _FIXED_HEAP_MANIPULATOR_

#include <vector>
#include "../FileManipulator.h"
#include "FixedHeapHeader.h"
#include "../FixedRecord.h"
using namespace std;

class FixedHeapManipulator : public FileManipulator
{
    public:
        FixedHeapManipulator(string fileName) : FileManipulator(fileName){return;};
        int printRecord(FixedRecord r);
        int findOne(int id);
        int findWhereEqual(string attribute, int value);
        int findWhereEqual(string attribute, double value);
        int findWhereEqual(string attribute, string value);

};
#endif