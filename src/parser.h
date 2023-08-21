/**
 * @file parser.h
 * @author Fatih Küçükkarakurt (https://github.com/fkkarakurt)
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef PARSER_H
#define PARSER_H

#include "expression_tree.h"
#include <vector>

class Parser
{
public:
    // Parses the expression and returns an expression tree
    NodePtr parse(const std::string &expression);

private:
    // Splits the expression into tokens
    std::vector<std::string> tokenize(const std::string &expression);

    // Creates an expression tree from tokens
    NodePtr buildTree(const std::vector<std::string> &tokens);
};

#endif // PARSER_H
