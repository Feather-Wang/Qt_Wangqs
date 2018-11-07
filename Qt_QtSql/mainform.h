#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>

class QSqlRelationalTableModel;
class QDialoButtonBox;
class QTableView;
class QPushButton;
class QLabel;

class MainForm : public QWidget
{
    Q_OBJECT
public:
    explicit MainForm(QWidget *parent = 0);

    enum
    {
        Department_Id = 0,
        Department_Name = 1,
        Department_LocationId = 2,
    };

    enum
    {
        Employee_Id = 0,
        Employee_Name = 1,
        Employee_DepartmentId = 2,
        Employee_Extension = 3,
        Employee_Email = 4,
        Employee_StartDate = 5
    };

signals:

private slots:
    void updateEmployeeView();
    void addDepartment();
    void deleteDepartment();
    void editEmployees();

private:
    void createDepartmentPanel();
    void createEmployeePanel();

    QSqlRelationalTableModel *departmentModel;
    QSqlRelationalTableModel *employeeModel;
    QTableView *departmentView;
    QTableView *employeeView;

    QWidget *departmentPanel;
    QWidget *employeePanel;

    QLabel *departmentLabel;
    QLabel *employeeLabel;

    QPushButton *addButton;
    QPushButton *deleteButton;
    QPushButton *editButton;
    QPushButton *quitButton;
    //QDialogButtonBox *buttonBox;
};

#endif // MAINFORM_H
