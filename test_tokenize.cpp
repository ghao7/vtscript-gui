#include "catch.hpp"

#include <string>
#include <fstream>
#include <iostream>

#include "tokenize.hpp"
#include "test_config.hpp"

TEST_CASE("Test tokenize constructor", "[Tokenize]"){
    {
        std::string program = "(begin (define r 10) (* pi (* r r)))";
        std::istringstream iss(program);
        Tokenize t(iss);
        std::string token = t.getRet();
        REQUIRE(token == program);
        std::list<std::string> vec = t.getToken();
        REQUIRE(vec.size() == 17);
    }
    {
        std::string fname = TEST_FILE_DIR + "/test4.vts";
        std::ifstream ifs(fname);
        REQUIRE(ifs.good() == true);
    }
    {
        std::string program = "( + ( + 1 2 ) 3 )";
        std::istringstream iss(program);
        Tokenize t(iss);
        std::string token = t.getRet();
        REQUIRE(token == program);
        std::list<std::string> vec = t.getToken();
        REQUIRE(vec.size() == 9);
    }
    {
        std::string program = "(+ 9 11)";
        std::istringstream iss(program);
        Tokenize t(iss);
        std::string token = t.getRet();
        REQUIRE(token == program);
        std::list<std::string> vec = t.getToken();
        REQUIRE(vec.size() == 5);
    }
    {
        std::string program = "( +( + 1 2)3)";
        std::istringstream iss(program);
        Tokenize t(iss);
        std::string token = t.getRet();
        REQUIRE(token == program);
        std::list<std::string> vec = t.getToken();
        REQUIRE(vec.size() == 9);
    }
    {
        std::string program = ";this is a comment\n(begin (define answer (+ 9 11)) (answer))";
        std::istringstream iss(program);
        Tokenize t(iss);
        std::list<std::string> vec = t.getToken();
        REQUIRE(vec.size() == 15);
    }
}

TEST_CASE("Test tokenize eraseComments function", "[Tokenize]"){

    {
        Tokenize t;
        std::string str = ";this is a comment\n(begin (define answer (+ 9 11)) (answer))";
        std::string temp = t.eraseComments(str);
        REQUIRE(temp == "(begin (define answer (+ 9 11)) (answer))");
    }
    
    {
        Tokenize t;
        std::string str = ";this is a comment\n(begin (define answer (+ 9 11)) (answer)) ;hahahah\n";
        std::string temp = t.eraseComments(str);
        REQUIRE(temp == "(begin (define answer (+ 9 11)) (answer)) ");
    }
    
    {
        Tokenize t;
        std::string str = ";this is a comment\n(begin (define answer (+ 9 11)) (answer)) ;hahahah\n ()()();define this\n";
        std::string temp = t.eraseComments(str);
        REQUIRE(temp == "(begin (define answer (+ 9 11)) (answer))  ()()()");
    }
    
}
