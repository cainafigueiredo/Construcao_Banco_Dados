#include "FixedHeapManipulator.h"

int FixedHeapManipulator::printRecord(FixedRecord r)
{
    cout << r.id << "\t" << r.nomedep << "\t" << r.de << "\t" <<
    r.distr << "\t" << r.mun << "\t" << r.tipoesc << "\t" << 
    r.cod_esc << "\t" << r.nomesc << "\t" << r.ds_pais << "\t" << r.n_alunos << endl;

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
    int attr;
    bool found;
    map<string, int> m = this->createMap();
    attr = m[attribute];
    
    this->openForReading();
    this->fileRead.read((char *) &head, sizeof(head));
    for (int i = 0; i < head.recordsAmount; i++)
    {
        this->fileRead.read((char *) &record, sizeof(FixedRecord));
        cout << "attr: " << attr << " n_alunos: " << record.n_alunos << endl;
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
    if (found)
    {
        cout << records.size() << endl;
        this->printSchema();
        for (auto const &r : records)
        {
            cout << "teste" << endl;
            this->printRecord(r);
        }
    }
   
    this->closeForReading();
    
}
int FixedHeapManipulator::findWhereEqual(string attribute, double value)
{
    
}
int FixedHeapManipulator::findWhereEqual(string attribute, string value)
{
    
}
