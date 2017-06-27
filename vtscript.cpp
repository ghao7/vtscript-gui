#include <iostream>
#include "interpreter.hpp"

bool execute(std::string fname, std::istream &ifs){
    Interpreter interp;
    
    bool ok = interp.parse(ifs);
    if(!ok){
        std::cerr << "Error: Failed to parse file: " << fname << std::endl;
        return false;
    }
    Expression result;
    try {
        result = interp.eval();
        std::cout << "(" ;
        result.showData();
        std::cout << ")" << std::endl;
    } catch (const InterpreterSemanticError &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }
    return true;
}

int main(int argc, char*argv[]){
    std::vector<std::string> arguments;
    for (int i = 0; i < argc; i++){
        arguments.push_back(argv[i]);
    }
    if (arguments.size() == 2){
        std::string fname = arguments[1];
        std::ifstream ifs(fname);
        if (!execute(fname, ifs)){
            return EXIT_FAILURE;
        }
    }else if (arguments.size() == 3){
        if (arguments[1] != "-e"){
            std::cerr << "Error: Invalid arguments" << std::endl;
            return EXIT_FAILURE;
        }
        std::string program = arguments[2];
        std::istringstream iss(program);
        if (!execute(program, iss)){
            return EXIT_FAILURE;
        }
    }else if (arguments.size() == 1){
        Interpreter i;
        while (true){
            std::string input;
            std::cout << "vtscript> ";
            std::getline(std::cin, input);
            if (!input.empty()){
                std::istringstream iss(input);
                bool ok = i.parse(iss);
                if(!ok){
                    std::cerr << "Error: Failed to parse: " << input << std::endl;
                    Interpreter newInterp;
                    i = newInterp;
                }else{
                    Expression result;
                    try {
                        result = i.eval();
                        std::cout << "(" ;
                        result.showData();
                        std::cout << ")" << std::endl;
                    } catch (const InterpreterSemanticError &e) {
                        std::cerr << "Error: " << e.what() << std::endl;
                        Interpreter newInterp;
                        i = newInterp;
                    }
                }
            }
        }
    }
    return EXIT_SUCCESS;
}
