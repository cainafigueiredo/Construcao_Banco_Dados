#include "FixedHeapManipulator.h"

int FixedHeapManipulator::printRecord(FixedRecord r)
{
    cout << r.id << "\t" << r.nomedep << "\t" << r.de << "\t" <<
    r.distr << "\t" << r.mun << "\t" << r.tipoesc << "\t" << 
    r.cod_esc << "\t" << r.nomesc << "\t" << r.ds_pais << "\t" << r.n_alunos << endl;
    return 0;
}

int FixedHeapManipulator::insertHeader(FixedHeapHeader head)
{
    this->openForWriting();
    this->fileWrite.seekp(0, ios::beg);
    this->fileWrite.write( (char *) &head, sizeof(head));
    this->closeForWriting();
    return 0;
}

int FixedHeapManipulator::findOne(int id)
{
    FixedRecord record;
    FixedHeapHeader head;
    int blocksAccessed;
    bool found = false;
    this->openForReading();
    this->fileRead.read((char *) &head, sizeof(head));
    for (int i = 0; i < head.recordsAmount; i++)
    {
        this->fileRead.read((char *) &record, sizeof(FixedRecord));
        if (record.id == id)
        {
            blocksAccessed = i+1;
            i = head.recordsAmount;
            found = true;
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

int FixedHeapManipulator::findWhereEqual(string attribute, int value)
{
    FixedRecord record;
    FixedHeapHeader head;
    vector<FixedRecord> records;
    int attr, blocksAccessed,  i;
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
int FixedHeapManipulator::findWhereEqual(string attribute, double value)
{
    FixedRecord record;
    FixedHeapHeader head;
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
int FixedHeapManipulator::findWhereEqual(string attribute, string value)
{
    FixedRecord record;
    FixedHeapHeader head;
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
        cout << "attr: " << attr << " n_alunos: " << record.ds_pais << endl;
        switch (attr)
        {
            case 1: /*nomedep*/
                if (string(record.nomedep).compare(value))
                {
                    records.push_back(record);
                }
                found = true;
                break;
            case 2: /*de*/
                if (string(record.de).compare(value))
                {
                    records.push_back(record);
                }
                found = true;
                break;
            case 3: /*distr*/
                if (string(record.distr).compare(value))
                {
                    records.push_back(record);
                }
                found = true;
                break;
            case 4: /*mun*/
                if (string (record.mun).compare(value))
                {
                    records.push_back(record);
                }
                found = true;
                break;
            case 7: /*nomesc*/
                if (string (record.nomesc).compare(value))
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

int FixedHeapManipulator::findWhereBetween (string attribute, int value1, int value2)
{
    FixedRecord record;
    FixedHeapHeader head;
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

int FixedHeapManipulator::findWhereBetween (string attribute, double value1, double value2)
{
    FixedRecord record;
    FixedHeapHeader head;
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

int FixedHeapManipulator::removeOne(int id)
{
    FixedHeapHeader head;
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

int FixedHeapManipulator::removeBetween(string attribute, int value1, int value2)
{
    FixedHeapHeader head;
    FixedRecord record;
    int attr;
    int offset, auxOffset;
    int numDeleted = 0;
    int i = 0;
    map<string, int> m = this->createMap();
    attr = m[attribute];
    
    offset = sizeof(FixedHeapHeader);
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

int FixedHeapManipulator::removeBetween(string attribute, double value1, double value2)
{
    FixedHeapHeader head;
    FixedRecord record;
    int attr;
    int offset, auxOffset;
    int numDeleted = 0;
    int i = 0;
    map<string, int> m = this->createMap();
    attr = m[attribute];
    
    offset = sizeof(FixedHeapHeader);
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

int FixedHeapManipulator::updateFreeListInsertDeleted(int offset, FixedHeapHeader head)
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

    head.recordsAmount--;
    this->insertHeader(head);
    
    return 0;
}

int FixedHeapManipulator::insertOne(string record)
{
    FixedRecord newR;
    FixedHeapHeader head;
    int offset;

    this->openForReading();
    this->fileRead.seekg(0, ios::beg);
    this->fileRead.read( (char *) &head, sizeof(head));
    this->closeForReading();
    
    /*botar o id*/
    newR.readCSVLine(record);
    /*if there is a deleted space*/
    if (head.freeList != 0)
    {
        FixedRecord auxRecord;
        this->openForReading();
        this->fileRead.seekg(head.freeList, ios::beg);
        this->fileRead.read( (char *) &auxRecord, sizeof(FixedRecord));
        this->closeForReading();

        this->openForWriting();
        this->fileWrite.seekp(head.freeList, ios::beg);
        this->fileWrite.write((char *) &newR, sizeof(FixedRecord));
        head.freeList = auxRecord.n_alunos;
        this->closeForWriting();
        head.recordsAmount++;
        this->insertHeader(head);
        return 0;
    }
    
    offset = head.recordsAmount * sizeof(FixedRecord) + sizeof(FixedHeapHeader);
    this->openForWriting();
    this->fileWrite.seekp(offset, ios::beg);
    this->fileWrite.write((char *) &newR, sizeof(FixedRecord));
    this->closeForWriting();
    head.recordsAmount++;
    this->insertHeader(head);

    return 0;;
}

int FixedHeapManipulator::insertMultiple(vector<string> inserts)
{
    for (auto const &record: inserts)
    {
        this->insertOne(record);
    }

    return 0;
}

int FixedHeapManipulator::reorganize()
{
    FixedRecord record;
    FixedHeapHeader head;


    this->openForReading();
    this->fileRead.seekg(0, ios::beg);
    this->fileRead.read((char *) &head, sizeof(FixedHeapHeader));
    this->closeForReading();
    
    if (head.freeList == 0)
    {
        return 0;
    }

    this->createTempFile();
    this->openTempFileWriting();
    this->openForReading();
    this->tempFile.write( (char *) &head, sizeof(FixedHeapHeader));
    for (int i = 0; i < head.recordsAmount; i++)
    {
        this->fileRead.read ( (char *) &record, sizeof(FixedRecord));
        if (record.id != -1)
        {
            this->tempFile.write( (char *) &record, sizeof(FixedRecord));
        }
        else
        {
            head.recordsAmount--;
        }
    }
    this->tempFile.seekp(0, ios::beg);
    this->tempFile.write( (char *) &head, sizeof (FixedHeapHeader));
    this->closeForReading();
    this->closeTempFileWriting();

    remove (this->fileName.c_str());
    rename ((this->fileName + ".temp").c_str(), this->fileName.c_str());
    return 0;
}

int FixedHeapManipulator::createTempFile()
{
    this->tempFile.open(this->fileName + ".temp", ios::binary | ios::out);
    if (!this->tempFile.good())
    {
        return -1;
    }
    this->tempFile.close();
    return 0;
}

int FixedHeapManipulator::openTempFileWriting()
{
    this->tempFile.open(this->fileName + ".temp", fstream::binary | ios::out | ios::in);
    if (!this->tempFile.is_open())
    {
        return -1;
    }
    return 0;
}

int FixedHeapManipulator::closeTempFileWriting()
{
    this->tempFile.close();
    return 0;
}