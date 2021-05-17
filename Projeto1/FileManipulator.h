#ifndef _FILE_MANIPULATOR_
#define _FILE_MANIPULATOR_
#include <string>
#include <iostream>
#include <fstream>
#include <map>
using namespace std;


class FileManipulator
{
    public:
        FileManipulator(string fileName);
        
        string fileName;
        ifstream fileRead;
        ofstream fileWrite;
        
        static map<string, int> createMap()
        {
            map <string, int> m;
            m.insert(pair<string, int>("id", 0));
            m.insert(pair<string, int>("NOMEDEP", 1));
            m.insert(pair<string, int>("DE", 2));
            m.insert(pair<string, int>("DISTR", 3));
            m.insert(pair<string, int>("MUN", 4));
            m.insert(pair<string, int>("TIPOESC", 5));
            m.insert(pair<string, int>("COD_ESC", 6));
            m.insert(pair<string, int>("NOMESC", 7));
            m.insert(pair<string, int>("DS_PAIS", 8));
            m.insert(pair<string, int>("N_ALUNOS", 9));
            return m;
        };

        // static const map<string, int> map = createMap();

        int openForReading();
        int openForWriting();
        int closeForReading();
        int closeForWriting();

        void printSchema();

        virtual int findOne(int id){return 0;};
        virtual int findWhereEqual(string attribute, int value){return 0;};
        virtual int findWhereEqual(string attribute, double value){return 0;};
        virtual int findWhereEqual(string attribute, string value){return 0;};
        virtual int findWhereBetween(string attribute, int value1, int value2){return 0;};
        virtual int findWhereBetween(string attribute, double value1, double value2){return 0;};
        virtual int removeOne(int id){return 0;};
        virtual int removeBetween(string attribute, int value1, int value2){return 0;};
        // bool between (int attribute, int first, int last);
        // bool unique (int attribute, string value);
        // bool unique (int attribute, int value);
        // bool unique (int attribute, double value);
        // int findAll();
        // int select ();
        // int deleteRecord ();
};
#endif