#include "FixedRecord.h"

FixedRecord::FixedRecord ()
{
    this->nomedep.resize(MAX_STRING_SIZE);
    this->de.resize(MAX_STRING_SIZE);
    this->distr.resize(MAX_STRING_SIZE);
    this->mun.resize(MAX_STRING_SIZE);
    this->nomesc.resize(MAX_STRING_SIZE);
    this->ds_pais.resize(MAX_STRING_SIZE);
}