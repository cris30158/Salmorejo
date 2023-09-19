#pragma once
#include "tokenUtilities.hpp"
#include <vector>
#include <variant>
using namespace std;

struct Assignment
{
    Token identifier;
    Token value;
};
// Basic node that contains instructions by itself
struct StatementNode
{
    Assignment statement;
};

// Universal container, contains every node
struct SyntaxTree
{
    vector<StatementNode> nodes;
};