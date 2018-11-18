isEmpty(subprojectroot_dir){
    error("You have to set subprojectroot_dir variable! Need for cppcheck")
}
unix{
    PLATFORM_OPTS="--platform=unix64 --template=gcc"
}
win32{
    PLATFORM_OPTS="--platform=win32 --template=vs"
}

for(addsrc, SOURCES) {
    CHECK_SOURCES += $$join(addsrc,,$${subprojectroot_dir}/)
}
cppcheck.commands = cppcheck $$PLATFORM_OPTS --enable=all\
    $$join(CHECK_SOURCES, " ") -I$$join(INCLUDEPATH, " -I")\
     -I$${subprojectroot_dir} -D$$join(DEFINES, " -D")

QMAKE_EXTRA_TARGETS += cppcheck
