#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
#include "token.hpp"
class lexicalAnalyzer
{

public:
    std::vector<Token> &_tokens;
    lexicalAnalyzer(std::string_view buffer, std::vector<Token> &tokens);
    bool getlexicalResult();
    void getTokenType(std::string_view line, int idx, int &lineIdx);
    TokenType getType(std::string &val);
    std::string getString(TokenType &type);
    bool isCommaOrClosingBracket(char ch);
};