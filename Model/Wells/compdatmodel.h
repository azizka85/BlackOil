#ifndef COMPDATMODEL_H
#define COMPDATMODEL_H

#include <qmetaobject.h>
#include <qstring.h>
#include <qvector.h>

#include <qabstractitemmodel.h>

#include <wellstatusenum.h>
#include <projectdata.h>

#include <welspecsmodel.h>

#include <model_global.h>

using namespace BlackOil::Data::Project;

namespace BlackOil {
namespace Model {
namespace Wells {

class MODEL_EXPORT COMPDATModel : public QAbstractItemModel
{
    Q_OBJECT
    Q_ENUMS(Columns)
public:
    explicit COMPDATModel(ProjectData *projectData, WELSPECSModel *welspecs, QObject *parent = nullptr);

    enum Columns {WellName, WellDate, WellI, WellJ, WellK1, WellK2, WellStatus, WellTranFactor, WellDiameter, WellKh, WellSkinFactor};

    void InitVariables();
    void ProcessData();
    void ProcessBeforeSave();

protected slots:
    void HandleWELSPECSInserted(int welspecsIndex);
    void HandleWELSPECSRemoved(int welspecsIndex);
    void HandleWELSPECSChanged(int welspecsIndex);    

protected:
    bool CheckWELSPECSMatch(int index, int welspecsIndex);
    void HandleWellNameChanged(QModelIndex index);

protected:
    ProjectData *projectData;
    WELSPECSModel *welspecs;
    QVector<int> groups;
    QVector<QVector<int>> indexes;
    QVector<int> removed;

    // QAbstractItemModel interface
public:
    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool insertRows(int row, int count, const QModelIndex &parent) override;
    bool removeRows(int row, int count, const QModelIndex &parent) override;
};

}}}

#endif // COMPDATMODEL_H
