#include "FileManipulator.h"

FileManipulator::FileManipulator(string fileName) {
	this->fileName = fileName;
}

int FileManipulator::openForReading()
{
	this->fileRead.open(this->fileName, fstream::in | fstream::binary);
	if (!this->fileRead)
    {
        return -1;
    }
	return 0;
}

int FileManipulator::openForWriting()
{
	this->fileWrite.open(this->fileName, fstream::binary | ios::out | ios::in);
	if (!this->fileRead)
    {
        return -1;
    }
	return 0;
}

int FileManipulator::closeForReading()
{
	this->fileRead.close();
	return 0;
}

int FileManipulator::closeForWriting()
{
	this->fileWrite.close();
	return 0;
}

void FileManipulator::printSchema()
{
    cout << "id\tNOMEDEP\tDE\tDISTR\tMUN\tTIPOESC\tCOD_ESC\tNOMESC\tDS_PAIS\tN_ALUNOS\n";
}