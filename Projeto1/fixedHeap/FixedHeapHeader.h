#include "../FileHeader.h"

using namespace std;

class FixedHeapHeader: public FileHeader 
{
    public:
        FixedHeapHeader();
        int recordSize;
        forward_list<int> freeList;
};