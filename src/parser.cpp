#include "parser.hpp"

bool parser::validDataType()
{
    lexicalAnalyzer::TokenType type = lexer.tokens[idx].type;
    return type == lexer.BOOLEAN || type == lexer.NULLVALUE || type == lexer.STRINGTOKEN || type == lexer.NUMTOKEN;
}

bool parser::isClosingBracket(lexicalAnalyzer::TokenType &type)
{
    return type == lexer.RIGHTCURLYBRACES || type == lexer.RIGHTSQUAREBRACES;
}

bool parser::validateIdx()
{
    return idx < lexer.tokens.size();
}

bool parser::parseBraces()
{
    idx++; // parsed '{'
    if (!validateIdx())
    {
        std::cout << "Failed at parseBraces\n"
                  << idx << '\n';
        return false;
    }
    if (lexer.tokens[idx].type == lexer.STRINGTOKEN)
    {
        idx++;
        if (!validateIdx())
        {
            std::cout << "Failed at parseBraces\n"
                      << idx << '\n';
            return false;
        }
        if (lexer.tokens[idx].type != lexer.COLON)
        {
            std::cout << "Failed at parseBraces\n"
                      << idx << '\n';
            return false;
        }
        idx++;
        if (!validateIdx())
        {
            std::cout << "Failed at parseBraces\n"
                      << idx << '\n';
            return false;
        }
        if (lexer.tokens[idx].type == lexer.LEFTCURLYBRACES)
        {
            if (!parseBraces())
            {
                std::cout << "Failed at parseBraces\n"
                          << idx << '\n';
                return false;
            }
        }
        else if (lexer.tokens[idx].type == lexer.LEFTSQUAREBRACES)
        {
            if (!parseSquareBraces())
            {
                std::cout << "Failed at parseBraces\n"
                          << idx << '\n';
                return false;
            }
        }
        else if (validDataType())
        {
            idx++;
        }
        else
        {
            std::cout << "Unknown Value encountered " << lexer.tokens[idx].value << '\n';
            return false;
        }
        if (!validateIdx())
        {
            std::cout << "Failed at parseBraces\n"
                      << idx << '\n';
            return false;
        }
        if (lexer.tokens[idx].type == lexer.COMMA)
        {
            if (idx + 1 >= lexer.tokens.size())
            {
                std::cout << "Failed at parseBraces\n"
                          << idx << '\n';
                return false;
            }
            if (isClosingBracket(lexer.tokens[idx + 1].type))
            {
                std::cout << "Failed at parseBraces\n"
                          << idx << '\n';
                return false;
            }
            if (!parseBraces())
            {
                std::cout << "Failed at parseBraces\n"
                          << idx << '\n';
                return false;
            }
        }
        else if (lexer.tokens[idx].type == lexer.RIGHTCURLYBRACES)
        {
            idx++;
        }
        else
        {
            std::cout << "Failed at parseBraces\n"
                      << idx << '\n';
            return false;
        }
    }
    else if (lexer.tokens[idx].type == lexer.RIGHTCURLYBRACES)
    {
        idx++;
    }
    else
    {
        return false;
    }
    return true;
}

bool parser::parseSquareBraces()
{
    idx++;
    if (!validateIdx())
    {
        return false;
    }
    if (lexer.tokens[idx].type == lexer.LEFTCURLYBRACES || lexer.tokens[idx].type == lexer.LEFTSQUAREBRACES || validDataType())
    {

        if (lexer.tokens[idx].type == lexer.LEFTCURLYBRACES)
        {
            if (!parseBraces())
            {
                std::cout << "Failed at parseBraces\n"
                          << idx << '\n';
                return false;
            }
        }
        else if (lexer.tokens[idx].type == lexer.LEFTSQUAREBRACES)
        {

            if (!parseSquareBraces())
            {
                std::cout << "Failed at parseBraces\n"
                          << idx << '\n';
                return false;
            }
        }
        else if (validDataType())
        {
            idx++;
        }

        if (!validateIdx())
        {
            std::cout << "Failed at parseBraces\n"
                      << idx << '\n';
            return false;
        }

        if (lexer.tokens[idx].type == lexer.COMMA)
        {

            if (idx + 1 >= lexer.tokens.size())
            {
                std::cout << "Failed at parseBraces\n"
                          << idx << '\n';
                return false;
            }

            if (isClosingBracket(lexer.tokens[idx + 1].type))
            {
                std::cout << "Failed at parseBraces\n"
                          << idx << '\n';
                return false;
            }

            if (!parseSquareBraces())
            {
                std::cout << "Failed at parseBraces\n"
                          << idx << '\n';
                return false;
            }
        }
        else if (lexer.tokens[idx].type == lexer.RIGHTSQUAREBRACES)
        {
            idx++;
        }
        else
        {
            std::cout << "Failed at parseBraces\n"
                      << idx << '\n';
            return false;
        }
    }
    else if (lexer.tokens[idx].type == lexer.RIGHTSQUAREBRACES)
    {
        idx++;
    }
    else
    {
        std::cout << "Failed at parseBraces\n"
                  << idx << '\n';
        return false;
    }
    return true;
}
// recursive parser
bool parser::parse()
{
    switch (lexer.tokens[idx].type)
    {
    case lexer.LEFTCURLYBRACES:
        if (!parseBraces())
        {
            return false;
        }
        break;
    case lexer.LEFTSQUAREBRACES:
        if (!parseSquareBraces())
        {
            return false;
        }
        break;
    default:
        return false;
    }
    return true;
}
