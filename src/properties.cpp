#include "./include/properties.h"

void Properties::setName(QString name)
{
    this->name = name;
}

QString Properties::getName()
{
    return name;
}

void Properties::setType(QString type)
{
    this->type = type;
}

QString Properties::getType()
{
    return type;
}

void Properties::setSize(QString size)
{
    this->size = size;
}

QString Properties::getSize()
{
    return size;
}

void Properties::setParentFolder(QString parent_folder)
{
    this->parent_folder = parent_folder;
}

QString Properties::getParentFolder()
{
    return parent_folder;
}

void Properties::setGroup(QString group)
{
    this->group = group;
}

QString Properties::getGroup()
{
    return group;
}

void Properties::setOwner(QString owner)
{
    this->owner = owner;
}

QString Properties::getOwner()
{
    return owner;
}

void Properties::setCreated(QString created)
{
    this->created = created;
}

QString Properties::getCreated()
{
    return created;
}

void Properties::setLastModified(QString last_modified)
{
    this->last_modified = last_modified;
}

QString Properties::getLastModified()
{
    return last_modified;
}

QString Properties::toString()
{
    QString properties_text;
    QStringList properties_list = {"Name: ", "Type: ", "Size: ", "Parent folder: ",
                                   "Group: ", "Owner: ", "Created: ", "Last modified: "
                                  };
    QStringList values_list = {name, type, size, parent_folder,
                               group, owner, created, last_modified
                              };
    for (int i = 0; i < properties_list.size(); i++) {
        properties_text.append(properties_list[i]);
        properties_text.append(values_list[i]);
        properties_text.append("\n\n");
    }
    return properties_text;
}
