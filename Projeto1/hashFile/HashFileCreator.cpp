#include "HashFileCreator.h"


HashFileCreator::HashFileCreator(string fileName, string newFileName) : FileCreator (fileName, newFileName)
{
    this->insertHeader();
}

int HashFileCreator::insertHeader()
{
    if(this->openNewFileWriting() == -1)
    {
        this->closeNewFileWriting();
        cout << "Error opening the file for writing";
        return -1;
    }
    this->outNewFile.seekp(0, ios::beg);
    this->outNewFile.write((char *) &(this->header), sizeof(this->header));
    this->closeNewFileWriting();
    return 0;
}

int HashFileCreator::getHeader()
{   
    this->openNewFileReading();
    this->inNewFile.seekg(0, ios::beg);
    if (!this->inNewFile.read((char *) &(this->header), sizeof(this->header)))
    {
        this->closeNewFileReading();
        return -1;
    }
    this->closeNewFileReading();
    return 0;
}

/*considers first line already has data.*/
int HashFileCreator::readCsvLine(HashFixedRecord &newRecord)
{
    string line;
    if (!getline(this->rawDataFile, line))
    {
        return -1;
    }

    newRecord.readCSVLine(line);

    return 0;
}

int HashFileCreator::insertRecords()
{
    /* 
    Algoritmo:
    ====================================================================
    Enquanto houver linhas no arquivo CSV
        Cria um registro a partir dos dados da próxima linha
        Determina o bucket no qual o registro deve ser inserido
        Se o registro couber no bloco correspondente a esse bucket
            Insere o registro nesse bloco
        Senão
            Insere o registro na lista encadeada de registro de overflow
    */

    // Declarando algumas variáveis

    // newRecord é usado para armazenar os dados de uma linha do CSV
    HashFixedRecord newRecord;
    // tempRecord é usado para carregar registros de overflow de buckets
    HashFixedRecord tempRecord;
    // numbers é usado para criar índices únicos para os registros do CSV
    int numbers = 0;
    
    // Variáveis referentes ao bucket e às posições de inserção
    int bucket_id, block_addr, n_recordsInBlock, recordAddr, last_overflow_addr;
    int overflow_block_addr, overflow_block_offset, last_overflow_block_addr, last_overflow_block_offset;

    if (this->getHeader() == -1)
    {
        return -1;
    }

    this->openNewFileWriting();

    // Leitura das linhas do CSV, armazenamento dessas informações em um objeto HashFixedRecord
    // e a inserção desses registros no arquivo de registros
    while(this->readCsvLine(newRecord) == 0)
    {
        newRecord.id = numbers++;
     
        // Determinando o bucket a partir do id do registro
        bucket_id = this->header.hashFunction(newRecord.id);
        
        // Encontrando o bloco onde o registro deveria ser inserido e obtendo o número de 
        // registros nesse bloco
        block_addr = this->header.buckets[bucket_id].block_addr;
        n_recordsInBlock = this->header.buckets[bucket_id].numberOfRecords;

        // Investigando se com a inserção haverá overflow de registros dentro do bloco. 
        // Em caso afirmativo, a inserção é feita na lista de registros de overflow. 
        // Caso contrário, a inserção é feita na próxima posição livre do bloco.
        if ((n_recordsInBlock+1)*this->header.recordSize >= this->header.blockSize) {
            // Se chegou aqui, é porque o registro precisa ser inserido na lista de overflow.
            // Na verdade, o registro é inserido na primeira posição livre dentre os blocos que
            // não são mapeados pelos buckets.
            overflow_block_addr = (NUMBER_OF_BUCKETS) + (this->header.numberOfOverflowRecords / this->header.getBlockingFactor());
            overflow_block_offset = this->header.numberOfOverflowRecords % this->header.getBlockingFactor();
            
            recordAddr = (overflow_block_addr * this->header.blockSize) + (overflow_block_offset * sizeof(newRecord));

            // Se for o primeiro registro de overflow, então faz com que o bucket saiba 
            // que ele é o primeiro da lista de registros de overflow.
            if (this->header.buckets[bucket_id].overflow.first_block_addr == -1) {
                this->header.buckets[bucket_id].overflow.first_block_addr = overflow_block_addr;
                this->header.buckets[bucket_id].overflow.first_block_offset = overflow_block_offset;    
                this->header.buckets[bucket_id].overflow.last_block_addr = overflow_block_addr;
                this->header.buckets[bucket_id].overflow.last_block_offset = overflow_block_offset;
            } 
            // Caso já existam registros na lista de registros de overflow, então apenas faça
            // com que o último registro saiba que um novo registro está entrando na lista.
            else {
                closeNewFileWriting();

                // Atualizando o ponteiro do último registro da lista encadeada
                openNewFileReading();
                
                last_overflow_block_addr = this->header.buckets[bucket_id].overflow.last_block_addr;
                last_overflow_block_offset = this->header.buckets[bucket_id].overflow.last_block_offset;
                last_overflow_addr = (last_overflow_block_addr * this->header.blockSize) + (last_overflow_block_offset * sizeof(newRecord));
                
                this->inNewFile.seekg(sizeof(this->header) + last_overflow_addr, ios::beg);

                this->inNewFile.read((char *) &tempRecord, sizeof(tempRecord));

                tempRecord.nextRecord_block_addr = overflow_block_addr;
                tempRecord.nextRecord_block_offset = overflow_block_offset;

                closeNewFileReading();

                // cout << "Next record: " << tempRecord.nextRecord_block_addr << " , " << tempRecord.nextRecord_block_offset << "\n";

                openNewFileWriting();

                this->outNewFile.seekp(sizeof(this->header) + last_overflow_addr, ios::beg);
                this->outNewFile.write((char *) &tempRecord, sizeof(tempRecord));
                
                // Fazendo o bucket apontar para este registro como sendo o último da lista 
                // encadeada.
                this->header.buckets[bucket_id].overflow.last_block_addr = overflow_block_addr;
                this->header.buckets[bucket_id].overflow.last_block_offset = overflow_block_offset;
            }

            // Incrementando o número de registros de overflow.
            this->header.incrementNumberOfOverflowRecords();

        } 
        
        else {
            // Obtendo o ponteiro para a próxima posição livre do bloco do bucket.
            recordAddr = (block_addr * this->header.blockSize) + (n_recordsInBlock * sizeof(newRecord));
        }

        // Escrevendo o novo registro no arquivo de registros.
        this->outNewFile.seekp(sizeof(this->header) + recordAddr, ios::beg);
        
        this->outNewFile.write((char *) &newRecord, sizeof(newRecord));
        // Incrementando o total de registros no arquivo e o total de registros no bucket.
        this->header.incrementRecordsAmount();
        this->header.buckets[bucket_id].incrementNumberOfRecords();
    }
    //cout << "Number of records: " << this->header.recordsAmount << "\n";
    // cout << endl;
    this->closeRawFile();
    this->closeNewFileWriting();
    this->insertHeader();
 
    return 0;

}

/*CODE FOR THE MANAGER*/
/*    if (!this->header.freeList.empty())
    {
        firstDeleted = this->header.freeList.front();
        this->header.freeList.pop_front();
    }
*/