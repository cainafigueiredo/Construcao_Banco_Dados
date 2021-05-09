#ifndef _FILE_MANAGER_
#define _FILE_MANAGER_
#include <iostream>
#include <string>
#include <fstream>
#include "FileManipulator.h"

using namespace std;

class FileManager
{
    public:
        FileManager();
        FileManipulator fm;
        string fileName;
        fstream file;
        int fileOrganization;
        int type; // Acho q esse atributo pode ser removido

        int fileExists();
        int openFile(); // Acho q essa função pode ser removida
        int getFileType(); // Acho q essa função pode ser removida
        int loadFile(string filePath); 
        int getFileOrganization();
        int close();

        void info();
};
#endif