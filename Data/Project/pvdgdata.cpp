#include "pvdgdata.h"

namespace BlackOil {
namespace Data {
namespace Project {

PVDGData::PVDGData()
{
    InitVariables();
}

double PVDGData::PG()
{
    return pg;
}

double PVDGData::BG()
{
    return bg;
}

double PVDGData::MG()
{
    return mg;
}

void PVDGData::SetPG(const double &pg)
{
    this->pg = pg;
}

void PVDGData::SetBG(const double &bg)
{
    this->bg = bg;
}

void PVDGData::SetMG(const double &mg)
{
    this->mg = mg;
}

void PVDGData::InitVariables()
{
    pg = 0;
    bg = 0;
    mg = 0;
}

}}}
