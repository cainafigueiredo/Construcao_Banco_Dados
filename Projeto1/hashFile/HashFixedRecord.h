#include "../FixedRecord.h"

class HashFixedRecord : public FixedRecord 
{
    public:
        HashFixedRecord();
        int nextRecord_block_addr;
        int nextRecord_block_offset;
};