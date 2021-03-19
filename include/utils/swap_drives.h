#ifndef SWAP_DISCS_H
#define SWAP_DISCS_H

#include <QStringList>
#include <QDir>
#include <QComboBox>

class SwapDrivesUtils {
public:
    static void configure_ui(QComboBox *ui);

private:
    static QStringList get_drives_name();
};

#endif
