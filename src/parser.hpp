#include <iostream>
#include "lexicalAnalyzer.hpp"

class parser
{
private:
    bool _parsing = true;
    lexicalAnalyzer &lexer;
    int idx = 0;

public:
    parser(lexicalAnalyzer &lex) : lexer(lex) {};
    bool parse();
    bool parseBraces();
    bool parseSquareBraces();
    bool validateIdx();
    bool validDataType();
    bool isClosingBracket(lexicalAnalyzer::TokenType &type);
};