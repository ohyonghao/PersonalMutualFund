#include <QSettings>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlField>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>

#include <QSqlRelationalDelegate>
#include <QStyledItemDelegate>

#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "DateDelegate.h"

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

    // Get default account
    bool ok{false};
    int maNumber = mutualAccounts_->record(0).field("id").value().toInt(&ok);
    if( !ok ){
        QMessageBox nodb;
        nodb.setText("Could not find mutual fund");
        nodb.setStandardButtons(QMessageBox::Ok);
    }
    accounts_ = new QSqlQueryModel;
    accounts_->setQuery( QString("SELECT name, id FROM accounts AS a, mutual_accounts AS ma WHERE a.id = ma.account_id AND ma.mutual_id = %1").arg(maNumber));

    if( accounts_->lastError().isValid() ){

        QMessageBox nodb;
        nodb.setText("Error Getting Data");
        nodb.setStandardButtons(QMessageBox::Ok);
    }

    ledger_ = new QSqlRelationalTableModel;
    ledger_->setTable("ledger");
    ledger_->setRelation(ACCOUNT, QSqlRelation("accounts", "id", "name"));
    ledger_->setFilter(QString("account_id = %1").arg(1));
    ledger_->setHeaderData(ID,      Qt::Orientation::Horizontal, "Id");
    ledger_->setHeaderData(DATE,    Qt::Orientation::Horizontal, "Date");
    ledger_->setHeaderData(ACCOUNT, Qt::Orientation::Horizontal, "Account");
    ledger_->setHeaderData(CREDIT,  Qt::Orientation::Horizontal, "Credit");
    ledger_->setHeaderData(DEBIT,   Qt::Orientation::Horizontal, "Debit");
    ledger_->setHeaderData(MEMO,    Qt::Orientation::Horizontal, "Memo");
    ledger_->select();
}

void MainWindow::setupUi(){

    ui->UserView->setModel(users_);
    ui->MutualView->setModel(mutualAccounts_);
    ui->AccountsView->setModel(accounts_);
    ui->LedgerView->setModel(ledger_);
    ui->LedgerView->setItemDelegateForColumn(ACCOUNT, new QSqlRelationalDelegate(ui->LedgerView) );
    ui->LedgerView->setItemDelegateForColumn(DATE, new DateDelegate(ui->LedgerView));

    // Setup Ledger
    ui->LedgerView->setColumnHidden(ID,true);
}
