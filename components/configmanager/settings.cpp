#include <QStandardPaths>

#include "settings.h"

/// Путь к файлу настроек по умолчанию:
/// в корневой директории программы
const char * const DEFAULT_SETTINGS_FILENAME = "smp.ini";

/// Путь к файлу настроек: в Windows - в той же директории, что и исполняемый,
/// в UNIX - в специально отведенной папке данных приложения
#ifdef Q_OS_WIN
const char* DEFAULT_SETTINGS_PATH = "";
#else
const char * const DEFAULT_SETTINGS_PATH = "/etc/smp";
#endif

QString Settings::settingsPath = QString();
QString Settings::settingsFileName = DEFAULT_SETTINGS_FILENAME;

//--------------------------------------------------------
QString Settings::makeSettingsPath()
{
    if (settingsPath.isNull() || settingsPath.isEmpty()) {

        settingsPath = getSettingsPath();

        // Если не удалось найти ни один файл настроек, завершаем
        // работу программы с ошибкой
        if (settingsPath.isNull()) {
            qCritical() << "Settings file not found! Quiting!";
        }
    }
    return settingsPath;
}

//--------------------------------------------------------
QString Settings::getSettingsPath()
{
    // Если он просто лежит рядом с исполняемым файлом
    if (QFileInfo(settingsFileName).exists()) {
        settingsPath = settingsFileName;
        return settingsPath;
    }

    // Если он лежит по дефолтному пути
    QString settingsPath = QString("%1%2")
                               .arg(DEFAULT_SETTINGS_PATH)
                               .arg(settingsFileName);
    if (QFileInfo(settingsPath).exists()) {
        return settingsPath;
    }

    // Если вдруг рабочая директория не совпадает с директорией
    // приложения
    QString dirPath = QCoreApplication::applicationDirPath();
    settingsPath = dirPath + "/" + settingsFileName;

    // Если не удалось найти ни один файл настроек, завершаем
    // работу программы с ошибкой
    if (!QFileInfo::exists(settingsPath)) {
        return QString();
    }

    return settingsPath;
}

//--------------------------------------------------------
void Settings::setSettingsFilename(QString filename)
{
    if (filename != settingsFileName) {
        settingsFileName = filename;
        settingsPath.clear();
    }
}

//---------------------------------------------------------
QString Settings::getNormalSettingsPath()
{
    if (QCoreApplication::applicationDirPath() == DEFAULT_SETTINGS_PATH) {
        return DEFAULT_SETTINGS_PATH + settingsFileName;
    } else {
        return settingsFileName;
    }
}
