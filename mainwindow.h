#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setupUi();
    void connectDb();

    Ui::MainWindow *ui;
    QSqlQueryModel *users_;
    QSqlQueryModel *mutualAccounts_;
    QSqlQueryModel *accounts_;

    QSqlRelationalTableModel *ledger_;

    enum LedgerColumnOrder{
        ID = 0,
        DATE = 1,
        ACCOUNT = 2,
        CREDIT = 3,
        DEBIT = 4,
        MEMO = 5
    };
};
#endif // MAINWINDOW_H
