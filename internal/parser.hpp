#pragma once
using namespace std;
class Parser
{
public:
    Parser(TokenList tokens) : m_tokens(move(tokens)) {}

    /* Expr parsing procedure */
    experimental::optional<Expr> parse_expr(unsigned short int d = 1)
    {
        if (isLiteral(next(d).type))
        {
            TokenType t = next(d).type;
            /* Check if is not a single literal, but a 2 literal operation */
            if (isOperator(next(d + 1).value[0]))
            {
                Token arg1 = next(d);
                char op = next(d + 1).value[0];
                Token arg2 = next(d + 2);
                /* Check if the types match */
                if (arg2.type == t)
                {
                    /* Check if there is not a division by 0 */
                    if (op != '/' && arg2.value != "0")
                    {
                        string s = arg1.value + " " + op + " " + arg2.value;
                        /* Return an expr with the new value */
                        return Expr{t, s};
                    }
                    throwError(DIVIDE_BY_ZERO);
                }
                throwError(EXPECTED_LITERAL);
            }
            return Expr{next()};
        }
        return {};
    }

    Root parse()
    {
        /* Converts tokens into an AST */
        while (i < m_tokens.size())
        {
            t = m_tokens.get(i);
            switch (t.type)
            {
            case IMPORT:
                if (next().type == IDENTIFIER && next(2).type == FROM && next(3).type == STRING_LITERAL)
                {
                    addImport({next(), next(3).value});
                }
                break;
            case EXIT:
                if (auto expr = parse_expr())
                {
                    debug("EXIT -> code: " + expr.value().literal.value);
                    addStatement({expr.value()});
                    break;
                }
                throwError(SYNTAX_ERROR);
                break;
            case INT_KEYWORD:
                if (next().type == IDENTIFIER)
                {
                    if (next(2).type == EQUAL)
                    {
                        if (auto expr = parse_expr(3))
                        {
                            // Push-back an int assign with value
                            debug("INT_INIT -> id: " + next().value + ", value: " + expr.value().literal.value);
                            break;
                        }
                        throwError(EXPECTED_EXPR);
                    }
                    else
                    {
                        // Push-back an int assign without value
                        debug("INT_INIT -> id: " + next().value + ", value: null");
                        break;
                    }
                    break;
                }
                throwError(SYNTAX_ERROR);
                break;
            default:
                break;
            }
            ++i;
        }
        return tree;
    }

private:
    TokenList m_tokens;
    Token t;
    unsigned int i = 0;
    Root tree;
    Token next(short unsigned int distance = 1)
    {
        return m_tokens.get(i + distance);
    }
    void debug(string input)
    {
        if (SHOW_COMPILER_DEBUG)
        {
            cout << input << endl;
        }
    }
    void addStatement(Exit stat)
    {
        tree.childs.push_back(stat);
    }
    void addImport(Import imp)
    {
        tree.imports.push_back(imp);
    }
};
