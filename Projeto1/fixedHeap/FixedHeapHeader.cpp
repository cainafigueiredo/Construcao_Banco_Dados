#include "FixedHeapHeader.h"

FixedHeapHeader::FixedHeapHeader()
{
    this->headerSize = sizeof(*this);
    this->fileOrganization = 0; // 0 means FixedHeap; ...
    this->recordSize = sizeof(FixedRecord);
    this->freeList = -1;
}