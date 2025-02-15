#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
class lexicalAnalyzer{
public:
    enum TokenType{
        LEFTCURLYBRACES,
        RIGHTCURLYBRACES,
        COLON,
        COMMA,
        LEFTSQUAREBRACES,
        RIGHTSQUAREBRACES,
        STRINGTOKEN,
        NUMTOKEN,
        BOOLEAN,
        NULLVALUE,
        SINGLEERRORQUOTE,
        UNKNOWNIDENTIFIER
    };
    struct Token{
        TokenType type;
        std::string value;
        Token(TokenType t, std::string v) : type(t), value(std::move(v)) {}
    };
    std::vector<Token> tokens;
    lexicalAnalyzer(std::string_view buffer);
    bool getlexicalResult();
    void getTokenType(std::string_view line, int idx, int& lineIdx);
    TokenType getType(std::string& val);
    std::string getString(TokenType& type);
    bool isCommaOrClosingBracket(char ch);
};