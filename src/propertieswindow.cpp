#include "./include/propertieswindow.h"

PropertiesWindow::PropertiesWindow(QWidget *parent)
    : QTextEdit(parent)
{

}

void PropertiesWindow::changeTextSlot(const QString &message)
{
    this->setText(message);
}
