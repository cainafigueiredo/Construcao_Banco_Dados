//#include "FileCreator.h"
//#include "FixedRecord.h"
//#include "fixedHeap/FixedHeapFileCreator.h"
//#include "fixedHeap/FixedHeapHeader.h"
//#include "fixedHeap/FixedHeapManipulator.h"
#include "variableHeap/VariableHeapManipulator.h"
#include "VariableRecord.h"
#include "variableHeap/VariableHeapFileCreator.h"
#include <iostream>


#include <iostream>

int main ()
{
    //FixedHeapFileCreator a ("teste.csv", "newFile_teste");
    //FixedHeapManipulator teste("newFile_teste");
    //a.insertRecords();
    //a.getHeader();
    // cout << "FRONT: " << a.header.freeList<< endl;
    //teste.removeBetween("id", 0, 2);
    //teste.findWhereBetween("id", 0, 10);
    //teste.findWhereEqual("id", -1);
    //VariableRecord record;
    //string g = "ESTADUAL - OUTROS, ADAMANTINA, ADAMANTINA, ADAMANTINA, 11, 31100, HERVAL BELLUSCI ENGENHEIRO ETEC, Paraguai, 1";
    //record.readCSVLine(g);
    //cout << record.total_size << endl;
    //cout << sizeof(record) << endl;
    //cout << sizeof(&record) << endl;
//    cout << record.nomedep_s<< endl;
  //  cout << record.de_s<< endl;
//    cout << record.distr_s<< endl;
  //  cout << record.mun_s<< endl;
  //  cout << record.nomesc_s<< endl;
  //  cout << record.ds_pais_s<< endl;


    VariableHeapFileCreator file ("teste.csv", "newFile_teste");
    VariableRecord  record, record2;

    file.insertRecords();

    VariableHeapManipulator man ("newFile_teste");

    
    man.readRecords(file.header.headerSize, &record);

    int t = record.total_size+file.header.headerSize;
    man.readRecords(t, &record2);
   // cout << sizeof(record) << endl;
    //cout << 4 << endl;

    //int ts;
    //file.outNewFile.open("newFile_teste", fstream::in | fstream::binary);
    //file.outNewFile.seekg(0, ios::beg);
    //cout << file.outNewFile.tellg() <<endl;
    //cout << 4 << endl;
   // file.outNewFile.read(reinterpret_cast<char*>(&ts), sizeof(ts));
    //cout <<  ts << endl;
    //file.outNewFile.seekg(0, ios::beg);



    //cout << rsize1 << endl;
    //cout << rsize2 << endl;
    //cout << 2 << endl;

/*
    cout << record.total_size << endl;
    cout << record.nomedep_s << endl;
    cout << record.de_s << endl;
    cout << record.distr_s << endl;
    cout << record.mun_s << endl;
    cout << record.nomesc_s << endl;
    cout << record.ds_pais_s<< endl;
    cout << record.cod_esc << endl;
    cout << record.tipoesc << endl;
    cout << record.n_alunos << endl;
*/
   printf ("%s \n", record.nomedep);
   printf ("%s \n" , record.de);
   printf ("%s \n", record.distr);
   printf ("%s \n" , record.mun);
   printf ("%s \n", record.nomesc);
   printf ("%s \n" , record.ds_pais);






    return 0;
}
