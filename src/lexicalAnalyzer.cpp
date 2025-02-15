#include "lexicalAnalyzer.hpp"
#include <regex>

lexicalAnalyzer::lexicalAnalyzer(std::string_view buffer)
{
    // std::string line;
    // int lineIdx = 0;
    // while (std::getline(file, line))
    // {
    //     getTokenType(line, 0, lineIdx++);
    // }

    size_t start = 0, end = 0;
    int lineIdx = 0;
    while ((end = buffer.find('\n', start)) != std::string_view::npos) {
        std::string_view line = buffer.substr(start, end - start);
        getTokenType(line, 0, lineIdx);
        start = end + 1;
    }
    
    // Process last line (if no trailing newline)
    if (start < buffer.size()) {
        std::string_view line = buffer.substr(start);
        getTokenType(line, 0, lineIdx);
    }
}

bool isNumber(std::string &val)
{
    std::regex number("^[-+]?(0|([1-9]\\d*\\.?\\d*)|0?\\.\\d+)([eE][-+]?\\d+)?$");

    // Check if the input matches the pattern
    return std::regex_match(val, number);
}
lexicalAnalyzer::TokenType lexicalAnalyzer::getType(std::string &val)
{
    if (val == "true" || val == "false")
    {
        return BOOLEAN;
    }
    else if (isNumber(val))
    {
        return NUMTOKEN;
    }
    else if (val == "null")
    {
        return NULLVALUE;
    }
    else
    {
        return UNKNOWNIDENTIFIER;
    }
}

std::string lexicalAnalyzer::getString(lexicalAnalyzer::TokenType &type)
{
    switch (type)
    {
    case LEFTCURLYBRACES:
        return "LEFTCURLYBRACES";
    case RIGHTCURLYBRACES:
        return "RIGHTCURLYBRACES";
    case COLON:
        return "COLON";
    case COMMA:
        return "COMMA";
    case LEFTSQUAREBRACES:
        return "LEFTSQUAREBRACES";
    case RIGHTSQUAREBRACES:
        return "RIGHTSQUAREBRACES";
    case STRINGTOKEN:
        return "STRINGTOKEN";
    case NUMTOKEN:
        return "NUMTOKEN";
    case BOOLEAN:
        return "BOOLEAN";
    case NULLVALUE:
        return "NULLVALUE";
    case SINGLEERRORQUOTE:
        return "SINGLEERRORQUOTE";
    default:
        return "UNKOWNIDENTIFIER";
    }
}

void lexicalAnalyzer::getTokenType(std::string_view line, int idx, int& lineIdx)
{
    while (idx < line.size())
    {
        if (isspace(line[idx]))
        {
            idx++;
            continue;
        }

        std::string val = "";
        if (line[idx] == '"')
        {
            val += line[idx];
            idx++;
            while (idx < line.size())
            {
                if (line[idx] == '\\') // to cover cases like "{\"object"
                {
                    val += line[idx]; // adding backslash to val
                    idx++;
                    if (idx < line.length())
                    {
                        val += line[idx];
                        idx++;
                    }
                    continue;
                }
                if (line[idx] == '"')
                {
                    val += line[idx];
                    tokens.emplace_back(Token(STRINGTOKEN, val));
                    break;
                }
                val += line[idx++];
            }
            if (idx == line.size())
            {
                std::cout << "String started but never closed on line" << lineIdx << ' ' << val << '\n';
                tokens.emplace_back(Token(UNKNOWNIDENTIFIER, val));
                return;
            }
        }
        else if (line[idx] == '{')
        {
            tokens.emplace_back(Token(LEFTCURLYBRACES, std::string(1, line[idx])));
        }
        else if (line[idx] == '}')
        {
            tokens.emplace_back(Token(RIGHTCURLYBRACES, std::string(1, line[idx])));
        }
        else if (line[idx] == '[')
        {
            tokens.emplace_back(Token(LEFTSQUAREBRACES, std::string(1, line[idx])));
        }
        else if (line[idx] == ']')
        {
            tokens.emplace_back(Token(RIGHTSQUAREBRACES, std::string(1, line[idx])));
        }
        else if (line[idx] == ':')
        {
            tokens.emplace_back(Token(COLON, std::string(1, line[idx])));
        }
        else if (line[idx] == ',')
        {
            tokens.emplace_back(Token(COMMA, std::string(1, line[idx])));
        }
        else if (line[idx] == '\'')
        {
            val += line[idx];
            while (idx < line.size() && line[++idx] != '\'')
            {
                val += line[idx];
            }
            val += line[idx];
            std::cout << "Should be doubleQuotes here on line " << lineIdx << ' ' << val << '\n';
            tokens.emplace_back(SINGLEERRORQUOTE, val);
        }
        else
        {
            while (idx < line.size())
            {

                if (isspace(line[idx]) || isCommaOrClosingBracket(line[idx]))
                {
                    idx--;
                    break;
                }
                val += line[idx++];
            }
            tokens.emplace_back(getType(val), val);
        }
        idx++;
    }
}

bool lexicalAnalyzer::isCommaOrClosingBracket(char ch)
{
    return ch == '}' || ch == ']' || ch == ',';
}

bool lexicalAnalyzer::getlexicalResult()
{
    if (tokens.empty())
        return false;

    for (auto &[type, value] : tokens)
    {
        if (type == UNKNOWNIDENTIFIER || type == SINGLEERRORQUOTE)
        {
            return false;
        }
    }
    return true;
}
