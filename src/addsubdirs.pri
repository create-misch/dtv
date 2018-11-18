TEMPLATE = subdirs

# addSubdirs(subdirs,deps): Adds directories to the project that depend on
# other directories
defineTest(addSubdirs) {
    for(subdirs, 1) {
        entries = $$files($$subdirs)
        for(entry, entries) {
            name = $$replace(entry, [/\\\\], _)
            SUBDIRS += $$name
            eval ($${name}.subdir = $$entry)
            for(dep, 2):eval ($${name}.depends += $$replace(dep, [/\\\\], _))
            export ($${name}.subdir)
            export ($${name}.depends)
        }
    }
    export (SUBDIRS)
}
defineTest(addDepends) {
    project = $$replace(1, [/\\\\], _)
    for (dep, 2) : eval($${project}.depends += $$replace(dep, [/\\\\], _))
    export ($${project}.depends)
}
