#ifndef PARSER_H
#define PARSER_H

#include "expression_tree.h"
#include <vector>

class Parser
{
public:
    // İfadeyi ayrıştırır ve bir ifade ağacı döndürür
    NodePtr parse(const std::string &expression);

private:
    // İfadeyi tokenlara ayırır
    std::vector<std::string> tokenize(const std::string &expression);

    // Tokenlerden bir ifade ağacı oluşturur
    NodePtr buildTree(const std::vector<std::string> &tokens);
};

#endif // PARSER_H
