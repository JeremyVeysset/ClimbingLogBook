#include "widget.h"
#include <QApplication>
#include <QTextCodec>
#include "ajoutvoiewidget.h"

int main(int argc, char *argv[])
{
    // UTF-8 Encoding
    //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    //QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    QApplication a(argc, argv);
    Widget w;
    w.show();
    AjoutVoieWidget test;
    test.show();
    return a.exec();
}
