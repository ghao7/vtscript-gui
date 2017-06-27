#include <iostream>
#include "interpreter.hpp"

Interpreter::Interpreter(){
    
}

Interpreter::~Interpreter(){
    
}

bool Interpreter::parse(std::istream & expression) noexcept{
    if (expression.peek() == std::istream::traits_type::eof()){
        return false;
    }
    Tokenize tokenize(expression);
    tokenList = tokenize.getToken();
    return buildAST();
}

bool Interpreter::buildAST(){
    try {
        checkParenStructure(tokenList);
        checkParenInPair();
        checkParenExist();
        tokenList.pop_front();
        root = createNode(tokenList.front());
        
        tokenList.pop_front();
        root = buildAST(root);
        return true;
    } catch (const std::invalid_argument &e) {
        //std::cerr << "Error: Invalid Expression. Reason: " << e.what() << std::endl;
        return false;
    }
}

Expression Interpreter::buildAST(Expression sRoot){
    if (tokenList.size() == 0){
        return sRoot;
    }
    
    if (tokenList.front() == ")"){
        tokenList.pop_front();
        return sRoot;
    }
    
    if (tokenList.front() == "("){
        tokenList.pop_front();
        Expression newChild = createNode(tokenList.front());
        tokenList.pop_front();
    
        newChild = buildAST(newChild);
        sRoot.add(newChild);

    }else{
        Expression newChild = createNode(tokenList.front());
        tokenList.pop_front();
        sRoot.add(newChild);
        sRoot = buildAST(sRoot);
        
        return sRoot;
    }
    
    sRoot = buildAST(sRoot);

    return sRoot;
}


void Interpreter::traversalPostOrder(){
    root = traversalPostOrder(root);
}

Expression Interpreter::traversalPostOrder(Expression sRoot){
    for (int i = 0; i < sRoot.getChildren().size(); i++){
        sRoot.setChild(i, traversalPostOrder(sRoot.getExpression(i)));
    }
    if (sRoot.getChildren().size() == 0){
        return sRoot;
    }
    std::string str = sRoot.getData().stringValue;
    if (str == "define"){
        sRoot = en.procedureDefine(sRoot);
    }else if (str == "+"){
        sRoot = en.procedurePlus(sRoot);
    }else if (str == "if"){
        sRoot = en.procedureIf(sRoot);
    }else if (str == "begin"){
        sRoot = en.procedureBegin(sRoot);
    }else if (str == "<" || str == "<=" || str == ">" || str == ">=" || str == "="){
        sRoot = en.procedureRelational(sRoot);
    }else if (str == "-"){
        sRoot = en.procedureMinus(sRoot);
    }else if (str == "*"){
        sRoot = en.procedureMultiply(sRoot);
    }else if (str == "/"){
        sRoot = en.procedureDivision(sRoot);
    }else if (str == "not"){
        sRoot = en.procedureNot(sRoot);
    }else if (str == "and"){
        sRoot = en.procedureAnd(sRoot);
    }else if (str == "or"){
        sRoot = en.procedureOr(sRoot);
    }else if (str == "point"){
        sRoot = en.procedurePoint(sRoot);
    }else if (str == "line"){
        sRoot = en.procedureLine(sRoot);
    }else if (str == "arc"){
        sRoot = en.procedureArc(sRoot);
    }else if (str == "draw"){
        sRoot = en.procedureDraw(sRoot);
    }else if (str == "sin"){
        sRoot = en.procedureSin(sRoot);
    }else if (str == "cos"){
        sRoot = en.procedureCos(sRoot);
    }else if (str == "arctan"){
        sRoot = en.procedureArctan(sRoot);
    }else{
        throw InterpreterSemanticError("No such procedure.");
    }
    
    return sRoot;
}

AtomType Interpreter::findType(std::string exp){
    if (exp == "True" || exp == "False")
    return BoolType;
    try {
        std::stod(exp);
        return DoubleType;
    } catch (std::invalid_argument &e) {
        return StringType;
    }
    return NoneType;
}

Expression Interpreter::createNode(std::string exp){
    
    AtomType type = findType(exp);
    
    switch (type) {
        case BoolType:
        {
            bool boolean = (exp == "True");
            Expression newNode(boolean);
            return newNode;
            break;
        }
        
        case DoubleType:
        {
            double d = std::stod(exp);
            if (checkBadString(exp)){
                throw std::invalid_argument("bad string");
            }
            Expression newNode(d);
            return newNode;
            break;
        }
        
        case StringType:
        {
            Expression newNode(exp);
            return newNode;
            break;
        }
        default:
        break;
    }

    Expression newNode;
    return newNode;
}

bool Interpreter::checkBadString(std::string exp){
    double d;
    std::stringstream ss;
    ss << exp;
    ss >> d;
    return (ss.tellg() != -1);
}

Expression Interpreter::eval(){
    
    if (root.getChildren().size() == 0){
        return en.mapping(root);
    }
    
    traversalPostOrder();
    return root;
}


void Interpreter::checkParenInPair(){
    if (checkParenInPair(tokenList) == false){
        throw std::invalid_argument("Parenthesis are not in pair.");
    }
}

void Interpreter::checkEmpty(){
    if (tokenList.size() == 0){
        throw std::invalid_argument("empty input");
    }
}

void Interpreter::checkParenExist(){
    std::list<std::string> temp = tokenList;
    if (temp.front() != "("){
        throw std::invalid_argument("This is a single non-keyword.");
    }
    temp.pop_front();
    if (temp.front() == ")"){
        throw std::invalid_argument("There is no expression.");
    }
    
}

void Interpreter::checkParenStructure(std::list<std::string> plist){
    int temp = 0;
    //std::cout << "the size of the list is " << plist.size() << std::endl;
    for (int i = 0; i < plist.size(); i++){
        if (plist.front() == "("){
            temp++;
            plist.pop_front();
        }else if (plist.front() == ")"){
            temp--;
            plist.pop_front();
        }else{
            plist.pop_front();
        }
        if (temp == 0 && plist.size() > 0){
            throw std::invalid_argument("Error...");
            //std::cout << "wrong" << std::endl;
        }
        
        //std::cout << i<<"Temp is " << temp << std::endl;
    }
    
}

bool Interpreter::checkParenInPair(std::list<std::string> list){
    int pair = 0;
    for (std::list<std::string>::iterator i = list.begin(); i != list.end(); ++i){
        if (*i == "("){
            pair++;
        }
        if (*i == ")"){
            pair--;
        }
    }
    return (pair == 0);
}

Expression Interpreter::getRoot(){
    return root;
}

void Interpreter::setTokenList(std::list<std::string> tokenList){
    this->tokenList = tokenList;
}

void Interpreter::setRoot(Expression root){
    this->root = root;
}

std::list<std::string> Interpreter::getTokenList(){
    return tokenList;
}


Environment Interpreter::getEn(){
    return en;
}
