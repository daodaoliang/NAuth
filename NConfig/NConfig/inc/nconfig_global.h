#ifndef NCONFIG_GLOBAL_H
#define NCONFIG_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(NCONFIG_LIBRARY)
#  define NCONFIGSHARED_EXPORT Q_DECL_EXPORT
#else
#  define NCONFIGSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // NCONFIG_GLOBAL_H
