#include "./include/propertieswindow.h"
#include <iostream>
#include <fstream>
PropertiesWindow::PropertiesWindow(QWidget *parent)
    : QTextEdit(parent)
{

}

void PropertiesWindow::changeTextSlot(const QString &message) {
    this->setText(message);
}
