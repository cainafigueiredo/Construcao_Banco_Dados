#include "orderedManipulator.h"

void orderedManipulator::ordenateFile()
{
    orderedHeader<char[MAX_ORDERED_FIELD_SIZE]> head;    
    
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

int orderedManipulator::comparator (int a, int b){
    if (a>b){return 1;}
    if (a==b){return 0;}
    return -1;
}

int orderedManipulator::comparator (double a, double b){
    if (a>b){return 1;}
    if (a==b){return 0;}
    return -1;
}

int orderedManipulator::comparator (string a, string b){
    int cmp = strcmp( a.c_str() ,b.c_str());
    if (cmp>0){return 1;}
    if (cmp==0){return 0;}
    return -1;
}

int orderedManipulator::binarySearcher(int value){
    int attr, blocksAccessed,  i, med, pos;
    orderedHeader<char[MAX_ORDERED_FIELD_SIZE]> head;
    bool found = false;
    map<string, int> m = this->createMap();
    this->openForReading();
    this->fileRead.read((char *) &head, sizeof(head));
    attr = m[head.ordered_by];
    FixedRecord recordLow, recordMed, recordHigh;
    int inf = 0;

    this->fileRead.seekg(0, ios::end);
    int sup = ((int)this->fileRead.tellg()-(head.headerSize))/sizeof(recordHigh)-1; //index of last element

    i = 0;
    while (i<10){
        i++;

        med = (inf+sup)/2;
        this->fileRead.seekg(head.headerSize + inf * head.recordSize,ios::beg);
        this->fileRead.read((char *) &recordLow, head.recordSize);
        this->fileRead.seekg(head.headerSize + med * head.recordSize,ios::beg);
        this->fileRead.read((char *) &recordMed, head.recordSize);
        this->fileRead.seekg(head.headerSize + sup * head.recordSize,ios::beg);
        this->fileRead.read((char *) &recordHigh, head.recordSize);
        switch (attr)
        {
            case 0: /*id*/
                if (recordHigh.id == -1){sup = sup-1; break;}
                if (recordLow.id == -1){inf = inf-1; break;}
                if (recordMed.id == -1){
                    if(!orderedManipulator::comparator(recordLow.id, value)){ return inf;}
                    inf=inf+1;
                    break;}
                if(!orderedManipulator::comparator(recordHigh.id, value)){ return sup;}
                if(!orderedManipulator::comparator(recordLow.id, value)){ return inf;}
                if(!orderedManipulator::comparator(recordMed.id, value)){ return med;}
                if ((med == sup)||(sup == inf )||(med == inf )){ return -1;}
                pos = orderedManipulator::comparator(recordMed.id, value) ;
                if(pos == 1){sup = med;}
                else {inf = med;}
                break;
            case 5: /*tipoesc*/
                if (recordHigh.tipoesc == -1){sup = sup-1; break;}
                if (recordLow.tipoesc == -1){inf = inf-1; break;}
                if (recordMed.tipoesc == -1){
                    if(!orderedManipulator::comparator(recordLow.tipoesc, value)){ return inf;}
                    inf=inf+1;
                    break;}
                if(!orderedManipulator::comparator(recordHigh.tipoesc, value)){ return sup;}
                if(!orderedManipulator::comparator(recordLow.tipoesc, value)){ return inf;}
                if(!orderedManipulator::comparator(recordMed.tipoesc, value)){ return med;}
                if ((med == sup)||(sup == inf )||(med == inf )){ return -1;}
                pos = orderedManipulator::comparator(recordMed.tipoesc, value) ;
                if(pos == 1){sup = med;}
                else {inf = med;}
                break;
            case 9: /*n_alunos*/
                if (recordHigh.id == -1){sup = sup-1; break;}
                if (recordLow.id == -1){inf = inf-1; break;}
                if (recordMed.id == -1){
                    if(!orderedManipulator::comparator(recordLow.n_alunos, value)){ return inf;}
                    inf=inf+1;
                    break;}
                if(!orderedManipulator::comparator(recordHigh.n_alunos, value)){ return sup;}
                if(!orderedManipulator::comparator(recordLow.n_alunos, value)){ return inf;}
                if(!orderedManipulator::comparator(recordMed.n_alunos, value)){ return med;}
                if ((med == sup)||(sup == inf )||(med == inf )){ return -1;}
                pos = orderedManipulator::comparator(recordMed.n_alunos, value) ;
                if(pos == 1){sup = med;}
                else {inf = med;}
                break;
            default:    
                return -1;
        }



    }
    return -1;
}

int orderedManipulator::binarySearcher(double value){
    int attr, blocksAccessed,  i, med, pos;
    orderedHeader<char[MAX_ORDERED_FIELD_SIZE]> head;
    bool found = false;
    map<string, int> m = this->createMap();
    this->openForReading();
    this->fileRead.read((char *) &head, sizeof(head));
    attr = m[head.ordered_by];
    FixedRecord recordLow, recordMed, recordHigh;
    int inf = 0;

    this->fileRead.seekg(0, ios::end);
    int sup = ((int)this->fileRead.tellg()-(head.headerSize))/sizeof(recordHigh)-1; //index of last element


    i = 0;
    while (i<999999999){
        i++;

        med = (inf+sup)/2;
        this->fileRead.seekg(head.headerSize + inf * head.recordSize,ios::beg);
        this->fileRead.read((char *) &recordLow, head.recordSize);
        this->fileRead.seekg(head.headerSize + med * head.recordSize,ios::beg);
        this->fileRead.read((char *) &recordMed, head.recordSize);
        this->fileRead.seekg(head.headerSize + sup * head.recordSize,ios::beg);
        this->fileRead.read((char *) &recordHigh, head.recordSize);
        switch (attr)
        {
            case 6: /*cod_esc*/
                if (recordHigh.cod_esc == -1.0){sup = sup-1; break;}
                if (recordLow.cod_esc == -1.0){inf = inf-1; break;}
                if (recordMed.cod_esc == -1.0){
                    if(!orderedManipulator::comparator(recordLow.cod_esc, value)){ return inf;}
                    inf=inf+1;
                    break;}
                if(!orderedManipulator::comparator(recordHigh.cod_esc, value)){ return sup;}
                if(!orderedManipulator::comparator(recordLow.cod_esc, value)){ return inf;}
                if(!orderedManipulator::comparator(recordMed.cod_esc, value)){ return med;}
                if ((med == sup)||(sup == inf )||(med == inf )){ return -1;}
                pos = orderedManipulator::comparator(recordMed.cod_esc, value) ;
                if(pos == 1){sup = med;}
                else {inf = med;}
               break;
            default:    
                return -1;
        }



    }
    return -1;
}

int orderedManipulator::binarySearcher(string value){
    int attr, blocksAccessed,  i, med, pos;
    orderedHeader<char[MAX_ORDERED_FIELD_SIZE]> head;
    bool found = false;
    map<string, int> m = this->createMap();
    this->openForReading();
    this->fileRead.read((char *) &head, sizeof(head));
    attr = m[head.ordered_by];
    FixedRecord recordLow, recordMed, recordHigh;
    int inf = 0;

    this->fileRead.seekg(0, ios::end);
    int sup = ((int)this->fileRead.tellg()-(head.headerSize))/sizeof(recordHigh)-1; //index of last element





    i = 0;




    while (i<99999999){
        i++;
        med = (inf+sup)/2;

        this->fileRead.seekg(head.headerSize + inf * head.recordSize,ios::beg);
        this->fileRead.read((char *) &recordLow, head.recordSize);
        this->fileRead.seekg(head.headerSize + med * head.recordSize,ios::beg);
        this->fileRead.read((char *) &recordMed, head.recordSize);
        this->fileRead.seekg(head.headerSize + sup * head.recordSize,ios::beg);
        this->fileRead.read((char *) &recordHigh, head.recordSize);
        switch (attr)
       {
            case 1: /*nomedep*/
                if (!orderedManipulator::comparator(recordHigh.nomedep, "DELETED")){sup = sup-1; break;}
                if (!orderedManipulator::comparator(recordLow.nomedep, "DELETED")){inf = inf-1; break;}
                if (!orderedManipulator::comparator(recordMed.nomedep, "DELETED")){
                    if(!orderedManipulator::comparator(recordLow.nomedep, value)){ return inf;}
                    inf=inf+1;
                    break;}
                if(!orderedManipulator::comparator(recordHigh.nomedep, value)){ return sup;}
                if(!orderedManipulator::comparator(recordLow.nomedep, value)){ return inf;}
                if(!orderedManipulator::comparator(recordMed.nomedep, value)){ return med;}
                if ((med == sup)||(sup == inf )||(med == inf )){ return -1;}
                pos = orderedManipulator::comparator(recordMed.nomedep, value) ;
                if(pos == 1){sup = med;}
                else {inf = med;}
                break;
            case 2: /*de*/
                if (!orderedManipulator::comparator(recordHigh.de, "DELETED")){sup = sup-1; break;}
                if (!orderedManipulator::comparator(recordLow.de, "DELETED")){inf = inf-1; break;}
                if (!orderedManipulator::comparator(recordMed.de, "DELETED")){
                    if(!orderedManipulator::comparator(recordLow.de, value)){ return inf;}
                    inf=inf+1;
                    break;}
                if(!orderedManipulator::comparator(recordHigh.de, value)){ return sup;}
                if(!orderedManipulator::comparator(recordLow.de, value)){ return inf;}
                if(!orderedManipulator::comparator(recordMed.de, value)){ return med;}
                if ((med == sup)||(sup == inf )||(med == inf )){ return -1;}
                pos = orderedManipulator::comparator(recordMed.de, value) ;
                if(pos == 1){sup = med;}
                else {inf = med;}
                break;
            case 3: /*distr*/
                if (!orderedManipulator::comparator(recordHigh.distr, "DELETED")){sup = sup-1; break;}
                if (!orderedManipulator::comparator(recordLow.distr, "DELETED")){inf = inf-1; break;}
               if (!orderedManipulator::comparator(recordMed.distr, "DELETED")){
                    if(!orderedManipulator::comparator(recordLow.distr, value)){ return inf;}
                    inf=inf+1;
                    break;}
                if(!orderedManipulator::comparator(recordHigh.distr, value)){ return sup;}
                if(!orderedManipulator::comparator(recordLow.distr, value)){ return inf;}
                if(!orderedManipulator::comparator(recordMed.distr, value)){ return med;}
                if ((med == sup)||(sup == inf )||(med == inf )){ return -1;}
                pos = orderedManipulator::comparator(recordMed.distr, value) ;
                if(pos == 1){sup = med;}
                else {inf = med;}
                break;
            case 4: /*mun*/
                if (!orderedManipulator::comparator(recordHigh.mun, "DELETED")){sup = sup-1; break;}
                if (!orderedManipulator::comparator(recordLow.mun, "DELETED")){inf = inf-1; break;}
                if (!orderedManipulator::comparator(recordMed.mun, "DELETED")){
                    if(!orderedManipulator::comparator(recordLow.mun, value)){ return inf;}
                    inf=inf+1;
                    break;}
                if(!orderedManipulator::comparator(recordHigh.mun, value)){ return sup;}
                if(!orderedManipulator::comparator(recordLow.mun, value)){ return inf;}
                if(!orderedManipulator::comparator(recordMed.mun, value)){ return med;}
                if ((med == sup)||(sup == inf )||(med == inf )){ return -1;}
                pos = orderedManipulator::comparator(recordMed.mun, value) ;
                if(pos == 1){sup = med;}
                else {inf = med;}
                break;
            case 7: /*nomesc*/
                if (!orderedManipulator::comparator(recordHigh.nomesc, "DELETED")){sup = sup-1; break;}
                if (!orderedManipulator::comparator(recordLow.nomesc, "DELETED")){inf = inf-1; break;}
                if (!orderedManipulator::comparator(recordMed.nomesc, "DELETED")){ 
                    if(!orderedManipulator::comparator(recordLow.nomesc, value)){ return inf;}
                    inf=inf+1;
                    break;}
                if(!orderedManipulator::comparator(recordHigh.nomesc, value)){ return sup;}
                if(!orderedManipulator::comparator(recordLow.nomesc, value)){ return inf;}
                if(!orderedManipulator::comparator(recordMed.nomesc, value)){ return med;}
                if ((med == sup)||(sup == inf )||(med == inf )){ return -1;}
                pos = orderedManipulator::comparator(recordMed.nomesc, value) ;
                if(pos == 1){sup = med;}
                else {inf = med;}
                break;
            case 8: /*ds_pais*/
                if (!orderedManipulator::comparator(recordHigh.ds_pais, "DELETED")){sup = sup-1; break;}
                if (!orderedManipulator::comparator(recordLow.ds_pais, "DELETED")){inf = inf-1; break;}
                if (!orderedManipulator::comparator(recordMed.ds_pais, "DELETED")){
                    if(!orderedManipulator::comparator(recordLow.ds_pais, value)){ return inf;}
                    inf=inf+1;
                    break;}
                if(!orderedManipulator::comparator(recordHigh.ds_pais, value)){ return sup;}
                if(!orderedManipulator::comparator(recordLow.ds_pais, value)){ return inf;}
                if(!orderedManipulator::comparator(recordMed.ds_pais, value)){ return med;}
                if ((med == sup)||(sup == inf )||(med == inf )){ return -1;}
                pos = orderedManipulator::comparator(recordMed.ds_pais, value) ;
                if(pos == 1){sup = med;}
                else {inf = med;}
                break;
            default:    
                return -1;
        }



    }
    return -1;
}


int orderedManipulator::findOne(int id)
{
    FixedRecord record;
    orderedHeader<char[MAX_ORDERED_FIELD_SIZE]> head;
    int blocksAccessed;
    bool found = false;
    this->openForReading();
    this->fileRead.read((char *) &head, sizeof(head));
    this->closeForReading();
    if (!orderedManipulator::comparator(head.ordered_by, "id")){
        int ind = orderedManipulator::binarySearcher(id);
        if (id == -1){return -1;}
        this->fileRead.seekg(head.headerSize + ind * head.recordSize,ios::beg);
        this->fileRead.read((char *) &record, sizeof(FixedRecord));
        this->printSchema();
        this->printRecord(record);
        //cout << "Blocks Acessed: " << blocksAccessed << endl;
        this->closeForReading();
        return 0;
    }
    else{
        this->openForReading();
        this->fileRead.seekg(head.headerSize,ios::beg);
        for (int i = 0; i < head.recordsAmount; i++)
        {   this->fileRead.read((char *) &record, sizeof(FixedRecord));
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
    return -1;
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


    this->fileRead.seekg(0, ios::end);
    int sup = ((int)this->fileRead.tellg()-(head.headerSize))/sizeof(record)-1; //index of last element

    int atord = m[head.ordered_by];
    atord = m[head.ordered_by];

    if (atord == attr){
        this->closeForReading();
        int index = orderedManipulator::binarySearcher(value);
        
        this->fileRead.seekg(head.headerSize + index * head.recordSize,ios::beg);
        this->fileRead.read((char *) &record, head.recordSize);
        records.push_back(record);

        int setBreak = false;
        int i = index;
        while (i< sup){
            if (setBreak == true) {break;}
            i++;
            this->fileRead.seekg(head.headerSize + i * head.recordSize,ios::beg);
            this->fileRead.read((char *) &record, head.recordSize);

            switch (attr)
            {
                case 0: /*id*/
                    if (record.id == value)
                    {
                        records.push_back(record);
                    }
                    else if (record.id != -1) {setBreak = true;}
                    found = true;
                    break;
                case 5: /*tipoesc*/
                    if (record.tipoesc == value)
                    {
                        records.push_back(record);
                    }
                    else if (record.tipoesc != -1) {setBreak = true;}
                    found = true;
                    break;
                case 9: /*n_alunos*/
                    if (record.n_alunos == value)
                    {
                        records.push_back(record);
                    }
                    else if (record.id != -1) {setBreak = true;}
                    found = true;
                    break;
                default:
                    return -1;
            }


            
        }
        i = index;
        setBreak = false;
        while (i>0){
            if (setBreak == true) {break;}
            i--;
            this->fileRead.seekg(head.headerSize + i * head.recordSize,ios::beg);
            this->fileRead.read((char *) &record, head.recordSize);
            switch (attr)
            {
                case 0: /*id*/
                    if (record.id == value)
                    {
                        records.push_back(record);
                    }
                    else if (record.id != -1) {setBreak = true;}
                    found = true;
                    break;
                case 5: /*tipoesc*/
                    if (record.tipoesc == value)
                    {
                        records.push_back(record);
                    }
                    else if (record.tipoesc != -1) {setBreak = true;}
                    found = true;
                    break;
                case 9: /*n_alunos*/
                    if (record.n_alunos == value)
                    {
                        records.push_back(record);
                    }
                    else if (record.id != -1) {setBreak = true;}
                    found = true;
                    break;
                default:
                    return -1;
            }


            
        }
        this->closeForReading();
    }
    else{
        this->fileRead.seekg(sizeof(head), ios::beg);
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
    //cout << "Blocks Acessed: " << blocksAccessed << endl;

    this->closeForReading();
    return 0;
    

}

int orderedManipulator::findWhereEqual(string attribute, double value)
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


    this->fileRead.seekg(0, ios::end);
    int sup = ((int)this->fileRead.tellg()-(head.headerSize))/sizeof(record)-1; //index of last element

    int atord = m[head.ordered_by];
    atord = m[head.ordered_by];

    if (atord == attr){
        this->closeForReading();
        int index = orderedManipulator::binarySearcher(value);
        
        this->fileRead.seekg(head.headerSize + index * head.recordSize,ios::beg);
        this->fileRead.read((char *) &record, head.recordSize);
        records.push_back(record);

        int setBreak = false;
        int i = index;
        while (i< sup){
            if (setBreak == true) {break;}
            i++;
            this->fileRead.seekg(head.headerSize + i * head.recordSize,ios::beg);
            this->fileRead.read((char *) &record, head.recordSize);

            switch (attr)
            {
                case 6: 
                    if (record.cod_esc == value)
                    {
                        records.push_back(record);
                    }
                    else if (record.cod_esc != -1) {setBreak = true;}
                    found = true;
                    break;
                default:
                    return -1;
            }


            
        }
        i = index;
        setBreak = false;
        while (i>0){
            if (setBreak == true) {break;}
            i--;
            this->fileRead.seekg(head.headerSize + i * head.recordSize,ios::beg);
            this->fileRead.read((char *) &record, head.recordSize);
            switch (attr)
            {
                case 6: 
                    if (record.cod_esc == value)
                    {
                        records.push_back(record);
                    }
                    else if (record.cod_esc != -1) {setBreak = true;}
                    found = true;
                    break;
                default:
                    return -1;
            }


            
        }
        this->closeForReading();
    }
    else{
        this->fileRead.seekg(sizeof(head), ios::beg);
        for (i = 0; i < head.recordsAmount; i++)
        {
            this->fileRead.read((char *) &record, sizeof(FixedRecord));
            switch (attr)
            {
                case 6: 
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
    //cout << "Blocks Acessed: " << blocksAccessed << endl;

    this->closeForReading();
    return 0;
    

}

int orderedManipulator::findWhereEqual(string attribute, string value)
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


    this->fileRead.seekg(0, ios::end);
    int sup = ((int)this->fileRead.tellg()-(head.headerSize))/sizeof(record)-1; //index of last element

    int atord = m[head.ordered_by];
    atord = m[head.ordered_by];

    if (atord == attr){
        this->closeForReading();
        int index = orderedManipulator::binarySearcher(value);
        
        this->fileRead.seekg(head.headerSize + index * head.recordSize,ios::beg);
        this->fileRead.read((char *) &record, head.recordSize);
        records.push_back(record);

        int setBreak = false;
        int i = index;
        while (i< sup){
            if (setBreak == true) {break;}
            i++;
            this->fileRead.seekg(head.headerSize + i * head.recordSize,ios::beg);
            this->fileRead.read((char *) &record, head.recordSize);

            switch (attr)
            {
                case 1: 
                    if (!orderedManipulator::comparator(record.nomedep,value))
                    {
                        records.push_back(record);
                    }
                    else if (orderedManipulator::comparator(record.nomedep,"DELETED")) {setBreak = true;}
                    found = true;
                    break;
                case 2: 
                    if (!orderedManipulator::comparator(record.de,value))
                    {
                        records.push_back(record);
                    }
                    else if (orderedManipulator::comparator(record.nomedep,"DELETED")) {setBreak = true;}
                    found = true;
                    break;
                case 3: 
                    if (!orderedManipulator::comparator(record.distr,value))
                    {
                        records.push_back(record);
                    }
                    else if (orderedManipulator::comparator(record.distr,"DELETED")) {setBreak = true;}
                    found = true;
                    break;
                case 4: 
                    if (!orderedManipulator::comparator(record.mun,value))
                    {
                        records.push_back(record);
                    }
                    else if (orderedManipulator::comparator(record.mun,"DELETED")) {setBreak = true;}
                    found = true;   
                    break;
                case 7: 
                    if (!orderedManipulator::comparator(record.nomesc,value))
                    {
                        records.push_back(record);
                    }
                    else if (orderedManipulator::comparator(record.nomesc,"DELETED")) {setBreak = true;}
                    found = true;
                    break;
                case 8: 
                    if (!orderedManipulator::comparator(record.ds_pais,value))
                    {
                        records.push_back(record);
                    }
                    else if (orderedManipulator::comparator(record.ds_pais,"DELETED")) {setBreak = true;}
                    found = true;
                    break;
                default:
                    return -1;
            }


            
        }
        i = index;
        setBreak = false;
        while (i>0){
            if (setBreak == true) {break;}
            i--;
            this->fileRead.seekg(head.headerSize + i * head.recordSize,ios::beg);
            this->fileRead.read((char *) &record, head.recordSize);
            switch (attr)
            {
                case 1: 
                    if (!orderedManipulator::comparator(record.nomedep,value))
                    {
                        records.push_back(record);
                    }
                    else if (orderedManipulator::comparator(record.nomedep,"DELETED")) {setBreak = true;}
                    found = true;
                    break;
                case 2: 
                    if (!orderedManipulator::comparator(record.de,value))
                    {
                        records.push_back(record);
                    }
                    else if (orderedManipulator::comparator(record.nomedep,"DELETED")) {setBreak = true;}
                    found = true;
                    break;
                case 3: 
                    if (!orderedManipulator::comparator(record.distr,value))
                    {
                        records.push_back(record);
                    }
                    else if (orderedManipulator::comparator(record.distr,"DELETED")) {setBreak = true;}
                    found = true;
                    break;
                case 4: 
                    if (!orderedManipulator::comparator(record.mun,value))
                    {
                        records.push_back(record);
                    }
                    else if (orderedManipulator::comparator(record.mun,"DELETED")) {setBreak = true;}
                    found = true;   
                    break;
                case 7: 
                    if (!orderedManipulator::comparator(record.nomesc,value))
                    {
                        records.push_back(record);
                    }
                    else if (orderedManipulator::comparator(record.nomesc,"DELETED")) {setBreak = true;}
                    found = true;
                    break;
                case 8: 
                    if (!orderedManipulator::comparator(record.ds_pais,value))
                    {
                        records.push_back(record);
                    }
                    else if (orderedManipulator::comparator(record.ds_pais,"DELETED")) {setBreak = true;}
                    found = true;
                    break;
                default:
                    return -1;
            }


            
        }
        this->closeForReading();
    }
    else{
        this->fileRead.seekg(sizeof(head), ios::beg);
        for (i = 0; i < head.recordsAmount; i++)
        {
            this->fileRead.read((char *) &record, sizeof(FixedRecord));
            switch (attr)
            {
                case 1: 
                    if (!orderedManipulator::comparator(record.nomedep,value))
                    {
                        records.push_back(record);
                    }
                    found = true;
                    break;
                case 2: 
                    if (!orderedManipulator::comparator(record.de,value))
                    {
                        records.push_back(record);
                    }
                    found = true;
                    break;
                case 3: 
                    if (!orderedManipulator::comparator(record.distr,value))
                    {
                        records.push_back(record);
                    }
                    found = true;
                    break;
                case 4: 
                    if (!orderedManipulator::comparator(record.mun,value))
                    {
                        records.push_back(record);
                    }
                    found = true;   
                    break;
                case 7: 
                    if (!orderedManipulator::comparator(record.nomesc,value))
                    {
                        records.push_back(record);
                    }
                    found = true;
                    break;
                case 8: 
                    if (!orderedManipulator::comparator(record.ds_pais,value))
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
    //cout << "Blocks Acessed: " << blocksAccessed << endl;

    this->closeForReading();
    return 0;
    

}


int orderedManipulator::findWhereBetween (string attribute, int value1, int value2)
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


    this->fileRead.seekg(0, ios::end);
    int sup = ((int)this->fileRead.tellg()-(head.headerSize))/sizeof(record)-1; //index of last element

    int atord = m[head.ordered_by];
    if (atord == attr){
        this->closeForReading();
        int index1 = -1;
        int index2 = -1;
        int j = value1;
        while (index1 == -1){
            j++;
            index1 = orderedManipulator::binarySearcher(j);
            this->closeForReading();
            if (j > value2){return -1;} 
        } 
        j = value2;
        while (index2 == -1){
            j--;
            index2 = orderedManipulator::binarySearcher(j);
            this->closeForReading();
            if (j < value1){return -1;} 
        } 
        
        this->openForReading();

        this->fileRead.seekg(head.headerSize + index1 * head.recordSize,ios::beg);
        this->fileRead.read((char *) &record, head.recordSize);
        records.push_back(record);
        
        if (index1 != index2){
            this->fileRead.seekg(head.headerSize + index2 * head.recordSize,ios::beg);
            this->fileRead.read((char *) &record, head.recordSize);
            records.push_back(record);
        }
        
        int setBreak = false;
        int i = index2;
        
        while (i< sup){
            if (setBreak == true) {break;}
            i++;
            this->fileRead.seekg(head.headerSize + i * head.recordSize,ios::beg);
            this->fileRead.read((char *) &record, head.recordSize);

            switch (attr)
            {
                case 0: /*id*/
                    if (record.id <= value2)
                    {
                        records.push_back(record);
                    }
                    else if (record.id != -1) {setBreak = true;}
                    found = true;
                    break;
                case 5: /*tipoesc*/
                    if (record.tipoesc <= value2)
                    {
                        records.push_back(record);
                    }
                    else if (record.tipoesc != -1) {setBreak = true;}
                    found = true;
                    break;
                case 9: /*n_alunos*/
                    if (record.n_alunos <= value2)
                    {
                        records.push_back(record);
                    }
                    else if (record.id != -1) {setBreak = true;}
                    found = true;
                    break;
                default:
                    return -1;
            }


            
        }
        i = index1;
        setBreak = false;
        while (i>0){
            if (setBreak == true) {break;}
            i--;
            this->fileRead.seekg(head.headerSize + i * head.recordSize,ios::beg);
            this->fileRead.read((char *) &record, head.recordSize);
            switch (attr)
            {
                case 0: /*id*/
                    if (record.id >= value1)
                    {
                        records.push_back(record);
                    }
                    else if (record.id != -1) {setBreak = true;}
                    found = true;
                    break;
                case 5: /*tipoesc*/
                    if (record.tipoesc >= value1)
                    {
                        records.push_back(record);
                    }
                    else if (record.tipoesc != -1) {setBreak = true;}
                    found = true;
                    break;
                case 9: /*n_alunos*/
                    if (record.n_alunos >= value1)
                    {
                        records.push_back(record);
                    }
                    else if (record.n_alunos != -1) {setBreak = true;}
                    found = true;
                    break;
                default:
                    return -1;
            }


            
        }
        i = index1;
        while (i<index2-1){
            i++;
            this->fileRead.seekg(head.headerSize + i * head.recordSize,ios::beg);
            this->fileRead.read((char *) &record, head.recordSize);
            if (record.id != -1)
            {
                records.push_back(record);
            }
            
        }
        this->closeForReading();
    }
    else{
        this->fileRead.seekg(sizeof(head), ios::beg);
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

    //cout << "Blocks Acessed: " << blocksAccessed << endl;
   
    this->closeForReading();
    return 0;
    

}

int orderedManipulator::findWhereBetween (string attribute, double value1, double value2)
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


    this->fileRead.seekg(0, ios::end);
    int sup = ((int)this->fileRead.tellg()-(head.headerSize))/sizeof(record)-1; //index of last element

    int atord = m[head.ordered_by];
    if (atord == attr){
        this->closeForReading();
        int index1 = -1;
        int index2 = -1;
        double j = (double) value1;

        //cout << value1 << " " << value2 << endl;
        while (index1 == -1){
            j++;
            index1 = orderedManipulator::binarySearcher(j);
            this->closeForReading();
            if (j > value2){return -1;} 
        } 
        j = (double )value2;
        while (index2 == -1){
            j--;
            index2 = orderedManipulator::binarySearcher(j);
            this->closeForReading();
            if (j < value1){return -1;} 
        } 
        this->openForReading();

        this->fileRead.seekg(head.headerSize + index1 * head.recordSize,ios::beg);
        this->fileRead.read((char *) &record, head.recordSize);
        records.push_back(record);

        if (index1 != index2){
            this->fileRead.seekg(head.headerSize + index2 * head.recordSize,ios::beg);
            this->fileRead.read((char *) &record, head.recordSize);
            records.push_back(record);
        }

        int setBreak = false;
        int i = index2;
        while (i< sup){
            if (setBreak == true) {break;}
            i++;
            this->fileRead.seekg(head.headerSize + i * head.recordSize,ios::beg);
            this->fileRead.read((char *) &record, head.recordSize);

            switch (attr)
            {
                case 6: 
                    if (record.cod_esc <= value2)
                    {
                        records.push_back(record);
                    }
                    else if (record.cod_esc != -1) {setBreak = true;}
                    found = true;
                    break;
                default:
                    return -1;
            }


            
        }
        i = index1;
        setBreak = false;
        while (i>0){
            if (setBreak == true) {break;}
            i--;
            this->fileRead.seekg(head.headerSize + i * head.recordSize,ios::beg);
            this->fileRead.read((char *) &record, head.recordSize);
            switch (attr)
            {
                case 6: 
                    if (record.cod_esc >= value1)
                    {
                        records.push_back(record);
                    }
                    else if (record.cod_esc != -1) {setBreak = true;}
                    found = true;
                    break;
                default:
                    return -1;
            }


            
        }
        i = index1;
        while (i<index2-1){
            i++;
            this->fileRead.seekg(head.headerSize + i * head.recordSize,ios::beg);
            this->fileRead.read((char *) &record, head.recordSize);
            if (record.cod_esc != -1)
            {
                records.push_back(record);
            }
            
        }
        this->closeForReading();
    }
    else{
        this->fileRead.seekg(sizeof(head), ios::beg);
        for (i = 0; i < head.recordsAmount; i++)
        {
            this->fileRead.read((char *) &record, sizeof(FixedRecord));
            switch (attr)
            {
                case 6: /*id*/
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

    //cout << "Blocks Acessed: " << blocksAccessed << endl;
   
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
    if (head.ordered_by == "id"){
        this->closeForReading();
        int index = orderedManipulator::binarySearcher(id);
        offset = index * sizeof(record);
    
    }
    else{
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
    }
    if (!found)
    {
        return -1;
    }
    blocksAccessed += this->updateFreeListInsertDeleted(offset, head);
    //cout << "Blocks Accessed: " << blocksAccessed << endl;
   
    return 0;
}

int orderedManipulator::removeBetween(string attribute, int value1, int value2)
{
    FixedRecord record;
    orderedHeader <char[MAX_ORDERED_FIELD_SIZE]>head;
    int numDeleted;
    int attr, blocksAccessed,  i;
    bool found = false;
    map<string, int> m = this->createMap();
    attr = m[attribute];
    this->openForReading();
    this->fileRead.read((char *) &head, sizeof(head));


    this->fileRead.seekg(0, ios::end);
    int sup = ((int)this->fileRead.tellg()-(head.headerSize))/sizeof(record)-1; //index of last element

    int atord = m[head.ordered_by];
    if (atord == attr){
        this->closeForReading();
        int index1 = -1;
        int index2 = -1;
        int j = value1;
        while (index1 == -1){
            j++;
            index1 = orderedManipulator::binarySearcher(j);
            this->closeForReading();
            if (j > value2){return -1;} 
        } 
        j = value2;
        while (index2 == -1){
            j--;
            index2 = orderedManipulator::binarySearcher(j);
            this->closeForReading();
            if (j < value1){return -1;} 
        } 
        
        this->openForReading();


        this->updateFreeListInsertDeleted(index1 * sizeof(record), head);
        numDeleted++;

        
        if (index1 != index2){
            this->updateFreeListInsertDeleted(index2 * sizeof(record), head);
            numDeleted++;
        }
        
        int setBreak = false;
        int i = index2;
        
        while (i< sup){
            if (setBreak == true) {break;}
            i++;
            this->fileRead.seekg(head.headerSize + i * head.recordSize,ios::beg);
            this->fileRead.read((char *) &record, head.recordSize);

            switch (attr)
            {
                case 0: /*id*/
                    if (record.id <= value2)
                    {
                        this->updateFreeListInsertDeleted(i * sizeof(record), head);
                        numDeleted++;
                    }
                    else if (record.id != -1) {setBreak = true;}
                    found = true;
                    break;
                case 5: /*tipoesc*/
                    if (record.tipoesc <= value2)
                    {
                        this->updateFreeListInsertDeleted(i * sizeof(record), head);
                        numDeleted++;
                    }
                    else if (record.tipoesc != -1) {setBreak = true;}
                    found = true;
                    break;
                case 9: /*n_alunos*/
                    if (record.n_alunos <= value2)
                    {
                        this->updateFreeListInsertDeleted(i * sizeof(record), head);
                        numDeleted++;
                    }
                    else if (record.id != -1) {setBreak = true;}
                    found = true;
                    break;
                default:
                    return -1;
            }


            
        }
        i = index1;
        setBreak = false;
        while (i>0){
            if (setBreak == true) {break;}
            i--;
            this->fileRead.seekg(head.headerSize + i * head.recordSize,ios::beg);
            this->fileRead.read((char *) &record, head.recordSize);
            switch (attr)
            {
                case 0: /*id*/
                    if (record.id >= value1)
                    {
                        this->updateFreeListInsertDeleted(i * sizeof(record), head);
                        numDeleted++;
                    }
                    else if (record.id != -1) {setBreak = true;}
                    found = true;
                    break;
                case 5: /*tipoesc*/
                    if (record.tipoesc >= value1)
                    {
                        this->updateFreeListInsertDeleted(i * sizeof(record), head);
                        numDeleted++;
                    }
                    else if (record.tipoesc != -1) {setBreak = true;}
                    found = true;
                    break;
                case 9: /*n_alunos*/
                    if (record.n_alunos >= value1)
                    {
                        this->updateFreeListInsertDeleted(i * sizeof(record), head);
                        numDeleted++;
                    }
                    else if (record.n_alunos != -1) {setBreak = true;}
                    found = true;
                    break;
                default:
                    return -1;
            }


            
        }
        i = index1;
        while (i<index2-1){
            i++;
            this->fileRead.seekg(head.headerSize + i * head.recordSize,ios::beg);
            this->fileRead.read((char *) &record, head.recordSize);
            if (record.id != -1)
            {
                this->updateFreeListInsertDeleted(i * sizeof(record), head);
                numDeleted++;
            }
            
        }
        this->closeForReading();
    }
    else{
        this->fileRead.seekg(sizeof(head), ios::beg);
        for (i = 0; i < head.recordsAmount; i++)
        {   cout << i << endl;
            this->fileRead.read((char *) &record, sizeof(FixedRecord));
            switch (attr)
            {
                case 0: /*id*/
                    if (record.id >= value1 && record.id <= value2)
                    {
                        this->updateFreeListInsertDeleted(i * sizeof(record), head);
                        numDeleted++;
                    }
                    found = true;
                    break;
                case 5: /*tipoesc*/
                    if (record.tipoesc >= value1 && record.tipoesc <= value2)
                    {
                        this->updateFreeListInsertDeleted(i * sizeof(record), head);
                        numDeleted++;
                    }
                    found = true;
                    break;
                case 9: /*n_alunos*/
                    if (record.n_alunos >= value1 && record.n_alunos <= value2)
                    {
                        this->updateFreeListInsertDeleted(i * sizeof(record), head);
                        numDeleted++;
                    }
                    found = true;
                    break;
                default:
                    return -1;
            }
        }
    }
    blocksAccessed = i;
    
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