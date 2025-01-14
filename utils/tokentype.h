enum TokenType
{
    // Exit statements
    EXIT,
    RETURN,
    IMPORT,
    FROM,
    // Data types and keywords
    INT_LITERAL,
    INT_KEYWORD,
    STRING_LITERAL,
    STRING_KEYWORD,
    NUMBER_LITERAL,
    NUMBER_KEYWORD,
    TRUE,
    FALSE,
    BOOL_KEYWORD,
    VAR_KEYWORD,
    FUNCTION_KEYWORD,
    NULL_KEYWORD,
    STRUCT_KEYWORD,
    ENUM_KEYWORD,
    CLASS_KEYWORD,
    PUBLIC_KEYWORD,
    PRIVATE_KEYWORD,
    MODULE_KEYWORD,
    // Operators
    OPERATOR,
    AND,
    OR,
    NOT,
    GREATER,
    LOWER,
    // Symbols
    EQUAL,
    COMMA,
    POINT,
    PAR_OPEN,
    PAR_CLOSE,
    C_BRACKET_OPEN,
    C_BRACKET_CLOSE,
    S_BRACKET_OPEN,
    S_BRACKET_CLOSE,
    // Modifiers
    CONST,
    UNSIGNED,
    SHORT,
    LONG,
    X8,
    X16,
    X32,
    X64,
    X128,
    THIS,
    STATIC,
    // Others
    IDENTIFIER,
    OUT,
    INPUT,
    TYPEOF
};
struct Token
{
    TokenType type;
    string value;
};