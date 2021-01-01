#include <QSettings>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>

#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connectDb();
    setupUi();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectDb(){
    QSettings settings;
    QString username = settings.value("username", "mutualfund").toString();
    QString password = settings.value("password", "Secret").toString();
    QString dbname   = settings.value("dbname", "mutualfund").toString();
    int port         = settings.value("port", 5432 ).toInt();

    auto db = QSqlDatabase::addDatabase("QPSQL");
    db.setDatabaseName(dbname);
    db.setPort(port);
    db.setUserName(username);
    db.setPassword(password);
    if( !db.open() ){
        QMessageBox nodb;
        nodb.setText("Database could not be established");
        nodb.setStandardButtons(QMessageBox::Ok);
    }
    users_ = new QSqlQueryModel;
    users_->setQuery("SELECT username FROM users");
    mutualAccounts_ = new QSqlQueryModel;
    mutualAccounts_->setQuery("SELECT name, id FROM mutualfunds");

    accounts_ = new QSqlQueryModel;
    accounts_->setQuery("SELECT name, id FROM accounts");
}

void MainWindow::setupUi(){

    ui->UserView->setModel(users_);
    ui->MutualView->setModel(mutualAccounts_);

    ui->AccountsView->setModel(accounts_);
}
