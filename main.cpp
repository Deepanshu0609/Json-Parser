#include <iostream>
#include <fstream>
#include "lexicalAnalyzer.hpp"
#include "parser.hpp"
#include <chrono>
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Please give FileName as input only\n";
        return 1;
    }
    std::string fileName = argv[1];
    std::ifstream file(fileName, std::ios::binary | std::ios::ate);
    if (!file.is_open())
    {
        std::cerr << "Can't open the file\n";
        return 1;
    }
    auto start = std::chrono::high_resolution_clock::now();
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<Token> tokens;
    std::string buffer(size, '\0');
    file.read(&buffer[0], size);
    lexicalAnalyzer lexAnalyzer(buffer, tokens);
    if (!lexAnalyzer.getlexicalResult())
    {
        std::cout << "Failed in lexical Analysis\n";
        return 1;
    }
    parser parse(tokens);
    bool parse_result = parse.parse();
    if (!parse_result)
    {
        std::cout << "JSON is INVALID\n";
        return 1;
    }
    std::cout << "JSON is VALID\n";
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Parsing Time: " << elapsed.count() << " seconds\n";
    return 0;
}