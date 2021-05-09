#include "FixedHeapManipulator.h"

int FixedHeapManipulator::findOne(int id)
{
    FixedRecord record;
    this->openForReading();
    this->fileRead.seekg(sizeof(FixedHeapHeader), ios::beg);
    do
    {
        this->fileRead.read((char *) &record, sizeof(FixedRecord));
        cout << record.ds_pais << endl;
    } while (!this->fileRead);
    this->closeForReading();
    return 0;
}