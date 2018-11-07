#include "processsystemcmd.h"

#include <QtDebug>

ProcessSystemCmd::ProcessSystemCmd(QWidget *parent)
    :QDialog(parent)
{

}

/*
同步的执行外部程序，当使用同步模型执行外部程序时，并不需要像异步模式一样，设置很多信号-槽。
在这里，打开记事本程序，使用记事本打开一个名为file.txt的文件。
当关闭记事本的时候，execute()程序也会结束返回。
*/
void ProcessSystemCmd::RunSystemCmd2()
{
    QProcess::execute("C:\\WINDOWS\\system32\\notepad.exe", QStringList() << "file.txt");
}

/*异步的执行外部程序*/
void ProcessSystemCmd::RunSystemCmd()
{
    /*只要外部程序向标准输出中写入数据，就会调用getCmdStdout()槽*/
    connect(&process, SIGNAL(readyReadStandardOutput()), this, SLOT(getCmdStdout()));
    /*只要外部程序向标准错误输出中写入数据，就会调用getCmdStderr()槽*/
    connect(&process, SIGNAL(readyReadStandardError()), this, SLOT(getCmdStderr()));
    /*当外部程序退出后，就会发送finished()信号，然后调用processFinished()槽*/
    connect(&process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(processFinished(int,QProcess::ExitStatus)));
    /*如果外部程序不能开启，QProcess就会发送error()信号，然后调用processError()槽*/
    connect(&process, SIGNAL(error(QProcess::ProcessError)), this, SLOT(processError(QProcess::ProcessError)));


    QStringList args;
    args << "args1" << "args2";
    /*运行名为dir的程序，args为传递的参数，也可以不写第二个参数*/
    process.start("D:\\SoftWare\\QTCreator\\Projects\\Qt_IO\\cmd.bat", args);
}


void ProcessSystemCmd::getCmdStderr()
{
    /*通过readAllStandardError()函数，获取输出到标准错误输出中的内容*/
    QByteArray errorData = process.readAllStandardError();
    qDebug() << "getCmdOutput() --> " << errorData;
}

void ProcessSystemCmd::getCmdStdout()
{
    /*通过readAllStandardOutput()函数，获取输出到标准输出中的内容*/
    QByteArray outData = process.readAllStandardOutput();
    qDebug() << "getCmdStdout() --> " << outData;
}

void ProcessSystemCmd::processError(QProcess::ProcessError error)
{
    if( error == QProcess::FailedToStart )
    {
        qDebug() << "processError() --> cmd program not found";
    }
}

void ProcessSystemCmd::processFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    if( exitStatus == QProcess::CrashExit )
    {
        qDebug() << "processFinished() --> cmd program crashed";
    }
    else if( exitCode != 0 )
    {
        qDebug() << "processFinished() --> cmd program failed";
    }
    else
    {
        qDebug() << "processFinished() --> cmd program is finished";
    }
}
