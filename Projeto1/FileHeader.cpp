#include "FileHeader.h"

FileHeader::FileHeader()
{
	this->fileOrganization = 2;
    this->recordsAmount = 0;
}

void FileHeader::incrementRecordsAmount() {
	this->recordsAmount++;
}

void FileHeader::decrementRecordsAmount() {
	this->recordsAmount--;
}