#include "CSVRawDataLoader.h"

int CSVRawDataLoader::open2ReadRawData(string filename)
{
    this->rawDataFile.open(filename);
    if (!this->rawDataFile)
    {
        return -1;
    }
    return 0;
}

int CSVRawDataLoader::closeRawDataFile()
{
    this->rawDataFile.close();
    return 0;
}

int CSVRawDataLoader::rawDataTransform (bool)
{
    
}
