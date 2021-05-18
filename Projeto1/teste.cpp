/* #include <iostream>
#include "./hashFile/HashFileCreator.h"
#include "FileManager.h"

using namespace std;

int main() {
	HashFileCreator * hash = new HashFileCreator("teste.csv","teste.dat");
	hash->insertRecords();
	FileManager * manager = new FileManager();
	manager->loadFile("teste.dat");
	cout << manager->fm->findWhereEqual("NOMEDEP", "ESTADUAL");
	return 0;
} */