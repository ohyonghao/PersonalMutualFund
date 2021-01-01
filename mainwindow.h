#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
    QStringListModel *users_;
    QStringListModel *mutualAccounts_;
    QList<QStringListModel *> accounts_;

    QStringList userList_;
    QStringList accountList_;
    QStringList mutualAccountList_;

private slots:
    void updateAccountModel( const QModelIndex &current, const QModelIndex &previous);

};
#endif // MAINWINDOW_H
