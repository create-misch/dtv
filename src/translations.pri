isEmpty(subprojectroot_dir){
        error("You have to set subprojectroot_dir variable. Need for dox sources")
    }

translations_lrelease.input = TRANSLATIONS
translations_lrelease.output = $$subprojectroot_dir/translations/${QMAKE_FILE_BASE}.qm
translations_lrelease.commands = $$[QT_INSTALL_BINS]/lrelease ${QMAKE_FILE_IN} -qm ${QMAKE_FILE_OUT}
translations_lrelease.CONFIG += no_link target_predeps no_clean
translations_lrelease.dependency_type = TYPE_QRC
QMAKE_EXTRA_COMPILERS += translations_lrelease
