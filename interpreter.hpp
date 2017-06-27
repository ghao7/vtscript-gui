#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <stdexcept>
#include "expression.hpp"
#include "tokenize.hpp"
#include "environment.hpp"
#include "interpreter_semantic_error.hpp"



class Interpreter{
public:
    // Default construct an Interpreter with the default environment and an empty AST
    Interpreter();
    
    //default destructor
    ~Interpreter();
    
    // Given a vtscript program as a std::istream, attempt to parse into an internal AST
    // return true on succes s, false on failure
    bool parse(std::istream & expression) noexcept;
    
    //put token list into ast
    bool buildAST();
    
    //the buildast helper function to to recursion
    Expression buildAST(Expression sRoot);
    
    //find the type of expression
    AtomType findType(std::string exp);
    
    //allocate new memory for expression
    Expression createNode(std::string exp);
    
    // Evaluate the current AST and return the resulting Expression
    // throws InterpreterSemanticError if a semantic error is encountered
    // the exception message string should document the nature of the semantic error
    Expression eval();
    
    //getter
    Expression getRoot();
    std::list<std::string> getTokenList();
    Environment getEn();
    
    //setter
    void setRoot(Expression root);
    void setTokenList(std::list<std::string> tokenList);
    
    //check if the parenthesis is in pair
    void checkParenInPair();
    bool checkParenInPair(std::list<std::string> list);
    void checkParenExist();
    void checkEmpty();
    void checkParenStructure(std::list<std::string> list);
    //return true if it is bad string
    bool checkBadString(std::string exp);
    
    //cout traversal tree in post order
    void traversalPostOrder();
    
    //traversal post order helper function
    Expression traversalPostOrder(Expression sRoot);
    
    private:
    Expression root;
    
    std::list<std::string> tokenList;
    
    Environment en;
};

#endif
