# CMakeList.txt : CMake project for TypeAhead, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (TypeAhead "main.cpp" "WordTree.cpp" "WordTree.hpp")


set_property(TARGET TypeAhead PROPERTY CXX_STANDARD 17)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    target_compile_options(TypeAhead PRIVATE /W4 /permissive-)
    #target_compile_options(UnitTestRunner PRIVATE /W4 /permissive-)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    target_compile_options(TypeAhead PRIVATE -Wall -Wextra -pedantic)
    #target_compile_options(UnitTestRunner PRIVATE -Wall -Wextra -pedantic)
endif()



#
# Add GoogleTest
#
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# Now simply link against gtest or gtest_main as needed. Eg
#target_link_libraries(UnitTestRunner gtest_main)
