#ifndef __FILE_HEADER__
#define __FILE_HEADER__

#include <forward_list>
#include "FixedRecord.h"

using namespace std;

class FileHeader
{
    public:
        FileHeader();
        int headerSize;
        int fileOrganization;
        int recordsAmount;
        int blockSize;
        int lastID;

		void incrementRecordsAmount();
		void decrementRecordsAmount();
};

#endif