#include <iostream>
#include <fstream>
#include "src/lexicalAnalyzer.hpp"
#include "src/parser.hpp"
#include <chrono>
int main(int argc, char *argv[])
{
    std::string fileName = argv[1];
    std::ifstream file(fileName, std::ios::binary | std::ios::ate);
    auto start = std::chrono::high_resolution_clock::now();
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    
    std::string buffer(size, '\0');
    file.read(&buffer[0], size);
    lexicalAnalyzer lexAnalyzer(buffer);
    if (!lexAnalyzer.getlexicalResult())
    {
        std::cout << "Failed in lexical Analysis\n";
        return 1;
    }
    parser parse(lexAnalyzer);
    bool parse_result = parse.parse();
    if (parse_result)
    {
        std::cout << "JSON is VALID\n";
    }
    else
    {
        std::cout << "JSON is INVALID\n";
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    
    std::cout << "Parsing Time: " << elapsed.count() << " seconds\n";
}