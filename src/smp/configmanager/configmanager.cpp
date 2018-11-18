/// @file configmanager.cpp
/// @brief Реализация менеджера конфигураций
/// @author Алексей Максимов
/// @date 2015-09-11

#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include <QtCore/QHash>
#include <QtCore/QSettings>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtGui/QColor>

#if defined(ANDROID)
#include <QtAndroidExtras/QAndroidJniEnvironment>
#include <QtAndroidExtras/QAndroidJniObject>
#endif /* ANDROID */

#include <configmanager/configmanager.h>

ConfigManager* ConfigManagerSingleton::instance()
{
    static ConfigManager cm;
    return &cm;
} // instance

struct ConfigManager::Private {

    QString cfgDirPath;
    QVariantHash sets;

    bool useConsul;

    void load();
    QString findConfigDir();

    template <typename T>
    T findValue(const QString& key, const T& defaultValue)
    {
        // Сначала проверяем на наличие параметра в конфиге
        QVariantHash::iterator it = sets.find(key);
        if (it == sets.end()) {
            return defaultValue;
        }

        return it->value<T>();
    }
};

int ConfigManager::value(const QString& key, int defaultValue)
{
    return d_->findValue(key, defaultValue);
}

QString ConfigManager::value(const QString& key, const QString& defaultValue)
{
    return d_->findValue(key, defaultValue);
} // value

QByteArray ConfigManager::value(const QString &key, const QByteArray &defaultValue)
{
    return d_->findValue(key, defaultValue);
} // value

QColor ConfigManager::value(const QString &key, const QColor &defaultValue)
{
    return d_->findValue(key, defaultValue);
} // value

double ConfigManager::value(const QString& key, double defaultValue)
{
  return d_->findValue(key, defaultValue);
}

float ConfigManager::value(const QString &key, float defaultValue)
{
  return d_->findValue(key, defaultValue);
} // value

bool ConfigManager::value(const QString& key, bool defaultValue)
{
    return d_->findValue(key, defaultValue);
} // value

void ConfigManager::setValue(const QString& key, const QVariant& value)
{
    d_->sets.insert(key, value);
}

QString ConfigManager::toAbsolutePath(const QString& relativePath) const
{
    QString path(QDir::fromNativeSeparators(relativePath));

    if (QDir::isRelativePath(path)) {
        return d_->cfgDirPath + path;
    }
    return path;
} // toAbsolutePath

FileSettingsPtr ConfigManager::openFileSettings(const QString& filename) const
{
    const QString filepath = d_->cfgDirPath + filename;
    FileSettingsPtr sets(new QSettings(filepath, QSettings::IniFormat));
    return sets;
} // openFileSettings

QString ConfigManager::logDir() const
{
    const QString logdir = "log";
    QDir d(d_->cfgDirPath);
    if (!d.exists(logdir)) {
        d.mkdir(logdir);
    }
    return d.absoluteFilePath(logdir);
} // logDir

void ConfigManager::reload()
{
    d_->load();
} // reload

ConfigManager::ConfigManager()
    : d_(new Private)
{
    d_->cfgDirPath = d_->findConfigDir();    
    d_->load();    
} // Ctor

ConfigManager::~ConfigManager()
{

} // Dtor

QString ConfigManager::Private::findConfigDir()
{
#if defined(ANDROID)

    QAndroidJniObject mediaDir = QAndroidJniObject::callStaticObjectMethod(
        "android/os/Environment", "getExternalStorageDirectory", "()Ljava/io/File;");
    QAndroidJniObject mediaPath = mediaDir.callObjectMethod(
        "getAbsolutePath", "()Ljava/lang/String;");
    QAndroidJniObject activity = QAndroidJniObject::callStaticObjectMethod(
        "org/qtproject/qt5/android/QtNative", "activity", "()Landroid/app/Activity;");
    QAndroidJniObject package = activity.callObjectMethod(
        "getPackageName", "()Ljava/lang/String;");

    QString dataPath = mediaPath.toString() + "/Android/data/" + package.toString() + "/";

    qDebug() << "DataPath:" << dataPath;
    QDir dir(dataPath);
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    //QAndroidJniEnvironment env;
    //if (env->ExceptionCheck()) { env->ExceptionClear(); }
    // TODO check storage state
    return dataPath;

#else

#if defined(Q_OS_LINUX) && !defined(_DEBUG)
    QString path = "/usr/local/etc/smp";
#else
    QString path = QCoreApplication::applicationDirPath();
#endif

    if (!path.endsWith("/")) {
        path.append("/");
    }
    return path;
#endif /* ANDROID */
} // selectDir

void ConfigManager::Private::load()
{
    QDir dir(cfgDirPath);
    for (const QString& ini : dir.entryList(QStringList() << "*.ini", QDir::Files)) {
        const QString filename = dir.filePath(ini);
        qDebug() << "Load ini: " << filename;
        /// Добоавляем всё в один большой QSettings
        QSettings temp_sets(filename, QSettings::IniFormat);
        if (temp_sets.status() != QSettings::NoError) {
            qDebug() << "Settings load error: " << (temp_sets.status() == QSettings::AccessError ? "AcessError" : "FormatError");
            continue;
        }
        temp_sets.setIniCodec("UTF-8");
        for (const QString& key : temp_sets.allKeys()) {
            sets.insert(key, temp_sets.value(key));
        }
    }
} // load
