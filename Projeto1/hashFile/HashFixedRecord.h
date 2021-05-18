#ifndef __Hash_FIXED_RECORD__
#define __Hash_FIXED_RECORD__

#include "../FixedRecord.h"

class HashFixedRecord : public FixedRecord 
{
    public:
        HashFixedRecord();
        int nextRecord_block_addr;
        int nextRecord_block_offset;
        bool deleted;
};
#endif