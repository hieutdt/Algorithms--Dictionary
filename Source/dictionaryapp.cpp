#include "dictionaryapp.h"
#include "ui_dictionaryapp.h"
#include "Tokenizer.h"
#include "Word.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <QMessageBox>
#include <QTextStream>
#include <QFile>

using namespace std;

#define WORD_NUMS 36222

DictionaryApp::DictionaryApp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DictionaryApp)
{
    ui->setupUi(this);

    Word *read = new Word[WORD_NUMS];
    QFile dataFile("DictionaryFile.txt");
    if (!dataFile.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Error", "Can't find the dictionary file!");
        ui->~DictionaryApp();
    }

    int i = 0;

    QTextStream in(&dataFile);

    while (!in.atEnd()) {
        string rword;
        string rmean;
        string line;
        QString qline = in.readLine();

        line = qline.toUtf8().constData();

        vector<string> tokens = Tokenizer::Parse(line, "  ");
        rword = tokens[0];
        for (int i = 1; i < tokens.size(); i++)
            rmean += tokens[i];

        if (rmean != "") {
            if (rword == "Usage")
                continue;
            if (rword[0] < 'A' || rword[0] > 'Z')
                continue;
            if (i >= 1) {
                if (rword == read[i - 1].getWord())
                    read[i - 1].setMean(read[i - 1].getMean() + "\n" + rmean);
               else {
                    read[i].setWord(rword);
                    read[i].setMean(rmean);
                    i++;
                }
            }
            else {
               read[i].setWord(rword);
               read[i].setMean(rmean);
               i++;
            }
        }
    }

    this->hashTable = new HashTable(i);

    for (int j = 0; j < i; j++)
        hashTable->insert(read[j]);

    ui->pushButton_2->setVisible(false);

    delete[] read;
    dataFile.close();
}

DictionaryApp::~DictionaryApp()
{
    this->hashTable->clear();
    delete ui;
}

string searchWord(string &searchKey, HashTable &hashTable) {
    const string error = "Can't find!";
    string result = "";
    transform(searchKey.begin(), searchKey.end(), searchKey.begin(), ::tolower);
    searchKey[0] = toupper(searchKey[0]);

    Word *word = hashTable.search(searchKey);
    if (word == nullptr) {
        bool flag = false;
        for (int i = 0; i < 3; i++) {
            stringstream ss;
            ss << i + 1;
            string newWord = searchKey + ss.str();
            word = hashTable.search(newWord);
            if (word != nullptr) {
                flag = true;
                result += word->getMean() + "\n";
            }
        }
        if (flag == false) {
            return error;
        }
    }
    else {
        result += word->getMean() + "\n";
        for (int i = 0; i < 3; i++) {
            stringstream ss;
            ss << i + 1;
            string newWord = searchKey + ss.str();
            word = hashTable.search(newWord);
            if (word != nullptr) {
                result += word->getMean() + "\n";
            }
        }
    }
    delete word;
    return result;
}

void DictionaryApp::on_pushButton_clicked()
{
    QTextDocument *key = ui->searchTextEdit->document();
    QString qsearch = key->toPlainText();

    string searchKey = qsearch.toUtf8().constData();

    string mean = searchWord(searchKey, *hashTable);

    QString qmean = QString::fromStdString(mean);

    ui->textEdit_mean->setText(qmean);

    if (ui->pushButton_ChinhSua->isChecked() == true) {
        if (mean == "Can't find!") {
            QMessageBox::critical(this, "Error", "Can't find the word! Please type again");
        }
        else {
            QMessageBox::about(this, "Finded", "Your word was found!");
        }
        ui->textEdit_mean->setText("");
    }
}


void DictionaryApp::on_pushButton_ChinhSua_clicked()
{
    if (ui->pushButton_ChinhSua->isChecked() == true) {
        ui->pushButton_ThemTu->setChecked(false);
        ui->pushButton_TraCuu->setChecked(false);
        ui->pushButton_XoaTu->setChecked(false);

        ui->pushButton_2->setVisible(true);
        ui->pushButton->setVisible(true);
        ui->pushButton_2->setText("Chỉnh sửa");

        ui->label_NhapTu->setText("Nhập từ cần chỉnh sửa:");
        ui->textEdit_mean->setReadOnly(false);
        ui->textEdit_mean->setText("");
    }
}

void DictionaryApp::on_pushButton_2_clicked()
{
    if (ui->pushButton_ChinhSua->isChecked() == true) { //Dang la chinh sua tu
        if (ui->textEdit_mean->toPlainText() == "Can't find!")
            return;
        if (ui->searchTextEdit->toPlainText() != "") {
            string word = ui->searchTextEdit->toPlainText().toUtf8().constData();
            string mean = ui->textEdit_mean->toPlainText().toUtf8().constData();
            Word *changeWord = new Word(word, mean);
            Word *removeWord = new Word(word);
            hashTable->remove(*removeWord);
            hashTable->insert(*changeWord);
            QMessageBox::about(this, "Done", "DONE!");
            delete changeWord;
            delete removeWord;
        }
    }
    else if (ui->pushButton_ThemTu->isChecked() == true) { //Them mot tu
        string word = ui->searchTextEdit->toPlainText().toUtf8().constData();
        string mean = ui->textEdit_mean->toPlainText().toUtf8().constData();
        Word *addWord = new Word(word, mean);
        hashTable->insert(*addWord);
        delete addWord;
        QMessageBox::about(this, "Done", "DONE!");
    }
    else if (ui->pushButton_XoaTu->isChecked() == true) { //Xoa mot tu
        string word = ui->searchTextEdit->toPlainText().toUtf8().constData();
        string mean = ui->textEdit_mean->toPlainText().toUtf8().constData();
        if (mean == "Can't find!") {
            QMessageBox::critical(this, "Failed", "Don't have this word!");
            return;
        }
        Word *rmWord = new Word(word, mean);
        hashTable->remove(*rmWord);
        delete rmWord;
        QMessageBox::about(this, "Done", "DONE!");
    }
}

void DictionaryApp::on_pushButton_TraCuu_clicked()
{
    if (ui->pushButton_TraCuu->isChecked() == true) {
        ui->pushButton_ChinhSua->setChecked(false);
        ui->pushButton_ThemTu->setChecked(false);
        ui->pushButton_XoaTu->setChecked(false);

        ui->pushButton_2->setVisible(false);
        ui->pushButton_2->setText("Tra cứu");
        ui->pushButton->setVisible(true);

        ui->label_NhapTu->setText("Nhập từ cần tra cứu:");
        ui->textEdit_mean->setReadOnly(true);
        ui->textEdit_mean->setText("");
    }
}


void DictionaryApp::on_pushButton_ThemTu_clicked()
{
    if (ui->pushButton_ThemTu->isChecked() == true) {
        ui->pushButton_ChinhSua->setChecked(false);
        ui->pushButton_TraCuu->setChecked(false);
        ui->pushButton_XoaTu->setChecked(false);

        ui->pushButton_2->setVisible(true);
        ui->pushButton->setVisible(false);
        ui->pushButton_2->setText("Thêm từ");

        ui->label_NhapTu->setText("Nhập từ cần thêm: ");
        ui->textEdit_mean->setReadOnly(false);
        ui->textEdit_mean->setText("");
    }
}

void DictionaryApp::on_pushButton_XoaTu_clicked()
{
    if (ui->pushButton_XoaTu->isChecked() == true) {
        ui->pushButton_ChinhSua->setChecked(false);
        ui->pushButton_ThemTu->setChecked(false);
        ui->pushButton_TraCuu->setChecked(false);

        ui->pushButton_2->setVisible(true);
        ui->pushButton->setVisible(true);
        ui->pushButton_2->setText("Xoá từ");

        ui->label_NhapTu->setText("Nhập từ cần xoá: ");
        ui->textEdit_mean->setReadOnly(true);
        ui->textEdit_mean->setText("");
    }
}
