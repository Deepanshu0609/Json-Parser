#include <iostream>
#include <vector>
#include "token.hpp"

class parser
{
private:
    bool _parsing = true;
    int idx = 0;
    std::vector<Token> &_tokens;

public:
    parser(std::vector<Token> &token) : _tokens(token) {};
    bool parse();
    bool parseBraces();
    bool parseSquareBraces();
    bool validateIdx();
    bool validDataType();
    bool isClosingBracket(TokenType &type);
};