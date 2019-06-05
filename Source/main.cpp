#include "dictionaryapp.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    DictionaryApp w;
    w.show();
    w.resize(700, 500);

    return a.exec();
}
