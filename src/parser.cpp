#include "parser.hpp"

bool parser::validDataType()
{
    TokenType type = _tokens[idx].type;
    return type == BOOLEAN || type == NULLVALUE || type == STRINGTOKEN || type == NUMTOKEN;
}

bool parser::isClosingBracket(TokenType &type)
{
    return type == RIGHTCURLYBRACES || type == RIGHTSQUAREBRACES;
}

bool parser::validateIdx()
{
    return idx < _tokens.size();
}

bool parser::parseBraces()
{
    idx++; // parsed '{'
    if (!validateIdx())
    {
        return false;
    }
    if (_tokens[idx].type == STRINGTOKEN)
    {
        idx++;
        if (!validateIdx())
        {
            return false;
        }
        if (_tokens[idx].type != COLON)
        {
            return false;
        }
        idx++;
        if (!validateIdx())
        {
            return false;
        }
        if (_tokens[idx].type == LEFTCURLYBRACES)
        {
            if (!parseBraces())
            {
                return false;
            }
        }
        else if (_tokens[idx].type == LEFTSQUAREBRACES)
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
            std::cout << "Unexpexted Value encountered " << _tokens[idx].value << '\n';
            return false;
        }
        if (!validateIdx())
        {
            return false;
        }
        if (_tokens[idx].type == COMMA)
        {
            if (idx + 1 >= _tokens.size())
            {
                return false;
            }
            if (isClosingBracket(_tokens[idx + 1].type))
            {
                return false;
            }
            if (!parseBraces())
            {
                return false;
            }
        }
        else if (_tokens[idx].type == RIGHTCURLYBRACES)
        {
            idx++;
        }
        else
        {
            return false;
        }
    }
    else if (_tokens[idx].type == RIGHTCURLYBRACES)
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
    if (_tokens[idx].type == LEFTCURLYBRACES || _tokens[idx].type == LEFTSQUAREBRACES || validDataType())
    {

        if (_tokens[idx].type == LEFTCURLYBRACES)
        {
            if (!parseBraces())
            {
                return false;
            }
        }
        else if (_tokens[idx].type == LEFTSQUAREBRACES)
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

        if (_tokens[idx].type == COMMA)
        {
            if (idx + 1 >= _tokens.size())
            {
                return false;
            }

            if (isClosingBracket(_tokens[idx + 1].type))
            {
                return false;
            }

            if (!parseSquareBraces())
            {
                return false;
            }
        }
        else if (_tokens[idx].type == RIGHTSQUAREBRACES)
        {
            idx++;
        }
        else
        {

            return false;
        }
    }
    else if (_tokens[idx].type == RIGHTSQUAREBRACES)
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
    switch (_tokens[idx].type)
    {
    case LEFTCURLYBRACES:
        if (!parseBraces())
        {
            return false;
        }
        break;
    case LEFTSQUAREBRACES:
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
