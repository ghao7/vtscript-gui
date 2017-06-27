#include "main_window.hpp"

MainWindow::MainWindow(QWidget * parent):QWidget(parent){
    repl = new REPLWidget(this);
    message = new MessageWidget(this);
    canvas = new CanvasWidget(this);
    interp = new QtInterpreter(this);
    resize(750, 600);
    QVBoxLayout *layout = new QVBoxLayout;
    layout -> addWidget(message);
    layout -> addWidget(canvas);
    layout -> addWidget(repl);

    setLayout(layout);
    
    QObject::connect(repl,SIGNAL(lineEntered(QString)) , interp, SLOT(parseAndEvaluate(QString)));
    QObject::connect(interp, SIGNAL(info(QString)), message, SLOT(info(QString)));
    QObject::connect(interp, SIGNAL(error(QString)), message, SLOT(error(QString)));
    QObject::connect(interp, SIGNAL(drawGraphic(QGraphicsItem *)), canvas, SLOT(addGraphic(QGraphicsItem*)));
}

MainWindow::MainWindow(std::string filename, QWidget * parent):QWidget(parent){
    std::ifstream ifs(filename);
    
    repl = new REPLWidget(this);
    message = new MessageWidget(this);
    canvas = new CanvasWidget(this);
    interp = new QtInterpreter(this);
    resize(750, 600);
    QVBoxLayout *layout = new QVBoxLayout;
    layout -> addWidget(message);
    layout -> addWidget(canvas);
    layout -> addWidget(repl);
    
    setLayout(layout);
    
    
    QObject::connect(interp, SIGNAL(drawGraphic(QGraphicsItem *)), canvas, SLOT(addGraphic(QGraphicsItem*)));
    QObject::connect(repl,SIGNAL(lineEntered(QString)) , interp, SLOT(parseAndEvaluate(QString)));
    QObject::connect(interp, SIGNAL(info(QString)), message, SLOT(info(QString)));
    QObject::connect(interp, SIGNAL(error(QString)), message, SLOT(error(QString)));
    
    interp->parseIss(ifs);
    
    
}
