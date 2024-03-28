cmake_minimum_required(VERSION 3.14.0)
project(SDL2Test)
set(CMAKE_CXX_STANDARD 14)

set(mySRC ${CMAKE_SOURCE_DIR}/src) 
set(myInclude ${CMAKE_SOURCE_DIR}/include)

# static library linking
set(SDL2_LIBRARIES "${CMAKE_SOURCE_DIR}/lib/SDL2d.lib;${CMAKE_SOURCE_DIR}/lib/SDL2maind.lib")

include_directories(${myInclude} ${myInclude}/SDL)

add_executable(SDL2Test ${mySRC}/main.cpp)
target_link_libraries(SDL2Test ${SDL2_LIBRARIES})

# Instead of using a default location, I specify where the binary should be saved.
set_target_properties( SDL2Test
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/lib" # not used in this example since we do not create our own library.
    LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/lib" # not used in this example since we do not create our own library.
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin"
)

# Copy the dynamic library to the same folder as the executable file.
add_custom_command(TARGET SDL2Test POST_BUILD           # Adds a post-build event to MyTest
    COMMAND ${CMAKE_COMMAND} -E copy_if_different       # which executes "cmake - E copy_if_different..."
        "${CMAKE_SOURCE_DIR}/lib/SDL2d.dll"             # <--this is in-file
        "${CMAKE_SOURCE_DIR}/resources/NittanyLion.bmp" # <--this is also in-file
        $<TARGET_FILE_DIR:SDL2Test>)                    # <--this is out-file path