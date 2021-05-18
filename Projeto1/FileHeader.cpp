#include "FileHeader.h"

FileHeader::FileHeader()
{
	this->fileOrganization = 2;
    this->recordsAmount = 0;
	this->blockSize = 4096;
	this->lastID = -1;
}

void FileHeader::incrementRecordsAmount() {
	this->recordsAmount++;
}

void FileHeader::decrementRecordsAmount() {
	this->recordsAmount--;
}