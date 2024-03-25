# ------------- TO EXECUTE ------------
#1. Delete the build folder with the following command: rm -rf build
#2. Create the build folder with the following command: mkdir build
#3. Access the build folder with the following command: cd build
#4. Run the following command without unit test: cmake -GNinja ..
# 4. Run the following command with unit test: cmake -DRUN_TESTS=1 -GNinja ..
#5. Run the following command: ninja
#6. Run the following command: ./FirstProjectInCMake
#
# ------------- TO RUN THE TESTS ------------
# Run the following command: ctest --test-dir tests
#
# ------------- TO RUN TESTS WITH COVERAGE ------------
# 1. Run the following command: cmake -DRUN_COVERAGE=1 -GNinja ..
#2. Run the following command: ninja
# 3. Run the following command: ctest --test-dir tests
# 4. Run the following command: gcovr -r /home/florxha/Desktop/SOII/setup-environment-FlorSchroder .

# Define the minimun version of cmake
cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

project(
    "FirstProjectInCMake"
    VERSION 1.0.0
    DESCRIPTION "CMake C Project Template for Operating Systems II"
    LANGUAGES C #The languages ​​with which cmake will work are enabled
)

#include the tests. CTest is a testing framework that comes with cmake
include(CTest)

#the C standard is established
set(CMAKE_STANDARD 17)

#We indicate the folder where you have to go to look for the headers
include_directories(include)

#FetchContent is a module that allows you to download source code from a git repository
include(FetchContent)

# In this example we are gonna use unity to download and test our program
set(UNITY_GIT_URL "https://github.com/ThrowTheSwitch/Unity.git")

# Enable debug. OFF para que no muestre mensajes de debug. ON para que muestre mensajes de debug
set(FETCHCONTEN_QUIET OFF)

#FetchContent_Declare is a function that declares a dependency. In this case the Unity dependency is declared
FetchContent_Declare(
    Unity
    GIT_REPOSITORY ${UNITY_GIT_URL}
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/Unity
    UPDATE_COMMAND ""
)
# insures the named dependencies have been populated
FetchContent_MakeAvailable(Unity)

#I define the source code, where it will go to look for the source code
file(GLOB_RECURSE SOURCES "src/*.c")

#I create the executable
add_executable(${PROJECT_NAME} ${SOURCES})

#I add the libraries. add_subdirectory is a function that looks for a CMakeLists.txt file in the folder passed to it as a parameter
add_subdirectory(lib/libdyn)
add_subdirectory(lib/libsta)

# I add the libraries to the project. The difference between target_include_directories and include_directories is that the former
#is for a specific target
target_include_directories(${PROJECT_NAME} PUBLIC lib/libdyn/include)
target_include_directories(${PROJECT_NAME} PUBLIC lib/libsta/include)

#Link the libraries
target_link_libraries(${PROJECT_NAME} StatiCLib DynamiCLib)


# add test's subdirectory. The tests folder is added so that cmake looks for the CMakeLists.txt file in that folder.
if (RUN_TESTS EQUAL 1 OR RUN_COVERAGE EQUAL 1)
  add_subdirectory(tests)
endif()
