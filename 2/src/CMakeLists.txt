add_executable(calculator
        main.cpp
        )

add_library(src STATIC
        commands.h
        commands.cpp
        main.cpp
        )