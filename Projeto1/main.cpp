#include <iostream>
#include "FileCreator.h"
#include "./hashFile/HashFileCreator.h"
#include "./fixedHeap/FixedHeapFileCreator.h"
#include "FileManager.h"

using namespace std;

#define NEW_BASE_INSTRUCTION "newBase"
#define LOAD_BASE_INSTRUCTION "loadBase"
#define INSERT_ONE_INSTRUCTION "insertOne"
#define INSERT_MULTIPLE_INSTRUCTION "insertMultiple"
#define FIND_ONE_BY_ID_INSTRUCTION "findOneById"
#define FIND_WHERE_EQUAL_INSTRUCTION "findWhereEqual"
#define FIND_WHERE_BETWEEN_INSTRUCTION "findWhereBetween"
#define REMOVE_ONE_BY_ID_INSTRUCTION "removeOneById"
#define REMOVE_WHERE_BETWEEN_INSTRUCTION "removeWhereBetween"
#define REORGANIZE_INSTRUCTION "reorganize"
#define HEADER_INFO_INSTRUCTION "headerInfo"

#define FIXED_HEAP_ORGANIZATION "fixedHeap"
#define HASH_ORGANIZATION "externalHash"

#define NEW_BASE_HELP "newBase:\nOrganização do arquivo | Caminho para o CSV | Caminho e nome do arquivo de destino\n"

int main(int argc, char *argv[]) {
	FileCreator * recordsFile = NULL; 
	string command;
	FileManager * manager = new FileManager();
	for (int i = 1; i < argc; i++) {
		
		command = argv[i];

		cout << "> Executing instruction: " << command << "\n";

		if (command == "help") {
			string instruction = argv[i+1];
			if (instruction == NEW_BASE_INSTRUCTION) {
				cout << NEW_BASE_HELP << endl; 
			}
			i = i+1;
		}

		// Criar um arquivo de registros a partir
		else if (command == NEW_BASE_INSTRUCTION) {
			string organization = argv[i+1];
			string source = argv[i+2];
			string destiny = argv[i+3];
			if (organization == HASH_ORGANIZATION) {
				recordsFile = new HashFileCreator(source, destiny);
				recordsFile->insertRecords();
			} 
			else if (organization == FIXED_HEAP_ORGANIZATION) {
				recordsFile = new FixedHeapFileCreator(source, destiny);
				recordsFile->insertRecords();
			}
			i = i+3;
		}

		// Criar um arquivo de registros a partir
		else if (command == LOAD_BASE_INSTRUCTION) {
			string source = argv[i+1];
			manager->loadFile(source);
			i = i+1;
		}

		else if (command == INSERT_ONE_INSTRUCTION) {
			string recordData = argv[i+1];
			//cout << recordData << endl;
			cout << manager->fm->insertOne(recordData) << endl;
			i = i+1;
		}

		else if (command == INSERT_MULTIPLE_INSTRUCTION) {
			string recordData1 = argv[i+1];
			string recordData2 = argv[i+2];
			vector<string> records {recordData1, recordData2};
			cout << manager->fm->insertMultiple(records) << endl;
			i = i+2;
		}

		else if (command == FIND_ONE_BY_ID_INSTRUCTION) {
			int id = atoi(argv[i+1]);
			manager->fm->findOne(id);
			i = i+1;
		}

		else if (command == FIND_WHERE_EQUAL_INSTRUCTION) {
			string fieldType = argv[i+1];
			string fieldName = argv[i+2];
			string string_value;
			int int_value;
			double double_value;
			
			if (fieldType == "integer") {
				int_value = atoi(argv[i+3]);
				cout << manager->fm->findWhereEqual(fieldName, int_value) << endl;
			} else 

			if (fieldType == "string") {
				string_value = argv[i+3];
				cout << manager->fm->findWhereEqual(fieldName, string_value) << endl;
			} else 

			if (fieldType == "double") {
				double_value = atoi(argv[i+3]);
				cout << manager->fm->findWhereEqual(fieldName, double_value) << endl;
			}
			
			i = i+3;
		}

		else if (command == FIND_WHERE_BETWEEN_INSTRUCTION) {
			string fieldType = argv[i+1];
			string fieldName = argv[i+2];

			int int_value1, int_value2;
			double double_value1, double_value2;
			
			if (fieldType == "integer") {
				int_value1 = atoi(argv[i+3]);
				int_value2 = atoi(argv[i+4]);
				cout << manager->fm->findWhereBetween(fieldName, int_value1, int_value2) << endl;
			} else 

			if (fieldType == "double") {
				double_value1 = atoi(argv[i+3]);
				double_value2 = atoi(argv[i+4]);
				cout << manager->fm->findWhereBetween(fieldName, double_value1, double_value2) << endl;
			}
			
			i = i+4;
		}

		else if (command == REMOVE_ONE_BY_ID_INSTRUCTION) {
			int id = atoi(argv[i+1]);
			cout << manager->fm->removeOne(id) << endl;
			i = i+1;
		} 

		else if (command == REMOVE_WHERE_BETWEEN_INSTRUCTION) {
			string fieldType = argv[i+1];
			string fieldName = argv[i+2];

			int int_value1, int_value2;
			double double_value1, double_value2;
			
			if (fieldType == "integer") {
				int_value1 = atoi(argv[i+3]);
				int_value2 = atoi(argv[i+4]);
				cout << manager->fm->removeBetween(fieldName, int_value1, int_value2) << endl;
			} else 

			if (fieldType == "double") {
				double_value1 = atoi(argv[i+3]);
				double_value2 = atoi(argv[i+4]);
				cout << manager->fm->removeBetween(fieldName, double_value1, double_value2) << endl;
			}
			
			i = i+4;
		} 

		else if (command == REORGANIZE_INSTRUCTION) {
			cout << manager->fm->reorganize();
		}

		else if (command == HEADER_INFO_INSTRUCTION) {
			string organization = argv[i+1];
			if (organization == HASH_ORGANIZATION) {
				manager->recordsFileInfo();
			}
			i = i+1;
		}

		cout << "\n> Instruction finished: " << command << "\n";
		cout << "-------------------------------------------------------\n\n";

	}
}