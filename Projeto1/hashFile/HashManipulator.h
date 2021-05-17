#ifndef _HASH_MANIPULATOR_
#define _HASH_MANIPULATOR_

#include <vector>

#include "../FileManipulator.h"
#include "HashHeader.h"
#include "./HashFixedRecord.h"

using namespace std;

class HashManipulator : public FileManipulator
{
    public:
        HashManipulator(string fileName);
        
        int printRecord(HashFixedRecord r);
        int insertHeader(HashHeader head);

        int findOne(int id);
        int findWhereEqual(string attribute, int value);
        int findWhereEqual(string attribute, double value);
        int findWhereEqual(string attribute, string value);
        int findWhereBetween(string attribute, int value1, int value2);
        int findWhereBetween(string attribute, double value1, double value2);
        
        int removeOne(int id);
        int removeBetween(string attribute, int value1, int value2);
        int removeBetween(string attribute, double value1, double value2);
};
#endif