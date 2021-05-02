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
    if (this->openNewFileWriting() == -1)
    {
        cout << "Error creating new file\n";
        return;
    }
    this->closeNewFile();
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

int FileCreator::openNewFileWriting()
{
    this->newFile.open(this->newFileName, fstream::out | fstream::binary);
    if (!this->newFile.good())
    {
        return -1;
    }
    return 0;
}
int FileCreator::openNewFileReading()
{
    this->newFile.open(this->newFileName, fstream::in | fstream::binary);
    if (!this->newFile.good())
    {
        return -1;
    }
    return 0;
}


int FileCreator::closeNewFile()
{
    this->newFile.close();
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