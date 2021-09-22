#include "pvtgdata.h"

namespace BlackOil {
namespace Data {
namespace Project {

PVTGData::PVTGData()
{
    InitVariables();
}

double PVTGData::PG()
{
    return pg;
}

double PVTGData::RV()
{
    return rv;
}

double PVTGData::BG()
{
    return bg;
}

double PVTGData::MG()
{
    return mg;
}

void PVTGData::SetPG(const double &pg)
{
    this->pg = pg;
}

void PVTGData::SetRV(const double &rv)
{
    this->rv = rv;
}

void PVTGData::SetBG(const double &bg)
{
    this->bg = bg;
}

void PVTGData::SetMG(const double &mg)
{
    this->mg = mg;
}

void PVTGData::InitVariables()
{
    pg = 0;
    rv = 0;
    bg = 0;
    mg = 0;
}

}}}
