# для использования необходимо установить Qt Installer Framework
# и добавить путь к нему в переменную окружения PATH
# для получения инсталятора выполнить

# make
# make install
# make createinstaller

# Инсталятор появится в каталоге installer

isEmpty(PACKAGENAME) {
    error("You have to set PACKAGENAME variable!")
}

win32 {
    root_prefix=$${PACKAGENAME}
    target_dir=bin
}

unix {
    root_prefix=usr

    contains(TEMPLATE,app) {
        target_dir=bin
    } else {
        target_dir=lib
    }
}
top_installerdir=$$top_srcdir/../installer
#CONFIG(release, debug|release){


target.path = $$top_installdir/$$root_prefix/$$target_dir
INSTALLS += target
data_dir=$$top_installerdir/packages/$${PACKAGENAME}/data

createinstaller.commands += $$top_installerdir/createinstaller.bat --installer-dir $$top_installerdir --install-dir $$top_installdir --src-dir $$top_srcdir
createinstaller.commands = $$replace(createinstaller.commands, '/', '\\')
QMAKE_EXTRA_TARGETS += createinstaller
#}
