add_executable(calculator
        main.cpp
        )

add_library(commands STATIC
        StackCalc.h
        StackCalc.cpp
        main.cpp
        )