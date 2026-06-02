cmake_minimum_required(VERSION 3.14)
project(CppProjectTemplate VERSION 1.0.0 LANGUAGES C CXX)


find_package(SQLite3 REQUIRED)

add_executable(MyExe main.cpp)
target_link_libraries(MyExe PRIVATE sqlite3)



