#include "./include/mainwindow.h"
#include <QDesktopWidget>
#include <QScreen>
#include <QGuiApplication>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("./icons/icon.png"));
    MainWindow w;
    w.setWindowTitle("QExplorer");
    QList<QScreen *> rec = QGuiApplication::screens();
    w.resize(rec.first()->availableGeometry().width() / 2, rec.first()->availableGeometry().height() / 2);
    w.setStyleSheet("QMainWindow {background: 'black';}");
    w.show();
    return a.exec();
}
