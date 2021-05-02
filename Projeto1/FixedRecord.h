#include <string>

#define MAX_STRING_SIZE  64

using namespace std;


class FixedRecord
{
    public:
    FixedRecord();
    int id;
    string nomedep, de, distr, mun, nomesc, ds_pais;
    int tipoesc, n_alunos;
    double cod_esc;
};