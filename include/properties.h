#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <QString>
#include <QStringList>

class Properties {
private:
    QString name;
    QString type;
    QString size;
    QString parent_folder;
    QString group;
    QString owner;
    QString created;
    QString last_modified;

public:
    void setName(QString name);

    QString getName();

    void setType(QString type);

    QString getType();

    void setSize(QString size);

    QString getSize();

    void setParentFolder(QString parent_folder);

    QString getParentFolder();

    void setGroup(QString group);

    QString getGroup();

    void setOwner(QString owner);

    QString getOwner();

    void setCreated(QString created);

    QString getCreated();

    void setLastModified(QString last_modified);

    QString getLastModified();

    QString toString();
};

#endif
