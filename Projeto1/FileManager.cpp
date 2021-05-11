#include "./FileManager.h"

FileManager::FileManager() {
	this->fileName = "None";
};

int FileManager::loadFile(string filePath) {
	// Tentando abrir o arquivo de registros
	this->file.open(filePath, ios::binary | ios::in);
	if (!this->file.good()) {
		cout << "Error during file opening.\n";
		this->fileName = "None";
		return -1;
	}

	// Tentando obter o tipo de organização primária utilizada pelo arquivo de registros
	if (getFileOrganization() == -1) {
		return -1;
	}

	// Se chegou aqui, é porque deu tudo certo. 
	// Vamos inicializar os atributos baseado nas informações do arquivo de registros carregado
	this->fileName = filePath;
	switch(this->fileOrganization)
	{
		case 0:
			this->fm = new FixedHeapManipulator(this->fileName);
			break;
	}

	return 0;
}

int FileManager::getFileOrganization() {
	if (!this->file.is_open()) {
		cout << "Error: There is no opened records file.\n";
		this->fileOrganization = -1;
		return -1;
	}

	int currentFilePointer = this->file.tellg();

	// Posicionando o ponteiro de leitura do arquivo para a posição onde tem o tipo da organização.
	this->file.seekg(sizeof(int), ios::beg); // Há um campo int (headerSize) antes do tipo da organização.
	this->file.read((char *) &this->fileOrganization, sizeof(this->fileOrganization));

	// Posicionando o ponteiro para o local onde ele estava incialmente
	this->file.seekg(currentFilePointer, ios::beg);	

	// Verificando se houve algum erro durante a leitura da organização utilizada pelo arquivo
	if (this->fileOrganization == -1) {
		cout << "An error has occured during file primary organization reading.\n";
		return -1;
	}
	
	// Se chegou aqui, é porque deu tudo certo.
	return 0;
}

int FileManager::close() {
	this->file.close();
	return 0;
}

void FileManager::info() {
	cout << this->fileName << "\t" << this->fileOrganization << "\n";
}