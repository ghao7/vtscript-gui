#ifndef REPL_WIDGET_HPP
#define REPL_WIDGET_HPP
#include <QWidget>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QLabel>
#include <deque>
#include <QDebug>
#include <QKeyEvent>
#include <QVector>



class REPLWidget: public QWidget{
    Q_OBJECT
public:
    // Default construct a REPLWidget
    REPLWidget(QWidget * parent = nullptr);
    
    //keypress event;
    void keyPressEvent(QKeyEvent *e);
    
signals:
    // A signal that sends the current edited text as a QString when the return key is pressed.
    void lineEntered(QString);
    
    public slots:
    //public slot receive when return is pressed
    void receive();
    
private:
    QLineEdit * replEdit;
    QVector<QString> replQueue;
    int cursor;
};


#endif
