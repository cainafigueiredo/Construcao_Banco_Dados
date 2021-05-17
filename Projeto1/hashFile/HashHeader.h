#ifndef HASH_HEADER_
#define HASH_HEADER_
#include "./HashFixedRecord.h"
#include "../FileHeader.h"
#include "./Bucket.h"

#define NUMBER_OF_BUCKETS 10

using namespace std;

class HashHeader: public FileHeader 
{
    public:
        HashHeader();
        int recordSize;
        Bucket * buckets = new Bucket[NUMBER_OF_BUCKETS];
        int numberOfOverflowRecords;
        int numberOfDeletedRecords;
        int hashFunction(int primaryKey);
		void incrementNumberOfOverflowRecords();
		void decrementNumberOfOverflowRecords();
        int getBlockingFactor();
        int getNumberOfNotDeletedRecords();
};

#endif