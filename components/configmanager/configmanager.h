/// @file configmanager.h
/// @brief Менеджер конфигураций
/// @author Алексей Максимов
/// @date 2015-09-11

#pragma once

#include <QtCore/QObject>
#include <QtCore/QScopedPointer>
#include <QtCore/QSettings>
#include <QtCore/QSharedPointer>
#include <QtGui/QColor>

#include "configmanager_export.h"

typedef QSharedPointer<QSettings> FileSettingsPtr;

class QColor;

///
/// \brief Менеджер конфигурации
/// Реализует прозрачное обращение к Consul либо
/// QSettings, если Consul не сконфигурирован
///
class CONFIGMANAGER_API ConfigManager {
    friend class ConfigManagerSingleton;

public:
    ///
    /// \brief Получить значение по ключу
    /// \param[in] key Ключ
    /// \param[in] defaultValue Значение по умолчанию
    /// \return Значение
    ///
    int value(const QString& key, int defaultValue = 0);

    /// \overload
    QString value(const QString& key, const QString& defaultValue = QString());

    /// \overload
    QByteArray value(const QString &key, const QByteArray& defaultValue = QByteArray());

#ifdef __OSX_UDEPRECATED
    QColor value(const QString &key, const QColor &defaultValue = QColor());
#endif
    /// \overload
    double value(const QString& key, double defaultValue = 0);

    /// \overload
    float value(const QString& key, float defaultValue = 0);

    /// \overload
    bool value(const QString& key, bool defaultValue = false);

    void setValue(const QString &key, const QVariant &value);

    ///
    /// \brief Преобразовать относительный путь в абсолютный относительно
    /// каталога с конфигурацией
    /// \param[in] relativePath Относительный путь
    /// \return Абсолютный путь
    ///
    QString toAbsolutePath(const QString& relativePath) const;

    ///
    /// \brief Открыть файл настроек и вернуть объект для управления
    /// \param[in] filename Название файла
    /// \return Объект для управлениями настройками
    ///
    FileSettingsPtr openFileSettings(const QString& filename) const;

    QString logDir() const;

    bool consulEnabled();
    void enableConsul(bool enable);

    void reload();

private:
    ///
    /// \brief Конструктор по умолчанию
    ///
    ConfigManager();
    ///
    /// \brief Деструктор
    ///
    virtual ~ConfigManager();

private:
    struct Private;
    QScopedPointer<Private> d_;

private:
    Q_DISABLE_COPY(ConfigManager)
};

///
/// \brief Экземпляр менеджера конфигураций
///
class CONFIGMANAGER_API ConfigManagerSingleton {
public:
    static ConfigManager* instance();
};

inline ConfigManager* Cm()
{
    return ConfigManagerSingleton::instance();
}
