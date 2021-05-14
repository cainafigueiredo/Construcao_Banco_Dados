#ifndef HASH_HEADER_
#define HASH_HEADER_
#include "../FixedRecord.h"
#include "../FileHeader.h"
#include "./Bucket.h"

#define NUMBER_OF_BUCKETS 2

using namespace std;

class HashHeader: public FileHeader 
{
    public:
        HashHeader();
        int recordSize;
        Bucket * buckets = new Bucket[NUMBER_OF_BUCKETS];
        int numberOfOverflowRecords;
        int freeList;
        int hashFunction(int primaryKey);
		void incrementNumberOfOverflowRecords();
		void decrementNumberOfOverflowRecords();
        int getBlockingFactor();
};

#endif