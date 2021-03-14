#ifndef PROPERTIESWINDOW_H
#define PROPERTIESWINDOW_H

#include <QTextEdit>

class PropertiesWindow : public QTextEdit
{
    Q_OBJECT

public:
    explicit PropertiesWindow(QWidget *parent = 0);

public slots:
    void changeTextSlot(const QString &message);

signals:
    void changeTextSignal(const QString &message);
};

#endif
