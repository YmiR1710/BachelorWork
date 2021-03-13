#include "./include/mainwindow.h"

#if defined(_WIN32)
QString mPath = "C:\\";
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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model_1 = new QFileSystemModel(this);
    model_2 = new QFileSystemModel(this);
    model_1->setFilter(QDir::QDir::AllEntries);
    model_1->setRootPath(mPath);
    model_2->setFilter(QDir::QDir::AllEntries);
    model_2->setRootPath(mPath);
    ui->lineEdit_1->setText(mPath);
    ui->lineEdit_2->setText(mPath);
    ui->listView_1->setModel(model_1);
    ui->listView_2->setModel(model_2);

    QModelIndex idx = model_1->index(model_1->rootPath());
    QModelIndex idx_2 = model_2->index(model_2->rootPath());
    ui->listView_1->setRootIndex(idx);
    ui->listView_2->setRootIndex(idx_2);
    ui->search_1->setVisible(false);
    ui->search_2->setVisible(false);
    connect(ui->listView_1, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(on_listView_doubleClicked(QModelIndex)));
    connect(ui->listView_2, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(on_listView_doubleClicked(QModelIndex)));
    connect(ui->listView_1, SIGNAL(clicked(QModelIndex)), this, SLOT(click(QModelIndex)));
    connect(ui->listView_2, SIGNAL(clicked(QModelIndex)), this, SLOT(click(QModelIndex)));
    connect(ui->listView_2, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(customMenuRequested(QPoint)));
    connect(ui->listView_1, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(customMenuRequested(QPoint)));
    connect(ui->lineEdit_1, SIGNAL(returnPressed()), SLOT(lineEditEnter()));
    connect(ui->lineEdit_2, SIGNAL(returnPressed()), SLOT(lineEditEnter()));
    connect(ui->search_button_1, SIGNAL (released()),this, SLOT (show_hide_search_1()));
    connect(ui->search_button_2, SIGNAL (released()),this, SLOT (show_hide_search_2()));
    connect(ui->search_1, SIGNAL(returnPressed()), SLOT(searchEnter()));
    connect(ui->search_2, SIGNAL(returnPressed()), SLOT(searchEnter()));
    ui->listView_1->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->listView_2->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->listView_1->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->listView_2->setSelectionMode(QAbstractItemView::ExtendedSelection);
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_C), this, SLOT(copy_file()));
    new QShortcut(QKeySequence(Qt::Key_Escape), this, SLOT(close_search()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::click(const QModelIndex &index){
    chosenFile = index;
}

void MainWindow::on_listView_doubleClicked(const QModelIndex &index)
{
    this->setCursor(QCursor(Qt::WaitCursor));
    QListView* listView = (QListView*)sender();
    QFileInfo fileInfo = model_1->fileInfo(index);
    if (fileInfo.isFile()) {
        QDesktopServices::openUrl(QUrl(fileInfo.absoluteFilePath().prepend("file:///")));
        this->setCursor(QCursor(Qt::ArrowCursor));
        return;
    }
    if(listView == ui->listView_1){
        open_folder(model_1, ui->listView_1, ui->lineEdit_1, fileInfo, index);
    }else{
        open_folder(model_2, ui->listView_2, ui->lineEdit_2, fileInfo, index);
    }

    this->setCursor(QCursor(Qt::ArrowCursor));
}

void MainWindow::show_hide_search_1(){
    if(ui->search_1->isVisible()){
        ui->search_1->setVisible(false);
    } else{
        ui->search_1->setVisible(true);
    }
}

void MainWindow::show_hide_search_2(){
    if(ui->search_2->isVisible()){
        ui->search_2->setVisible(false);
    } else{
        ui->search_2->setVisible(true);
    }
}

void MainWindow::delete_file(){
    if(chosenFiles.size()>=2){
        QMessageBox::StandardButton reply;
        QString question = "Are you sure you want to delete " + QString::number(chosenFiles.size()) +
                " files?";
        reply = QMessageBox::question(this, "", question,
                                      QMessageBox::Yes|QMessageBox::No);
        for(auto &c_file: chosenFiles){
            if(model_1->fileInfo(c_file).isDir()){
                QDir dir(model_1->fileInfo(c_file).absoluteFilePath());
                if (reply == QMessageBox::Yes) {
                    this->setCursor(QCursor(Qt::WaitCursor));
                    QFileInfo f(dir.absolutePath());
                    QString own = f.owner();
                    if (f.permission(QFile::WriteUser) && own != "root"){
                        dir.removeRecursively();
                    }else{
                        QMessageBox messageBox;
                        messageBox.setText("No permission");
                        messageBox.setFixedSize(500,200);
                        messageBox.exec();
                    }

                    this->setCursor(QCursor(Qt::ArrowCursor));
                }
            }else{
                QFile file(model_1->fileInfo(c_file).absoluteFilePath());
                if (reply == QMessageBox::Yes) {
                    this->setCursor(QCursor(Qt::WaitCursor));
                    QFileInfo f(file);
                    QString own = f.owner();
                    if (f.permission(QFile::WriteUser) && own != "root"){
                        file.remove();
                    }else{
                        QMessageBox messageBox;
                        messageBox.setText("No permission");
                        messageBox.setFixedSize(500,200);
                        messageBox.exec();
                    }
                    this->setCursor(QCursor(Qt::ArrowCursor));
                }
            }
        }
    }
    else{
        QMessageBox::StandardButton reply;
        QString question = "Are you sure you want to delete ";
        question.append(model_1->fileInfo(chosenFile).baseName());
        if(!(model_1->fileInfo(chosenFile).completeSuffix() == "")){
            question.append(".");
        }
        question.append(model_1->fileInfo(chosenFile).completeSuffix());
        question.append("?");
        reply = QMessageBox::question(this, "", question,
                                      QMessageBox::Yes|QMessageBox::No);
        if(model_1->fileInfo(chosenFile).isDir()){
            QDir dir(model_1->fileInfo(chosenFile).absoluteFilePath());
            if (reply == QMessageBox::Yes) {
                this->setCursor(QCursor(Qt::WaitCursor));
                QFileInfo f(dir.absolutePath());
                QString own = f.owner();
                if (f.permission(QFile::WriteUser) && own != "root"){
                    dir.removeRecursively();
                }else{
                    QMessageBox messageBox;
                    messageBox.setText("No permission");
                    messageBox.setFixedSize(500,200);
                    messageBox.exec();
                }
                this->setCursor(QCursor(Qt::ArrowCursor));
            }
        }else{
            QFile file(model_1->fileInfo(chosenFile).absoluteFilePath());
            if (reply == QMessageBox::Yes) {
                this->setCursor(QCursor(Qt::WaitCursor));
                QFileInfo f(file);
                QString own = f.owner();
                if (f.permission(QFile::WriteUser) && own != "root"){
                    file.remove();
                }else{
                    QMessageBox messageBox;
                    messageBox.setText("No permission");
                    messageBox.setFixedSize(500,200);
                    messageBox.exec();
                }
                this->setCursor(QCursor(Qt::ArrowCursor));
            }
        }
    }
    chosenFiles.clear();
}

void MainWindow::rename_file(){
    int counter = 1;
    bool result;
    QFileInfo info = model_1->fileInfo(chosenFile);
    QString name = info.baseName();
    if(!(info.completeSuffix() == "")){
        name.append(".");
    }
    name.append(info.completeSuffix());
    QString text;
    if (info.permission(QFile::WriteUser)){
        text = QInputDialog::getText(this, tr(""),
                                             tr("New name:"), QLineEdit::Normal,
                                             name, &result);
    } else
    {
        QMessageBox msg;
        msg.setText("No permission");
        msg.setFixedSize(500,200);
        msg.exec();
    }

    if(result){
        if(info.isDir()){
            QDir dir(info.absoluteFilePath());
            QString new_path = info.absolutePath();
            new_path.append("/");
            new_path.append(text);
            while(!dir.rename(info.absoluteFilePath(), new_path)){
                new_path = info.absolutePath();
                new_path.append("/");
                QStringList text_list = text.split('.');
                text_list[0].append("(");
                text_list[0].append(QString::number(counter));
                text_list[0].append(")");
                new_path.append(text_list.join("."));
                counter++;
            }
        }else{
            QFile file(info.absoluteFilePath());
            QString new_path = info.absolutePath();
            new_path.append("/");
            new_path.append(text);
            while(!file.rename(new_path)){
                new_path = info.absolutePath();
                new_path.append("/");
                QStringList text_list = text.split('.');
                text_list[0].append("(");
                text_list[0].append(QString::number(counter));
                text_list[0].append(")");
                new_path.append(text_list.join("."));
                counter++;
            }
        }
    }
}

void MainWindow::get_properties(){
        this->setCursor(QCursor(Qt::WaitCursor));
        QFileInfo info = model_1->fileInfo(chosenFile);
        QMessageBox properties_window(this);
        properties_window.setWindowTitle("Properties");
        properties_window.setStandardButtons(QMessageBox::Close);
        QString properties_text;
        QStringList properties_list = {"Name: ", "Type: ", "Size: ", "Parent folder: ",
                                       "Group: ", "Owner: ", "Created: ", "Last modified: "};
        properties_text.append(properties_list[0]);
        QString name = info.baseName();
        if(!(info.completeSuffix() == "")){
            name.append(".");
        }
        name.append(info.completeSuffix());
        properties_text.append(name);
        properties_text.append("\n");
        QString type;
        properties_text.append(properties_list[1]);
        if(info.isDir()){
            type = "directory";
        }else if(info.isExecutable()){
            type = "executable";
        }else if(info.isSymLink()){
            type = "symbolic link";
        }else if(info.isBundle()){
            type = "bundle";
        }else{
            type = "file";
        }
        properties_text.append(type);
        properties_text.append("\n");
        properties_text.append(properties_list[2]);
        qint64 size;
        if(info.isDir()){
            size = dirSize(info.absoluteFilePath());
        }else{
            size = info.size()/1000;
        }
        properties_text.append(QString::number(size));
        properties_text.append(" kB");
        properties_text.append("\n");
        properties_text.append(properties_list[3]);
        properties_text.append(info.absolutePath());
        properties_text.append("\n");
        properties_text.append(properties_list[4]);
        properties_text.append(info.group());
        properties_text.append("\n");
        properties_text.append(properties_list[5]);
        properties_text.append(info.owner());
        properties_text.append("\n");
        properties_text.append(properties_list[6]);
        properties_text.append(info.lastModified().toString(Qt::SystemLocaleLongDate));
        properties_text.append("\n");
        properties_text.append(properties_list[7]);
        properties_text.append(info.created().toString(Qt::SystemLocaleLongDate));
        properties_window.setText(properties_text);
        this->setCursor(QCursor(Qt::ArrowCursor));
        properties_window.exec();
    }

void MainWindow::copy_file(){
    copiedFiles = chosenFiles;
}

void MainWindow::cut_file(){
    copiedFiles = chosenFiles;
    to_cut = true;
}

void MainWindow::paste_file(){
    this->setCursor(QCursor(Qt::WaitCursor));
    for (auto& c_file: copiedFiles){
        QFileInfo copy_info = model_1->fileInfo(c_file);
        QFileInfo chosen_info = model_1->fileInfo(chosenFile);
        if(copy_info.isDir()){
            QDir dir_to_copy(copy_info.absoluteFilePath());
            if(dir_to_copy.exists()){
                QString new_path = chosen_info.absolutePath();
                QString src_path = copy_info.absoluteFilePath();
                new_path.append("/");
                new_path.append(copy_info.baseName());
                if(!copy_info.completeSuffix().isEmpty()){
                    new_path.append(".");
                }
                new_path.append(copy_info.completeSuffix());
                copyPath(src_path, new_path);
            }
        }else{
            QFile file_to_copy(copy_info.absoluteFilePath());
            if(file_to_copy.exists()){
                QString new_path = chosen_info.absolutePath();
                new_path.append("/");
                new_path.append(copy_info.baseName());
                if(copy_info.completeSuffix().size() != 0){
                    new_path.append(".");
                    new_path.append(copy_info.completeSuffix());
                }
                int counter = 1;
                while(!file_to_copy.copy(new_path)){
                    new_path = chosen_info.absolutePath();
                    new_path.append("/");
                    QString text = copy_info.baseName();
                    if(copy_info.completeSuffix().size() != 0){
                        text.append(".");
                        text.append(copy_info.completeSuffix());
                    }
                    QStringList text_list = text.split('.');
                    text_list[0].append("(");
                    text_list[0].append(QString::number(counter));
                    text_list[0].append(")");
                    new_path.append(text_list.join("."));
                    counter++;
                }
            }
        }
        if(to_cut){
            if(model_1->fileInfo(c_file).isDir()){
                QDir dir(model_1->fileInfo(c_file).absoluteFilePath());
                this->setCursor(QCursor(Qt::WaitCursor));
                dir.removeRecursively();
                this->setCursor(QCursor(Qt::ArrowCursor));
            }else{
                QFile file(model_1->fileInfo(c_file).absoluteFilePath());
                this->setCursor(QCursor(Qt::WaitCursor));
                file.remove();
                this->setCursor(QCursor(Qt::ArrowCursor));
            }
        }
    }
    to_cut = false;
    this->setCursor(QCursor(Qt::ArrowCursor));
}

void MainWindow::create_file(){
    int counter = 1;
    bool result;
    QString text = QInputDialog::getText(this, tr(""),
                                         tr("New file:"), QLineEdit::Normal,
                                         "", &result);
    if(result){
        QString path = model_1->fileInfo(chosenFile).absolutePath();
        path.append("/");
        path.append(text);
        QFile newFile(path);
        if(newFile.exists()){
            while(true){
                path = model_1->fileInfo(chosenFile).absolutePath();
                path.append("/");
                QStringList text_list = text.split('.');
                text_list[0].append("(");
                text_list[0].append(QString::number(counter));
                text_list[0].append(")");
                path.append(text_list.join("."));
                QFile newFile(path);
                if(!newFile.exists()){
                    newFile.open(QFile::WriteOnly);
                    break;
                }
                counter++;
            }
        }
        else{
            newFile.open(QFile::WriteOnly);
        }
        newFile.close();
    }
}

void MainWindow::create_folder(){
    int counter = 1;
    bool result;
    QString text = QInputDialog::getText(this, tr(""),
                                         tr("New folder:"), QLineEdit::Normal,
                                         "", &result);
    if(result){
        QString path = model_1->fileInfo(chosenFile).absolutePath();
        path.append("/");
        path.append(text);
        QDir newFolder(path);
        if(newFolder.exists()){
            while(true){
                path = model_1->fileInfo(chosenFile).absolutePath();
                path.append("/");
                QStringList text_list = text.split('.');
                text_list[0].append("(");
                text_list[0].append(QString::number(counter));
                text_list[0].append(")");
                path.append(text_list.join("."));
                QDir newFolder(path);
                if(!newFolder.exists()){
                    newFolder.mkpath(".");
                    break;
                }
                counter++;
            }
        }
        else{
            newFolder.mkpath(".");
        }
    }
}

void MainWindow::customMenuRequested(const QPoint &pos){
    QListView* listView = (QListView*)sender();
    QModelIndex index=listView->indexAt(pos);
    QModelIndexList list = listView->selectionModel()->selectedIndexes();
    chosenFiles.clear();
    foreach(const QModelIndex &indexx, list){
        chosenFiles.append(indexx);
    }
    if(!(model_1->fileInfo(index).completeBaseName() == "." || model_1->fileInfo(index).completeBaseName() == "")){
        if(chosenFiles.size() >= 2){
            chosenFile = index;
            QMenu *menu=new QMenu(this);
            menu->setObjectName("menu");
            QMenu *create_menu = menu->addMenu("Create");
            QAction *create_folder_action = new QAction("Folder", this);
            QAction *create_file_action = new QAction("File", this);
            create_menu->addAction(create_folder_action);
            create_menu->addAction(create_file_action);
            QAction *copy_action = new QAction("Copy", this);
            menu->addAction(copy_action);
            QAction *cut_action = new QAction("Cut", this);
            menu->addAction(cut_action);
            QAction *paste_action = new QAction("Paste", this);
            menu->addAction(paste_action);
            paste_action->setObjectName("paste_action");
            QAction *compress_action = new QAction("Archive", this);
            menu->addAction(compress_action);
            QAction *delete_action = new QAction("Delete", this);
            menu->addAction(delete_action);
            connect(create_file_action, SIGNAL(triggered()), this, SLOT(create_file()));
            connect(create_folder_action, SIGNAL(triggered()), this, SLOT(create_folder()));
            connect(copy_action, SIGNAL(triggered()), this, SLOT(copy_file()));
            connect(cut_action, SIGNAL(triggered()), this, SLOT(cut_file()));
            connect(paste_action, SIGNAL(triggered()), this, SLOT(paste_file()));
            connect(compress_action, SIGNAL(triggered()), this, SLOT(compress_files()));
            connect(delete_action, SIGNAL(triggered()), this, SLOT(delete_file()));
            menu->popup(listView->viewport()->mapToGlobal(pos));
        }
        else{
            chosenFile = index;
            QFileInfo fileInfo = model_1->fileInfo(index);
            QMenu *menu=new QMenu(this);
            menu->setObjectName("menu");
            if(fileInfo.isFile()){
                QAction *open_action = new QAction("Open", this);
                menu->addAction(open_action);
                connect(open_action, SIGNAL(triggered()), this, SLOT(open_file()));
            }
            QMenu *create_menu = menu->addMenu("Create");
            QAction *create_folder_action = new QAction("Folder", this);
            QAction *create_file_action = new QAction("File", this);
            create_menu->addAction(create_folder_action);
            create_menu->addAction(create_file_action);
            QAction *copy_action = new QAction("Copy", this);
            menu->addAction(copy_action);
            QAction *cut_action = new QAction("Cut", this);
            menu->addAction(cut_action);
            QAction *paste_action = new QAction("Paste", this);
            menu->addAction(paste_action);
            paste_action->setObjectName("paste_action");
            QAction *compress_action = new QAction("Archive", this);
            menu->addAction(compress_action);
            QAction *delete_action = new QAction("Delete", this);
            menu->addAction(delete_action);
            QAction *rename_action = new QAction("Rename", this);
            menu->addAction(rename_action);
            QAction *properties_action = new QAction("Properties", this);
            menu->addAction(properties_action);
            connect(create_file_action, SIGNAL(triggered()), this, SLOT(create_file()));
            connect(create_folder_action, SIGNAL(triggered()), this, SLOT(create_folder()));
            connect(copy_action, SIGNAL(triggered()), this, SLOT(copy_file()));
            connect(cut_action, SIGNAL(triggered()), this, SLOT(cut_file()));
            connect(paste_action, SIGNAL(triggered()), this, SLOT(paste_file()));
            connect(delete_action, SIGNAL(triggered()), this, SLOT(delete_file()));
            connect(rename_action, SIGNAL(triggered()), this, SLOT(rename_file()));
            connect(properties_action, SIGNAL(triggered()), this, SLOT(get_properties()));
            menu->popup(listView->viewport()->mapToGlobal(pos));
        }
    }
}

void MainWindow::lineEditEnter(){
    QLineEdit* line = (QLineEdit*)sender();
    QString path = line->text();
    QDir dir(path);
    QModelIndex idx;
    if(line == ui->search_1){
        idx = model_1->index(path);
    }
    else{
        idx = model_2->index(path);
    }
    if(dir.exists()){
        if(line == ui->lineEdit_1){
            ui->listView_1->setRootIndex(idx);
        }
        else{
            ui->listView_2->setRootIndex(idx);
        }
    }
}

void MainWindow::searchEnter(){
    QLineEdit* line = (QLineEdit*)sender();
    QString item_name = line->text();
    QStringList filters;
    QString request = "*";
    request.append(item_name);
    request.append("*");
    filters << request;
    filters << ".";
    filters << "..";
    if(line == ui->search_1){
        model_1->setNameFilters(filters);
        model_1->setNameFilterDisables(false);
        ui->listView_1->setRootIndex(model_1->index(ui->lineEdit_1->text()));
    } else if(line == ui->search_2){
        model_2->setNameFilters(filters);
        model_2->setNameFilterDisables(false);
        ui->listView_2->setRootIndex(model_2->index(ui->lineEdit_2->text()));
    }
}

void MainWindow::close_search(){
    ui->search_1->setVisible(false);
    ui->search_2->setVisible(false);
    QStringList filters;
    model_1->setNameFilters(filters);
    model_2->setNameFilters(filters);
}


void MainWindow::open_file(){
    this->setCursor(QCursor(Qt::WaitCursor));
    QFileInfo fileInfo = model_1->fileInfo(chosenFile);
    QDesktopServices::openUrl(QUrl(fileInfo.absoluteFilePath().prepend("file:///")));
    this->setCursor(QCursor(Qt::ArrowCursor));
}


