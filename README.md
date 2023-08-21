# MathParser

MathParser actually works as a **Mathematical Expression Evaluator**. It's pretty fast. **Written in C++**. It uses standard libraries and has zero external dependency. So you can compile easily and not have to deal with annoying debug errors. It is quite light. The main reason for its development was that the C and C++ codes on the servers were compiled in the background with hot reloading and rendered with HTML. I am still working on this project.

## To summarize briefly:

### Mathematical Expression Evaluator

The Mathematical Expression Evaluator is an intricate and robust system designed to parse and evaluate a wide range of mathematical expressions, transforming them from their standard infix notation into a structured expression tree. This transformation facilitates efficient and accurate computation, ensuring that even complex expressions are handled with precision.

At the heart of this evaluator lies the `Parser` class, which tokenizes input expressions and constructs the expression tree. The tree itself is composed of nodes, each representing mathematical operations or values. These nodes, ranging from basic arithmetic operations to advanced trigonometric and hyperbolic functions, encapsulate the logic required to compute their respective operations. The versatility of the node system allows for the addition of further mathematical functions in the future, making the evaluator extensible.

A notable feature is the ability to handle **2x2 matrix** inversion, highlighting the evaluator's potential in linear algebra applications. Comprehensive testing ensures that the parser accurately interprets a wide array of mathematical expressions, from simple arithmetic to complex functions.

Developers and mathematicians alike will find this project to be a valuable tool. Whether it's for educational purposes, software development, or advanced mathematical research, the Mathematical Expression Evaluator stands as a testament to the power of structured programming and algorithmic design.

## Example Usage:

Using Mathparser is very practical.

For example, suppose we have an example file named `example.cpp`:

```cpp
#include <iostream>
#include "parser.h"

int main()
{
    Parser parser;

    // Let's calculate 2 to the -8 power.
    std::string powerNegativeReal = "2^-8";
    NodePtr powerNegativeRealRoot = parser.parse(powerNegativeReal);
    std::cout << powerNegativeReal << " = " << powerNegativeRealRoot->evaluate() << std::endl;

    return 0;
}
```

If you compile it as follows, you will get an executable named `Example`:

`g++ expression_tree.cpp math_module.cpp parser.cpp example.cpp -o Example`

Then run the `Example` file with the following command:

`./Example`

You should get an output like the following:
```bash
Toke: 2
NodeStack Size: 1
Toke: ^
Toke: -8
NodeStack Size: 1
NodeStack Size: 1
2^-8 = 0.00390625
```

## How is it working?

I will try to explain this by explaining the task of each file one by one.

### `expression_tree.h`

The `expression_tree.h` file provides a tree structure to represent mathematical expressions. This tree is composed of nodes that represent mathematical operations and functions and defines the basic structures necessary to store and evaluate mathematical expressions in a tree structure. The main structures defined in the file are: 

- `Node`: This is the base class for all nodes. All nodes are derived from this class.
- `UnaryOperationNode`: Used for operations that have a single child node (e.g., sin, cos).
- `ConstantNode`: Represents a constant value (e.g., 5, 3.14).
- `AdditionNode`, `SubtractionNode`, `MultiplicationNode`, `DivisionNode`: Nodes representing basic arithmetic operations between two child nodes.
- `PowerNode`: Represents exponentiation.
- `SinNode`, `CosNode`, `TanNode` etc.: Nodes representing trigonometric functions that have a single child node.
- `FactorialNode`: Represents the factorial function.

### `expression_tree.cpp`

The expression_tree.cpp file provides the implementation of the nodes defined in the corresponding header file. 

1.  **ConstantNode Implementation**:
    -   This node simply returns its value when evaluated.
2.  **AdditionNode Implementation**:
    -   Evaluates by summing the results of its left and right child nodes.
3.  **SubtractionNode Implementation**:
    -   Evaluates by subtracting the result of the right child node from the left child node.
4.  **MultiplicationNode Implementation**:
    -   Evaluates by multiplying the results of its left and right child nodes.
5.  **DivisionNode Implementation**:
    -   Evaluates by dividing the result of the left child node by the right child node.
    -   There's an error check for division by zero.
6.  **SinNode, CosNode, TanNode Implementations**:
    -   Evaluate by computing the sin, cos, and tan (respectively) of the result of their child node.
7.  **CotNode Implementation**:
    -   Evaluates by computing the cotangent of the result of its child node.
    -   There's an error check for a tan value of zero.
8.  **LnNode Implementation**:
    -   Evaluates by computing the natural logarithm of the result of its child node.
9.  **LogNode Implementation**:
    -   Evaluates by computing the base 10 logarithm of the result of its child node.
10.  **SqrtNode Implementation**:
		-   Evaluates by computing the square root of the result of its child node.
		-   There's an error check for negative values.

This file essentially dictates how each node behaves when it's asked to evaluate its mathematical expression.

### `parser.h`

The `parser.h` file defines the `Parser` class, which is responsible for translating mathematical expressions into the expression tree structure we saw earlier.

**Parser Class**:

1.  **Public Method**:
    
    -   `NodePtr parse(const std::string &expression)`:
        -   Takes a mathematical expression as a string.
        -   Returns the root of the expression tree representing the given expression.
        
2.  **Private Methods**:
    -   `std::vector<std::string> tokenize(const std::string &expression)`:
        -   Splits the expression into a list of tokens. This is likely the first step in parsing where mathematical symbols, numbers, and functions are separated.
    -   `NodePtr buildTree(const std::vector<std::string> &tokens)`:
        -   Constructs the expression tree from the list of tokens. It translates the linear list of tokens into a hierarchical tree structure.

From this, you can infer that the parsing process involves two main steps: **tokenization** and tree **construction**. The actual logic and rules of the parsing would be in the implementation (`parser.cpp`).

### `parser.cpp`

The `parser.cpp` file implements the methods of the `Parser` class, which is responsible for converting mathematical expressions into an expression tree.

1.  **`tokenize(const std::string &expression)`**:
        -   This method converts the input expression into a list of tokens.
    -   Tokens can be numbers, mathematical operators (+, -, *, /, ^, etc.), parentheses, or function names (sin, cos, etc.).
    -   The method handles unary minus (e.g., "-5" or "-x") by checking the context in which the minus sign appears.
    -   It also recognizes multi-character function names (e.g., "sinh", "cosh").

2.  **`buildTree(const std::vector<std::string> &tokens)`**:
        -   This method constructs the expression tree from the tokenized expression.
    -   It uses the Shunting Yard algorithm, a classic method to parse mathematical expressions specified in infix notation.
    -   During the process, it maintains two data structures: a stack for operators and a stack for nodes (operands).
    -   The method constructs nodes for numbers, binary operations, and functions, and pushes them onto the node stack.
    -   It handles different mathematical operations, including basic arithmetic, trigonometric functions, hyperbolic functions, and the factorial operation.
    -   At the end of the process, the node stack should contain a single node, which is the root of the expression tree.

3.  **`parse(const std::string &expression)`**:
        -   This is the main method that external callers would use.
    -   It first tokenizes the input expression and then constructs the expression tree using the tokenized input.
    -   The root of the resulting expression tree is returned.

It translates infix mathematical expressions into a tree structure that can then be evaluated using the nodes defined in `expression_tree.h`.

### `math_module.h`

It provides a declaration for a utility function:

**`inverse2x2Matrix` Function**:
-   **Input**: A 2x2 matrix represented as a `std::vector<std::vector<double>>`.
-   **Output**: The inverse of the given 2x2 matrix, also represented as a `std::vector<std::vector<double>>`.
-   **Purpose**: To compute the inverse of a 2x2 matrix.

This function suggests that there might be some linear algebra operations involved in the project, specifically related to 2x2 matrices.

### `math_module.cpp`

The `math_module.cpp` file provides the implementation for the `inverse2x2Matrix` function:

**`inverse2x2Matrix` Function Implementation**:
-   First, the determinant of the given 2x2 matrix is calculated.
-   If the determinant is zero, an exception is thrown, indicating that the matrix does not have an inverse.
-   If the determinant is non-zero, the inverse of the matrix is computed using the formula for the inverse of a 2x2 matrix.
-   The calculated inverse matrix is then returned.

The function is straightforward and is specialized for **2x2 matrices**. Given its specificity, it could be useful in a scenario where only **2x2 matrices** need to be inverted, such as certain linear algebra operations or transformations.

### `test_parser.cpp`

The `test_parser.cpp` file is a test file for the `Parser` class and the associated expression tree functionality. It demonstrates the parsing of various mathematical expressions and their subsequent evaluation. 

1.  **Initialization**:
    
    -   A `Parser` object is created.
    -   Multiple mathematical expressions are defined as strings, including basic arithmetic operations, functions (like sin, cos), and more complex expressions using parentheses.
2.  **Parsing and Evaluation**:
    
    -   For each expression, the `Parser` object's `parse` method is called to convert the expression string into an expression tree (represented by the root node).
    -   The resulting tree is then evaluated by calling the `evaluate` method on the root node.
3.  **Output**:
    
    -   The original expression and its evaluated result are printed to the console.

The test expressions cover a wide range of mathematical operations, including:

-   **Basic arithmetic**: addition, subtraction, multiplication, division.
-   **Use of parentheses** to alter the order of operations.
-   **Exponentiation**.
-   **Trigonometric functions**: sin, cos, tan, cot.
-   **Hyperbolic functions**: sinh, cosh, tanh, coth, sech, csch.
-   **Logarithmic functions**: natural log (ln) and base 10 log.
-   **Square root**.
-   **Factorial**.
-  	I hope more to come.

This test file serves as a comprehensive demonstration of the parser's capabilities and provides a clear example of how to use the `Parser` class and associated expression tree to evaluate mathematical expressions.