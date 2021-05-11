#include "HashManipulator.h"

HashManipulator::HashManipulator(string fileName) : FileManipulator(fileName) {
    
}

int HashManipulator::printRecord(FixedRecord r)
{
    cout << r.id << "\t" << r.nomedep << "\t" << r.de << "\t" <<
    r.distr << "\t" << r.mun << "\t" << r.tipoesc << "\t" << 
    r.cod_esc << "\t" << r.nomesc << "\t" << r.ds_pais << "\t" << r.n_alunos << endl;
    return 0;
}

int HashManipulator::insertHeader(HashHeader head)
{
    this->openForWriting();
    this->fileWrite.seekp(0, ios::beg);
    this->fileWrite.write( (char *) &head, sizeof(head));
    this->closeForWriting();
    return 0;
}

int HashManipulator::findOne(int id)
{
    FixedRecord record;
    HashHeader head;
    int bucket_id, block_addr, n_recordsInBlock, firstRecordAddr;
    int blocksAccessed;
    bool found = false;
    this->openForReading();
    this->fileRead.read((char *) &head, sizeof(head));

    bucket_id = head.hashFunction(id);
    block_addr = head.buckets[bucket_id].block_addr;
    n_recordsInBlock = head.buckets[bucket_id].numberOfRecords;
    firstRecordAddr = (block_addr * head.blockSize);

    this->fileRead.seekg(sizeof(head) + firstRecordAddr);

    for (int i = 0; i < n_recordsInBlock; i++)
    {
        this->fileRead.read((char *) &record, sizeof(FixedRecord));

        if (record.id == id)
        {
            blocksAccessed = i+1;
            found = true;
            break;
        }
    }

    if (!found)
    {
        return -1;
    }
    this->printSchema();
    this->printRecord(record);
    cout << "Blocks Acessed: " << blocksAccessed << endl;
    this->closeForReading();

    return 0;
}

int HashManipulator::findWhereEqual(string attribute, int value)
{
    FixedRecord record;
    HashHeader head;
    vector<FixedRecord> records;
    int attr, blocksAccessed,  i;
    bool found = false;
    map<string, int> m = this->createMap();
    attr = m[attribute];
    
    this->openForReading();
    this->fileRead.read((char *) &head, sizeof(head));

    int bucket_id, block_addr, n_recordsInBlock, firstRecordAddr;
    
    blocksAccessed = 0;

    for (bucket_id = 0; bucket_id < NUMBER_OF_BUCKETS; bucket_id++)
    {
        block_addr = head.buckets[bucket_id].block_addr;
        n_recordsInBlock = head.buckets[bucket_id].numberOfRecords;
        firstRecordAddr = (block_addr * head.blockSize);
        this->fileRead.seekg(sizeof(head) + firstRecordAddr);

        for (int i = 0; i < n_recordsInBlock; i++) {
            this->fileRead.read((char *) &record, sizeof(FixedRecord));
            blocksAccessed++;

            switch (attr)
            {
                case 0: /*id*/
                    if (record.id == value)
                    {
                        records.push_back(record);
                    }
                    found = true;
                    break;
                case 5: /*tipoesc*/
                    if (record.tipoesc == value)
                    {
                        records.push_back(record);
                    }
                    found = true;
                    break;
                case 9: /*n_alunos*/
                    if (record.n_alunos == value)
                    {
                        records.push_back(record);
                    }
                    found = true;
                    break;
                default:
                    return -1;
            }
        }
    }

    if (!found)
    {
        return -1;
    }

    this->printSchema();
    for (auto const &r : records)
    {
        this->printRecord(r);
    }
    cout << "Blocks Acessed: " << blocksAccessed << endl;

    this->closeForReading();
    return 0;    
}

int HashManipulator::findWhereEqual(string attribute, double value)
{
    FixedRecord record;
    HashHeader head;
    vector<FixedRecord> records;
    int attr, blocksAccessed, i;
    bool found = false;
    map<string, int> m = this->createMap();
    attr = m[attribute];
    
    int bucket_id, block_addr, n_recordsInBlock, firstRecordAddr;

    this->openForReading();
    this->fileRead.read((char *) &head, sizeof(head));

    blocksAccessed = 0;

    for (bucket_id = 0; bucket_id < NUMBER_OF_BUCKETS; bucket_id++)
    {
        block_addr = head.buckets[bucket_id].block_addr;
        n_recordsInBlock = head.buckets[bucket_id].numberOfRecords;
        firstRecordAddr = (block_addr * head.blockSize);
        this->fileRead.seekg(sizeof(head) + firstRecordAddr);

        for (int i = 0; i < n_recordsInBlock; i++) {
            this->fileRead.read((char *) &record, sizeof(FixedRecord));
            blocksAccessed++;

            switch (attr)
            {
                case 6: /*cod_esc*/
                    if (record.cod_esc == value)
                    {
                        records.push_back(record);
                    }
                    found = true;
                    break;
                default:
                    return -1;
            }
        }
    }
    
    if (!found)
    {
        return -1;
    }

    this->printSchema();
    for (auto const &r : records)
    {
        this->printRecord(r);
    }

    cout << "Blocks Acessed: " << blocksAccessed << endl;
   
    this->closeForReading();
    return 0;
   
}
int HashManipulator::findWhereEqual(string attribute, string value)
{
    FixedRecord record;
    HashHeader head;
    vector<FixedRecord> records;
    int attr, blocksAccessed, i;
    bool found = false;
    map<string, int> m = this->createMap();
    attr = m[attribute];
    
    int bucket_id, block_addr, n_recordsInBlock, firstRecordAddr;

    this->openForReading();
    this->fileRead.read((char *) &head, sizeof(head));
    cout << value;
    blocksAccessed = 0;

    for (bucket_id = 0; bucket_id < NUMBER_OF_BUCKETS; bucket_id++)
    {
        block_addr = head.buckets[bucket_id].block_addr;
        n_recordsInBlock = head.buckets[bucket_id].numberOfRecords;
        firstRecordAddr = (block_addr * head.blockSize);
        this->fileRead.seekg(sizeof(head) + firstRecordAddr);

        for (int i = 0; i < n_recordsInBlock; i++) {
            this->fileRead.read((char *) &record, sizeof(FixedRecord));
            blocksAccessed++;

            switch (attr)
            {
                case 1: /*nomedep*/
                    if (string(record.nomedep).compare(value) == 0)
                    {
                        records.push_back(record);
                    }
                    found = true;
                    break;
                case 2: /*de*/
                    if (string(record.de).compare(value) == 0)
                    {
                        records.push_back(record);
                    }
                    found = true;
                    break;
                case 3: /*distr*/
                    if (string(record.distr).compare(value) == 0)
                    {
                        records.push_back(record);
                    }
                    found = true;
                    break;
                case 4: /*mun*/
                    if (string (record.mun).compare(value) == 0)
                    {
                        records.push_back(record);
                    }
                    found = true;
                    break;
                case 7: /*nomesc*/
                    if (string (record.nomesc).compare(value) == 0)
                    {
                        records.push_back(record);
                    }
                    found = true;
                    break;
                case 8: /*ds_pais*/
                    if (string (record.ds_pais).compare(value) == 0)
                    {
                        records.push_back(record);
                    }
                    found = true;
                    break;
                default:
                    return -1;
            }
        }
    }
    
    if (!found)
    {
        return -1;
    }

    this->printSchema();
    for (auto const &r : records)
    {
        this->printRecord(r);
    }

    cout << "Blocks Acessed: " << blocksAccessed << endl;
   
    this->closeForReading();
    return 0;
}

int HashManipulator::findWhereBetween (string attribute, int value1, int value2)
{
    FixedRecord record;
    HashHeader head;
    vector<FixedRecord> records;
    int attr, blocksAccessed, i;
    bool found = false;
    map<string, int> m = this->createMap();
    attr = m[attribute];
    
    this->openForReading();
    this->fileRead.read((char *) &head, sizeof(head));
    for (i = 0; i < head.recordsAmount; i++)
    {
        this->fileRead.read((char *) &record, sizeof(FixedRecord));
        switch (attr)
        {
            case 0: /*id*/
                if (record.id >= value1 && record.id <= value2)
                {
                    records.push_back(record);
                }
                found = true;
                break;
            case 5: /*tipoesc*/
                if (record.tipoesc >= value1 && record.tipoesc <= value2)
                {
                    records.push_back(record);
                }
                found = true;
                break;
            case 9: /*n_alunos*/
                if (record.n_alunos >= value1 && record.n_alunos <= value2)
                {
                    records.push_back(record);
                }
                found = true;
                break;
            default:
                return -1;
        }
    }

    blocksAccessed = i;
    
    if (!found)
    {
        return -1;
    }

    this->printSchema();
    for (auto const &r : records)
    {
        this->printRecord(r);
    }

    cout << "Blocks Acessed: " << blocksAccessed << endl;
   
    this->closeForReading();
    return 0;
}

int HashManipulator::findWhereBetween (string attribute, double value1, double value2)
{
    FixedRecord record;
    HashHeader head;
    vector<FixedRecord> records;
    int attr, blocksAccessed, i;
    bool found = false;
    map<string, int> m = this->createMap();
    attr = m[attribute];
    
    this->openForReading();
    this->fileRead.read((char *) &head, sizeof(head));
    for (i = 0; i < head.recordsAmount; i++)
    {
        this->fileRead.read((char *) &record, sizeof(FixedRecord));
        switch (attr)
        {
            case 6: /*cod_esc*/
                if (record.cod_esc >= value1 && record.cod_esc <= value2)
                {
                    records.push_back(record);
                }
                found = true;
                break;
            default:
                return -1;
        }
    }

    blocksAccessed = i;
    
    if (!found)
    {
        return -1;
    }

    this->printSchema();
    for (auto const &r : records)
    {
        this->printRecord(r);
    }

    cout << "Blocks Acessed: " << blocksAccessed << endl;
   
    this->closeForReading();
    return 0;
}

int HashManipulator::removeOne(int id)
{
    HashHeader head;
    FixedRecord record;
    bool found = false;
    int i;
    int offset = 0;

    this->openForReading();
    this->fileRead.seekg(0, ios::beg);
    this->fileRead.read((char *) &head, sizeof(head));
    offset += sizeof(head);
    for (i = 0; i < head.recordsAmount; i++)
    {
        this->fileRead.read((char *) &record, sizeof(FixedRecord));
        if (record.id == id)
        {
            found = true;
            break;
        }
        offset += sizeof(FixedRecord);
    }

    if (!found)
    {
        return -1;
    }

    this->updateFreeListInsertDeleted(offset, head);
   
    return 0;
}

int HashManipulator::removeBetween(string attribute, int value1, int value2)
{
    HashHeader head;
    FixedRecord record;
    int attr;
    int offset, auxOffset;
    int numDeleted = 0;
    int i = 0;
    map<string, int> m = this->createMap();
    attr = m[attribute];
    
    offset = sizeof(HashHeader);
    auxOffset = offset;
    do
    {
        this->openForReading();
        this->fileRead.seekg(0, ios::beg);
        this->fileRead.read((char *) &head, sizeof(head));
        
        this->fileRead.seekg(auxOffset, ios::beg);
        this->fileRead.read((char *) &record, sizeof(FixedRecord));

        auxOffset = this->fileRead.tellg();
        
        this->closeForReading();
        switch (attr)
        {
            case 0: /*id*/
                if (record.id >= value1 && record.id <= value2)
                {
                    this->updateFreeListInsertDeleted(offset, head);
                    numDeleted++;
                }
                break;
            case 5: /*tipoesc*/
                if (record.tipoesc >= value1 && record.tipoesc <= value2)
                {
                    this->updateFreeListInsertDeleted(offset, head);
                    numDeleted++;
                }
                break;
            case 9: /*n_alunos*/
                if (record.n_alunos >= value1 && record.n_alunos <= value2)
                {
                    this->updateFreeListInsertDeleted(offset, head);
                    numDeleted++;
                }
                break;
            default:
                return -1;
        }
        offset += sizeof(FixedRecord);
        i++;
    }while (i < head.recordsAmount);

    cout << "Rows deleted: " << numDeleted << endl;
    
    return 0;
}

int HashManipulator::removeBetween(string attribute, double value1, double value2)
{
 return 0;   
}

int HashManipulator::updateFreeListInsertDeleted(int offset, HashHeader head)
{
    FixedRecord deleted;
    FixedRecord record;

    int auxOffset;
    deleted.makeDeleted();
    /*storing offset for next element at n_alunos*/
    if (head.freeList == -1)
    {
        head.freeList = offset;
        deleted.n_alunos = -1;
    }
    else /*if there is a list of deleted blocks, find the last one*/
    {
        /*jump to the first*/
        auxOffset = head.freeList;
        this->openForReading();
        do
        {
            this->fileRead.seekg(auxOffset, ios::beg);
            this->fileRead.read((char *) &record, sizeof(FixedRecord));
            auxOffset = record.n_alunos;
        } while (record.n_alunos != -1);
        record.n_alunos = offset;
        
        /*get the position of the last record in the list, to overwrite it
        with the new n_alunos info*/
        this->fileRead.seekg(-sizeof(FixedRecord), ios::cur);
        auxOffset = this->fileRead.tellg();
        this->closeForReading();
        
        this->openForWriting();
        this->fileWrite.seekp(auxOffset, ios::beg);
        this->fileWrite.write((char *) &record, sizeof(record));
        this->closeForWriting();

    }

    this->closeForReading();

    this->openForWriting();
    this->fileWrite.seekp(offset, ios::beg);
    this->fileWrite.write( (char *) &deleted, sizeof(deleted));
    this->closeForWriting();

    this->insertHeader(head);
    
    return 0;
}