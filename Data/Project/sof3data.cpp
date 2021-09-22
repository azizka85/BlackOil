#include "sof3data.h"

namespace BlackOil {
namespace Data {
namespace Project {

SOF3Data::SOF3Data()
{
    InitVariables();
}

double SOF3Data::SO()
{
    return so;
}

QVariant SOF3Data::KrOW()
{
    return krow;
}

QVariant SOF3Data::KrOGWC()
{
    return krogwc;
}

void SOF3Data::SetSO(const double &so)
{
    this->so = so;
}

void SOF3Data::SetKrOW(const QVariant &krow)
{
    this->krow = krow;
}

void SOF3Data::SetKrOGWC(const QVariant &krogwc)
{
    this->krogwc = krogwc;
}

void SOF3Data::InitVariables()
{
    so = 0;

    krow.clear();
    krogwc.clear();
}

}}}
