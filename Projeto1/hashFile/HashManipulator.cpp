#include "HashManipulator.h"

HashManipulator::HashManipulator(string fileName) : FileManipulator(fileName) {
    
}

int HashManipulator::printRecord(HashFixedRecord r)
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
    HashFixedRecord record;
    HashHeader head;
    int bucket_id, block_addr, n_recordsInBucket, n_recordsInBlock, n_overflowRecords, recordAddr;
    int blocksAccessed = 0;
    bool found = false;
    this->openForReading();
    this->fileRead.read((char *) &head, sizeof(head));

    bucket_id = head.hashFunction(id);
    block_addr = head.buckets[bucket_id].block_addr;
    n_recordsInBucket = head.buckets[bucket_id].numberOfRecords;
    n_overflowRecords = (n_recordsInBucket <= head.getBlockingFactor()) ? 0 : n_recordsInBucket % head.getBlockingFactor();
    n_recordsInBlock = n_recordsInBucket - n_overflowRecords; 

    // cout << "Records: " << n_recordsInBucket << "\n";

    // Se houver registros no bloco do bucket, então comece a buscar entre eles.
    if (n_recordsInBlock > 0) {
    
        recordAddr = (block_addr * head.blockSize);
        this->fileRead.seekg(sizeof(head) + recordAddr);

        for (int i = 0; i < n_recordsInBlock; i++) {
            // Procurando pelo registro no bloco mapeado pelo bucket.
            this->fileRead.read((char *) &record, sizeof(HashFixedRecord));
            blocksAccessed++;

            if (record.id == id && !record.deleted) {
                found = true;
                break;
            }
        }
    }

    // Se houver registros de overflow no bucket, então comece a buscar entre eles.
    if (n_overflowRecords > 0 && !found) {
        int overflow_record_block_addr = head.buckets[bucket_id].overflow.first_block_addr;
        int overflow_record_block_offset = head.buckets[bucket_id].overflow.first_block_offset;
        // cout << overflow_record_block_addr << " , " << overflow_record_block_offset << "\n";  
        while (overflow_record_block_addr > 0) {
            // Carrega o próximo registro de overflow.
            recordAddr = (overflow_record_block_addr * head.blockSize + overflow_record_block_offset * sizeof(HashFixedRecord));
            // cout << record.nomedep << "\n";
            // cout << "\n\n" << recordAddr << "\n\n";
            this->fileRead.seekg(sizeof(head) + recordAddr);
            this->fileRead.read((char *) &record, sizeof(HashFixedRecord));
            // cout << "\n\n" << record.nextRecord_block_addr << " , " << record.nextRecord_block_offset << "\n\n";
            blocksAccessed++;
            
            // Verificando se o registro é o que estamos procurando.
            if (record.id == id && !record.deleted) {
                found = true;
                break;
            }

            // Carregando o próximo registro da lista de overflows.
            overflow_record_block_addr = record.nextRecord_block_addr;
            overflow_record_block_offset = record.nextRecord_block_offset;
            // cout << overflow_record_block_addr << " , " << overflow_record_block_offset << "\n";  

        };
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
    HashFixedRecord record;
    HashHeader head;
    vector<HashFixedRecord> records;
    int attr, blocksAccessed,  i;
    bool found = false;
    map<string, int> m = this->createMap();
    attr = m[attribute];
    
    this->openForReading();
    this->fileRead.read((char *) &head, sizeof(head));

    int bucket_id, block_addr, n_recordsInBlock, n_recordsInBucket, n_overflowRecords, recordAddr;
    int overflow_record_block_addr, overflow_record_block_offset;

    blocksAccessed = 0;

    // Procurando pelos registros nos blocos mapeados pelos buckets.
    for (bucket_id = 0; bucket_id < NUMBER_OF_BUCKETS; bucket_id++)
    {        
        block_addr = head.buckets[bucket_id].block_addr;
        n_recordsInBucket = head.buckets[bucket_id].numberOfRecords;
        n_overflowRecords = (n_recordsInBucket <= head.getBlockingFactor()) ? 0 : n_recordsInBucket % head.getBlockingFactor();
        n_recordsInBlock = n_recordsInBucket - n_overflowRecords; 
        
        recordAddr = (block_addr * head.blockSize);
        this->fileRead.seekg(sizeof(head) + recordAddr);

        for (int i = 0; i < n_recordsInBlock; i++) {
            this->fileRead.read((char *) &record, sizeof(HashFixedRecord));
            blocksAccessed++;

            switch (attr)
            {
                case 0: /*id*/
                    if (record.id == value)
                    {
                        records.push_back(record);
                        found = true;
                    }
                    break;
                case 5: /*tipoesc*/
                    if (record.tipoesc == value)
                    {
                        records.push_back(record);
                        found = true;
                    }
                    break;
                case 9: /*n_alunos*/
                    if (record.n_alunos == value)
                    {
                        records.push_back(record);
                        found = true;
                    }
                    break;
                default:
                    return -1;
            }
        }
    }

    // Procurando pelos registros nos blocos de overflow.
    for (int OFRecord = 0; OFRecord < head.numberOfOverflowRecords; OFRecord++)
    {        
        overflow_record_block_addr = (NUMBER_OF_BUCKETS) + (head.numberOfOverflowRecords / head.getBlockingFactor());
        overflow_record_block_offset = head.numberOfOverflowRecords % head.getBlockingFactor();
        
        recordAddr = (overflow_record_block_addr * head.blockSize) + (overflow_record_block_offset * sizeof(record));
        this->fileRead.seekg(sizeof(head) + recordAddr);

        this->fileRead.read((char *) &record, sizeof(HashFixedRecord));
        blocksAccessed++;

        switch (attr)
        {
            case 0: /*id*/
                if (record.id == value)
                {
                    records.push_back(record);
                    found = true;
                }
                break;
            case 5: /*tipoesc*/
                if (record.tipoesc == value)
                {
                    records.push_back(record);
                    found = true;
                }
                break;
            case 9: /*n_alunos*/
                if (record.n_alunos == value)
                {
                    records.push_back(record);
                    found = true;
                }
                break;
            default:
                return -1;
            
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
    HashFixedRecord record;
    HashHeader head;
    vector<HashFixedRecord> records;
    int attr, blocksAccessed,  i;
    bool found = false;
    map<string, int> m = this->createMap();
    attr = m[attribute];
    
    this->openForReading();
    this->fileRead.read((char *) &head, sizeof(head));

    int bucket_id, block_addr, n_recordsInBlock, n_recordsInBucket, n_overflowRecords, recordAddr;
    int overflow_record_block_addr, overflow_record_block_offset;

    blocksAccessed = 0;

    // Procurando pelos registros nos blocos mapeados pelos buckets.
    for (bucket_id = 0; bucket_id < NUMBER_OF_BUCKETS; bucket_id++)
    {        
        block_addr = head.buckets[bucket_id].block_addr;
        n_recordsInBucket = head.buckets[bucket_id].numberOfRecords;
        n_overflowRecords = (n_recordsInBucket <= head.getBlockingFactor()) ? 0 : n_recordsInBucket % head.getBlockingFactor();
        n_recordsInBlock = n_recordsInBucket - n_overflowRecords; 
        
        recordAddr = (block_addr * head.blockSize);
        this->fileRead.seekg(sizeof(head) + recordAddr);

        for (int i = 0; i < n_recordsInBlock; i++) {
            this->fileRead.read((char *) &record, sizeof(HashFixedRecord));
            blocksAccessed++;

            switch (attr)
            {
                case 6: /*cod_esc*/
                    if (record.cod_esc == value)
                    {
                        records.push_back(record);
                        found = true;
                    }
                    break;
                default:
                    return -1;
            }
        }
    }

    // Procurando pelos registros nos blocos de overflow.
    for (int OFRecord = 0; OFRecord < head.numberOfOverflowRecords; OFRecord++)
    {        
        overflow_record_block_addr = (NUMBER_OF_BUCKETS) + (head.numberOfOverflowRecords / head.getBlockingFactor());
        overflow_record_block_offset = head.numberOfOverflowRecords % head.getBlockingFactor();
        
        recordAddr = (overflow_record_block_addr * head.blockSize) + (overflow_record_block_offset * sizeof(record));
        this->fileRead.seekg(sizeof(head) + recordAddr);

        this->fileRead.read((char *) &record, sizeof(HashFixedRecord));
        blocksAccessed++;

        switch (attr)
        {
            case 6: /*cod_esc*/
                if (record.cod_esc == value)
                {
                    records.push_back(record);
                    found = true;
                }
                break;
            default:
                return -1;
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
    HashFixedRecord record;
    HashHeader head;
    vector<HashFixedRecord> records;
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
            this->fileRead.read((char *) &record, sizeof(HashFixedRecord));
            blocksAccessed++;

            switch (attr)
            {
                case 1: /*nomedep*/
                    if (string(record.nomedep).compare(value) == 0)
                    {
                        records.push_back(record);
                        found = true;
                    }
                    break;
                case 2: /*de*/
                    if (string(record.de).compare(value) == 0)
                    {
                        records.push_back(record);
                        found = true;
                    }
                    break;
                case 3: /*distr*/
                    if (string(record.distr).compare(value) == 0)
                    {
                        records.push_back(record);
                        found = true;
                    }
                    break;
                case 4: /*mun*/
                    if (string (record.mun).compare(value) == 0)
                    {
                        records.push_back(record);
                        found = true;
                    }
                    break;
                case 7: /*nomesc*/
                    if (string (record.nomesc).compare(value) == 0)
                    {
                        records.push_back(record);
                        found = true;
                    }
                    break;
                case 8: /*ds_pais*/
                    if (string (record.ds_pais).compare(value) == 0)
                    {
                        records.push_back(record);
                        found = true;
                    }
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

int HashManipulator::findWhereBetween(string attribute, int value1, int value2)
{
    HashFixedRecord record;
    HashHeader head;
    vector<HashFixedRecord> records;
    int attr, blocksAccessed,  i;
    bool found = false;
    map<string, int> m = this->createMap();
    attr = m[attribute];
    
    this->openForReading();
    this->fileRead.read((char *) &head, sizeof(head));

    int bucket_id, block_addr, n_recordsInBlock, n_recordsInBucket, n_overflowRecords, recordAddr;
    int overflow_record_block_addr, overflow_record_block_offset;

    blocksAccessed = 0;

    // Procurando pelos registros nos blocos mapeados pelos buckets.
    for (bucket_id = 0; bucket_id < NUMBER_OF_BUCKETS; bucket_id++)
    {        
        block_addr = head.buckets[bucket_id].block_addr;
        n_recordsInBucket = head.buckets[bucket_id].numberOfRecords;
        n_overflowRecords = (n_recordsInBucket <= head.getBlockingFactor()) ? 0 : n_recordsInBucket % head.getBlockingFactor();
        n_recordsInBlock = n_recordsInBucket - n_overflowRecords; 
        
        recordAddr = (block_addr * head.blockSize);
        this->fileRead.seekg(sizeof(head) + recordAddr);

        for (int i = 0; i < n_recordsInBlock; i++) {
            this->fileRead.read((char *) &record, sizeof(HashFixedRecord));
            blocksAccessed++;

            switch (attr)
            {
                case 0: /*id*/
                    if (record.id >= value1 && record.id <= value2)
                    {
                        records.push_back(record);
                        found = true;
                    }
                    break;
                case 5: /*tipoesc*/
                    if (record.tipoesc >= value1 && record.tipoesc <= value2)
                    {
                        records.push_back(record);
                        found = true;
                    }
                    break;
                case 9: /*n_alunos*/
                    if (record.n_alunos >= value1 && record.n_alunos <= value2)
                    {
                        records.push_back(record);
                        found = true;
                    }
                    break;
                default:
                    return -1;
            }
        }
    }

    // Procurando pelos registros nos blocos de overflow.
    for (int OFRecord = 0; OFRecord < head.numberOfOverflowRecords; OFRecord++)
    {        
        overflow_record_block_addr = (NUMBER_OF_BUCKETS) + (head.numberOfOverflowRecords / head.getBlockingFactor());
        overflow_record_block_offset = head.numberOfOverflowRecords % head.getBlockingFactor();
        
        recordAddr = (overflow_record_block_addr * head.blockSize) + (overflow_record_block_offset * sizeof(record));
        this->fileRead.seekg(sizeof(head) + recordAddr);

        this->fileRead.read((char *) &record, sizeof(HashFixedRecord));
        blocksAccessed++;

        switch (attr)
        {
            case 0: /*id*/
                if (record.id >= value1 && record.id <= value2)
                {
                    records.push_back(record);
                    found = true;
                }
                break;
            case 5: /*tipoesc*/
                if (record.tipoesc >= value1 && record.tipoesc <= value2)
                {
                    records.push_back(record);
                    found = true;
                }
                break;
            case 9: /*n_alunos*/
                if (record.n_alunos >= value1 && record.n_alunos <= value2)
                {
                    records.push_back(record);
                    found = true;
                }
                break;
            default:
                return -1;
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

int HashManipulator::findWhereBetween(string attribute, double value1, double value2)
{
    HashFixedRecord record;
    HashHeader head;
    vector<HashFixedRecord> records;
    int attr, blocksAccessed,  i;
    bool found = false;
    map<string, int> m = this->createMap();
    attr = m[attribute];
    
    this->openForReading();
    this->fileRead.read((char *) &head, sizeof(head));

    int bucket_id, block_addr, n_recordsInBlock, n_recordsInBucket, n_overflowRecords, recordAddr;
    int overflow_record_block_addr, overflow_record_block_offset;

    blocksAccessed = 0;

    // Procurando pelos registros nos blocos mapeados pelos buckets.
    for (bucket_id = 0; bucket_id < NUMBER_OF_BUCKETS; bucket_id++)
    {        
        block_addr = head.buckets[bucket_id].block_addr;
        n_recordsInBucket = head.buckets[bucket_id].numberOfRecords;
        n_overflowRecords = (n_recordsInBucket <= head.getBlockingFactor()) ? 0 : n_recordsInBucket % head.getBlockingFactor();
        n_recordsInBlock = n_recordsInBucket - n_overflowRecords; 
        
        recordAddr = (block_addr * head.blockSize);
        this->fileRead.seekg(sizeof(head) + recordAddr);

        for (int i = 0; i < n_recordsInBlock; i++) {
            this->fileRead.read((char *) &record, sizeof(HashFixedRecord));
            blocksAccessed++;

            switch (attr)
            {
                case 6: /*cod_esc*/
                    if (record.cod_esc >= value1 && record.cod_esc <= value2)
                    {
                        records.push_back(record);
                        found = true;
                    }
                    break;
                default:
                    return -1;
            }
        }
    }

    // Procurando pelos registros nos blocos de overflow.
    for (int OFRecord = 0; OFRecord < head.numberOfOverflowRecords; OFRecord++)
    {        
        overflow_record_block_addr = (NUMBER_OF_BUCKETS) + (head.numberOfOverflowRecords / head.getBlockingFactor());
        overflow_record_block_offset = head.numberOfOverflowRecords % head.getBlockingFactor();
        
        recordAddr = (overflow_record_block_addr * head.blockSize) + (overflow_record_block_offset * sizeof(record));
        this->fileRead.seekg(sizeof(head) + recordAddr);

        this->fileRead.read((char *) &record, sizeof(HashFixedRecord));
        blocksAccessed++;

        switch (attr)
        {
            case 6: /*cod_esc*/
                if (record.cod_esc >= value1 && record.cod_esc <= value2)
                {
                    records.push_back(record);
                    found = true;
                }
                break;
            default:
                return -1;
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

int HashManipulator::removeOne(int id)
{

    /* 
    Encontre o registro com o id solicitado
    Se nenhum registro for encontrado, retorne -1
    Caso contrário, seja R o endereço do registro encontrado
    Adicione esse registro na lista encadeada de registros excluídos
    Decremente o número de registros no bucket
    Decremente o número de registros no arquivo de registros
    Se R estiver na lista de overflow
        Faça R_next ser o endereço do próximo registro na lista de overflow depois de R
        Se R é o primeiro da lista de overflow
            Atualiza o endereço do primeiro registro de overflow no bucket para R_next
        Senão 
            Faça R_prev ser o endereço do registro que precede R na lista de overflow
            Atualiza o endereço do próximo registro de overflow em R_prev para R_next
        Decremente o número de registros de overflow
    */
    HashFixedRecord record, last_record;
    HashHeader head;
    int bucket_id, block_addr, n_recordsInBucket, n_recordsInBlock, n_overflowRecords, recordAddr;
    int blocksAccessed = 0;
    bool found = false;
    this->openForReading();
    this->fileRead.read((char *) &head, sizeof(head));
    int foundRecordBlock, foundRecordOffset;

    bucket_id = head.hashFunction(id);
    block_addr = head.buckets[bucket_id].block_addr;
    n_recordsInBucket = head.buckets[bucket_id].numberOfRecords;
    n_overflowRecords = (n_recordsInBucket <= head.getBlockingFactor()) ? 0 : n_recordsInBucket % head.getBlockingFactor();
    n_recordsInBlock = n_recordsInBucket - n_overflowRecords; 

    // cout << "Records: " << n_recordsInBucket << "\n";

    // Se houver registros no bloco do bucket, então comece a buscar entre eles.
    if (n_recordsInBlock > 0) {

        recordAddr = (block_addr * head.blockSize);
        this->fileRead.seekg(sizeof(head) + recordAddr);

        for (int i = 0; i < n_recordsInBlock; i++) {
            // Procurando pelo registro no bloco mapeado pelo bucket.
            this->fileRead.read((char *) &record, sizeof(HashFixedRecord));
            blocksAccessed++;

            if (record.id == id) {
                found = true;
                record.deleted = true;
                foundRecordBlock = block_addr;
                foundRecordOffset = i;
                break;
            }
        }
    }

    // Se houver registros de overflow no bucket, então comece a buscar entre eles.
    if (n_overflowRecords > 0 && !found) {
        int cur_overflow_record_block_addr = head.buckets[bucket_id].overflow.first_block_addr;
        int cur_overflow_record_block_offset = head.buckets[bucket_id].overflow.first_block_offset;
        int last_overflow_record_block_addr = -1;
        int last_overflow_record_block_offset = -1;
        // cout << cur_overflow_record_block_addr << " , " << cur_overflow_record_block_offset << "\n";  
        while (cur_overflow_record_block_addr > 0) {
            // Carrega o próximo registro de overflow.
            recordAddr = (cur_overflow_record_block_addr * head.blockSize + cur_overflow_record_block_offset * sizeof(HashFixedRecord));
            // cout << record.nomedep << "\n";
            // cout << "\n\n" << recordAddr << "\n\n";
            this->fileRead.seekg(sizeof(head) + recordAddr);
            this->fileRead.read((char *) &record, sizeof(HashFixedRecord));
            // cout << "\n\n" << record.nextRecord_block_addr << " , " << record.nextRecord_block_offset << "\n\n";
            blocksAccessed++;
            
            // Verificando se o registro é o que estamos procurando.
            if (record.id == id) {
                found = true;
                record.deleted = true; 

                foundRecordBlock = cur_overflow_record_block_addr;
                foundRecordOffset = cur_overflow_record_block_offset;

                // Se for o primeiro da lista de overflow, então altera o ponteiro do bucket
                if (last_overflow_record_block_addr == -1) {
                    head.buckets[bucket_id].overflow.first_block_addr = cur_overflow_record_block_addr;
                    head.buckets[bucket_id].overflow.first_block_offset = cur_overflow_record_block_offset;
                    head.buckets[bucket_id].overflow.last_block_addr = cur_overflow_record_block_addr;
                    head.buckets[bucket_id].overflow.last_block_offset = cur_overflow_record_block_offset;
                }
                // Se não for o primeiro da lista de overflow, então altera o ponteiro do registro anterior
                else {
                    recordAddr = (last_overflow_record_block_addr * head.blockSize + last_overflow_record_block_offset * sizeof(HashFixedRecord));
                    this->fileRead.seekg(sizeof(head) + recordAddr);
                    this->fileRead.read((char *) &last_record, sizeof(HashFixedRecord));
                    last_record.nextRecord_block_addr = record.nextRecord_block_addr;
                    last_record.nextRecord_block_offset = record.nextRecord_block_offset;
                    // Escrevendo o registro de volta no arquivo
                    this->closeForReading();
                    this->openForWriting();
                    this->fileWrite.seekp(sizeof(head) + recordAddr);
                    this->fileWrite.write((char *) &last_record, sizeof(HashFixedRecord));
                    this->closeForWriting();
                }

                break;
            }

            // Carregando o próximo registro da lista de overflows.
            last_overflow_record_block_addr = cur_overflow_record_block_addr;
            last_overflow_record_block_offset = cur_overflow_record_block_offset;
            cur_overflow_record_block_addr = record.nextRecord_block_addr;
            cur_overflow_record_block_offset = record.nextRecord_block_offset;
            // cout << cur_overflow_record_block_addr << " , " << cur_overflow_record_block_offset << "\n";  

        };
    }  
    

    if (!found)
    {
        cout << "Record " << id << " does not exist." << endl;
        return -1;
    }

    // Se foi encontrado, então também foi removido. Vamos atualizar o registro e as variáveis com 
    // os números de registros
    recordAddr = (foundRecordBlock * head.blockSize + foundRecordOffset * sizeof(HashFixedRecord));
    this->openForWriting();
    this->fileWrite.seekp(sizeof(head) + recordAddr);
    this->fileWrite.write((char *) &record, sizeof(HashFixedRecord));
    this->closeForWriting();

    head.numberOfDeletedRecords++;
    head.buckets[bucket_id].numDeleted++;
    // head.decrementNumberOfOverflowRecords();
    // head.decrementRecordsAmount();
    // head.buckets[bucket_id].decrementNumberOfRecords();
    cout << "Record " << id << " was removed." << endl;


    //this->printSchema();
    //this->printRecord(record);
    cout << "Blocks Acessed: " << blocksAccessed << endl;
    this->insertHeader(head);
    this->closeForReading();

    return 0;
}

int HashManipulator::removeBetween(string attribute, int value1, int value2)
{
    HashFixedRecord record;
    HashHeader head;
    int attr, blocksAccessed,  i;
    bool found = false;
    map<string, int> m = this->createMap();
    attr = m[attribute];
    
    this->openForReading();
    this->fileRead.read((char *) &head, sizeof(head));

    int bucket_id, block_addr, n_recordsInBlock, n_recordsInBucket, n_overflowRecords, recordAddr;
    int overflow_record_block_addr, overflow_record_block_offset;
    bool toRemove = false;
    blocksAccessed = 0;

    // Procurando pelos registros nos blocos mapeados pelos buckets.
    for (bucket_id = 0; bucket_id < NUMBER_OF_BUCKETS; bucket_id++)
    {        
        block_addr = head.buckets[bucket_id].block_addr;
        n_recordsInBucket = head.buckets[bucket_id].numberOfRecords;
        n_overflowRecords = (n_recordsInBucket <= head.getBlockingFactor()) ? 0 : n_recordsInBucket % head.getBlockingFactor();
        n_recordsInBlock = n_recordsInBucket - n_overflowRecords; 
        
        recordAddr = (block_addr * head.blockSize);
        this->fileRead.seekg(sizeof(head) + recordAddr);

        for (int i = 0; i < n_recordsInBlock; i++) {
            this->fileRead.read((char *) &record, sizeof(HashFixedRecord));
            blocksAccessed++;
        
            switch (attr)
            {
                case 0: /*id*/
                    if (record.id >= value1 && record.id <= value2)
                    {
                        found = true;
                        toRemove = true;
                    }
                    break;
                case 5: /*tipoesc*/
                    if (record.tipoesc >= value1 && record.tipoesc <= value2)
                    {
                        found = true;
                        toRemove = true;
                    }
                    break;
                case 9: /*n_alunos*/
                    if (record.n_alunos >= value1 && record.n_alunos <= value2)
                    {
                        found = true;
                        toRemove = true;
                    }
                    break;
                default:
                    return -1;
            }

            if (toRemove) {
                toRemove = false;
                int previousReadPointer = this->fileRead.tellg();
                this->closeForReading();
                this->removeOne(record.id);
                this->openForReading();
                this->fileRead.seekg(previousReadPointer);
            }
        }
    }

    // Procurando pelos registros nos blocos de overflow.
    for (int OFRecord = 0; OFRecord < head.numberOfOverflowRecords; OFRecord++)
    {        
        overflow_record_block_addr = (NUMBER_OF_BUCKETS) + (head.numberOfOverflowRecords / head.getBlockingFactor());
        overflow_record_block_offset = head.numberOfOverflowRecords % head.getBlockingFactor();
        
        recordAddr = (overflow_record_block_addr * head.blockSize) + (overflow_record_block_offset * sizeof(record));
        this->fileRead.seekg(sizeof(head) + recordAddr);

        this->fileRead.read((char *) &record, sizeof(HashFixedRecord));
        blocksAccessed++;

        switch (attr)
        {
            case 0: /*id*/
                if (record.id >= value1 && record.id <= value2)
                {
                    found = true;
                    toRemove = true;
                }
                break;
            case 5: /*tipoesc*/
                if (record.tipoesc >= value1 && record.tipoesc <= value2)
                {
                    found = true;
                    toRemove = true;
                }
                break;
            case 9: /*n_alunos*/
                if (record.n_alunos >= value1 && record.n_alunos <= value2)
                {
                    found = true;
                    toRemove = true;
                }
                break;
            default:
                return -1;
        }

        if (toRemove) {
            toRemove = false;
            int previousReadPointer = this->fileRead.tellg();
            this->closeForReading();
            this->removeOne(record.id);
            this->openForReading();
            this->fileRead.seekg(previousReadPointer);
        }
    }

    if (!found)
    {
        return -1;
    }

    //cout << "Blocks Acessed: " << blocksAccessed << endl;

    this->closeForReading();
    return 0;
}


int HashManipulator::removeBetween(string attribute, double value1, double value2)
{
    HashFixedRecord record;
    HashHeader head;
    int attr, blocksAccessed,  i;
    bool found = false;
    map<string, int> m = this->createMap();
    attr = m[attribute];
    
    this->openForReading();
    this->fileRead.read((char *) &head, sizeof(head));

    int bucket_id, block_addr, n_recordsInBlock, n_recordsInBucket, n_overflowRecords, recordAddr;
    int overflow_record_block_addr, overflow_record_block_offset;
    bool toRemove = false;
    blocksAccessed = 0;

    // Procurando pelos registros nos blocos mapeados pelos buckets.
    for (bucket_id = 0; bucket_id < NUMBER_OF_BUCKETS; bucket_id++)
    {        
        block_addr = head.buckets[bucket_id].block_addr;
        n_recordsInBucket = head.buckets[bucket_id].numberOfRecords;
        n_overflowRecords = (n_recordsInBucket <= head.getBlockingFactor()) ? 0 : n_recordsInBucket % head.getBlockingFactor();
        n_recordsInBlock = n_recordsInBucket - n_overflowRecords; 
        
        recordAddr = (block_addr * head.blockSize);
        this->fileRead.seekg(sizeof(head) + recordAddr);

        for (int i = 0; i < n_recordsInBlock; i++) {
            this->fileRead.read((char *) &record, sizeof(HashFixedRecord));
            blocksAccessed++;
        
            switch (attr)
            {
                case 6: /*cod_esc*/
                    if (record.cod_esc >= value1 && record.cod_esc <= value2)
                    {
                        found = true;
                        toRemove = true;
                    }
                    break;
                default:
                    return -1;
            }

            if (toRemove) {
                toRemove = false;
                int previousReadPointer = this->fileRead.tellg();
                this->closeForReading();
                this->removeOne(record.id);
                this->openForReading();
                this->fileRead.seekg(previousReadPointer);
            }
        }
    }

    // Procurando pelos registros nos blocos de overflow.
    for (int OFRecord = 0; OFRecord < head.numberOfOverflowRecords; OFRecord++)
    {        
        overflow_record_block_addr = (NUMBER_OF_BUCKETS) + (head.numberOfOverflowRecords / head.getBlockingFactor());
        overflow_record_block_offset = head.numberOfOverflowRecords % head.getBlockingFactor();
        
        recordAddr = (overflow_record_block_addr * head.blockSize) + (overflow_record_block_offset * sizeof(record));
        this->fileRead.seekg(sizeof(head) + recordAddr);

        this->fileRead.read((char *) &record, sizeof(HashFixedRecord));
        blocksAccessed++;

        switch (attr)
        {
            case 6: /*cod_esc*/
                if (record.cod_esc >= value1 && record.cod_esc <= value2)
                {
                    found = true;
                    toRemove = true;
                }
                break;
            default:
                return -1;
        }

        if (toRemove) {
            toRemove = false;
            int previousReadPointer = this->fileRead.tellg();
            this->closeForReading();
            this->removeOne(record.id);
            this->openForReading();
            this->fileRead.seekg(previousReadPointer);
        }
    }

    if (!found)
    {
        return -1;
    }

    //cout << "Blocks Acessed: " << blocksAccessed << endl;

    this->closeForReading();
    return 0;
}

int HashManipulator:: insertOne (string strRecord)
{
    HashHeader header;
    HashFixedRecord newRecord, tempRecord;
    int bucket_id, block_addr, n_recordsInBlock;
    int overflow_block_addr, overflow_block_offset;
    int recordAddr;
    int last_overflow_block_addr, last_overflow_block_offset, last_overflow_addr;
    newRecord.readCSVLine(strRecord);

    bucket_id = header.hashFunction(newRecord.id);

    // Encontrando o bloco onde o registro deveria ser inserido e obtendo o número de 
    // registros nesse bloco
    block_addr = header.buckets[bucket_id].block_addr;
    n_recordsInBlock = header.buckets[bucket_id].numberOfRecords;

    // Investigando se com a inserção haverá overflow de registros dentro do bloco. 
    // Em caso afirmativo, a inserção é feita na lista de registros de overflow. 
    // Caso contrário, a inserção é feita na próxima posição livre do bloco.
    if ((n_recordsInBlock+1)*header.recordSize >= header.blockSize) {
        // Se chegou aqui, é porque o registro precisa ser inserido na lista de overflow.
        // Na verdade, o registro é inserido na primeira posição livre dentre os blocos que
        // não são mapeados pelos buckets.
        overflow_block_addr = (NUMBER_OF_BUCKETS) + (header.numberOfOverflowRecords / header.getBlockingFactor());
        overflow_block_offset = header.numberOfOverflowRecords % header.getBlockingFactor();
        
        recordAddr = (overflow_block_addr * header.blockSize) + (overflow_block_offset * sizeof(newRecord));

        // Se for o primeiro registro de overflow, então faz com que o bucket saiba 
        // que ele é o primeiro da lista de registros de overflow.
        if (header.buckets[bucket_id].overflow.first_block_addr == -1) {
            header.buckets[bucket_id].overflow.first_block_addr = overflow_block_addr;
            header.buckets[bucket_id].overflow.first_block_offset = overflow_block_offset;    
            header.buckets[bucket_id].overflow.last_block_addr = overflow_block_addr;
            header.buckets[bucket_id].overflow.last_block_offset = overflow_block_offset;
        } 
        // Caso já existam registros na lista de registros de overflow, então apenas faça
        // com que o último registro saiba que um novo registro está entrando na lista.
        else {
            this->closeForWriting();

            // Atualizando o ponteiro do último registro da lista encadeada
            this->openForReading();
            
            last_overflow_block_addr = header.buckets[bucket_id].overflow.last_block_addr;
            last_overflow_block_offset = header.buckets[bucket_id].overflow.last_block_offset;
            last_overflow_addr = (last_overflow_block_addr * header.blockSize) + (last_overflow_block_offset * sizeof(newRecord));
            
            this->fileRead.seekg(sizeof(header) + last_overflow_addr, ios::beg);

            this->fileRead.read((char *) &tempRecord, sizeof(tempRecord));

            tempRecord.nextRecord_block_addr = overflow_block_addr;
            tempRecord.nextRecord_block_offset = overflow_block_offset;

            this->closeForReading();

            // cout << "Next record: " << tempRecord.nextRecord_block_addr << " , " << tempRecord.nextRecord_block_offset << "\n";

            this->openForWriting();

            this->fileWrite.seekp(sizeof(header) + last_overflow_addr, ios::beg);
            this->fileWrite.write((char *) &tempRecord, sizeof(tempRecord));
            
            // Fazendo o bucket apontar para este registro como sendo o último da lista 
            // encadeada.
            header.buckets[bucket_id].overflow.last_block_addr = overflow_block_addr;
            header.buckets[bucket_id].overflow.last_block_offset = overflow_block_offset;
        }

        // Incrementando o número de registros de overflow.
        header.incrementNumberOfOverflowRecords();

    } 
    
    else {
        // Obtendo o ponteiro para a próxima posição livre do bloco do bucket.
        recordAddr = (block_addr * header.blockSize) + (n_recordsInBlock * sizeof(newRecord));
    }

    // Escrevendo o novo registro no arquivo de registros.
    this->fileWrite.seekp(sizeof(header) + recordAddr, ios::beg);
    
    this->fileWrite.write((char *) &newRecord, sizeof(newRecord));
    // Incrementando o total de registros no arquivo e o total de registros no bucket.
    header.incrementRecordsAmount();
    header.buckets[bucket_id].incrementNumberOfRecords();    

}

int HashManipulator::reorganize ()
{

}