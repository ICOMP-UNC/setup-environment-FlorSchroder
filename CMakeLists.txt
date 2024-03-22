# ------------- PARA EJECUTAR ------------
# 1. Elimanar la carpeta build con el siguiente comando: rm -rf build
# 2. Crear la carpeta build con el siguiente comando: mkdir build
# 3. Acceder a la carpeta build con el siguiente comando: cd build
# 4. Ejecutar el siguiente comando sin unit test: cmake -GNinja .. 
# 4. Ejecutar el siguiente comando con unit test: cmake -DRUN_TESTS=1 -GNinja ..
# 5. Ejecutar el siguiente comando: ninja
# 6. Ejecutar el siguiente comando: ./FirstProjectInCMake
#
# ------------- PARA EJECUTAR LOS TESTS ------------
# Ejecutar el siguiente comando: ctest --test-dir tests
#
# ------------- PARA EJECUTAR LOS TESTS CON COBERTURA ------------
# 1. Ejecutar el siguiente comando: cmake -DRUN_COVERAGE=1 -GNinja .. 
# 2. Ejecutar el siguiente comando: ninja
# 3. Ejecutar el siguiente comando: ctest --test-dir tests
# 4. Ejecutar el siguiente comando: gcovr -r /home/florxha/Desktop/SOII/setup-environment-FlorSchroder .

# Se define la minima version de cmake
cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

project(
    "FirstProjectInCMake"
    VERSION 1.0.0
    DESCRIPTION "CMake C Project Template for Operating Systems II"
    LANGUAGES C #se habilitan los lenguajes con los cuales cmake va a ir trabajano
)

#incluir los test. CTest es un framework de testing que viene con cmake
include(CTest)

#se establece el estandar de C
set(CMAKE_STANDARD 17)

#le indicamos la carpeta donde tiene que ir a buscar los headers
include_directories(include)

#FetchContent es un modulo que permite descargar codigo fuente de un repositorio git
include(FetchContent)

# In this example we are gonna use unity to download and test our program
set(UNITY_GIT_URL "https://github.com/ThrowTheSwitch/Unity.git")

# Enable debug. OFF para que no muestre mensajes de debug. ON para que muestre mensajes de debug
set(FETCHCONTEN_QUIET OFF)

#FetchContent_Declare es una funcion que declara una dependencia. En este caso se declara la dependencia de Unity
FetchContent_Declare(
    Unity
    GIT_REPOSITORY ${UNITY_GIT_URL}
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/Unity
    UPDATE_COMMAND ""
)
# insures the named dependencies have been populated
FetchContent_MakeAvailable(Unity)

#defino el codigo fuente, a donde va a ir a buscar el codigo fuente
file(GLOB_RECURSE SOURCES "src/*.c")

#Creo el ejecutable
add_executable(${PROJECT_NAME} ${SOURCES})

#Agrego las librerias. add_subdirectory es una funcion que busca un archivo CMakeLists.txt en la carpeta que se le pasa como parametro
add_subdirectory(lib/libdyn)
add_subdirectory(lib/libsta)

# Agrego las librerias al proyecto. La diferencia entre target_include_directories y include_directories es que la primera 
#es para un target en especifico
target_include_directories(${PROJECT_NAME} PUBLIC lib/libdyn/include)
target_include_directories(${PROJECT_NAME} PUBLIC lib/libsta/include)

#Linkear las librerias
target_link_libraries(${PROJECT_NAME} StatiCLib DynamiCLib)


# add test's subdirectory. Se agrega la carpeta de tests para que cmake busque el archivo CMakeLists.txt en esa carpeta. 
if (RUN_TESTS EQUAL 1 OR RUN_COVERAGE EQUAL 1)
  add_subdirectory(tests)
endif()