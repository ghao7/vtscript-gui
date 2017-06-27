#include <iostream>
#include <QApplication>
#include <vector>
#include "main_window.hpp"

int main(int argc, char*argv[]){
    QApplication app(argc,argv);
    std::vector<std::string> arguments;
    for (int i = 0; i < argc; i++){
        arguments.push_back(argv[i]);
    }
    if (arguments.size() == 1){
        MainWindow window;
        window.show();
        return app.exec();
    }
    if (arguments.size() == 2){
        MainWindow window(arguments[1]);
        window.show();
        return app.exec();
    }
    std::cout << "Number argument number\n";
    return app.exec();
    

}
