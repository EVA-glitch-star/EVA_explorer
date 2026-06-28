cmake_minimum_required(VERSION 4.2)
project(binary_explorer C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON) # this line ensures that in this project we use standard 17 only.


add_executable(binary_explorer main.c)

target_compile_options(binary_explorer PRIVATE
    -Wall # this enables most useful and common warnings
    -Wextra # warnings that Wall doesn't include
    -Wpedantic # this warns when your code relies on compiler-specific extensions, it helps to keep project portable
    -Wconversion # with this the gcc warns you that information might be lost
)
