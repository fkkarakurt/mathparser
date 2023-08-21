/**
 * @file parser.cpp
 * @author Fatih Küçükkarakurt (https://github.com/fkkarakurt)
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "parser.h"

std::vector<std::string> Parser::tokenize(const std::string &expression)
{
    std::vector<std::string> tokens;
    std::string currentToken;

    for (size_t i = 0; i < expression.size(); ++i)
    {
        char ch = expression[i];

        if (ch == '-')
        {
            // If the "-" sign comes at the beginning of the expression or immediately after an operator, it is a negative number.
            if (i == 0 || tokens.back() == "+" || tokens.back() == "-" || tokens.back() == "*" || tokens.back() == "/" || tokens.back() == "^" || tokens.back() == "(")
            {
                currentToken += ch;

                // Skip the rest of the loop
                continue;
            }
        }

        if (expression.substr(i, 4) == "sinh" || expression.substr(i, 4) == "cosh" ||
            expression.substr(i, 4) == "tanh" || expression.substr(i, 4) == "coth" ||
            expression.substr(i, 4) == "sech" || expression.substr(i, 4) == "csch")
        {
            tokens.push_back(expression.substr(i, 4));

            // skip 4 characters
            i += 3;
            continue;
        }

        if (expression.substr(i, 3) == "sin" || expression.substr(i, 3) == "cos" ||
            expression.substr(i, 3) == "tan" || expression.substr(i, 3) == "cot")
        {
            tokens.push_back(expression.substr(i, 3));

            // skip 3 characters
            i += 2;
            continue;
        }

        if (isdigit(ch) || ch == '.')
        {
            currentToken += ch;
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')' || ch == '^')
        {
            if (!currentToken.empty())
            {
                tokens.push_back(currentToken);
                currentToken.clear();
            }
            tokens.push_back(std::string(1, ch));
        }
        else if (isspace(ch))
        {
            if (!currentToken.empty())
            {
                tokens.push_back(currentToken);
                currentToken.clear();
            }
        }

        else if (i + 1 < expression.size() && expression.substr(i, 2) == "ln")
        {
            tokens.push_back("ln");

            // Since 'ln' is two characters long, an extra increment.
            i += 1;
        }
        else if (i + 2 < expression.size() && expression.substr(i, 3) == "log")
        {
            tokens.push_back("log");

            // An extra increment since 'log' is three characters long.
            i += 2;
        }

        else if (i + 3 < expression.size() && expression.substr(i, 4) == "sqrt")
        {
            tokens.push_back("sqrt");

            // Since 'sqrt' is four characters long, an extra increment.
            i += 3;
        }

        else if (ch == '!')
        {
            if (!currentToken.empty())
            {
                tokens.push_back(currentToken);
                currentToken.clear();
            }
            tokens.push_back("!");
        }

        else
        {
            std::cerr << "Unknown character: " << ch << std::endl;
            exit(1);
        }
    }

    // Add the last token
    if (!currentToken.empty())
    {
        tokens.push_back(currentToken);
    }

    return tokens;
}

NodePtr Parser::buildTree(const std::vector<std::string> &tokens)
{
    std::vector<NodePtr> nodeStack;

    for (size_t i = 0; i < tokens.size(); ++i)
    {
        const auto &token = tokens[i];
        std::cout << "Toke: " << token << std::endl;
        if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1))
        {
            // Number token (additional check for negative numbers)
            nodeStack.push_back(std::make_shared<ConstantNode>(std::stod(token)));
        }
        else if (token == "+" || token == "-" || token == "*" || token == "/")
        {
            if (nodeStack.size() < 1 || i == tokens.size() - 1)
            {
                std::cerr << "Incorrect statement: There are not enough operands. " << std::endl;
                exit(1);
            }
            NodePtr left = nodeStack.back();
            nodeStack.pop_back();

            // Process next token
            i++;
            NodePtr right;
            if (isdigit(tokens[i][0]) || tokens[i][0] == '-')
            {
                right = std::make_shared<ConstantNode>(std::stod(tokens[i]));
            }
            else if (tokens[i] == "(")
            {
                // bracket balance
                int balance = 1;
                size_t j = i + 1;
                for (; j < tokens.size() && balance != 0; ++j)
                {
                    if (tokens[j] == "(")
                    {
                        balance++;
                    }
                    else if (tokens[j] == ")")
                    {
                        balance--;
                    }
                }
                std::vector<std::string> subTokens(tokens.begin() + i + 1, tokens.begin() + j - 1);
                right = buildTree(subTokens);
                i = j - 1;
            }
            else
            {
                std::cerr << "Incorrect statement: Unexpected token: " << tokens[i] << std::endl;
                exit(1);
            }

            NodePtr operationNode;
            if (token == "+")
            {
                operationNode = std::make_shared<AdditionNode>(left, right);
            }
            else if (token == "-")
            {
                operationNode = std::make_shared<SubtractionNode>(left, right);
            }
            else if (token == "*")
            {
                operationNode = std::make_shared<MultiplicationNode>(left, right);
            }
            else // token == "/"
            {
                operationNode = std::make_shared<DivisionNode>(left, right);
            }

            nodeStack.push_back(operationNode);
        }
        else if (token == "(")
        {
            int balance = 1;
            size_t j = i + 1;
            for (; j < tokens.size() && balance != 0; ++j)
            {
                if (tokens[j] == "(")
                {
                    balance++;
                }
                else if (tokens[j] == ")")
                {
                    balance--;
                }
            }

            if (balance != 0)
            {
                std::cerr << "Incorrect statement: The parentheses are not balanced." << std::endl;
                exit(1);
            }

            std::vector<std::string> subTokens(tokens.begin() + i + 1, tokens.begin() + j - 1);
            NodePtr subTree = buildTree(subTokens);
            nodeStack.push_back(subTree);
            i = j - 1;
        }
        else if (token == "^")
        {
            if (nodeStack.size() < 1 || i == tokens.size() - 1)
            {
                std::cerr << "Incorrect statement: There are not enough operands." << std::endl;
                exit(1);
            }
            NodePtr base = nodeStack.back();
            nodeStack.pop_back();

            // Process next token
            i++;
            NodePtr exponent;
            if (isdigit(tokens[i][0]) || tokens[i][0] == '-' || tokens[i] == "(")
            {
                exponent = buildTree(std::vector<std::string>{tokens[i]});
            }
            else
            {
                std::cerr << "Incorrect statement: Unexpected token:" << tokens[i] << std::endl;
                exit(1);
            }

            NodePtr powerNode = std::make_shared<PowerNode>(base, exponent);
            nodeStack.push_back(powerNode);
        }
        else if (token == "sin" || token == "cos" || token == "tan" || token == "cot")
        {
            if (i == tokens.size() - 1 || tokens[i + 1] != "(")
            {
                std::cerr << "Incorrect statement: Parenthesis is missing for trigonometric function." << std::endl;
                exit(1);
            }

            // bracket balance
            int balance = 1;
            size_t j = i + 2;
            for (; j < tokens.size() && balance != 0; ++j)
            {
                if (tokens[j] == "(")
                {
                    balance++;
                }
                else if (tokens[j] == ")")
                {
                    balance--;
                }
            }

            if (balance != 0)
            {
                std::cerr << "Incorrect statement: The parentheses are not balanced." << std::endl;
                exit(1);
            }

            std::vector<std::string> subTokens(tokens.begin() + i + 2, tokens.begin() + j - 1);
            NodePtr operand = buildTree(subTokens);

            NodePtr trigNode;
            if (token == "sin")
            {
                trigNode = std::make_shared<SinNode>(operand);
            }
            else if (token == "cos")
            {
                trigNode = std::make_shared<CosNode>(operand);
            }
            else if (token == "tan")
            {
                trigNode = std::make_shared<TanNode>(operand);
            }
            else // token == "cot"
            {
                trigNode = std::make_shared<CotNode>(operand);
            }

            nodeStack.push_back(trigNode);

            // Jump to end of trigonometric expression
            i = j - 1;
        }
        else if (token == "ln" || token == "log")
        {
            if (i == tokens.size() - 1)
            {
                std::cerr << "Incorrect statement: The operand for the logarithmic function is missing." << std::endl;
                exit(1);
            }

            NodePtr operand;
            if (tokens[i + 1] == "(")
            {
                int balance = 1;
                size_t j = i + 2;
                for (; j < tokens.size() && balance != 0; ++j)
                {
                    if (tokens[j] == "(")
                    {
                        balance++;
                    }
                    else if (tokens[j] == ")")
                    {
                        balance--;
                    }
                }

                if (balance != 0)
                {
                    std::cerr << "Incorrect statement: The parentheses are not balanced." << std::endl;
                    exit(1);
                }

                std::vector<std::string> subTokens(tokens.begin() + i + 2, tokens.begin() + j - 1);
                operand = buildTree(subTokens);
                i = j - 1;
            }
            else
            {
                operand = buildTree(std::vector<std::string>{tokens[i + 1]});
                i++;
            }

            NodePtr logNode;
            if (token == "ln")
            {
                logNode = std::make_shared<LnNode>(operand);
            }
            else // token == "log"
            {
                logNode = std::make_shared<LogNode>(operand);
            }

            nodeStack.push_back(logNode);
        }
        else if (token == "sqrt")
        {
            if (i == tokens.size() - 1)
            {
                std::cerr << "Incorrect statement: The operand for the square root function is missing." << std::endl;
                exit(1);
            }

            NodePtr operand;
            if (tokens[i + 1] == "(")
            {
                int balance = 1;
                size_t j = i + 2;
                for (; j < tokens.size() && balance != 0; ++j)
                {
                    if (tokens[j] == "(")
                    {
                        balance++;
                    }
                    else if (tokens[j] == ")")
                    {
                        balance--;
                    }
                }

                if (balance != 0)
                {
                    std::cerr << "Incorrect statement: The parentheses are not balanced." << std::endl;
                    exit(1);
                }

                std::vector<std::string> subTokens(tokens.begin() + i + 2, tokens.begin() + j - 1);
                operand = buildTree(subTokens);
                i = j - 1;
            }
            else
            {
                operand = buildTree(std::vector<std::string>{tokens[i + 1]});
                i++;
            }

            NodePtr sqrtNode = std::make_shared<SqrtNode>(operand);
            nodeStack.push_back(sqrtNode);
        }
        else if (token == "^")
        {
            if (nodeStack.size() < 1 || i == tokens.size() - 1)
            {
                std::cerr << "Incorrect statement: There are not enough operands." << std::endl;
                exit(1);
            }

            NodePtr base = nodeStack.back();
            nodeStack.pop_back();

            // Process next token
            i++;
            NodePtr exponent;

            if (tokens[i] == "(")
            {
                // bracket balance
                int balance = 1;
                size_t j = i + 1;
                for (; j < tokens.size() && balance != 0; ++j)
                {
                    if (tokens[j] == "(")
                    {
                        balance++;
                    }
                    else if (tokens[j] == ")")
                    {
                        balance--;
                    }
                }

                if (balance != 0)
                {
                    std::cerr << "Incorrect statement: The parentheses are not balanced." << std::endl;
                    exit(1);
                }

                std::vector<std::string> subTokens(tokens.begin() + i + 1, tokens.begin() + j - 1);
                exponent = buildTree(subTokens);
                i = j - 1;
            }
            else
            {
                exponent = buildTree(std::vector<std::string>{tokens[i]});
            }

            NodePtr powerNode = std::make_shared<PowerNode>(base, exponent);
            nodeStack.push_back(powerNode);
        }
        else if (token == "sinh" || token == "cosh" || token == "tanh" || token == "coth" || token == "sech" || token == "csch")
        {
            if (i == tokens.size() - 1 || tokens[i + 1] != "(")
            {
                std::cerr << "Incorrect statement: Parenthesis missing for hyperbolic function." << std::endl;
                exit(1);
            }

            // bracket balance
            int balance = 1;
            size_t j = i + 2;
            for (; j < tokens.size() && balance != 0; ++j)
            {
                if (tokens[j] == "(")
                {
                    balance++;
                }
                else if (tokens[j] == ")")
                {
                    balance--;
                }
            }

            if (balance != 0)
            {
                std::cerr << "Incorrect statement: The parentheses are not balanced." << std::endl;
                exit(1);
            }

            std::vector<std::string> subTokens(tokens.begin() + i + 2, tokens.begin() + j - 1);
            NodePtr operand = buildTree(subTokens);

            NodePtr hyperbolicNode;
            if (token == "sinh")
            {
                hyperbolicNode = std::make_shared<SinhNode>(operand);
            }
            else if (token == "cosh")
            {
                hyperbolicNode = std::make_shared<CoshNode>(operand);
            }
            else if (token == "tanh")
            {
                hyperbolicNode = std::make_shared<TanhNode>(operand);
            }
            else if (token == "coth")
            {
                hyperbolicNode = std::make_shared<CothNode>(operand);
            }
            else if (token == "sech")
            {
                hyperbolicNode = std::make_shared<SechNode>(operand);
            }
            else // token == "csch"
            {
                hyperbolicNode = std::make_shared<CschNode>(operand);
            }

            nodeStack.push_back(hyperbolicNode);

            // Jump to end of hyperbolic expression
            i = j - 1;
        }
        else if (token == "!")
        {
            if (nodeStack.size() < 1)
            {
                std::cerr << "Incorrect statement: There are not enough operands." << std::endl;
                exit(1);
            }

            NodePtr operand = nodeStack.back();
            nodeStack.pop_back();
            NodePtr factorialNode = std::make_shared<FactorialNode>(operand);
            nodeStack.push_back(factorialNode);
        }
        else
        {
            std::cerr << "Unknown token: " << token << std::endl;
            exit(1);
        }

        std::cout << "NodeStack Size: " << nodeStack.size() << std::endl;
    }

    if (nodeStack.size() != 1)
    {
        std::cerr << "Incorrect statement: Not enough operators." << std::endl;
        exit(1);
    }

    return nodeStack.back();
}

NodePtr Parser::parse(const std::string &expression)
{
    std::vector<std::string> tokens = tokenize(expression);
    return buildTree(tokens);
}
