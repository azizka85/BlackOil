#include "figuresettingsform.h"
#include "ui_figuresettingsform.h"

namespace BlackOil {
namespace Desktop {
namespace Views {
namespace Settings {

FigureSettingsForm::FigureSettingsForm(QVector<QLineSeries *> *lines, QVector<QScatterSeries *> *scatters, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FigureSettingsForm)
{
    ui->setupUi(this);

    auto model = new QSortFilterProxyModel(this);
    model->setSourceModel(new FigureSettingsModel(lines, scatters, this));

    auto booleanDelegate = new BooleanDelegate(model, this);
    auto colorDelegate = new ColorDelegate(this);

    ui->Table->setModel(model);
    ui->Table->setItemDelegateForColumn(FigureSettingsModel::Display, booleanDelegate);
    ui->Table->setItemDelegateForColumn(FigureSettingsModel::MarkerDisplay, booleanDelegate);
    ui->Table->setItemDelegateForColumn(FigureSettingsModel::LineColor, colorDelegate);
    ui->Table->setItemDelegateForColumn(FigureSettingsModel::MarkerColor, colorDelegate);
    ui->Table->setItemDelegateForColumn(FigureSettingsModel::MarkerBorderColor, colorDelegate);
}

FigureSettingsForm::~FigureSettingsForm()
{
    delete ui;
}

}}}}
