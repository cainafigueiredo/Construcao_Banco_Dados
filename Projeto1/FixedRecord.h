#include <string>

using namespace std;

#define MAX_STRING_SIZE  64

class FixedRecord
{
    public:
    FixedRecord();
    string nomedep, de, distr, mun, nomesc, ds_pais;
    int tipoesc, n_alunos;
    double cod_esc;
};