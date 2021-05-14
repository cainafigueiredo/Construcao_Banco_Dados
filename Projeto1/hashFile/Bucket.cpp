#include "Bucket.h"

Bucket::Bucket() {
	this->overflow.first_block_addr = -1;
	this->overflow.first_block_offset = -1;
	this->overflow.last_block_addr = -1;
	this->overflow.last_block_offset = -1;
	setNumberOfRecords(0);
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