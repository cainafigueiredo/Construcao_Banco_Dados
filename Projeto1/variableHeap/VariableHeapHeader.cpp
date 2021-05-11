#include "VariableHeapHeader.h"

VariableHeapHeader::VariableHeapHeader()
{
    this->headerSize = sizeof(*this);
    this->fileOrganization = 1; // 0 means FixedHeap; ...
    this->freeList = -1;
}