#ifndef _FIXED_HEAP_MANIPULATOR_
#define _FIXED_HEAP_MANIPULATOR_

#include <cstring>
#include "../FileManipulator.h"
#include "FixedHeapHeader.h"
#include "../FixedRecord.h"
using namespace std;

class FixedHeapManipulator : public FileManipulator
{
    public:
        FixedHeapManipulator(string fileName) : FileManipulator(fileName){return;};
        
        int printRecord(FixedRecord r);
        int insertHeader(FixedHeapHeader head);
        

        int findOne(int id);
        int findWhereEqual(string attribute, int value);
        int findWhereEqual(string attribute, double value);
        int findWhereEqual(string attribute, string value);
        int findWhereBetween(string attribute, int value1, int value2);
        int findWhereBetween(string attribute, double value1, double value2);
        
        
        int removeOne(int id);
        int removeBetween(string attribute, int value1, int value2);
        int removeBetween(string attribute, double value1, double value2);
        int updateFreeListInsertDeleted (int offset, FixedHeapHeader head);

        int insertOne(string record);
        int insertMultiple(vector<string> inserts);

        int reorganize(); 
        int createTempFile();
        int openTempFileWriting();
        int closeTempFileWriting();
};
#endif