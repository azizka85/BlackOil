#ifndef MODEL_GLOBAL_H
#define MODEL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MODEL_LIBRARY)
#  define MODEL_EXPORT Q_DECL_EXPORT
#else
#  define MODEL_EXPORT Q_DECL_IMPORT
#endif

#endif // MODEL_GLOBAL_H
