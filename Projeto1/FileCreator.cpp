#include "FileCreator.h"

FileCreator::FileCreator(string rawfileName, string newFileName)
{
    this->rawFileName = rawfileName;
    this->newFileName = newFileName;
    if (this->openRawFile() == -1)
    {
        cout << "Error opening raw file\n";
        return;
    }
    if (this->createNewFile() == -1)
    {
        cout << "Error creating new file\n";
        return;
    }
}

int FileCreator::openRawFile ()
{
    this->rawDataFile.open(this->rawFileName);
    if (!this->rawDataFile)
    {
        return -1;
    }
    return 0;

}

int FileCreator::closeRawFile ()
{
    this->rawDataFile.close();
    return 0;
}

int FileCreator::createNewFile()
{
    this->outNewFile.open(this->newFileName, ios::binary | ios::out);
    if (!this->outNewFile.good())
    {
        return -1;
    }
    this->outNewFile.close();
    return 0;
}

int FileCreator::openNewFileWriting()
{
    this->outNewFile.open(this->newFileName, fstream::binary | ios::out | ios::in);
    if (!this->outNewFile.is_open())
    {
        return -1;
    }
    return 0;
}
int FileCreator::openNewFileReading()
{
    this->inNewFile.open(this->newFileName, fstream::in | fstream::binary);
    if (!this->inNewFile.is_open())
    {
        return -1;
    }
    return 0;
}


int FileCreator::closeNewFileWriting()
{
    this->outNewFile.close();
    return 0;
}

int FileCreator::closeNewFileReading()
{
    this->inNewFile.close();
    return 0;
}

int FileCreator::addDict()
{
    string toWrite;
    this->dictFile.open("filetypeDict.txt", fstream::out);
    if (!this->dictFile.good())
    {
        return -1;
    }
    toWrite = this->newFileName + ":" + to_string(this->type);
    this->dictFile << toWrite;
    this->dictFile.close();
    return 0;
}