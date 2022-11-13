
#include "powerpoint.h"
#include "pwpt_icommand.h"

namespace pwpt
{ 

namespace App
{ 

PowerPoint::PowerPoint(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PowerPointClass())
{
    ui->setupUi(this);

    QObject::connect(m_pConsole.get(), SIGNAL(commandConstructed(ICommand_Ptr)),
                    m_pCommandHandler.get(), SLOT(OnCommandConstructed(ICommand_Ptr)));

}

PowerPoint::~PowerPoint()
{
    delete ui;
}

void PowerPoint::Exec()
{
    m_pConsole->Run();
}

} // namespace App

} // namespace pwpt
