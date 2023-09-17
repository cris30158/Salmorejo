#pragma once

using namespace std;

class Parser
{
public:
    inline explicit Parser(vector<Token> input)
    {
        tokens = input;
    }

    optional<ExpressionNode> expr_node()
    {
        ExpressionNode expr;
        expr.token = next();

        // If the expression is not empty...
        if (expr.token.value.has_value())
        {
            return expr;
        }
        return {};
    }

    optional<ExitNode> exit_node()
    {
        ExitNode exit;
        // If there is an expression node with value...
        if (auto exprNode = expr_node() && next(2).type == SEMI)
        {
            optional<ExpressionNode> expr = expr_node();
            exit.exitCode = expr.value();
            return exit;
        }
        return {};
    }

    SyntaxTree parse()
    {
        l = tokens.size();
        i = 0;
        while (i < l)
        {
            Token token = tokens.at(i);
            switch (token.type)
            {
            case EXIT:
                // If there is an exit node with value...
                if (auto exitNode = exit_node())
                {
                    optional<ExitNode> node = exit_node();
                    result.exitNodes.push_back(node.value());

                    cout << result.exitNodes.size() << " | EXIT NODE - Code " << result.exitNodes.at(result.exitNodes.size() - 1).exitCode.token.value.value() << endl;

                    i += 3; // Increment by the size in tokens of the node
                }
                else
                {
                    abort();
                }
                break;
            }
        }
        cout << "Parsing procedure finished." << endl;
        return result;
    }

private:
    SyntaxTree result;
    vector<Token> tokens;
    int l, i;
    Token next(int distance = 1)
    {
        if (i + distance < l)
        {
            return tokens.at(i + distance);
        }
        return {};
    };
    void abort()
    {
        cerr << "Error: invalid syntax" << endl;
        exit(EXIT_FAILURE);
    }
};