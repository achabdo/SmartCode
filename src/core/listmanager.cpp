#include "listmanager.h"

ListManager::ListManager(QObject *parent) :
    QObject(parent)
{
}
void ListManager::addItem()
{
    listWidget->insertItem(listWidget->count(),edit->text());
    list<<edit->text();
}
void ListManager::deleteItem()
{
    listWidget->takeItem(list->currentRow());
}
void ListManager::editItem()
{
    QListWidgetItem *item= list->item(list->currentRow());
    item->setText(edit->text());

}
void ListManager::clear()
{
    listWidget->clear();
    list.clear();
}
void ListManager::addFile()
{

}

