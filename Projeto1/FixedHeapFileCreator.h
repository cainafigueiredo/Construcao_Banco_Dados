#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <forward_list>
using namespace std;


class FixedHeapHeader
{
    public:
        FixedHeapHeader(){};
        int headerSize;
        int recordSize;
        forward_list<int> freeList;
        int recordsAmount;
};

class FixedHeapFileCreator
{
    public:
        FixedHeapHeader header;
        fstream rawDataFile;
        fstream newFile;
        int createNewFile();
        int insertHeader();
        int insertRecords();
        int updateHeader();
};