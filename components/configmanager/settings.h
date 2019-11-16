#ifndef COMMON_SETTINGS_H
#define COMMON_SETTINGS_H

#include <QCoreApplication>
#include <QDebug>
#include <QFileInfo>
#include <QSettings>

class Settings : public QSettings {
public:
    Settings()
        : QSettings(makeSettingsPath(),
              QSettings::IniFormat)
    {
    }

    /// Получить путь к файлу настроек.
    /// Используйте этот метод для создания локального
    /// объекта QSettings вместо обращения к глобальному
    /// через globalSettings()
    static QString makeSettingsPath();

    static QString getSettingsPath();

    /// Устанавливает имя файла настроек для текущего приложения
    static void setSettingsFilename(QString);

    /// Возвращает путь, по которому должен лежать файл
    static QString getNormalSettingsPath();

private:
    static QString settingsPath;
    static QString settingsFileName;
};

#endif // COMMON_SETTINGS_H
