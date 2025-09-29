cmake_minimum_required(VERSION 3.16)
project(matheto VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets)

# Source files organized by component
set(SOURCES
    src/main.cpp
    src/Calculator.cpp
    src/CalculatorButton.cpp
    src/MathEngine.cpp
    src/LaTeXConverter.cpp
    src/TypstConverter.cpp
)

set(HEADERS
    src/Calculator.h
    src/CalculatorButton.h
    src/MathEngine.h
    src/LaTeXConverter.h
    src/TypstConverter.h
)

add_executable(matheto ${SOURCES} ${HEADERS})

target_include_directories(matheto PRIVATE src)
target_link_libraries(matheto Qt5::Widgets)

install(TARGETS matheto DESTINATION bin)