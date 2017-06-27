#include "repl_widget.hpp"

REPLWidget::REPLWidget(QWidget * parent):QWidget(parent){
    cursor = -1;
    replEdit = new QLineEdit;
    auto label = new QLabel("vtscript>");
    QHBoxLayout * layout = new QHBoxLayout(this);
    layout->addWidget(label);
    layout->addWidget(replEdit);
    
    QObject::connect(replEdit, SIGNAL(returnPressed()),this,SLOT(receive()));
    
}

void REPLWidget::receive(){
    qDebug() <<replEdit->text();
    replQueue.append(replEdit->text());
    cursor = replQueue.size();
    emit lineEntered(replEdit->text());
    replEdit->clear();

}

void REPLWidget::keyPressEvent(QKeyEvent *e){
    if(e->key() == Qt::Key_Up){
        if (cursor > 0){
            cursor--;
            QString str = replQueue[cursor];
            replEdit->setText(str);
            //qDebug() << replQueue[cursor];
            //qDebug() << "up" << cursor;
        }
    }
    if (e->key() == Qt::Key_Down){
        if (cursor >= 0 && cursor < replQueue.size()-1){
            cursor++;
            QString str = replQueue[cursor];
            replEdit->setText(str);
            //qDebug() << replQueue[cursor];
            //qDebug() << "down" << cursor;
        }
    }
    
}

