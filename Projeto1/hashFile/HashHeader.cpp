#include "HashHeader.h"

HashHeader::HashHeader()
{
    this->headerSize = sizeof(*this);
    this->fileOrganization = 3; // 3 means Hash; ...
    this->recordSize = sizeof(HashFixedRecord);
    this->numberOfDeletedRecords = 0;

    for (int i = 0; i < NUMBER_OF_BUCKETS; i++) {
        this->buckets[i].setBlockAddr(i);
        this->buckets[i].setNumberOfRecords(0);
    }

    this->numberOfOverflowRecords = 0;
}

int HashHeader::hashFunction(int primaryKey) {
    return (primaryKey % NUMBER_OF_BUCKETS);
}

void HashHeader::incrementNumberOfOverflowRecords() {
	this->numberOfOverflowRecords++;
}

void HashHeader::decrementNumberOfOverflowRecords() {
	this->numberOfOverflowRecords--;
}

int HashHeader::getBlockingFactor() {
    return (this->blockSize/this->recordSize);
}

int HashHeader::getNumberOfNotDeletedRecords() {
    return (this->recordsAmount - this->numberOfDeletedRecords);
}