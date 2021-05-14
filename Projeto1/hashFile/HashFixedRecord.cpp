#include "./HashFixedRecord.h"

HashFixedRecord::HashFixedRecord() : FixedRecord() {
	this->nextRecord_block_addr = -1;
	this->nextRecord_block_offset = -1;
}