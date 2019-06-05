#ifndef DICTIONARYAPP_H
#define DICTIONARYAPP_H

#include <QMainWindow>

#include "HashTable.h"

namespace Ui {
class DictionaryApp;
}

class DictionaryApp : public QMainWindow
{
    Q_OBJECT

public:
    explicit DictionaryApp(QWidget *parent = nullptr);
    ~DictionaryApp();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_ChinhSua_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_TraCuu_clicked();

    void on_pushButton_ThemTu_clicked();

    void on_pushButton_XoaTu_clicked();

private:
    Ui::DictionaryApp *ui;
    HashTable *hashTable;
};

#endif // DICTIONARYAPP_H
