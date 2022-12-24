
#include "powerpoint.h"
#include "pwpt_appmanager.h"

#include <QtCore/QCoreApplication>

int main(int argc, char *argv[])
{
    using namespace pwpt::App;

    QCoreApplication a(argc, argv);
    //pwpt::App::PowerPoint w;
    //w.show();
    
    auto& oApp = CAppManager::AppInstance();
    oApp.Run();

    return a.exec();
}
