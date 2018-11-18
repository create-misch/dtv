#pragma once

#include <QtCore/qglobal.h>

#if !defined(LIBLOG4APP_LIB_STATICLIB)
#ifdef LIBLOG4APP_LIB
#define LIBLOG4APP_API Q_DECL_EXPORT
#else
#define LIBLOG4APP_API Q_DECL_IMPORT
#endif /* LIBLOG4APP_API */
#else
#define LIBLOG4APP_API
#endif
