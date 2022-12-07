#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_powerpoint.h"

#include "document.h"
#include "pwpt_icommandhandler.h"
#include "pwpt_icommandline.h"

QT_BEGIN_NAMESPACE
namespace Ui { class PowerPointClass; };
QT_END_NAMESPACE

namespace pwpt
{

namespace App
{

class PowerPoint : public QMainWindow
{
    Q_OBJECT

public:
    PowerPoint(QWidget *parent = nullptr);
    ~PowerPoint();

private:
    Ui::PowerPointClass *ui;
};

} // namespace App

} // namespace pwpt
