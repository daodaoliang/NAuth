#ifndef NAUTH_GLOBAL_H
#define NAUTH_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(NAUTH_LIBRARY)
#  define NAUTHSHARED_EXPORT Q_DECL_EXPORT
#else
#  define NAUTHSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // NAUTH_GLOBAL_H
