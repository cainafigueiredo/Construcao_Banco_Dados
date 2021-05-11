#include "Bucket.h"

Bucket::Bucket() {

};

void Bucket::setBlockAddr(int block_addr) {
	this->block_addr = block_addr;
}

void Bucket::setNumberOfRecords(int numberOfRecords) {
	this->numberOfRecords = numberOfRecords;
}

void Bucket::incrementNumberOfRecords() {
	this->numberOfRecords++;
}

void Bucket::decrementNumberOfRecords() {
	this->numberOfRecords--;
}