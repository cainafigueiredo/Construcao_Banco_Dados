#include "FixedHeapHeader.h"

FixedHeapHeader::FixedHeapHeader()
{
    this->headerSize = sizeof(*this);
    this->fileOrganization = 22; // 0 means FixedHeap; ...
    this->recordSize = sizeof(FixedRecord);
}