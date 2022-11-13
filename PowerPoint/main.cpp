
#include "powerpoint.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    pwpt::App::PowerPoint w;
    w.Exec();
    //w.show();
    return a.exec();
}
