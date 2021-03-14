#include "./include/properties.h"

void Properties::setName(QString name){
    this->name = name;
}

QString Properties::getName(){
    return name;
}

void Properties::setType(QString type){
    this->type = type;
}

QString Properties::getType(){
    return type;
}

void Properties::setSize(QString size){
    this->size = size;
}

QString Properties::getSize(){
    return size;
}

void Properties::setParentFolder(QString parent_folder){
    this->parent_folder = parent_folder;
}

QString Properties::getParentFolder(){
    return parent_folder;
}

void Properties::setGroup(QString group){
    this->group = group;
}

QString Properties::getGroup(){
    return group;
}

void Properties::setOwner(QString owner){
    this->owner = owner;
}

QString Properties::getOwner(){
    return owner;
}

void Properties::setCreated(QString created){
    this->created = created;
}

QString Properties::getCreated(){
    return created;
}

void Properties::setLastModified(QString last_modified){
    this->last_modified = last_modified;
}

QString Properties::getLastModified(){
    return last_modified;
}

QString Properties::toString(){
    QString properties_text;
    QStringList properties_list = {"Name: ", "Type: ", "Size: ", "Parent folder: ",
                                   "Group: ", "Owner: ", "Created: ", "Last modified: "};
    properties_text.append(properties_list[0]);
    properties_text.append(name);
    properties_text.append("\n");
    properties_text.append(properties_list[1]);
    properties_text.append(type);
    properties_text.append("\n");
    properties_text.append(properties_list[2]);
    properties_text.append(size);
    properties_text.append("\n");
    properties_text.append(properties_list[3]);
    properties_text.append(parent_folder);
    properties_text.append("\n");
    properties_text.append(properties_list[4]);
    properties_text.append(group);
    properties_text.append("\n");
    properties_text.append(properties_list[5]);
    properties_text.append(owner);
    properties_text.append("\n");
    properties_text.append(properties_list[6]);
    properties_text.append(last_modified);
    properties_text.append("\n");
    properties_text.append(properties_list[7]);
    properties_text.append(created);
    return properties_text;
}
