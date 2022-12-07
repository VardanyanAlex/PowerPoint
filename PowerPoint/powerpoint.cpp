
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
}

PowerPoint::~PowerPoint()
{
    delete ui;
}

} // namespace App

} // namespace pwpt
