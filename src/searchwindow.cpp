#include "./include/searchwindow.h"

enum { absoluteFileNameRole = Qt::UserRole + 1 };

static inline QString fileNameOfItem(const QTableWidgetItem *item)
{
    return item->data(absoluteFileNameRole).toString();
}

static inline void openFile(const QString &fileName)
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(fileName));
}

SearchWindow::SearchWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(tr("Find Files"));
    findButton = new QPushButton(tr("&Find"), this);
    connect(findButton, &QAbstractButton::clicked, this, &SearchWindow::find);

    fileComboBox = createComboBox(tr("*"));
    connect(fileComboBox->lineEdit(), &QLineEdit::returnPressed,
            this, &SearchWindow::animateFindClick);
    textComboBox = createComboBox();
    connect(textComboBox->lineEdit(), &QLineEdit::returnPressed,
            this, &SearchWindow::animateFindClick);
    directoryComboBox = createComboBox();
    connect(directoryComboBox->lineEdit(), &QLineEdit::returnPressed,
            this, &SearchWindow::animateFindClick);

    filesFoundLabel = new QLabel;

    createFilesTable();

    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(new QLabel(tr("Named:")), 0, 0);
    mainLayout->addWidget(fileComboBox, 0, 1, 1, 2);
    mainLayout->addWidget(new QLabel(tr("Containing text:")), 1, 0);
    mainLayout->addWidget(textComboBox, 1, 1, 1, 2);
    mainLayout->addWidget(new QLabel(tr("In directory:")), 2, 0);
    mainLayout->addWidget(directoryComboBox, 2, 1, 1, 2);
    mainLayout->addWidget(filesTable, 3, 0, 1, 3);
    mainLayout->addWidget(filesFoundLabel, 4, 0, 1, 2);
    mainLayout->addWidget(findButton, 4, 2);
    connect(new QShortcut(QKeySequence::Quit, this), &QShortcut::activated,
            qApp, &QApplication::quit);
}

static void updateComboBox(QComboBox *comboBox)
{
    if (comboBox->findText(comboBox->currentText()) == -1)
        comboBox->addItem(comboBox->currentText());
}

void SearchWindow::find()
{
    filesTable->setRowCount(0);
    findButton->disconnect();
    std::thread worker([this]() {
        QString fileName = fileComboBox->currentText();
        QString text = textComboBox->currentText();
        QString path = QDir::cleanPath(directoryComboBox->currentText());
        currentDir = QDir(path);

        updateComboBox(fileComboBox);
        updateComboBox(textComboBox);
        updateComboBox(directoryComboBox);

        QStringList filter;
        if (!fileName.isEmpty())
            filter << fileName;
        QDirIterator it(path, filter, QDir::AllEntries | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
        findFiles(it, text);
    });
    worker.detach();
}

void SearchWindow::animateFindClick() const
{
    findButton->animateClick();
}

void SearchWindow::findFiles(QDirIterator &iterator, const QString &text) const
{
    QStringList files;
    while (iterator.hasNext()) {
        QString path = iterator.next();
        if (!QFileInfo(path).isDir()) {
            if (text.isEmpty()) {
                showFile(path);
            } else {
                files << path;
            }
        }
    }
    if (!text.isEmpty()) {
        QMimeDatabase mimeDatabase;
        QStringList foundFiles;

        for (int i = 0; i < files.size(); ++i) {
            QCoreApplication::processEvents();
            const QString fileName = files.at(i);
            const QMimeType mimeType = mimeDatabase.mimeTypeForFile(fileName);
            if (mimeType.isValid() && !mimeType.inherits(QStringLiteral("text/plain"))) {
                continue;
            }
            QFile file(fileName);
            if (file.open(QIODevice::ReadOnly)) {
                QString line;
                QTextStream in(&file);
                while (!in.atEnd()) {
                    line = in.readLine();
                    if (line.contains(text, Qt::CaseInsensitive)) {
                        foundFiles << files[i];
                        showFile(fileName);
                        break;
                    }
                }
            }
        }
    }
    connect(findButton, &QAbstractButton::clicked, this, &SearchWindow::find);
}

void SearchWindow::showFile(const QString &filePath) const
{
    const QString toolTip = QDir::toNativeSeparators(filePath);
    const QString relativePath = QDir::toNativeSeparators(currentDir.relativeFilePath(filePath));
    const qint64 size = QFileInfo(filePath).size();
    QTableWidgetItem *fileNameItem = new QTableWidgetItem(relativePath);
    fileNameItem->setData(absoluteFileNameRole, QVariant(filePath));
    fileNameItem->setToolTip(toolTip);
    fileNameItem->setFlags(fileNameItem->flags() ^ Qt::ItemIsEditable);
    QTableWidgetItem *sizeItem = new QTableWidgetItem(QLocale().formattedDataSize(size));
    sizeItem->setData(absoluteFileNameRole, QVariant(filePath));
    sizeItem->setToolTip(toolTip);
    sizeItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    sizeItem->setFlags(sizeItem->flags() ^ Qt::ItemIsEditable);

    int row = filesTable->rowCount();
    filesTable->insertRow(row);
    filesTable->setItem(row, 0, fileNameItem);
    filesTable->setItem(row, 1, sizeItem);
    filesFoundLabel->setText(tr("%n file(s) found (Double click on a file to open it)", nullptr, filesTable->rowCount()));
    filesFoundLabel->setWordWrap(true);
}

QComboBox *SearchWindow::createComboBox(const QString &text) const
{
    QComboBox *comboBox = new QComboBox;
    comboBox->setEditable(true);
    comboBox->addItem(text);
    comboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    return comboBox;
}

void SearchWindow::createFilesTable()
{
    filesTable = new QTableWidget(0, 2);
    filesTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    QStringList labels;
    labels << tr("Filename") << tr("Size");
    filesTable->setHorizontalHeaderLabels(labels);
    filesTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    filesTable->verticalHeader()->hide();
    filesTable->setFocusPolicy(Qt::NoFocus);
    filesTable->setShowGrid(false);

    connect(filesTable, &QTableWidget::cellActivated,
            this, &SearchWindow::openFileOfItem);
}

void SearchWindow::openFileOfItem(int row, int /* column */) const
{
    const QTableWidgetItem *item = filesTable->item(row, 0);
    openFile(fileNameOfItem(item));
}
