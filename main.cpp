#include "librarymain.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    libraryMain w;
    return a.exec();
}
