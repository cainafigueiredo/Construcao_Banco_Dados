#ifndef _FIXED_HEAP_HEADER_
#define _FIXED_HEAP_HEADER_
#include "../FixedRecord.h"
#include "../FileHeader.h"


using namespace std;

class FixedHeapHeader: public FileHeader 
{
    public:
        FixedHeapHeader();
        int recordSize;
        int freeList;
};

#endif