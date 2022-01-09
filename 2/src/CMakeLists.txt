add_executable(calculator
        main.cpp
        commands.h
        commands.cpp
        )

add_library(src STATIC
        commands.h
        commands.cpp
        main.cpp
        )