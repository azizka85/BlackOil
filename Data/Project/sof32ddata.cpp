#include "sof32ddata.h"

namespace BlackOil {
namespace Data {
namespace Project {

SOF32DData::SOF32DData()
{
    InitVariables();
}

vector<double> &SOF32DData::SW()
{
    return sw;
}

vector<SOF32DKrOData> &SOF32DData::SOF32DKrO()
{
    return sof32dKrO;
}

void SOF32DData::InitVariables()
{
    sw.clear();

    sof32dKrO.clear();
}

}}}
