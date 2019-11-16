#pragma once

#include <QtCore/qglobal.h>

#ifndef CONFIGMANAGER_LIB_STATICLIB
#ifdef CONFIGMANAGER_LIB
#define CONFIGMANAGER_API Q_DECL_EXPORT
#else
#define CONFIGMANAGER_API Q_DECL_IMPORT
#endif /* CONFIGMANAGER_API */
#else
#define CONFIGMANAGER_API
#endif
