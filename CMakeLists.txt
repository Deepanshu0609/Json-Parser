cmake_minimum_required(VERSION 3.25.1)
project(json_parser)
add_executable(json_parser main.cpp src/lexicalAnalyzer.cpp src/parser.cpp)