#include <string>
#include <fstream>
#include "FileManipulator.h"
using namespace std;

class FileManager
{
    public:
        FileManager(string database);
        FileManipulator fm;
        string fileName;
        fstream file;
        int type;
        int fileExists();
        int openFile();
        int getFileType(); /*chamar manipulator especifico - polimorfismo*/
        
};