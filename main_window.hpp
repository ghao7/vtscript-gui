#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QWidget>
#include "repl_widget.hpp"
#include "message_widget.hpp"
#include "canvas_widget.hpp"
#include "qt_interpreter.hpp"
#include <QVBoxLayout>

class MainWindow:public QWidget{
    Q_OBJECT
public:
    // Default construct a MainWindow
    MainWindow(QWidget * parent = nullptr);
    
    // Default construct a MainWidow, using filename as the script file to attempt to preload
    MainWindow(std::string filename, QWidget * parent = nullptr);
    
private:
    REPLWidget * repl;
    MessageWidget * message;
    CanvasWidget * canvas;
    QtInterpreter * interp;
};

#endif
