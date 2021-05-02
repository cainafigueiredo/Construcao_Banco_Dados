#include <forward_list>
#include "../FixedRecord.h"

using namespace std;

class FixedHeapHeader
{
    public:
        FixedHeapHeader();
        int headerSize;
        int recordSize;
        forward_list<int> freeList;
        int recordsAmount;
};