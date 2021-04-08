#include "./include/mainwindow.h"

#if defined(_WIN32)
QString mPath = "C:/";
#endif
#if defined(unix) || defined(__unix__) || defined(__unix)
QString mPath = "/";
#endif
#if defined(__APPLE__)
QString mPath = "/";
#endif

QModelIndex chosenFile;
QModelIndex copiedFile;
QList<QModelIndex> chosenFiles;
QList<QModelIndex> copiedFiles;
bool to_cut = false;
QFileSystemModel *model_1;
QFileSystemModel *model_2;
qint64 directorySize;
Panel active_panel;
Theme currentTheme;
QStringList existingFavoritePaths;
Panel favorites_active_panel;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    existingFavoritePaths = QStringList();
    model_1 = new QFileSystemModel(this);
    model_2 = new QFileSystemModel(this);
    model_1->setFilter(QDir::QDir::AllEntries | QDir::QDir::NoDot);
    model_1->setRootPath(mPath);
    model_2->setFilter(QDir::QDir::AllEntries | QDir::QDir::NoDot);
    model_2->setRootPath(mPath);
    ui->lineEdit_1->setText(mPath);
    ui->lineEdit_2->setText(mPath);
    ui->listView_1->setModel(model_1);
    ui->listView_2->setModel(model_2);
    QModelIndex idx = model_1->index(model_1->rootPath());
    QModelIndex idx_2 = model_2->index(model_2->rootPath());
    ui->listView_1->setRootIndex(idx);
    ui->listView_2->setRootIndex(idx_2);
    ui->listView_1->verticalHeader()->setVisible(false);
    ui->listView_2->verticalHeader()->setVisible(false);
    ui->listView_1->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->listView_2->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->listView_1->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->listView_2->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->listView_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->listView_1->horizontalHeader()->setStretchLastSection(true);
    ui->listView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->listView_2->horizontalHeader()->setStretchLastSection(true);
    ui->listView_1->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->listView_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->listView_1->setSortingEnabled(true);
    ui->listView_2->setSortingEnabled(true);
    ui->listView_1->horizontalHeader()->setSortIndicator(0, Qt::AscendingOrder);
    ui->listView_2->horizontalHeader()->setSortIndicator(0, Qt::AscendingOrder);
    ui->listView_1->horizontalHeader()->setSortIndicator(0, Qt::AscendingOrder);
    ui->listView_1->setShowGrid(false);
    ui->listView_2->setShowGrid(false);
    ui->listView_1->setFocusPolicy(Qt::NoFocus);
    ui->listView_2->setFocusPolicy(Qt::NoFocus);
    ui->search_1->setVisible(false);
    ui->search_2->setVisible(false);
    SwapDrivesUtils::configure_ui(ui->comboBox_1);
    SwapDrivesUtils::configure_ui(ui->comboBox_2);
    configure();
    emit ui->statistics->update_charts(QFileInfo(mPath));
    connect(ui->comboBox_1, SIGNAL(textActivated(QString)), this, SLOT(change_root_path(QString)));
    connect(ui->comboBox_2, SIGNAL(textActivated(QString)), this, SLOT(change_root_path(QString)));
    connect(ui->listView_1, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(on_listView_doubleClicked(QModelIndex)));
    connect(ui->listView_2, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(on_listView_doubleClicked(QModelIndex)));
    connect(ui->listView_1, SIGNAL(clicked(QModelIndex)), this, SLOT(click(QModelIndex)));
    connect(ui->listView_2, SIGNAL(clicked(QModelIndex)), this, SLOT(click(QModelIndex)));
    connect(ui->listView_2, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(custom_menu_requested(QPoint)));
    connect(ui->listView_1, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(custom_menu_requested(QPoint)));
    connect(ui->lineEdit_1, SIGNAL(returnPressed()), SLOT(line_edit_enter()));
    connect(ui->lineEdit_2, SIGNAL(returnPressed()), SLOT(line_edit_enter()));
    connect(ui->search_button_1, SIGNAL (released()), this, SLOT (show_hide_search_1()));
    connect(ui->search_button_2, SIGNAL (released()), this, SLOT (show_hide_search_2()));
    connect(ui->search_1, SIGNAL(returnPressed()), SLOT(searchEnter()));
    connect(ui->search_2, SIGNAL(returnPressed()), SLOT(searchEnter()));
    connect(ui->actionDark, SIGNAL(triggered()), this, SLOT(change_theme()));
    connect(ui->actionLight, SIGNAL(triggered()), this, SLOT(change_theme()));
    connect(ui->favoritePathsButton_1, SIGNAL(clicked()), this, SLOT(show_favorite_paths()));
    connect(ui->favoritePathsButton_2, SIGNAL(clicked()), this, SLOT(show_favorite_paths()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_C), this, SLOT(copy_file()));
    new QShortcut(QKeySequence(Qt::Key_Escape), this, SLOT(close_search()));
//    new QShortcut(QKeySequence(Qt::Key_Delete), this, SLOT(delete_file())); TODO
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::click(const QModelIndex &index) {
    chosenFile = index.siblingAtColumn(0);
}

void MainWindow::on_listView_doubleClicked(const QModelIndex &index)
{
    this->setCursor(QCursor(Qt::WaitCursor));
    QTableView *listView = (QTableView *)sender();
    QFileInfo fileInfo = model_1->fileInfo(index);
    if (fileInfo.isFile()) {
        QDesktopServices::openUrl(QUrl(fileInfo.absoluteFilePath().prepend("file:///")));
        this->setCursor(QCursor(Qt::ArrowCursor));
        return;
    }
    else if (fileInfo.isSymLink()) {
        if (listView == ui->listView_1) {
            QModelIndex index = model_1->index(fileInfo.symLinkTarget());
            emit ui->statistics->update_charts(model_1->fileInfo(index));
            NavigationUtils::open_folder(model_1, ui->listView_1, ui->lineEdit_1, model_1->fileInfo(index));
        } else {
            emit ui->statistics->update_charts(model_2->fileInfo(index));
            QModelIndex index = model_2->index(fileInfo.symLinkTarget());
            NavigationUtils::open_folder(model_2, ui->listView_2, ui->lineEdit_2, model_2->fileInfo(index));
        }
        this->setCursor(QCursor(Qt::ArrowCursor));
        return;
    }
    if (listView == ui->listView_1) {
        NavigationUtils::open_folder(model_1, ui->listView_1, ui->lineEdit_1, fileInfo);
    } else {
        NavigationUtils::open_folder(model_2, ui->listView_2, ui->lineEdit_2, fileInfo);
    }
    emit ui->statistics->update_charts(fileInfo);
    this->setCursor(QCursor(Qt::ArrowCursor));
}

void MainWindow::show_hide_search_1() {
    if (ui->search_1->isVisible()) {
        ui->search_1->setVisible(false);
    } else {
        ui->search_1->setVisible(true);
    }
}

void MainWindow::show_hide_search_2() {
    if (ui->search_2->isVisible()) {
        ui->search_2->setVisible(false);
    } else {
        ui->search_2->setVisible(true);
    }
}

void MainWindow::delete_file() {
    QMessageBox::StandardButton reply;
    QString question = "Are you sure you want to delete " + QString::number(chosenFiles.size()) +
                       " files?";
    reply = QMessageBox::question(this, "Delete", question,
                                  QMessageBox::Yes | QMessageBox::No);
    this->setCursor(QCursor(Qt::WaitCursor));
    for (auto &c_file : chosenFiles) {
        QString absolutePath = model_1->fileInfo(c_file).absoluteFilePath();
        DeletionUtils::delete_unit(absolutePath, reply, model_1->fileInfo(c_file));
    }
    this->setCursor(QCursor(Qt::ArrowCursor));
    chosenFiles.clear();
}

void MainWindow::rename_file() {
    bool result;
    QFileInfo info = model_1->fileInfo(chosenFile);
    QString name = info.baseName();
    if (!(info.completeSuffix() == "")) {
        name.append(".");
    }
    name.append(info.completeSuffix());
    QString text;
    if (info.permission(QFile::WriteUser)) {
        text = QInputDialog::getText(this, tr("Rename"),
                                     tr("New name:"), QLineEdit::Normal,
                                     name, &result);
    } else {
        QMessageBox msg;
        msg.setText("No permission");
        msg.setFixedSize(500, 200);
        msg.exec();
    }

    if (result) {
        if (info.isDir()) {
            RenameUtils::rename_unit(info, text, true);
        } else {
            RenameUtils::rename_unit(info, text, false);
        }
    }
}

void MainWindow::get_properties() {
    this->setCursor(QCursor(Qt::WaitCursor));
    QFileInfo info(ui->lineEdit_1->text());
    if (chosenFile.isValid()) {
        info = model_1->fileInfo(chosenFile);
    }
    else {
        if (active_panel == Panel::PANEL_1) {
            info = QFileInfo(ui->lineEdit_1->text());
        }
        else if (active_panel == Panel::PANEL_2) {
            info = QFileInfo(ui->lineEdit_2->text());
        }
    }
    QDialog *widget = new QDialog(this);
    QVBoxLayout *layout = new QVBoxLayout(widget);
    PropertiesWindow *properties_window = new PropertiesWindow(widget);
    properties_window->setReadOnly(true);
    QFont sansFont("Times", 10);
    properties_window->setCurrentFont(sansFont);
    widget->setWindowTitle("Properties");
    QPushButton *button = new QPushButton(widget);
    button->setText("Close");
    connect(button, SIGNAL(clicked()), widget, SLOT(close()));
    Properties *properties = new Properties();
    QString name = info.baseName();
    if (!(info.completeSuffix() == "")) {
        name.append(".");
    }
    name.append(info.completeSuffix());
    properties->setName(name);
    QString type;
    if (info.isDir()) {
        type = "directory";
    } else if (info.isExecutable()) {
        type = "executable";
    } else if (info.isSymLink()) {
        type = "symbolic link";
    } else if (info.isBundle()) {
        type = "bundle";
    } else {
        type = "file";
    }
    properties->setType(type);
    qint64 size;
    if (info.isDir()) {
        directorySize = 0;
        connect(properties_window, SIGNAL(changeTextSignal(QString)), properties_window, SLOT(changeTextSlot(QString)));
        std::thread worker(DirectorySizeCalculationUtils::dirSizeWrap, info.absoluteFilePath(), properties, properties_window);
        worker.detach();
        size = directorySize;
    } else {
        size = info.size();
    }
    properties->setSize(DirectorySizeCalculationUtils::formatSize(size));
    properties->setParentFolder(info.absolutePath());
    properties->setGroup(info.group());
    properties->setOwner(info.owner());
    properties->setLastModified(info.lastModified().toString(Qt::SystemLocaleLongDate));
    properties->setCreated(info.created().toString(Qt::SystemLocaleLongDate));
    properties_window->setText(properties->toString());
    properties_window->setFixedHeight(this->height() / 2);
    properties_window->setFixedWidth(this->width() / 4);
    this->setCursor(QCursor(Qt::ArrowCursor));
    layout->addWidget(properties_window, 0, 0);
    layout->addWidget(button);
    widget->setLayout(layout);
    widget->exec();
}

void MainWindow::copy_file() {
    if (chosenFiles.empty()) {
        copiedFiles.append(chosenFile);
    }
    else {
        copiedFiles = chosenFiles;
    }
}

void MainWindow::cut_file() {
    if (chosenFiles.empty()) {
        copiedFiles.append(chosenFile);
    }
    else {
        copiedFiles = chosenFiles;
    }
    to_cut = true;
}

void MainWindow::paste_file() {
    this->setCursor(QCursor(Qt::WaitCursor));
    for (auto &c_file : copiedFiles) {
        QFileInfo copy_info = model_1->fileInfo(c_file);
        QString path;
        if (active_panel == Panel::PANEL_1) {
            path = ui->lineEdit_1->text();
        }
        else if (active_panel == Panel::PANEL_2) {
            path = ui->lineEdit_2->text();
        }
        if (copy_info.isDir() && !copy_info.isSymLink()) {
            CopyPasteUtils::paste_unit(copy_info, path, true);
        } else {
            CopyPasteUtils::paste_unit(copy_info, path, false);
        }
        if (to_cut) {
            if (model_1->fileInfo(c_file).isDir() && !model_1->fileInfo(c_file).isSymLink()) {
                QDir dir(model_1->fileInfo(c_file).absoluteFilePath());
                dir.removeRecursively();
            } else {
                QFile file(model_1->fileInfo(c_file).absoluteFilePath());
                file.remove();
            }
        }
    }
    to_cut = false;
    copiedFiles.clear();
    this->setCursor(QCursor(Qt::ArrowCursor));
}

void MainWindow::create_file() {
    bool result;
    QString text = QInputDialog::getText(this, tr("Create"),
                                         tr("New file:"), QLineEdit::Normal,
                                         "", &result);
    if (result) {
        if (active_panel == Panel::PANEL_1) {
            CreationUtils::create_unit(text, ui->lineEdit_1->text(), false);
        }
        else if (active_panel == Panel::PANEL_2) {
            CreationUtils::create_unit(text, ui->lineEdit_2->text(), false);
        }
    }
}

void MainWindow::create_folder() {
    bool result;
    QString text = QInputDialog::getText(this, tr("Create"),
                                         tr("New folder:"), QLineEdit::Normal,
                                         "", &result);
    if (result) {
        if (active_panel == Panel::PANEL_1) {
            CreationUtils::create_unit(text, ui->lineEdit_1->text(), true);
        }
        else if (active_panel == Panel::PANEL_2) {
            CreationUtils::create_unit(text, ui->lineEdit_2->text(), true);
        }
    }
}

void MainWindow::custom_menu_requested(const QPoint &pos) {
    QTableView *listView = (QTableView *)sender();
    QModelIndex index = listView->indexAt(pos);
    if (listView == ui->listView_1) {
        active_panel = Panel::PANEL_1;
    }
    else if ( listView == ui->listView_2) {
        active_panel = Panel::PANEL_2;
    }
    QModelIndexList list = listView->selectionModel()->selectedIndexes();
    chosenFiles.clear();
    foreach (const QModelIndex &indexx, list) {
        if (indexx.column() == 0)
            chosenFiles.append(indexx);
    }
    if (!(model_1->fileInfo(index).completeBaseName() == ".")) {
        chosenFile = index;
        QMenu *menu = new QMenu(this);
        menu->setObjectName("menu");
        QFileInfo fileInfo = model_1->fileInfo(index);
        if (chosenFiles.size() < 2 && fileInfo.isFile() && index.isValid()) {
            QAction *open_action = new QAction("Open", this);
            menu->addAction(open_action);
            connect(open_action, SIGNAL(triggered()), this, SLOT(open_file()));
        }
        QMenu *create_menu = menu->addMenu("Create");
        QAction *create_folder_action = new QAction("Folder", this);
        QAction *create_file_action = new QAction("File", this);
        create_menu->addAction(create_folder_action);
        create_menu->addAction(create_file_action);
        if (index.isValid()) {
            QAction *copy_action = new QAction("Copy", this);
            menu->addAction(copy_action);
            QAction *cut_action = new QAction("Cut", this);
            menu->addAction(cut_action);
            connect(copy_action, SIGNAL(triggered()), this, SLOT(copy_file()));
            connect(cut_action, SIGNAL(triggered()), this, SLOT(cut_file()));
        }
        QAction *paste_action = new QAction("Paste", this);
        menu->addAction(paste_action);
        paste_action->setObjectName("paste_action");
        if (index.isValid()) {
            QAction *delete_action = new QAction("Delete", this);
            menu->addAction(delete_action);
            if (chosenFiles.size() < 2) {
                QAction *rename_action = new QAction("Rename", this);
                menu->addAction(rename_action);
                connect(rename_action, SIGNAL(triggered()), this, SLOT(rename_file()));
            }
            QAction *shortcut_action = new QAction("Create shortcut", this);
            menu->addAction(shortcut_action);
            connect(shortcut_action, SIGNAL(triggered()), this, SLOT(create_shortcut()));
            connect(delete_action, SIGNAL(triggered()), this, SLOT(delete_file()));
        }
        if (chosenFiles.size() < 2) {
            QAction *properties_action = new QAction("Properties", this);
            menu->addAction(properties_action);
            connect(properties_action, SIGNAL(triggered()), this, SLOT(get_properties()));
        }
        connect(create_file_action, SIGNAL(triggered()), this, SLOT(create_file()));
        connect(create_folder_action, SIGNAL(triggered()), this, SLOT(create_folder()));
        connect(paste_action, SIGNAL(triggered()), this, SLOT(paste_file()));
        menu->popup(listView->viewport()->mapToGlobal(pos));
    }
}

void MainWindow::line_edit_enter() {
    QLineEdit *line = (QLineEdit *)sender();
    QString path = line->text();
    QDir dir(path);
    QModelIndex idx;
    if (line == ui->search_1) {
        idx = model_1->index(path);
    }
    else {
        idx = model_2->index(path);
    }
    if (dir.exists()) {
        if (line == ui->lineEdit_1) {
            ui->listView_1->setRootIndex(idx);
        }
        else {
            ui->listView_2->setRootIndex(idx);
        }
    }
}

void MainWindow::change_root_path(QString path) {
    QComboBox *box = (QComboBox *)sender();
    emit ui->statistics->update_charts(QFileInfo(path));
    if (box == ui->comboBox_1) {
        ui->listView_1->setRootIndex(model_1->index(path));
        ui->lineEdit_1->setText(path);
    }
    else if (box == ui->comboBox_2) {
        ui->listView_2->setRootIndex(model_2->index(path));
        ui->lineEdit_2->setText(path);
    }
}

void MainWindow::searchEnter() {
    QLineEdit *line = (QLineEdit *)sender();
    QString item_name = line->text();
    if (line == ui->search_1) {
        FiltersUtils::search_filter(item_name, ui->listView_1, ui->lineEdit_1, model_1);
    } else if (line == ui->search_2) {
        FiltersUtils::search_filter(item_name, ui->listView_2, ui->lineEdit_2, model_2);
    }
}

void MainWindow::close_search() {
    ui->search_1->setVisible(false);
    ui->search_2->setVisible(false);
    QStringList filters;
    model_1->setNameFilters(filters);
    model_2->setNameFilters(filters);
}

void MainWindow::show_favorite_paths() {
    FavoritesMainWindow *window = new FavoritesMainWindow(this);
    QPushButton *button = (QPushButton *)sender();
    FavoritePathsContainer *container;
    if (button == ui->favoritePathsButton_1) {
        favorites_active_panel = Panel::PANEL_1;
        container = new FavoritePathsContainer(window, ui->lineEdit_1->text());
    }
    else {
        favorites_active_panel = Panel::PANEL_2;
        container = new FavoritePathsContainer(window, ui->lineEdit_2->text());
    }
    window->setCentralWidget(container);
    window->setFixedHeight(this->height() / 2);
    window->setFixedWidth(this->width() / 4);
    window->setWindowTitle("Favorites");
    window->show();
}

void MainWindow::open_file() {
    this->setCursor(QCursor(Qt::WaitCursor));
    QFileInfo fileInfo = model_1->fileInfo(chosenFile);
    QDesktopServices::openUrl(QUrl(fileInfo.absoluteFilePath().prepend("file:///")));
    this->setCursor(QCursor(Qt::ArrowCursor));
}

void MainWindow::open_cloud_drive(QString path) {
    emit ui->statistics->update_charts(QFileInfo(path));
    if (active_panel == Panel::PANEL_1) {
        NavigationUtils::open_folder(model_1, ui->listView_1, ui->lineEdit_1, QFileInfo(path));
    }
    else if (active_panel == Panel::PANEL_2) {
        NavigationUtils::open_folder(model_2, ui->listView_2, ui->lineEdit_2, QFileInfo(path));
    }
}

void MainWindow::create_shortcut() {
    this->setCursor(QCursor(Qt::WaitCursor));
    for (auto &c_file : chosenFiles) {
        QString absolutePath = model_1->fileInfo(c_file).absoluteFilePath();
        QFile::link(absolutePath, absolutePath + " - Shortcut.lnk");
    }
    this->setCursor(QCursor(Qt::ArrowCursor));
    chosenFiles.clear();
}

void MainWindow::open_favorite_path(QString path) {
    emit ui->statistics->update_charts(QFileInfo(path));
    if (favorites_active_panel == Panel::PANEL_1) {
        NavigationUtils::open_folder(model_1, ui->listView_1, ui->lineEdit_1, QFileInfo(path));
    }
    else if (favorites_active_panel == Panel::PANEL_2) {
        NavigationUtils::open_folder(model_2, ui->listView_2, ui->lineEdit_2, QFileInfo(path));
    }
}

void MainWindow::change_theme() {
    QAction *action = (QAction *)sender();
    if (action == ui->actionDark) {
        ConfigParser::change_config(QString("theme"), QString("DARK"));
        currentTheme = Theme::DARK;
        ui->statistics->updateChartsTheme(Theme::DARK);
        QFile fileDark(":/ui/styles/dark.qss");
        fileDark.open(QFile::ReadOnly);
        setStyleSheet(fileDark.readAll());
    }
    else if (action == ui->actionLight) {
        ConfigParser::change_config(QString("theme"), QString("LIGHT"));
        currentTheme = Theme::LIGHT;
        ui->statistics->updateChartsTheme(Theme::LIGHT);
        QFile fileLight(":/ui/styles/light.qss");
        fileLight.open(QFile::ReadOnly);
        setStyleSheet(fileLight.readAll());
    }
}

void MainWindow::configure() {
    setWindowTitle("QExplorer");
    QList<QScreen *> rec = QGuiApplication::screens();
    resize(rec.first()->availableGeometry().width() / 1.5, rec.first()->availableGeometry().height() / 1.5);
    ConfigParser::configure();
    if (currentTheme == Theme::DARK) {
        QFile fileDark(":/ui/styles/dark.qss");
        fileDark.open(QFile::ReadOnly);
        setStyleSheet(fileDark.readAll());
    }
    else if (currentTheme == Theme::LIGHT) {
        QFile fileLight(":/ui/styles/light.qss");
        fileLight.open(QFile::ReadOnly);
        setStyleSheet(fileLight.readAll());
    }
}
