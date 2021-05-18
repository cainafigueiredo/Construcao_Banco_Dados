#ifndef __ORDERED_MANIPULATOR__
#define __ORDERED_MANIPULATOR__

#include <cstring>
#include "../FileManipulator.h"
#include "orderedHeader.h"
#include "../FixedRecord.h"
#include "../FileHeader.h"
#define MAX_SIZE_IN_MEM 4096

using namespace std;

class orderedManipulator : public FileManipulator
{
    public:
        orderedManipulator(string fileName) : FileManipulator(fileName){return;};
        void ordenateFile();
        int printRecord(FixedRecord r);
        int insertHeader(orderedHeader<char[MAX_ORDERED_FIELD_SIZE]> head);
        

        int findOne(int id);
        int findWhereEqual(string attribute, int value);
        int findWhereEqual(string attribute, double value);
        int findWhereEqual(string attribute, string value);
        int findWhereBetween(string attribute, int value1, int value2);
        int findWhereBetween(string attribute, double value1, double value2);
        
        
        int removeOne(int id);
        int removeBetween(string attribute, int value1, int value2);
        int removeBetween(string attribute, double value1, double value2);
        int updateFreeListInsertDeleted (int offset, orderedHeader<char[MAX_ORDERED_FIELD_SIZE]> head);

        int insertOne(string record);
        int insertMultiple(vector<string> inserts);

        int reorganize(); 
        int createTempFile();
        int openTempFileWriting();
        int closeTempFileWriting();

        int comparator(string a, string b);
        int comparator(int a, int b);
        int comparator(double a, double b);

        int binarySearcher(int value);
        int binarySearcher(double value);
        int binarySearcher(string value);

        int blockParc; 

};
#endif