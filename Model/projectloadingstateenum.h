#ifndef PROJECTLOADINGSTATEENUM_H
#define PROJECTLOADINGSTATEENUM_H

#include <qobject.h>

#include <model_global.h>

namespace BlackOil {
namespace Model {

class MODEL_EXPORT ProjectLoadingStateEnum : public QObject
{
    Q_OBJECT
    Q_ENUMS(ProjectLoadingState)
public:
    explicit ProjectLoadingStateEnum(QObject *parent = nullptr);

    enum ProjectLoadingState {StartLoading, Processing, Drawing, FinishLoading, FinishInitializing};
};

}}

#endif // PROJECTLOADINGSTATEENUM_H
