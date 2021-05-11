#ifndef _VARIABLE_HEAP_HEADER_
#define _VARIABLE_HEAP_HEADER_
#include "../VariableRecord.h"
#include "../FileHeader.h"


using namespace std;

class VariableHeapHeader: public FileHeader 
{
    public:
        VariableHeapHeader();
        int freeList;
};

#endif