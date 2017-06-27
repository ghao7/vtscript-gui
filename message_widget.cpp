#include "message_widget.hpp"

MessageWidget::MessageWidget(QWidget * parent): QWidget(parent){
    messageEdit = new QLineEdit;
    messageEdit->setReadOnly(true);
    auto label = new QLabel("Message:");
    auto layout = new QHBoxLayout();
    layout->addWidget(label);
    layout->addWidget(messageEdit);
    setLayout(layout);
}

void MessageWidget::info(QString message){
    messageEdit->clear();
    QPalette * color = new QPalette();
    messageEdit->setPalette(* color);
    messageEdit->setText(message);
}

void MessageWidget::error(QString message){
    messageEdit->clear();
    QPalette * color = new QPalette(Qt::red);
    messageEdit->setText(message);
    messageEdit->selectAll();
    color ->setColor(QPalette::Highlight,Qt::red);
    color ->setColor(QPalette::HighlightedText,Qt::white);
    messageEdit->setPalette(* color);
}
