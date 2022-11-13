#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_powerpoint.h"

#include "document.h"
#include "pwpt_icommandhandler.h"
#include "pwpt_icommandline.h"
#include "pwpt_itaskmachine.h"

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

    void Exec();

private:
    Ui::PowerPointClass *ui;

private:
    ICommandLine_Ptr		m_pConsole = nullptr;
    ICommandHandler_Ptr		m_pCommandHandler = nullptr;
    //IMachine_ptr			m_pActionMachine;

private:
    Document::CPwPtDocument		m_oDocument;
};

} // namespace App

} // namespace pwpt
