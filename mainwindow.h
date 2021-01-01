#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include <QSqlTableModel>

#include <QStringListModel>

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

};
#endif // MAINWINDOW_H
