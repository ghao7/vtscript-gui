#include <iostream>
#include <sstream>
#include <ctype.h>
#include <stdio.h>
#include "tokenize.hpp"

Tokenize::Tokenize(){
    
}

Tokenize::~Tokenize(){
    
}

Tokenize::Tokenize(std::istream & expression){
    
    char buffer[4096];
    while (expression.read(buffer, sizeof(buffer)))
    ret.append(buffer, sizeof(buffer));
    ret.append(buffer, expression.gcount());
    
    
    token = parseRet();

}

std::string Tokenize::getRet(){
    return ret;
}

std::list<std::string> Tokenize::getToken(){
    return token;
}

std::list<std::string> Tokenize::parseRet(){
    
    ret = eraseComments(ret);
    std::list<std::string> temp;
    std::istringstream iss(ret);
    
    do
    {
        std::string sub;
        iss >> sub;
        std::string leftStr;
        std::string rightStr;
        
        if (sub.length() == 1){
            temp.push_back(sub);
        }else{
            for (int i = 0; i < sub.length(); i++){
                char c = sub.at(i);
                if (c == '('){
                    if (leftStr.length() != 0){
                        temp.push_back(leftStr);
                    }
                    temp.push_back("(");
                    leftStr.clear();
                }else if (c == ')'){
                    if (leftStr.length() != 0){
                        temp.push_back(leftStr);
                    }
                    temp.push_back(")");
                    leftStr.clear();
                }else{
                    std::string t(1,c);
                    leftStr.append(t);
                }
            }
            if (leftStr.length() != 0){
                temp.push_back(leftStr);
            }
        }
        
    } while (iss);
    return temp;
}

std::string Tokenize::eraseComments(std::string str){
    std::string c = ";";
    std::string n = "\n";
    
    size_t cPos = str.find(c);
    while(cPos != -1){
        size_t nPos = str.find(n);
        while(nPos < cPos){
            nPos = str.find(n, nPos + 1);
        }
        
        str.erase(cPos, nPos - cPos + 1);
        cPos = str.find(c);
    }
    
    return str;

}


