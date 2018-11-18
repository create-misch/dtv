# зависимости от хедеров поставляемых с библиотекой
dox.depends=$$libheaders.files
# выходной каталог и путь к Doxyfile
doxoutdir=$$top_srcdir/../doc/$${DOXPROJECT}/$${PACKAGENAME}
doxyfile=$$builddir/Doxyfile
doxyinputfiles=$${doxyfile}.input
dox_input_files = $$libheaders.files
dox_input_files += $$doxmodules

isEmpty(dox_input_encoding) {
    dox_input_encoding=UTF-8
}
# Документировать все исходники и хедеры
doxsources{
    isEmpty(subprojectroot_dir){
        error("You have to set subprojectroot_dir variable. Need for dox sources")
    }
    # добавляем сорцы
    for(addsrc, SOURCES) {
        dox_input_files += $$join(addsrc,,$${subprojectroot_dir}/)
    }
    for(addheader, HEADERS) {
        !contains(dox_input_files, $$addheader) {
            dox_input_files += $$join(addheader,,$${subprojectroot_dir}/)
        }
    }
}

# Создание doxyfile
dox.commands=@$(COPY_FILE) $$top_srcdir/../doc/Doxyfile  $$doxyfile $$escape_expand(\\n\\t)

doxinput=INPUT=$$join(dox_input_files, " ")
# записываем одной строкой список всех файлов для тега INPUT doxygen
write_file($$doxyinputfiles, doxinput)

#dox.commands+=@echo INPUT = $$join(dox_input_files, " ") >> $$doxyfile $$escape_expand(\\n\\t)
dox.commands+=@type $$doxyinputfiles >> $$doxyfile $$escape_expand(\\n\\t)
dox.commands+=@echo "OUTPUT_DIRECTORY = $$doxoutdir" >> $$doxyfile $$escape_expand(\\n\\t)
dox.commands+=@echo INCLUDE_PATH = $$join(INCLUDEPATH, " ") >> $$doxyfile $$escape_expand(\\n\\t)
dox.commands+=@echo "PROJECT_NAME = $$PROJECTNAME" >> $$doxyfile $$escape_expand(\\n\\t)
dox.commands+=@echo QHP_NAMESPACE = dox.xmodel.$$PROJECTNAME >> $$doxyfile $$escape_expand(\\n\\t)
dox.commands+=@echo PROJECT_NUMBER = $$DOX_VERSION >> $$doxyfile $$escape_expand(\\n\\t)
dox.commands+=@echo INPUT_ENCODING = $$dox_input_encoding >> $$doxyfile $$escape_expand(\\n\\t)
# создание выходных каталогов для документации
win32{
    dox.commands+=@$(CHK_DIR_EXISTS) $$doxoutdir $(MKDIR) $$doxoutdir
}
unix{
    dox.commands+=@$(CHK_DIR_EXISTS) $$doxoutdir || $(MKDIR) $$doxoutdir
    CHK_DIR_NOT_EXISTS=test ! -d
}
dox.commands+=$$escape_expand(\\n\\t)
# генерация
dox.commands+=doxygen $$doxyfile

# замена слешей на обратные
win32 {
    dox.commands = $$replace(dox.commands, '/', '\\')
}
# не добавляем, т.к. options.pri уже созданы пустые цели
#QMAKE_EXTRA_TARGETS += dox

# очистка сгенерированной документации
unix {
    doxcleansubdir=$$doxoutdir/html/search
    doxclean.commands+=$(DEL_FILE) $$doxcleansubdir/* $$escape_expand(\\n\\t)
    doxclean.commands+=$$CHK_DIR_NOT_EXISTS $$doxcleansubdir || $(DEL_DIR) $$doxcleansubdir $$escape_expand(\\n\\t)

    doxcleansubdir=$$doxoutdir/html
    doxclean.commands+=-$(DEL_FILE) $$doxcleansubdir/* $$escape_expand(\\n\\t)
    doxclean.commands+=$$CHK_DIR_NOT_EXISTS $$doxcleansubdir || $(DEL_DIR) $$doxcleansubdir $$escape_expand(\\n\\t)

    doxclean.commands+=-$(DEL_FILE) $$doxyfile
}

win32 {
    doxoutdir=$$replace(doxoutdir, '/', '\\')
    doxyfile=$$replace(doxyfile, '/', '\\')

    doxcleansubdir=$$doxoutdir\\html\\search
    doxclean.commands+=-$(DEL_FILE) /Q /F $$doxcleansubdir\\* $$escape_expand(\\n\\t)
    doxclean.commands+=-$(DEL_DIR) $$doxcleansubdir $$escape_expand(\\n\\t)

    doxcleansubdir=$$doxoutdir\\html
    doxclean.commands+=-$(DEL_FILE) /Q /F $$doxcleansubdir\\* $$escape_expand(\\n\\t)
    doxclean.commands+=-$(DEL_DIR) $$doxcleansubdir $$escape_expand(\\n\\t)
    doxclean.commands+=-$(DEL_FILE) $$doxyfile
}

# FIX надо вставить $(INSTALL_ROOT)
doxinstalldir=$$top_installdir/$${DOXPROJECT}-doc/share/doc/$${DOXPROJECT}/$${PACKAGENAME}
doxinstalldir=$$replace(doxinstalldir, '/', '\\')
doxinstall.commands = $(INSTALL_DIR) $$doxoutdir $$doxinstalldir
doxinstall.depends += dox

doxuninstall.commands += -$(DEL_DIR) /Q /S $$doxinstalldir

# не добавляем, т.к. options.pri уже созданы пустые цели
#QMAKE_EXTRA_TARGETS += doxinstall
#QMAKE_CLEAN += doxclean
#QMAKE_EXTRA_TARGETS += doxclean
