#include "./include/utils/swap_drives.h"

void SwapDrivesUtils::configure_ui(QComboBox *ui)
{
    ui->setVisible(false);
#if defined(_WIN32)
    ui->setVisible(true);
    ui->setFocusPolicy(Qt::NoFocus);
    for (auto drive : get_drives_name()) {
        ui->addItem(drive);
    }
#endif
}

QStringList SwapDrivesUtils::get_drives_name()
{
    QStringList list;
    for (auto info : QDir::drives()) {
        list.append(info.absoluteFilePath());
    }
    return list;
}
