# -------------------------------
# Add targets for executable code (SRC)
# -------------------------------
add_executable(studio16 Studio16.cpp
        ../lib/mockos/RenameMacro.cpp
        ../lib/mockos/Lab5Tests.cpp)
target_link_libraries(studio16 mockos)

add_executable(studio17 Studio17.cpp
        ../lib/mockos/RenameMacro.cpp
        ../lib/mockos/Lab5Tests.cpp)
target_link_libraries(studio17 mockos)

add_executable(studio18 Studio18.cpp
        ../lib/mockos/RenameMacro.cpp
        ../lib/mockos/Lab5Tests.cpp)
target_link_libraries(studio18 mockos)

add_executable(studio19 Studio19.cpp
        ../lib/mockos/RenameMacro.cpp
        ../lib/mockos/Lab5Tests.cpp)
target_link_libraries(studio19 mockos)

add_executable(studio20 Studio20.cpp
        ../lib/mockos/RenameMacro.cpp
        ../lib/mockos/Lab5Tests.cpp)
target_link_libraries(studio20 mockos)

add_executable(studio21 Studio21.cpp
        ../lib/mockos/RenameMacro.cpp
        ../lib/mockos/Lab5Tests.cpp)
target_link_libraries(studio21 mockos)

add_executable(lab5 Lab5.cpp
        ../lib/mockos/RenameMacro.cpp)
target_link_libraries(lab5 mockos)
