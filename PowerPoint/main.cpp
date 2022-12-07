
#include "application.h"
#include "powerpoint.h"

#include <QtCore/QCoreApplication>

int main(int argc, char *argv[])
{
    using namespace pwpt::App;

    QCoreApplication a(argc, argv);
    //pwpt::App::PowerPoint w;
    //w.show();
    
    CApplication& oApp = CApplication::Instance();
    oApp.Run();

    return a.exec();
}
