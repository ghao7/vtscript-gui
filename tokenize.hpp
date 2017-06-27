#ifndef TOKENIZE_HPP
#define TOKENIZE_HPP

#include <iostream>
#include <string>
#include <list>
#include <sstream>
#include <vector>

class Tokenize{
    public:
    
    //default constructor
    Tokenize();
    
    //default destructor
    ~Tokenize();
    
    //constructor with input
    Tokenize(std::istream & expression);
    
    //get private ret;
    std::string getRet();
    
    //get private token vector
    std::list<std::string> getToken();
    
    //seperate characters
    std::list<std::string> parseRet();
    
    //erase comments
    std::string eraseComments(std::string str);
    
    private:
    std::list<std::string> token;
    std::string ret;
};

#endif
