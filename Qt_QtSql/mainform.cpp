#include "mainform.h"

#include <QtDebug>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableView>
#include <QPushButton>
#include <QLabel>

#include <QMessageBox>

#include <QSqlQuery>
#include <QSqlDatabase>

#include <QSqlRelationalTableModel>
#include <QSqlRelation>
#include <QSqlRecord>
#include <QSqlRelationalDelegate>

#include <QHeaderView>
#include <QModelIndex>

MainForm::MainForm(QWidget *parent) : QWidget(parent)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("mainform.db");
    qDebug() << db.databaseName();
    if( db.isValid() )
        qDebug() << "isValid()";
    qDebug() << "open " << db.open();


    QSqlQuery query(db);

    qDebug() << query.exec("create table department(id integer premary key auto_increment, name varchar(100) not null, location varchar(100) not null);");
/*
    qDebug() << query.exec("insert into department(id, name, location) values(1, 'name_01', 'The Shed, Elmtree Drive, Boston, MA');");
    qDebug() << query.exec("insert into department(id, name, location) values(2, 'name_02', 'Floor 18, 1129 Evanston Heights, New York, NY');");
    qDebug() << query.exec("insert into department(id, name, location) values(3, 'name_03', '14 Valentine Buildings, Amor Street, Cambridge, MA');");

    qDebug() << query.exec("create table employee(id integer premary key auto_increment, name varchar(100) not null, departmentid iinteger not null, extension integer not null, email varchar(100) not null, startdate varchar(100) not null, foreign key(departmentid) references department);");
    qDebug() << query.exec("insert into employee(id, name, departmentid, extension, email, startdate) values(1, 'employee_01', 1, 238, 'wangqingsong01@163.com', '2017-03-19');");
    qDebug() << query.exec("insert into employee(id, name, departmentid, extension, email, startdate) values(2, 'employee_01', 2, 239, 'wangqingsong02@163.com', '2017-03-19');");
    qDebug() << query.exec("insert into employee(id, name, departmentid, extension, email, startdate) values(3, 'employee_01', 3, 230, 'wangqingsong03@163.com', '2017-03-19');");
*/

    /*创建并设立主表的模型和视图*/
    createDepartmentPanel();
    /*创建并设立从表的模型和视图*/
    createEmployeePanel();

    addButton = new QPushButton(tr("add"));
    deleteButton = new QPushButton(tr("delete"));
    editButton = new QPushButton(tr("edit"));
    quitButton = new QPushButton(tr("quit"));

    connect(addButton, SIGNAL(clicked(bool)), this, SLOT(addDepartment()));
    connect(deleteButton, SIGNAL(clicked(bool)), this, SLOT(deleteDepartment()));
    connect(editButton, SIGNAL(clicked(bool)), this, SLOT(editEmployees()));
    connect(quitButton, SIGNAL(clicked(bool)), this, SLOT(close()));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(quitButton);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(departmentLabel);
    layout->addWidget(departmentView);
    layout->addWidget(employeeLabel);
    layout->addWidget(employeeView);
    layout->addLayout(buttonLayout);

    setLayout(layout);

    /*确保开始以主表的第一条记录为当前选项*/
    departmentView->setCurrentIndex(departmentModel->index(0,0));

    setWindowTitle("MainForm");
}

void MainForm::createDepartmentPanel()
{
    departmentPanel = new QWidget;

    departmentModel = new QSqlRelationalTableModel(NULL, QSqlDatabase::database("QSQLITE"));
    departmentModel->setTable("department");
    qDebug() << "select()" << departmentModel->select();
    departmentModel->setRelation(Department_LocationId, QSqlRelation("localtion", "id", "name"));
    departmentModel->setSort(Department_Name, Qt::AscendingOrder);
    departmentModel->setHeaderData(Department_Name, Qt::Horizontal, tr("Dept."));
    departmentModel->setHeaderData(Department_LocationId, Qt::Horizontal, tr("Location"));


    departmentView = new QTableView;
    departmentView->setModel(departmentModel);
    departmentView->setItemDelegate(new QSqlRelationalDelegate(this));
    departmentView->setSelectionMode(QAbstractItemView::SingleSelection);
    departmentView->setSelectionBehavior(QAbstractItemView::SelectRows);
    departmentView->setColumnHidden(Department_Id, true);
    departmentView->resizeColumnsToContents();
    departmentView->horizontalHeader()->setStretchLastSection(true);

    connect(departmentView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(updateEmployeeView()));

    departmentLabel = new QLabel(tr("Depar&tments"));
    departmentLabel->setBuddy(departmentView);
}

void MainForm::createEmployeePanel()
{
    employeePanel = new QWidget;

    employeeModel = new QSqlRelationalTableModel;
    employeeModel->setTable("employee");
    employeeModel->setRelation(Employee_DepartmentId, QSqlRelation("department", "id", "name"));
    employeeModel->setSort(Employee_Name, Qt::AscendingOrder);
    employeeModel->setHeaderData(Employee_Name, Qt::Horizontal, tr("Name"));
    employeeModel->setHeaderData(Employee_Extension, Qt::Horizontal, tr("Ext."));
    employeeModel->setHeaderData(Employee_Email, Qt::Horizontal, tr("Email"));

    employeeView = new QTableView;
    employeeView->setModel(employeeModel);
    employeeView->setSelectionMode(QAbstractItemView::SingleSelection);
    employeeView->setSelectionBehavior(QAbstractItemView::SelectRows);
    employeeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    employeeView->horizontalHeader()->setStretchLastSection(true);
    employeeView->setColumnHidden(Employee_Id, true);
    employeeView->setColumnHidden(Employee_DepartmentId, true);
    employeeView->setColumnHidden(Employee_StartDate, true);

    employeeLabel = new QLabel(tr("E&mployees"));
    employeeLabel->setBuddy(employeeView);
}

void MainForm::updateEmployeeView()
{
    /*获取主表，选中的记录的模型索引*/
    QModelIndex index = departmentView->currentIndex();
    if( index.isValid() )
    {
        /*如果模型索引有效，获取对应的记录，然后获取记录中的id*/
        QSqlRecord record = departmentModel->record(index.row());
        int id = record.value("id").toInt();
        /*根据id，设置从表中的过滤条件，并修改从表标题的显示信息*/
        employeeModel->setFilter(QString("departmentid = %1").arg(id));
        employeeLabel->setText(tr("E&mployees in the %1 Department").arg(record.value("name").toString()));
    }
    else
    {
        /*如果模型索引无效，则将过滤条件设置成一个不存在的条件，然后重新设置从表标题的信息*/
        employeeModel->setFilter("departmentid = -1");
        employeeLabel->setText(tr("E&mployees"));
    }

    /*重新执行查询语句*/
    employeeModel->select();
    /*如果从表过滤出来的记录大于0条，则显示标题头*/
    employeeView->horizontalHeader()->setVisible(employeeModel->rowCount() > 0);
}

void MainForm::addDepartment()
{
    int row = departmentModel->rowCount();
    departmentModel->insertRow(row);

    QModelIndex index = departmentModel->index(row, Department_Name);
    departmentView->setCurrentIndex(index);
    departmentView->edit(index);
}

void MainForm::deleteDepartment()
{
    QModelIndex index = departmentView->currentIndex();
    if( !index.isValid() )
        return;

    QSqlDatabase::database().transaction();

    QSqlRecord record = departmentModel->record(index.row());
    int id = record.value(Department_Id).toInt();
    int numEmployees = 0;

    QSqlQuery query(QString("select count(*) from employee where departmentid = %1").arg(id));
    if( query.next() )
        numEmployees = query.value(0).toInt();

    if( numEmployees > 0 )
    {
        int r = QMessageBox::warning(this, tr("Delete Department"), tr("Delete %1 and all it's employees?").arg(record.value(Department_Name).toString()), QMessageBox::Yes | QMessageBox::No);
        if( r == QMessageBox::No )
        {
            QSqlDatabase::database().rollback();
            return;
        }

        query.exec(QString("delete from employee where departmentid = %1").arg(id));
    }

    departmentModel->removeRow(index.row());
    departmentModel->submitAll();
    QSqlDatabase::database().commit();

    updateEmployeeView();
    departmentView->setFocus();
}

void MainForm::editEmployees()
{
    int employeeId = -1;
    QModelIndex index = employeeView->currentIndex();

    if( index.isValid() )
    {
        QSqlRecord record = employeeModel->record(index.row());
        employeeId = record.value(Employee_Id).toInt();
    }

    //对从表数据库更新值
}
