#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include <QWidget>
#include <QtWidgets>
#include <QDir>

QT_BEGIN_NAMESPACE
class QComboBox;
class QLabel;
class QPushButton;
class QTableWidget;
class QTableWidgetItem;
QT_END_NAMESPACE

class SearchWindow : public QWidget
{
    Q_OBJECT

public:
    SearchWindow(QWidget *parent = nullptr);

private slots:
    void find();
    void animateFindClick() const;
    void openFileOfItem(int row, int column) const;

private:
    void findFiles(QDirIterator &iterator, const QString &text) const;
    void showFile(const QString &filePath) const;
    QComboBox *createComboBox(const QString &text = QString()) const;
    void createFilesTable();

    QComboBox *fileComboBox;
    QComboBox *textComboBox;
    QComboBox *directoryComboBox;
    QLabel *filesFoundLabel;
    QPushButton *findButton;
    QTableWidget *filesTable;

    QDir currentDir;
};

#endif
