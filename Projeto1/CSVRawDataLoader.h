#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

#define Tint int
#define Tfloat float
#define Tstring string


class CSVRawDataLoader 
{
    public:
        fstream rawDataFile;
        vector<string> columnNames {"NOMEDEP", "DE", "DISTR", "MUN", "TIPOESC", "COD_ESC", "NOMESC",
                                      "DS_PAIS", "N_ALUNOS"};
        vector<string> columnTypes;
        /*opens file and sets rawDataFile*/
        int open2ReadRawData(string filename);
        /*closes rawDataFile*/
        int closeRawDataFile();
        // /*puts columnNames in columnNames*/
        // int extractColumnsNamesFromRawData();

        // int setColumnsNames (vector<string>);
        // int getColumnsNames (vector<string>);
        // int setColumnsTypes (vector<string>);
        // int getColumnsTypes (vector<string>);

        int rawDataTransform (bool);
        int prepareRawDataWithColumns (string filename);
        int prepareRawDataWithoutColumns (string filename);
}
