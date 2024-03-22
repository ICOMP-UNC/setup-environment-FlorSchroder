# Se define la minima version de cmake
cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

project(
    "FirstProjectInCMake"
    VERSION 1.0.0
    DESCRIPTION "CMake C Project Template for Operating Systems II"
    LANGUAGES C #se habilitan los lenguajes con los cuales cmake va a ir trabajano
)

#se establece el estandar de C
set(CMAKE_STANDARD 17)

#le indicamos la carpeta donde tiene que ir a buscar los headers
include_directories(include)

#set(CMAKE_C_)

#defino el codigo fuente, a donde va a ir a buscar el codigo fuente
file(GLOB_RECURSE SOURCES "src/*.c")

#Creo el ejecutable
add_executable(${PROJECT_NAME} ${SOURCES})