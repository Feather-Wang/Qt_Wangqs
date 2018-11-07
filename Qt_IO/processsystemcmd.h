#ifndef PROCESSSYSTEMCMD_H
#define PROCESSSYSTEMCMD_H

#include <QProcess>
#include <QDialog>

class ProcessSystemCmd : public QDialog
{
    Q_OBJECT

public:
    ProcessSystemCmd(QWidget *parent = 0);

    /*异步的执行外部程序*/
    void RunSystemCmd();
    /*同步的执行外部程序*/
    void RunSystemCmd2();

private slots:
    void getCmdStderr();
    void getCmdStdout();
    void processFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void processError(QProcess::ProcessError error);

private:
    QProcess process;
};

#endif // PROCESSSYSTEMCMD_H
