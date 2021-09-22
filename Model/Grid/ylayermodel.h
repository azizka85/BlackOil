#ifndef YLAYERMODEL_H
#define YLAYERMODEL_H

#include <qvector.h>

#include <qabstractitemmodel.h>

#include <model_global.h>

namespace BlackOil {
namespace Model {
namespace Grid {

class MODEL_EXPORT YLayerModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit YLayerModel(QObject *parent = nullptr);

    QVector<bool> &DisplayBlocks();

    void InitVariables();
    void ProcessData(int n);
    void ProcessBeforeSave();

public slots:
    void Clear();
    void CheckAll();

protected:
    QVector<bool> displayBlocks;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
};

}}}

#endif // YLAYERMODEL_H
