#include "FixedHeapHeader.h"

FixedHeapHeader::FixedHeapHeader()
{
    this->headerSize = sizeof(*this);
    this->recordSize = sizeof(FixedRecord);
    this->recordsAmount = 0;
}