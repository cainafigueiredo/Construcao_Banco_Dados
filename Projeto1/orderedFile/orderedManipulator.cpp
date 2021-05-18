#include "orderedManipulator.h"
#include "orderedHeader.h"
#include <sys/stat.h>
#include <math.h>  
#include <dirent.h>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>
#include <filesystem>
#include <regex>

vector<wrapper> make_wrapper_buffer(vector<FixedRecord>buff,int order)
{
    vector<wrapper> vec_wp;
    int i = 0;
    for(;i<buff.size();i++)
    {
        wrapper wp(order,&buff[i]);
        vec_wp.push_back(wp);
    }
    // delete buff;
    return vec_wp;
}

//retorna true quando a.campo < b.campo
bool compare_records(wrapper &a,wrapper &b)
{   
    bool resultado = false;
    switch(a.compare_by)
    {
        case 0:    
            resultado = (a.r->id < b.r->id);   
            break;
        case 1:
            resultado = (strcmp(a.r->nomedep,b.r->nomedep) <= 0);
            break;
        case 2:
            resultado = (strcmp(a.r->de,b.r->de) <= 0);
            // cout<<"LEFT: "<<a.r->de<<"|RIGHT: "<<b.r->de<<"|result "<<resultado<<endl;
            break;
        case 3:
            resultado =  (strcmp(a.r->distr,b.r->distr) <= 0) ;
            break;
        case 4:
            resultado = (strcmp(a.r->mun,b.r->mun) <=0 );
            break;
        case 5:
            resultado = (a.r->tipoesc <= b.r->tipoesc);
            break;
        case 6:
            resultado = (a.r->cod_esc <= b.r->cod_esc);
            break;
        case 7:
            resultado = (strcmp(a.r->nomesc,b.r->nomesc) <= 0);
            break;
        case 8:
            resultado = (strcmp(a.r->ds_pais,b.r->ds_pais) <= 0);
            break;
        case 9:
            resultado = (a.r->n_alunos <= b.r->n_alunos);
            break;
    }
    return resultado;
}

void orderedManipulator::writeBufferToTempFile(vector<wrapper> buffer,
                                            orderedHeader<char[MAX_ORDERED_FIELD_SIZE]> *head,
                                            string fileName)
{
    if(fileName != "")
        this->createTempFile(fileName);
    else
        this->createTempFile();
    this->openTempFileWriting();
    this->tempFile.seekp(0, ios::beg);
    if(head)
    {
        this->tempFile.write( (char *) head, sizeof(orderedHeader<char[MAX_ORDERED_FIELD_SIZE]>));
    }
    for(int i=0; i < buffer.size(); i++){
        FixedRecord *cur = buffer[i].r;
        this->tempFile.write( (char *) cur, sizeof(FixedRecord));
        cout<<"Escrevendo registro "<<cur->id<<" no arquivo temp"<<endl;
    }
    this->closeTempFileWriting();
    remove (this->fileName.c_str());
    rename ((this->fileName + ".temp").c_str(), this->fileName.c_str());
}

void orderedManipulator::breakFileInNparts(string fileName,
orderedHeader<char[MAX_ORDERED_FIELD_SIZE]> *head,
vector<int>*total_per_file)
{
    int total_records = head->recordsAmount;
    ofstream temp_unordered_file;
    string cur_file;
    FixedRecord *rec_curr;
    this->currPos = 0;
    int i;
    int cur_temp_file = i = 0;
    int total = floor(MAX_SIZE_IN_MEM/sizeof(FixedRecord));
    while(total_records > 0)
    {
        rec_curr = this->findNext();
        cur_file = fileName+to_string(int(i/total));
        temp_unordered_file.open(cur_file.c_str(),fstream::binary | ios::out | ios::in | ios::app);
        temp_unordered_file.write((char*) rec_curr,sizeof(FixedRecord));
        temp_unordered_file.close();
        total_records--;
        cout<<"Writing "<<rec_curr->id<<" to file "<<(i/total)<<endl;
        (*total_per_file)[int(i/total)]++;
        i++;
    }     
}

FixedRecord* orderedManipulator::pickOrdered(map<int,int>*recToFile,vector<ifstream*>
*inputFiles,
vector<wrapper>*wp,int *totalOpenedFiles,vector<int>*total_per_file)
{
    if(wp->size() > 0)
    {
        sort((*wp).begin(), (*wp).end(), compare_records);
        FixedRecord *a = (*wp)[0].r;
        FixedRecord *nextReg;
        wp->erase(wp->begin());
        int fileId = recToFile->find(a->id)->second;
        cout<<"OK-PICK"<<endl;
        cout<<a->id<<" Try access file "<<fileId<<endl;
        if((*inputFiles)[fileId]->is_open())
        {
            if((*total_per_file)[fileId]==1)
            {
                cout<<"OK-PICK2"<<endl;
                cout<<"Closing file "<<fileId<<endl;
                (*inputFiles)[fileId]->close();
                recToFile->erase(a->id);
                (*totalOpenedFiles)--;
                cout<<"Arquivos restantes: "<<*totalOpenedFiles<<endl;
            }
            else
            {
                cout<<"OK-PICK3"<<endl;
                //cout<<"__"<<endl;
                nextReg = new FixedRecord;
                //cout<<"__"<<endl;
                (*inputFiles)[fileId]->read((char*) nextReg,sizeof(FixedRecord));
                //cout<<"__"<<endl;
                wrapper b(this->ordered_by,nextReg);
                //cout<<"__"<<endl;
                wp->push_back(b);
                //cout<<"__"<<endl;
                recToFile->insert(pair<int,int>(nextReg->id,fileId));
                cout<<"Pick: Inserting pair "<<nextReg->id<<","<<fileId<<endl;
                (*total_per_file)[fileId]--;
            }
        }
        cout<<"OK-PICK4"<<endl;
        return a;
    }
    return NULL;
}

void orderedManipulator::mergeNFiles(string path,
orderedHeader<char[MAX_ORDERED_FIELD_SIZE]>*head,
string pattern,vector<int>*total_per_file)
{
    ofstream output;
    pattern = pattern.substr(2);
    output.open("ordered_file",fstream::out|ios::binary);
    output.write((char*)head,sizeof(orderedHeader<char[MAX_ORDERED_FIELD_SIZE]>));
    map<int,int>recordIDToFileID;
    vector<FixedRecord> records;
    vector<ifstream *>inputFiles;
    ifstream *f;
    FixedRecord *fr;
    int fileId = 0;
    string filestr;
    for (const auto & entry : __fs::filesystem::directory_iterator(path))
    {
        filestr = entry.path().string().substr(2);
        if (regex_match(filestr, regex(pattern)))
        {
            // cout<<filestr<<endl;
            fr = new FixedRecord;
            f = new ifstream;
            f->open(filestr, fstream::in | fstream::binary);
            inputFiles.push_back(f);
            f->read((char*) fr,sizeof(FixedRecord));
            records.push_back(*fr);
            recordIDToFileID.insert(pair<int,int>(fr->id,fileId));
            cout<<"inserting pair "<<fr->id<<","<<fileId<<endl;
            fileId++;
        }
    }
    cout<<(*total_per_file)[0]<<"|"<<(*total_per_file)[1]<<"|"<<(*total_per_file).size()<<endl;
    vector<wrapper> wp = make_wrapper_buffer(records,this->ordered_by);
    bool keepReading =true;
    int i = head->recordsAmount;
    while (keepReading)
    {
        if(i >0 )
        {
            FixedRecord *a = this->pickOrdered(&recordIDToFileID,&inputFiles,&wp,&fileId,total_per_file);
            output.write((char*)a,sizeof(FixedRecord));
            cout<<a->de<<endl;
            i--;
        }
        else
            keepReading = false;

        // FixedRecord *a = wp[i].r;
        // output.write((char*)a,sizeof(FixedRecord));
        // i++;
        // if(i>wp.size()-1)
        // {
        //     break;
        // }
    }
    output.close();
}

void orderedManipulator::ordernateInRAM(string fileName)
{
        ifstream fileRead;
        vector<FixedRecord> buffer;
        // buffer.resize(total);
        fileRead.open(fileName, fstream::in | fstream::binary);
        //apenas o arquivo original possui o header, que será pulado. 
        //Essa condicao só é executada quando o arquivo todo cabe na RAM
        if(fileName.compare(this->fileName) != 0)  
            fileRead.seekg(sizeof(orderedHeader<char[MAX_ORDERED_FIELD_SIZE]>),ios::beg);
        int i = 0;
        while (!fileRead.eof())
        {   
            FixedRecord *f = new FixedRecord;
            fileRead.read((char *) f, sizeof(FixedRecord));
            buffer.push_back(*f);   
            i++;
        }
        fileRead.close();
        buffer.resize(i);
        vector<wrapper> wp = make_wrapper_buffer(buffer,this->ordered_by);
        sort(wp.begin(), wp.end(), compare_records);
        this->writeBufferToTempFile(wp,NULL,fileName);
}

void orderedManipulator::ordenateFile(string fileName)
{
    orderedHeader<char[MAX_ORDERED_FIELD_SIZE]> head; 
    ifstream fileRead;
    fileRead.open(fileName, fstream::in | fstream::binary);   
    fileRead.read((char *) &head, sizeof(head));
    fileRead.close();
    cout<<"ORDENANDO: "<<endl;
    if(MAX_SIZE_IN_MEM >= head.recordsAmount * head.recordSize )
    {   //LÊ E ORDENA NA RAM
        cout<<"NA RAM "<<head.recordsAmount * head.recordSize<<endl;
        this->ordernateInRAM(fileName);
    }
    else
    {
        cout<<"NO EXTERNO "<<head.recordsAmount * head.recordSize<<endl;
        vector<int> total_per_file;
        total_per_file.resize(ceil(sizeof(FixedRecord)*head.recordsAmount/MAX_SIZE_IN_MEM));
        for(int i = 0 ; i<total_per_file.size() + 1;i++)
        {
            cout<<i<<endl;
            total_per_file[i] = 0;
            cout<<total_per_file[i]<<endl;
        }
        this->breakFileInNparts(fileName,&head,&total_per_file);
        cout<<"OK"<<endl;
        string filestr;
        string pattern = "./"+fileName+"([0-9]+)$";
        for (const auto & entry : __fs::filesystem::directory_iterator("./"))
        {
            filestr = entry.path().string().substr(2);
            if (regex_match(filestr, regex(pattern)))
                this->ordernateInRAM(filestr);
        }
        cout<<"OK"<<endl;
        this->mergeNFiles("./",&head,pattern,&total_per_file);
        __fs::filesystem::remove(fileName);
        __fs::filesystem::rename("ordered_file",fileName);
        for (const auto & entry : __fs::filesystem::directory_iterator("./"))
        {
            filestr = entry.path().string().substr(2);
            if (regex_match(filestr,regex(pattern)))
                __fs::filesystem::remove(entry.path().string());
        }
    }
    cout<<"FIM ORDENACAO"<<endl;
}

FixedRecord *orderedManipulator::findNext()
{
    FixedRecord *record = NULL;
    this->openForReading();
    this->fileRead.seekg(this->currPos,ios::beg);
    if(this->currPos == 0)
    {
        orderedHeader <char[MAX_ORDERED_FIELD_SIZE]> head;
        this->fileRead.read((char *) &head, sizeof(head));
        this->currPos = this->fileRead.tellg();
        cout<<head.extension_file<<"| tellg: "<<this->currPos<<endl;
    }
    if(!this->fileRead.eof())
    {
        record = new FixedRecord;
        this->fileRead.read((char *) record, sizeof(FixedRecord));
        this->currPos = this->fileRead.tellg(); 
        // cout<<record->de<<"| tellg: "<<this->currPos<<endl;
    }
    else
        this->currPos = 0;
    this->closeForReading();
    return record;
}

int orderedManipulator::printRecord(FixedRecord r)
{
    cout << r.id << "\t" << r.nomedep << "\t" << r.de << "\t" <<
    r.distr << "\t" << r.mun << "\t" << r.tipoesc << "\t" << 
    r.cod_esc << "\t" << r.nomesc << "\t" << r.ds_pais << "\t" << r.n_alunos << endl;
    return 0;
}

int orderedManipulator::insertHeader(orderedHeader <char[MAX_ORDERED_FIELD_SIZE]> head)
{
    this->openForWriting();
    this->fileWrite.seekp(0, ios::beg);
    this->fileWrite.write( (char *) &head, sizeof(head));
    this->closeForWriting();
    return 0;
}

int orderedManipulator::findOne(int id)
{
    FixedRecord record;
    orderedHeader<char[MAX_ORDERED_FIELD_SIZE]> head;
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

int orderedManipulator::findWhereEqual(string attribute, int value)
{
    FixedRecord record;
    orderedHeader <char[MAX_ORDERED_FIELD_SIZE]>head;
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
int orderedManipulator::findWhereEqual(string attribute, double value)
{
    FixedRecord record;
    orderedHeader <char[MAX_ORDERED_FIELD_SIZE]>head;
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
int orderedManipulator::findWhereEqual(string attribute, string value)
{
    FixedRecord record;
    orderedHeader <char[MAX_ORDERED_FIELD_SIZE]>head;
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
            case 1: /*nomedep*/
                if (!string(record.nomedep).compare(value))
                {
                    records.push_back(record);
                }
                found = true;
                break;
            case 2: /*de*/
                if (!string(record.de).compare(value))
                {
                    records.push_back(record);
                }
                found = true;
                break;
            case 3: /*distr*/
                if (!string(record.distr).compare(value))
                {
                    records.push_back(record);
                }
                found = true;
                break;
            case 4: /*mun*/
                if (!string (record.mun).compare(value))
                {
                    records.push_back(record);
                }
                found = true;
                break;
            case 7: /*nomesc*/
                if (!string (record.nomesc).compare(value))
                {
                    records.push_back(record);
                }
                found = true;
                break;
            case 8: /*ds_pais*/
                if (!string (record.ds_pais).compare(value))
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

int orderedManipulator::findWhereBetween (string attribute, int value1, int value2)
{
    FixedRecord record;
    orderedHeader <char[MAX_ORDERED_FIELD_SIZE]>head;
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

int orderedManipulator::findWhereBetween (string attribute, double value1, double value2)
{
    FixedRecord record;
    orderedHeader <char[MAX_ORDERED_FIELD_SIZE]>head;
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

int orderedManipulator::removeOne(int id)
{
    orderedHeader<char[MAX_ORDERED_FIELD_SIZE]> head;
    FixedRecord record;
    bool found = false;
    int i, blocksAccessed = 0;
    int offset = 0;

    this->openForReading();
    this->fileRead.seekg(0, ios::beg);
    this->fileRead.read((char *) &head, sizeof(head));
    offset += sizeof(head);
    for (i = 0; i < head.recordsAmount; i++)
    {
        this->fileRead.read((char *) &record, sizeof(FixedRecord));
        blocksAccessed++;
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

    blocksAccessed += this->updateFreeListInsertDeleted(offset, head);
    cout << "Blocks Accessed: " << blocksAccessed << endl;
   
    return 0;
}

int orderedManipulator::removeBetween(string attribute, int value1, int value2)
{
    orderedHeader <char[MAX_ORDERED_FIELD_SIZE]>head;
    FixedRecord record;
    int attr, blocksAccessed = 0;
    int offset, auxOffset;
    int numDeleted = 0;
    int i = 0;
    map<string, int> m = this->createMap();
    attr = m[attribute];
    
    offset = sizeof(orderedHeader<char[MAX_ORDERED_FIELD_SIZE]>);
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
                    blocksAccessed += this->updateFreeListInsertDeleted(offset, head);
                    numDeleted++;
                }
                break;
            case 5: /*tipoesc*/
                if (record.tipoesc >= value1 && record.tipoesc <= value2)
                {
                    blocksAccessed += this->updateFreeListInsertDeleted(offset, head);
                    numDeleted++;
                }
                break;
            case 9: /*n_alunos*/
                if (record.n_alunos >= value1 && record.n_alunos <= value2)
                {
                    blocksAccessed += this->updateFreeListInsertDeleted(offset, head);
                    numDeleted++;
                }
                break;
            default:
                return -1;
        }
        offset += sizeof(FixedRecord);
        i++;
        blocksAccessed++;
    }while (i < head.recordsAmount);
    
    cout << "Blocks Accessed: " << blocksAccessed << endl;
    cout << "Rows deleted: " << numDeleted << endl;
    
    return 0;
}

int orderedManipulator::removeBetween(string attribute, double value1, double value2)
{
    orderedHeader <char[MAX_ORDERED_FIELD_SIZE]>head;
    FixedRecord record;
    int attr, blocksAccessed = 0;
    int offset, auxOffset;
    int numDeleted = 0;
    int i = 0;
    map<string, int> m = this->createMap();
    attr = m[attribute];
    
    offset = sizeof(orderedHeader<char[MAX_ORDERED_FIELD_SIZE]>);
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
                    blocksAccessed += this->updateFreeListInsertDeleted(offset, head);
                    numDeleted++;
                }
                break;
            case 5: /*tipoesc*/
                if (record.tipoesc >= value1 && record.tipoesc <= value2)
                {
                    blocksAccessed += this->updateFreeListInsertDeleted(offset, head);
                    numDeleted++;
                }
                break;
            case 9: /*n_alunos*/
                if (record.n_alunos >= value1 && record.n_alunos <= value2)
                {
                    blocksAccessed += this->updateFreeListInsertDeleted(offset, head);
                    numDeleted++;
                }
                break;
            default:
                return -1;
        }
        offset += sizeof(FixedRecord);
        i++;
    }while (i < head.recordsAmount);

    cout << "Blocks Accessed: " << blocksAccessed << endl;
    cout << "Rows deleted: " << numDeleted << endl;
    
    return 0;
}

int orderedManipulator::updateFreeListInsertDeleted(int offset, orderedHeader <char[MAX_ORDERED_FIELD_SIZE]>head)
{
    FixedRecord deleted;
    FixedRecord record;
    int blocksAccessed = 0;

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
            blocksAccessed++;
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
    
    return blocksAccessed;
}

int orderedManipulator::insertOne(string record)
{
    FixedRecord newR;
    orderedHeader <char[MAX_ORDERED_FIELD_SIZE]>head;
    int offset;
    int acessedBlocks = 0;

    this->openForReading();
    this->fileRead.seekg(0, ios::beg);
    this->fileRead.read( (char *) &head, sizeof(head));
    this->closeForReading();
    
    /*botar o id*/
    newR.readCSVLine(record);
    newR.id = head.lastID + 1;
    head.lastID++;
    /*if there is a deleted space*/
    if (head.freeList != 0)
    {
        FixedRecord auxRecord;
        this->openForReading();
        this->fileRead.seekg(head.freeList, ios::beg);
        this->fileRead.read( (char *) &auxRecord, sizeof(FixedRecord));
        acessedBlocks++;
        this->closeForReading();

        this->openForWriting();
        this->fileWrite.seekp(head.freeList, ios::beg);
        this->fileWrite.write((char *) &newR, sizeof(FixedRecord));
        head.freeList = auxRecord.n_alunos;
        this->closeForWriting();
        this->insertHeader(head);

        cout << "Accessed Blocks: " << acessedBlocks << endl;
        return 0;
    }
    
    offset = (head.recordsAmount * sizeof(FixedRecord)) + sizeof(orderedHeader<char[MAX_ORDERED_FIELD_SIZE]>);
    this->openForWriting();
    this->fileWrite.seekp(offset, ios::beg);
    this->fileWrite.write((char *) &newR, sizeof(FixedRecord));
    this->closeForWriting();
    head.recordsAmount++;
    this->insertHeader(head);

    cout << "Accessed Blocks: " << acessedBlocks << endl;
    return 0;
}

int orderedManipulator::insertMultiple(vector<string> inserts)
{
    for (auto const &record: inserts)
    {
        this->insertOne(record);
    }

    return 0;
}

int orderedManipulator::reorganize()
{
    FixedRecord record;
    orderedHeader <char[MAX_ORDERED_FIELD_SIZE]>head;
    int recordCount = 0;
    int accessedBlocks = 0;

    this->openForReading();
    this->fileRead.seekg(0, ios::beg);
    this->fileRead.read((char *) &head, sizeof(orderedHeader<char[MAX_ORDERED_FIELD_SIZE]>));
    this->closeForReading();
    
    if (head.freeList == 0)
    {
        return 0;
    }

    this->createTempFile();
    
    this->openTempFileWriting();
    this->openForReading();
    
    this->fileRead.seekg(sizeof(orderedHeader<char[MAX_ORDERED_FIELD_SIZE]>), ios::beg);
    this->tempFile.seekp(0, ios::beg);
    this->tempFile.write( (char *) &head, sizeof(orderedHeader<char[MAX_ORDERED_FIELD_SIZE]>));
    for (int i = 0; i < head.recordsAmount; i++)
    {
        this->fileRead.read ( (char *) &record, sizeof(FixedRecord));
        if (record.id != -1)
        {
            this->tempFile.write( (char *) &record, sizeof(FixedRecord));
            recordCount++;
        }
        accessedBlocks++;
    }
    head.recordsAmount = recordCount;
    this->tempFile.seekp(0, ios::beg);
    this->tempFile.write( (char *) &head, sizeof (orderedHeader<char[MAX_ORDERED_FIELD_SIZE]>));
    
    this->closeForReading();
    this->closeTempFileWriting();

    remove (this->fileName.c_str());
    rename ((this->fileName + ".temp").c_str(), this->fileName.c_str());
    
    cout << "Accessed Blocks: " << accessedBlocks << endl;
    return 0;
}


int orderedManipulator::createTempFile(string fileName)
{
    this->tempFile.open(fileName + ".temp", ios::binary | ios::out);
    if (!this->tempFile.good())
    {
        return -1;
    }
    this->tempFile.close();
    return 0;
}

int orderedManipulator::createTempFile()
{
    this->tempFile.open(this->fileName + ".temp", ios::binary | ios::out);
    if (!this->tempFile.good())
    {
        return -1;
    }
    this->tempFile.close();
    return 0;
}

int orderedManipulator::openTempFileWriting()
{
    this->tempFile.open(this->fileName + ".temp", fstream::binary | ios::out | ios::in);
    if (!this->tempFile.is_open())
    {
        return -1;
    }
    return 0;
}

int orderedManipulator::closeTempFileWriting()
{
    this->tempFile.close();
    return 0;
}