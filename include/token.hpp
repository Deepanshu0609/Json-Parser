#pragma once
enum TokenType
{
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
struct Token
{
    TokenType type;
    std::string value;
    Token(TokenType t, std::string v) : type(t), value(std::move(v)) {}
};