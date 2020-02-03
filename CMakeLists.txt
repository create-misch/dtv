project (smp)

set(TYPE_BUILD SHARED)

add_subdirectory (3rdparty)
add_subdirectory (components)
add_subdirectory (smp_apps)

set(CMAKE_C_FLAGS  "-Wall -Wextra -Wshadow -Wunknown-pragmas -Wformat -Wformat-security  -Wconversion -Wsign-conversion -D_FORTIFY_SOURCE=2")

