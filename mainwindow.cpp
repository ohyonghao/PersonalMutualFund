#include <QSettings>
#include <QSqlDatabase>
#include <QSqlQuery>

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
}

void MainWindow::setupUi(){

    QSqlQuery query;
    query.exec("SELECT username FROM users");
    while(query.next()){
        userList_ << query.value(0).toString();
    }
    users_ = new QStringListModel(userList_, this);
    ui->UserView->setModel(users_);

    // Setup Mutual Account List
    mutualAccountList_ << "Complete Index"
                       << "Riskier Investments";
    mutualAccounts_ = new QStringListModel(mutualAccountList_, this);
    ui->MutualView->setModel(mutualAccounts_);

    // Setup Account List
    for( int i = 0; i < 5; ++i ){
        QStringList list;
        list << "S&P " + QString::number(i)
             << "DJ " + QString::number(i)
             << "Low Risk " + QString::number(i);
        accounts_.append(new QStringListModel(list, this));
    }
    ui->AccountsView->setModel(accounts_.at(0));

    connect(ui->MutualView->selectionModel(), &QItemSelectionModel::currentChanged, this, &MainWindow::updateAccountModel );
}

void MainWindow::updateAccountModel(const QModelIndex &current, const QModelIndex &previous){
    ui->AccountsView->setModel(accounts_.at(current.row()));
}
