cmake_minimum_required(VERSION 3.10)
project(json_parser)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(json_parser 
    main.cpp
    src/lexicalAnalyzer.cpp 
    src/parser.cpp  # Add other .cpp files here
)

target_include_directories(json_parser PRIVATE include)
