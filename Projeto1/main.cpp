#include "FileCreator.h"
#include "FixedRecord.h"
#include "fixedHeap/FixedHeapFileCreator.h"
#include "fixedHeap/FixedHeapHeader.h"
#include <iostream>

int main ()
{

    FixedHeapFileCreator file ("teste.csv", "newFile_teste");
    FixedHeapHeader head;
    FixedRecord record,  record7;
    
    file.insertRecords();
    
    file.openNewFileReading();
    file.inNewFile.read((char *) &head, sizeof(head));
    file.inNewFile.read((char *) &record, sizeof(record));
    
    file.inNewFile.seekg(sizeof(record) * 5,ios::cur);
    
    file.inNewFile.read((char *) &record7, sizeof(record7));
    
    file.closeNewFileReading();
    
    cout << record.ds_pais << endl;
    cout << record7.ds_pais << endl;

    return 0;
}
