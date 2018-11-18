#pragma once

#include <QtCore/qglobal.h>

#if !defined(LOG4QT_LIB_STATICLIB)
#ifdef LOG4QT_LIB
#define LOG4QT_API Q_DECL_EXPORT
#else
#define LOG4QT_API Q_DECL_IMPORT
#endif /* LOG4QT_API */
#else
#define LOG4QT_API
#endif
