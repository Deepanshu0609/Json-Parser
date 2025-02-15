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
        return false;
    }
    if (lexer.tokens[idx].type == lexer.STRINGTOKEN)
    {
        idx++;
        if (!validateIdx())
        {
            return false;
        }
        if (lexer.tokens[idx].type != lexer.COLON)
        {
            return false;
        }
        idx++;
        if (!validateIdx())
        {
            return false;
        }
        if (lexer.tokens[idx].type == lexer.LEFTCURLYBRACES)
        {
            if (!parseBraces())
            {
                return false;
            }
        }
        else if (lexer.tokens[idx].type == lexer.LEFTSQUAREBRACES)
        {
            if (!parseSquareBraces())
            {
                return false;
            }
        }
        else if (validDataType())
        {
            idx++;
        }
        else
        {
            std::cout << "Unexpexted Value encountered " << lexer.tokens[idx].value << '\n';
            return false;
        }
        if (!validateIdx())
        {
            return false;
        }
        if (lexer.tokens[idx].type == lexer.COMMA)
        {
            if (idx + 1 >= lexer.tokens.size())
            {
                return false;
            }
            if (isClosingBracket(lexer.tokens[idx + 1].type))
            {
                return false;
            }
            if (!parseBraces())
            {
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
                return false;
            }
        }
        else if (lexer.tokens[idx].type == lexer.LEFTSQUAREBRACES)
        {

            if (!parseSquareBraces())
            {
                return false;
            }
        }
        else if (validDataType())
        {
            idx++;
        }

        if (!validateIdx())
        {
            return false;
        }

        if (lexer.tokens[idx].type == lexer.COMMA)
        {
            if (idx + 1 >= lexer.tokens.size())
            {
                return false;
            }

            if (isClosingBracket(lexer.tokens[idx + 1].type))
            {
                return false;
            }

            if (!parseSquareBraces())
            {
                return false;
            }
        }
        else if (lexer.tokens[idx].type == lexer.RIGHTSQUAREBRACES)
        {
            idx++;
        }
        else
        {

            return false;
        }
    }
    else if (lexer.tokens[idx].type == lexer.RIGHTSQUAREBRACES)
    {
        idx++;
    }
    else
    {
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
