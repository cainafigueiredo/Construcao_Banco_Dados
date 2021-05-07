#include "fixedHeap/FixedHeapFileCreator.h"
#include <iostream>

int main ()
{
    FixedHeapFileCreator file ("teste.csv", "newFile_teste");
    FixedHeapHeader head;
    FixedRecord record, record2;
    file.insertRecords();

    file.openNewFileReading();
    file.inNewFile.read((char *) &head, sizeof(head));
    file.inNewFile.read((char *) &record, sizeof(record));
    file.inNewFile.read((char *) &record2, sizeof(record2));
    file.closeNewFileReading();

    cout << head.recordsAmount << endl;
    cout << record.cod_esc << endl;
    cout << record2.cod_esc << endl;

    return 0;
}
