/**
 * @file test_parser.cpp
 * @author Fatih Küçükkarakurt (https://github.com/fkkarakurt)
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <iostream>
#include "parser.h"

int main()
{
    Parser parser;
    std::string expression = "3.5 + 4.5";
    std::string subtraction = "5.4 - 3.2";
    std::string multiplication = "4.2 * 1.2";
    std::string divide = "6.7 / 3.1";
    std::string parentheses = "(3.5 + 3.2) * 2";
    std::string parentheses2 = "4.2 / (1.2 * 2.3)";
    std::string power = "2^3";
    std::string negative = "-5 + 2";
    std::string sinExpression = "sin(0)";
    std::string cosExpression = "cos(0)";
    std::string tanExpression = "tan(0)";
    std::string cotExpression = "cot(1.5708)";
    std::string naturalLog = "ln(2.71)";
    std::string logBase10 = "log(100)";
    std::string sqrtExpression = "sqrt(144)";
    std::string powerReal = "2^3.5";
    std::string powerNegativeReal = "2^-0.5";
    std::string sinhExpression = "sinh(1)";
    std::string coshExpression = "cosh(1)";
    std::string tanhExpression = "tanh(1)";
    std::string cothExpression = "coth(1)";
    std::string sechExpression = "sech(1)";
    std::string cschExpression = "csch(1)";
    std::string factorialExpression = "5!";

    NodePtr root = parser.parse(expression);
    NodePtr root2 = parser.parse(subtraction);
    NodePtr root3 = parser.parse(multiplication);
    NodePtr root4 = parser.parse(divide);
    NodePtr root5 = parser.parse(parentheses);
    NodePtr root6 = parser.parse(parentheses2);
    NodePtr root7 = parser.parse(power);
    NodePtr root8 = parser.parse(negative);
    NodePtr sinRoot = parser.parse(sinExpression);
    NodePtr cosRoot = parser.parse(cosExpression);
    NodePtr tanRoot = parser.parse(tanExpression);
    NodePtr cotRoot = parser.parse(cotExpression);
    NodePtr root9 = parser.parse(naturalLog);
    NodePtr root10 = parser.parse(logBase10);
    NodePtr sqrtRoot = parser.parse(sqrtExpression);
    NodePtr powerRealRoot = parser.parse(powerReal);
    NodePtr powerNegativeRealRoot = parser.parse(powerNegativeReal);
    NodePtr sinhRoot = parser.parse(sinhExpression);
    NodePtr coshRoot = parser.parse(coshExpression);
    NodePtr tanhRoot = parser.parse(tanhExpression);
    NodePtr cothRoot = parser.parse(cothExpression);
    NodePtr sechRoot = parser.parse(sechExpression);
    NodePtr cschRoot = parser.parse(cschExpression);
    NodePtr factorialRoot = parser.parse(factorialExpression);

    double result = root->evaluate();
    double result2 = root2->evaluate();
    double result3 = root3->evaluate();
    double result4 = root4->evaluate();
    double result5 = root5->evaluate();
    double result6 = root6->evaluate();
    double result7 = root7->evaluate();
    double result8 = root8->evaluate();
    double result9 = root9->evaluate();
    double result10 = root10->evaluate();
    double factorialResult = factorialRoot->evaluate();

    std::cout << expression << " = " << result << std::endl;
    std::cout << subtraction << " = " << result2 << std::endl;
    std::cout << multiplication << " = " << result3 << std::endl;
    std::cout << divide << " = " << result4 << std::endl;
    std::cout << parentheses << " = " << result5 << std::endl;
    std::cout << parentheses2 << " = " << result6 << std::endl;
    std::cout << power << " = " << result7 << std::endl;
    std::cout << negative << " = " << result8 << std::endl;
    std::cout << sinExpression << " = " << sinRoot->evaluate() << std::endl;
    std::cout << cosExpression << " = " << cosRoot->evaluate() << std::endl;
    std::cout << tanExpression << " = " << tanRoot->evaluate() << std::endl;
    std::cout << cotExpression << " = " << cotRoot->evaluate() << std::endl;
    std::cout << naturalLog << " = " << result9 << std::endl;
    std::cout << logBase10 << " = " << result10 << std::endl;
    std::cout << sqrtExpression << " = " << sqrtRoot->evaluate() << std::endl;
    std::cout << powerReal << " = " << powerRealRoot->evaluate() << std::endl;
    std::cout << powerNegativeReal << " = " << powerNegativeRealRoot->evaluate() << std::endl;
    std::cout << sinhExpression << " = " << sinhRoot->evaluate() << std::endl;
    std::cout << coshExpression << " = " << coshRoot->evaluate() << std::endl;
    std::cout << tanhExpression << " = " << tanhRoot->evaluate() << std::endl;
    std::cout << cothExpression << " = " << cothRoot->evaluate() << std::endl;
    std::cout << sechExpression << " = " << sechRoot->evaluate() << std::endl;
    std::cout << cschExpression << " = " << cschRoot->evaluate() << std::endl;
    std::cout << factorialExpression << " = " << factorialResult << std::endl;

    return 0;
}
