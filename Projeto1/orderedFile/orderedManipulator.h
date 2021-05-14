#ifndef __ORDERED_MANIPULATOR__
#define __ORDERED_MANIPULATOR__
#include <cstring>
#include "../FileManipulator.h"
#include "orderedHeader.h"
#include "../FixedRecord.h"
#include "../FileHeader.h"
#include <vector>
#define MAX_SIZE_IN_MEM 4096

using namespace std;
class wrapper
{
 public:   
    int compare_by = 0;
    FixedRecord *r;
    wrapper(int ordered_by, FixedRecord *b)
    {
        compare_by = ordered_by;
        r = b;
    }
};

vector<wrapper> make_wrapper_buffer(FixedRecord *buff,int order);

//checa se a.r->attribute < b.r->attribute
bool compare_records(wrapper &a,wrapper &b);
class orderedManipulator : public FileManipulator
{
    public:

        int currPos;
        int ordered_by;
        orderedManipulator(string fileName) : FileManipulator(fileName)
        {
            orderedHeader<char[MAX_ORDERED_FIELD_SIZE]> head; 
            this->openForReading();   
            this->fileRead.read((char *) &head, sizeof(head));
            this->closeForReading();
            char order[MAX_ORDERED_FIELD_SIZE];
            strcpy(order,head.ordered_by);
            cout<<"FILE MANIP COM ORDENACAO |"<<string(order)<<"|"<<endl;
            map<string, int> m = this->createMap();
            this->ordered_by = m[order];
            cout<<this->ordered_by<<endl;  
            this->currPos = 0;
        };
        void writeBufferToTempFile(vector<wrapper> buffer,orderedHeader<char[MAX_ORDERED_FIELD_SIZE]> *head = NULL);
        FixedRecord *findNext();
        int createTempFile(string fileName);
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
};
#endif