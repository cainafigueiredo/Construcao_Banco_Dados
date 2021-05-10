#include "FixedHeapManipulator.h"

int FixedHeapManipulator::printRecord(FixedRecord r)
{
    cout << r.id << "\t" << r.nomedep << "\t" << r.de << "\t" <<
    r.distr << "\t" << r.mun << "\t" << r.tipoesc << "\t" << 
    r.cod_esc << "\t" << r.nomesc << "\t" << r.ds_pais << "\t" << r.n_alunos << endl;
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

    cout << records.size() << endl;
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

    cout << records.size() << endl;
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

    cout << records.size() << endl;
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

    cout << records.size() << endl;
    this->printSchema();
    for (auto const &r : records)
    {
        this->printRecord(r);
    }

    cout << "Blocks Acessed: " << blocksAccessed << endl;
   
    this->closeForReading();
    return 0;
}

