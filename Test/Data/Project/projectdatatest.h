#ifndef PROJECTDATATEST_H
#define PROJECTDATATEST_H

#include <qobject.h>

#include <unitsenum.h>
#include <modelsenum.h>
#include <directionalenum.h>
#include <irreversibleenum.h>
#include <referencepressureoptionsenum.h>
#include <maotpoptionsenum.h>
#include <ihboptionsenum.h>
#include <regionoptionsenum.h>
#include <projectdata.h>

#include <test.h>

using namespace BlackOil::Data::Project;

namespace BlackOil {
namespace Test {
namespace Data {
namespace Project {

class ProjectDataTest : public QObject
{
    Q_OBJECT
public:
    explicit ProjectDataTest(QObject *parent = nullptr);

private slots:
    void CheckVariables();
};

}}}}

#endif // PROJECTDATATEST_H
