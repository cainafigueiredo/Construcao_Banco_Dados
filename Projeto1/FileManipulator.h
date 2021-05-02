#include <string>
using namespace std;


class FileManipulator
{
    public:
        FileManipulator(fstream database);
        
        bool between (int attribute, int first, int last);
        bool unique (int attribute, string value);
        bool unique (int attribute, int value);
        bool unique (int attribute, double value);
        int findAll();
        int finOne();
        int select ();
        int deleteRecord ();
};